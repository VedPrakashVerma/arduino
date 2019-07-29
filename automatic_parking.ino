#include <LiquidCrystal.h>
const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //10=12
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int trigPin = 9;
const int echoPin = 8;
const int trigPin1= 7;
const int echoPin1= 6;
long time1=0;
float hr=0;
float charge=0;
int t;


long duration,duration1;
int distance,distance1;
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(A2,OUTPUT); //10
  pinMode(A3,OUTPUT); //11
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT); 
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2); 
}

void loop()
{
  if(Serial.available()){
    t=Serial.read();
    Serial.println(t);
    }
  if(t==99)
  {
    charge=0;
    }  
  int value=analogRead(A0);
  //Serial.println(value);
  int value1=analogRead(A1);
  //Serial.println(value1);
  //delay(1000);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  //Serial.print("Distance: ");
  //delay(1000);
  //Serial.println(distance);
  
  if(distance>10&&value1<500){
  digitalWrite(A2,HIGH);     //G1
  //digitalWrite(11,HIGH);
  digitalWrite(12,LOW);      //R1
  //digitalWrite(13,LOW);    
  }
  if(distance>10&&value<500){
  //digitalWrite(12,HIGH);
  digitalWrite(A3,HIGH);     //G2
  //digitalWrite(10,LOW);
  digitalWrite(13,LOW);      //R2
  }

  if(distance<10||value1>500){
  digitalWrite(A2,LOW);     //G1
  //digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);    //R1
  //digitalWrite(13,LOW);    
  }
  if(distance<10||value>500){
  //digitalWrite(12,HIGH);
  digitalWrite(A3,LOW);     //G2
  //digitalWrite(10,LOW);
  digitalWrite(13,HIGH);      //R2
  }

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);  
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1= duration1*0.034/2;
  //Serial.print("Distance1: ");
  //delay(1000);
  //Serial.println(distance1);

    if(distance1<10)
  {
    time1=time1+1;
    //delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("Already Parked");
  }
  if(distance1>10)
  {
    lcd.setCursor(0, 0);
    lcd.print("Parking avl   ");
    }
  delay(1000);
  hr=(time1);
  charge=hr*6;
  Serial.println(charge);

  if(value>500||value1>500||distance<10)
  {
    lcd.setCursor(0, 1);
    lcd.print("Track Busy ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Track Clear");
    }
    
}
