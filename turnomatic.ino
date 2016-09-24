byte dispval[]={B000000,B111111,B000110,B011011,B001111,B100110,B101101,B111101,B000111,B111111,B100111, B000000};
int dissolo[]={0,0,0,1,1,1,1,1,0,1,1,0};
//  Vector con los puertos de salida
int puertos[]={3,4,5,6,7,8,9,10,11,12,13};
//  Indices de los vectores
int X=1;
int Y=1;
//  Frecuencia del sonido
int frecuencia=200;
//  Numero de tecla pulsada
int tecla=1;
boolean Condi=true;
boolean asterisco= false;
boolean pulsada= false;
void setup(){
  pinMode(2,INPUT);

  digitalWrite(2, HIGH);
  DDRC = B000000;
  PORTC = B111111;
  for (int i=0;i<11;i++){
    pinMode(puertos[i], OUTPUT);
  }
}

void loop(){
  if (asterisco && pulsada){
    frecuencia=tecla*200 +200;       // Calculamos la frecuencia
    pitidoFrec();
    asterisco=false;
    pulsada = false;
   
  }
  if (digitalRead(19)==LOW){         //  Reseteamos los displays cuando se pulsan los dos botones
    delay(25);                       //  Como es dificil que se pulsen los dos a la ves exactamente
    if( digitalRead(18)==LOW){       //  ponemos un pequeño delay
      X=1;
      Y=1;
      pitidoReset();    
      while (digitalRead(19)==LOW);
      while (digitalRead(18)==LOW);
    }
  }
  
  if (digitalRead(18)==LOW){         // Hacemos lo mismo, pero comprobando primero por el otro boton
    delay(25);
    if( digitalRead(19)==LOW){    
      X=1;
      Y=1;      
      pitidoReset();      
      while (digitalRead(19)==LOW);
      while (digitalRead(18)==LOW);
    }
  }
  
  if (digitalRead(19)==LOW){        //  Incrementamos el contador
    X++;
    noTone(3);
    digitalWrite(3,HIGH);
    tone(4, frecuencia, 100);
    delay(100);
    noTone(4);
    tone(3, 100);
    while (digitalRead(19)==LOW);
  }
  
  if (digitalRead(18)==LOW){       //  Decrementamos el contador
    X--;
    noTone(3);
    digitalWrite(3,HIGH);
    tone(4, frecuencia, 100);
    delay(100);
    noTone(4);
    tone(3, 100);
    while (digitalRead(18)==LOW);
  }
  
  if(X > 10){                     //  Controlamos que las unidades superen 9
    X=1;
    Y=Y + 1;
    if(Y > 10) Y=1;               //  Controlamos que las decenas superen 9
  }
  
  if (X < 1){                     //  Controlamos que las unidades tomen valores negativos
    X=10;
    Y--;
    if(Y < 1) Y=10;               //  Controlamos que las decenas tomen valores negativos
  }
  tone(3, 100);
  attachInterrupt(0, rutina, RISING);
}

void rutina(){
  if(Condi){                      //  Mostramos un display
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    PORTB=dispval[X];
    digitalWrite(5,dissolo[X]);
    digitalWrite(6, LOW);
    teclado();
    Condi = false;
  } else {                        //  Mostramos el otro display
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    PORTB=dispval[Y];
    digitalWrite(5,dissolo[Y]);
    digitalWrite(7, LOW);
    teclado();
    Condi = true;
  }
}

void teclado(){
  if (Condi){
    if (digitalRead(14)==LOW) asterisco=true;
    if(asterisco){
      if (digitalRead(17)==LOW){
        tecla=1;
        pulsada=true;
      }
      if (digitalRead(16)==LOW){
        tecla=3;
        pulsada=true;
      }
      if (digitalRead(15)==LOW){
        tecla=5;
        pulsada=true;
      }
    }
  } else {
    if(asterisco){
      if (digitalRead(17)==LOW){
        tecla=2;
        pulsada=true;
      }
      if (digitalRead(16)==LOW){
        tecla=4;
        pulsada=true;
      }
      if (digitalRead(15)==LOW){
        tecla=6;
        pulsada=true;
      }
      if (digitalRead(14)==LOW){
        tecla=0;
        pulsada = true;
      }
    }
  }
}

void pitidoReset(){                        //  Pitido que suena al resetear el contador
  noTone(3);
  digitalWrite(3,HIGH);
  tone(4, 400, 100);
  delay(100);
  noTone(4);
  tone(3, 100);
  delay(100);
  noTone(3);
  digitalWrite(3,HIGH);
  tone(4, 1600, 100);
  delay(100);
  noTone(4);
  tone(3, 100);
}

void pitidoFrec(){                        //  Pitido que suena al cambiar la frecuencia
  noTone(3);
  digitalWrite(3,HIGH);
  tone(4, 1600, 100);
  delay(100);
  noTone(4);
  tone(3, 100);
  delay(100);
  noTone(3);
  digitalWrite(3,HIGH);
  tone(4, 400, 100);
  delay(100);
  noTone(4);
  tone(3, 100);
}