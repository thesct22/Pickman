// code to be on the Uno with an HC-05 on the bot.
#include<Servo.h>
float jx,jy,ax,ay;
int lw1=5;
int lw2=6;
int rw1=7;
int rw2=8;
char ib;
Servo sv1;
Servo sv2;
void up();
void dw();
void in();
void ou();
void fr();
void ba();
void le();
void ri();
void st();
void setup() {
  Serial.begin(9600);
  for(int i=5;i<9;i++)
    pinMode(i,OUTPUT); 
  sv1.attach(9);
  sv2.attach(10);
}

void loop() {
  while (Serial.available()>0){
    ib= Serial.read();
   int value = ib-'0';
   //Serial.println(value); //Only for debugging
  if(value==1)
    fr();
  else if(value==2)
    ba();
  else if(value==3)
    ri();
  else if(value==4)
    le();
  else if(value==5)
    up();
  else if(value==6)
    dw();
  else if(value==7)
    in();
  else if(value==8)
    ou();
  else
    st();
 }
}
void fr()
{
  digitalWrite(lw1,HIGH);
  digitalWrite(rw1,HIGH);
  digitalWrite(lw2,LOW);
  digitalWrite(rw2,LOW);
}
void le()
{
  digitalWrite(lw1,LOW);
  digitalWrite(rw1,HIGH);
  digitalWrite(lw2,HIGH);
  digitalWrite(rw2,LOW);
}
void ba()
{
  digitalWrite(lw2,HIGH);
  digitalWrite(rw2,HIGH);
  digitalWrite(lw1,LOW);
  digitalWrite(rw1,LOW);
}
void ri()
{
  digitalWrite(lw2,LOW);
  digitalWrite(rw2,HIGH);
  digitalWrite(lw1,HIGH);
  digitalWrite(rw1,LOW);
}
void st()
{
  digitalWrite(lw1,LOW);
  digitalWrite(rw1,LOW);
  digitalWrite(lw2,LOW);
  digitalWrite(rw2,LOW);
}
void up()
{
  st();
  sv1.write(80);
  Serial.println("UP");
}
void dw()
{
  st();
  sv1.write(160);
  Serial.println("DOWN");
}
void in()
{
  st();
  sv2.write(98);
  Serial.println("IN");
}
void ou()
{
  st();
  sv2.write(45);
  Serial.println("OUT");
}
