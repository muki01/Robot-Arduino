#define IN_1  13          // L298N in1 motors Rightx          GPIO15(D8)
#define IN_2  15          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  12           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  14           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 1023;         // 400 - 1023.
int speed_Coeff = 3;

const char* ssid = "Robot";
ESP8266WebServer server(80);

void setup() {
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);

      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
  }

void goBack(){ 

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar);
  }

void goRight(){ 

      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar);
  }

void goLeft(){

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);

      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
  }

void goAheadRight(){
      
      analogWrite(IN_1, speedCar/speed_Coeff);
      analogWrite(IN_2, 0);
 
      analogWrite(IN_3, speedCar);
      analogWrite(IN_4, 0);
   }

void goAheadLeft(){
      
      analogWrite(IN_1, speedCar);
      analogWrite(IN_2, 0);

      analogWrite(IN_3, speedCar/speed_Coeff);
      analogWrite(IN_4, 0);
  }

void goBackRight(){ 

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar/speed_Coeff);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar);
  }

void goBackLeft(){ 

      analogWrite(IN_1, 0);
      analogWrite(IN_2, speedCar);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, speedCar/speed_Coeff);
  }

void stopRobot(){  

      analogWrite(IN_1, 0);
      analogWrite(IN_2, 0);

      analogWrite(IN_3, 0);
      analogWrite(IN_4, 0);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
