#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
double pos = 0;
double posMin = 0;
double posMax = 0;

void setup() {
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  Serial.println("MPU-6050 sensör bulundu kartı oynatmadan bekleyin");
  mpu6050.calcGyroOffsets(true);
}

void loop() { 
  mpu6050.update();
  Serial.print(" aci_Y : ");
  Serial.print(mpu6050.getAngleY());
  delay(50);

  pos=mpu6050.getAngleY();
  posMin=pos*(pos*3.5);
  posMax=-pos*(-pos*3.5);
  Serial.println(posMax);
  Serial.println(posMin);
  //posMin=map(pos, 0, 1024, 100, 250);
  //posMax=map(pos, 0, 1024, 100, 250);

  if (pos>5 && pos < 70) {
    analogWrite(D5,LOW);
    analogWrite(D6,posMin);
    analogWrite(D7,posMin);
    analogWrite(D8,LOW);
  }
  else  if(pos<-5 && pos > -70){
    analogWrite(D5,posMax);
    analogWrite(D6,LOW);
    analogWrite(D7,LOW);
    analogWrite(D8,posMax);
  }
  else{
    analogWrite(D6,LOW);
    analogWrite(D7,LOW);
    analogWrite(D5,LOW);
    analogWrite(D8,LOW);
  }
}
