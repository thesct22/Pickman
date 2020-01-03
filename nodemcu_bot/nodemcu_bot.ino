
#include <WiFi.h>
WiFiClient client;
WiFiServer server(80);
 char* ssid = "dummy";
 char* password = "lmfaohaha";
String  command ="";
int rightMotor2 = 15;    // D7 - right Motor -
int rightMotor1 = 13;    // D8 - right Motor +
int leftMotor2 = 14;    // D3 - left Motor - 
int leftMotor1 = 12;    // D4 - left Motor +

void setup()  
{
  Serial.begin(9600);
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

         if (command == "forward") forwardMotor();
    else if (command == "reverse") reverseMotor();
    else if (command == "left")    leftMotor();    
    else if (command == "right")   rightMotor();     
    //else if (command== "stop")     stopMotor();
    else                           stopMotor();
    sendBackEcho(command); // send command echo back to android device
    command = "";   
} 
void forwardMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  Serial.println(command);
  delay(1000);
}
void reverseMotor(void)   
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,HIGH);
  Serial.println(command);
}
void leftMotor(void)   
{
  digitalWrite(leftMotor1,HIGH);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,HIGH);
  Serial.println(command);
}
void rightMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,HIGH);
  digitalWrite(rightMotor1,HIGH);
  digitalWrite(rightMotor2,HIGH);
  Serial.println(command);
}
void stopMotor(void)   
{
  digitalWrite(leftMotor1,LOW);
  digitalWrite(leftMotor2,LOW);
  digitalWrite(rightMotor1,LOW);
  digitalWrite(rightMotor2,LOW);
  Serial.println(command);
}
void connectWiFi()
{
  WiFi.begin(ssid,password);
Serial.println("\nConnecting to network!");
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.print(".");
  delay(300);
}
Serial.println("\nConnected to network!");
while(WiFi.localIP()==INADDR_NONE)
{
  Serial.print(".");
  delay(300);
}
Serial.print("\nAquired IP Adress is: ");
Serial.println(WiFi.localIP());
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
