int up,dw,le,ri;
float jx,jy;
void setup() {
  for (int i=2;i<6;++i)
  {
   pinMode(i, INPUT);
  }
  Serial.begin(9600); //use an HC-05 bluetooth module on the Arduino Uno
}

void loop() {
  jx=analogRead(A0);
  jy=analogRead(A1);
  up=digitalRead(2);
  ri=digitalRead(3);
  dw=digitalRead(4);
  le=digitalRead(5);
  if(jy<150&&(jx>300&&jx<700))
    Serial.println("2");
  else if(jy>950&&(jx>300&&jx<700))
    Serial.println("1");
  else if(jx<150&&(jy>300&&jy<700))
    Serial.println("4");
  else if(jx>950&&(jy>300&&jy<700))
    Serial.println("3");
  else if(up==0)
    Serial.println("5");
  else if(dw==0)
    Serial.println("6");
  else if(ri==0)
    Serial.println("7");
  else if(le==0)
    Serial.println("8");
  else
    Serial.println("0");  
 }
