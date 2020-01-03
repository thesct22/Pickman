#include<Servo.h>

float jx,jy,ax,ay;
int lw1=5;
int lw2=6;
int rw1=7;
int rw2=8;
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
  jx=analogRead(A0);
  jy=analogRead(A1);
  ax=analogRead(A2);
  ay=analogRead(A3);
  if(jy<150&&(jx>300&&jx<700))
    fr();
  else if(jy>950&&(jx>300&&jx<700))
    ba();
  else if(jx<150&&(jy>300&&jy<700))
    ri();
  else if(jx>950&&(jy>300&&jy<700))
    le();
  else if(ay<150&&(ax>300&&ax<700))
    up();
  else if(ay>950&&(ax>300&&ax<700))
    dw();
  else if(ax<150&&(ay>300&&ay<700))
    in();
  else if(ax>950&&(ay>300&&ay<700))
    ou();
  else
    st();
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
