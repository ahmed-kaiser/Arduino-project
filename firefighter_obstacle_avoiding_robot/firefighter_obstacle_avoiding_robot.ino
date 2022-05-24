#include<Servo.h>

Servo myservo_1;
Servo myservo_2;

#define Left_S A1
#define Right_S A3
#define Forward_S A2
#define buzzer A4
#define IN1_A 9
#define IN2_A 8
#define IN3_B 7
#define IN4_B 4
#define ENA_1 6
#define ENA_2 5
#define ENA_p 3
#define pump 2
#define trigpin 13
#define echopin 12

int pos=0;
boolean fire=false;
int Robotspeed;
int pumpspeed;
void setup()
{ 
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN3_B, OUTPUT);
  pinMode(IN4_B, OUTPUT);
  pinMode(ENA_1, OUTPUT);
  pinMode(ENA_2, OUTPUT);
  pinMode(ENA_p, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
  myservo_1.attach(10);
  myservo_2.attach(11);
  myservo_1.write(65);
  myservo_2.write(50);
}


void loop()
{
  Robotspeed=180;
  analogWrite(ENA_1,Robotspeed);
  analogWrite(ENA_2,Robotspeed);
  pumpspeed=180;
  analogWrite(ENA_p,pumpspeed);
  int distanceF=0;
  int distanceR=0;
  int distanceL=0;
  
  TOP:
  if(digitalRead(Forward_S)==LOW ||digitalRead(Left_S)==LOW || digitalRead(Right_S)==LOW)
    {
      if(digitalRead(Forward_S)==LOW)
      {
        Robotspeed=120;
           analogWrite(ENA_1,Robotspeed);
           analogWrite(ENA_2,Robotspeed);
        Robotstop();
        delay(100);
        digitalWrite(buzzer,HIGH);
        fire=true;
      }
      else if(digitalRead(Left_S)==LOW)
      {
        Robotstop();
        delay(100);
        Robotleft();
        delay(300);
        Robotstop();
        delay(200);
      }
      else if(digitalRead(Right_S)==LOW)
      {
        Robotstop();
        delay(100);
        Robotright();
        delay(300);
        Robotstop();
        delay(200);
      }
      else
      {
        
      }
      while(fire==true){
        off_fire();
      }
    }
  else 
    {
      distanceF=search();
      if(distanceF<=30)
      {
        Robotspeed=150;
        analogWrite(ENA_1,Robotspeed);
        analogWrite(ENA_2,Robotspeed);
        Robotstop();
        delay(100);
        Robotbackward();
        delay(200);
        Robotstop();
        distanceR=lookRight();
        delay(400);
        distanceL=lookLeft();
        delay(400);
         if(distanceR>distanceL)
         {
          Robotbackward();
          delay(100);
          Robotright();
          delay(450);
          Robotstop();
          delay(50);
           if(digitalRead(Forward_S)==LOW || digitalRead(Left_S)==LOW || digitalRead(Right_S)==LOW)
            {
              goto TOP;
              }
           }
           else if(distanceR<distanceL)
           {
            Robotbackward();
            delay(100);
            Robotleft();
            delay(450);
            Robotstop();
            delay(50);
              if(digitalRead(Forward_S)==LOW || digitalRead(Left_S)==LOW || digitalRead(Right_S)==LOW)
              {
                goto TOP;
              }
           }
           else 
           {
            Robotbackward();
            delay(500);
            Robotstop();
            delay(200);
           }
      }
     else
     {
       Robotspeed=180;
       analogWrite(ENA_1,Robotspeed);
       analogWrite(ENA_2,Robotspeed);
       Robotforward();
     }
    }
}

int search(void)
{
  float duration=0.00;
  float CM=0.00;
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  CM=(duration/58.82);
  return CM;
}

int lookRight()
{
  myservo_1.write(0);
  delay(500);
  int distance = search();
  delay(100);
  myservo_1.write(65);
  return distance;
}
 
int lookLeft()
{
  myservo_1.write(135);
  delay(500);
  int distance = search();
  delay(100);
  myservo_1.write(65);
  return distance;
  delay(100);
}

void off_fire()
{
  pumpspeed=180;
  analogWrite(ENA_p,pumpspeed);
  digitalWrite(pump,HIGH);
  delay(100);
  for (pos = 0; pos <= 100; pos += 1) 
  {
    myservo_2.write(pos);
    delay(10); 
  }
  for (pos = 100; pos >= 0; pos -= 1) 
  {
    myservo_2.write(pos);
    delay(10);
  }
  digitalWrite(pump,LOW);
  digitalWrite(buzzer,LOW);
  myservo_2.write(50);
  delay(100);
  fire=false;    
}

void  Robotforward()
{
  digitalWrite(IN1_A,HIGH);
  digitalWrite(IN2_A,LOW);
  digitalWrite(IN3_B,HIGH);
  digitalWrite(IN4_B,LOW);
}

void Robotbackward()
{
  digitalWrite(IN1_A,LOW);
  digitalWrite(IN2_A,HIGH);
  digitalWrite(IN3_B,LOW);
  digitalWrite(IN4_B,HIGH);
}

void Robotleft()
{
  digitalWrite(IN1_A,LOW);
  digitalWrite(IN2_A,HIGH);
  digitalWrite(IN3_B,HIGH);
  digitalWrite(IN4_B,LOW);
}

void Robotright()
{
  digitalWrite(IN1_A,HIGH);
  digitalWrite(IN2_A,LOW);
  digitalWrite(IN3_B,LOW);
  digitalWrite(IN4_B,HIGH);
}
void Robotstop()
{
  digitalWrite(IN1_A,LOW);
  digitalWrite(IN2_A,LOW);
  digitalWrite(IN3_B,LOW);
  digitalWrite(IN4_B,LOW);
}
