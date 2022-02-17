#include<ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

const char* ssid="Area 51";
const char* password = "9aaliens";
String data = "";

int Relay1 = 12; //D0
int Relay2 = 16; //D6


void setup() {
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);

  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop() {
  client = server.available();
  if(!client) 
  return;
  data = checkClient();
  Serial.print(data);
  Serial.println();
  if(data == "light")
  digitalWrite(Relay1, !digitalRead(Relay1));
  if(data == "fan%20on")
  digitalWrite(Relay2, LOW);
  if(data == "fan%20off")
  digitalWrite(Relay2, HIGH);
}

void connectWiFi(){
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

String checkClient(void){
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
