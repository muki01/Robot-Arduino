#define IN_1 13
#define IN_2 15
#define IN_3 12
#define IN_4 14

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

String command;       //String to store app command state.
int speedCar = 1023;  // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "MERCUSYS_F412";
const char* password = "94023498";

void setup() {
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  Serial.begin(115200);

  WiFi.begin(ssid, password);  //begin WiFi connection
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void Forward() {
  analogWrite(IN_1, speedCar);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, speedCar);
  analogWrite(IN_4, 0);
}

void Backward() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, speedCar);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, speedCar);
}

void TurnRight() {
  analogWrite(IN_1, speedCar);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, speedCar);
}

void TurnLeft() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, speedCar);
  analogWrite(IN_3, speedCar);
  analogWrite(IN_4, 0);
}

void ForwardRight() {
  analogWrite(IN_1, speedCar);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, speedCar / speed_Coeff);
  analogWrite(IN_4, 0);
}

void ForwardLeft() {
  analogWrite(IN_1, speedCar / speed_Coeff);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, speedCar);
  analogWrite(IN_4, 0);
}

void BackwardRight() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, speedCar);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, speedCar / speed_Coeff);
}

void BackwardLeft() {

  analogWrite(IN_1, 0);
  analogWrite(IN_2, speedCar / speed_Coeff);

  analogWrite(IN_3, 0);
  analogWrite(IN_4, speedCar);
}

void Stop() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, 0);
}

void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "L") TurnLeft();
  else if (command == "R") TurnRight();
  else if (command == "I") ForwardRight();
  else if (command == "G") ForwardLeft();
  else if (command == "J") BackwardRight();
  else if (command == "H") BackwardLeft();
  else if (command == "0") speedCar = 330;
  else if (command == "1") speedCar = 400;
  else if (command == "2") speedCar = 470;
  else if (command == "3") speedCar = 540;
  else if (command == "4") speedCar = 610;
  else if (command == "5") speedCar = 680;
  else if (command == "6") speedCar = 750;
  else if (command == "7") speedCar = 820;
  else if (command == "8") speedCar = 890;
  else if (command == "9") speedCar = 960;
  else if (command == "q") speedCar = 1023;
  else if (command == "S") Stop();
}

void HTTP_handleRoot(void) {

  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}