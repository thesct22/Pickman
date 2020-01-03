#include<Servo.h>
#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "ISA";
const char* password = "PICKMAN@ISA";
String  command ="";
int rightMotor2 = 13;    // D7 - right Motor -
int rightMotor1 = 15;    // D8 - right Motor +
int leftMotor2 = D5;    // D3 - left Motor - 
int leftMotor1 = D6;    // D4 - left Motor +
Servo sv1;  
Servo sv2;

void setup()  
{
  Serial.begin(115200);

  sv1.attach(12);//D6
  sv2.attach(14);//D5
  pinMode(leftMotor1, OUTPUT); 
  pinMode(leftMotor2, OUTPUT);  
  pinMode(rightMotor1, OUTPUT);  
  pinMode(rightMotor2, OUTPUT);  
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
      
  connectWiFi();
  server.begin();
}

void loop()
{
    client = server.available();
    if (!client) return; 
    command = checkClient ();
    Serial.println(command);

         if (command == "forward") forwardMotor();
    else if (command == "reverse") reverseMotor();
    else if (command == "left")    leftMotor();    
    else if (command == "right")   rightMotor();     
    else if (command == "in")      in();
    else if (command == "out")     ou();
    else if (command == "up")      up();
    else if (command == "down")    dw();   
    else                           stopMotor();
    sendBackEcho(command); // send command echo back to android device
    command = "";   
} 
void up()
{
  stopMotor();
  sv1.write(80);
  Serial.println("UP");
}
void dw()
{
  stopMotor();
  sv1.write(160);
  Serial.println("DOWN");
}
void in()
{
  stopMotor();
  sv2.write(98);
  Serial.println("IN");
}
void ou()
{
   stopMotor();
  sv2.write(45);
  Serial.println("OUT");
}
void forwardMotor(void)   
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  stopMotor();
}
void reverseMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  stopMotor();
}
void leftMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,LOW);
  stopMotor();
  
}
void rightMotor(void)   
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  stopMotor();
}
void stopMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
 
}
void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
void sendBackEcho(String echo)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(echo);
  client.println("</html>");
  client.stop();
  delay(1);
}
