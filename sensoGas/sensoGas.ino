int gas;

int vermelho=11;

int amarelo=12;

int verde=13;

int alarme=10;



void setup()

{

  Serial.begin(9600); 

  pinMode(vermelho,OUTPUT);

  pinMode(amarelo,OUTPUT);

  pinMode(verde,OUTPUT);

  pinMode(alarme,OUTPUT);

}



void loop()

{

  gas = analogRead(A5);

  

  if (gas<930)

  {

    digitalWrite(verde,HIGH);

    digitalWrite(amarelo,LOW);

    digitalWrite(vermelho,LOW);

    noTone(alarme);

    Serial.println("Seguro");

    delay(500);

  }

  
  if ((gas>930) and (gas<960))

  {

    digitalWrite(verde,LOW);

    digitalWrite(amarelo,HIGH);

    digitalWrite(vermelho,LOW);

    noTone(alarme);

    Serial.println("Cuidado");

    delay(500);

  }

      

   if (gas>960)

  {

    digitalWrite(verde,LOW);

    digitalWrite(amarelo,LOW);

    digitalWrite(vermelho,HIGH);

    tone(alarme,440);

    delay(500);

    noTone(alarme);

    delay(300);

    Serial.println("Perigo");

    delay(10);

   }                                          

}

