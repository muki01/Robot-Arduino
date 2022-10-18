#include "MPU6050.h"
#include <Wire.h>
MPU6050 mpu;

int accZ = 0;
double accZMin = 0;
double accZMax = 0;

void setup() {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  Wire.begin();
  //analogWriteRange(255);
  mpu.initialize();
  mpu.setXAccelOffset(-1528);
  mpu.setYAccelOffset(-510);
  mpu.setZAccelOffset(1826);
  mpu.setXGyroOffset(85);
  mpu.setYGyroOffset(-75);
  mpu.setZGyroOffset(42);
}

void loop() {
  delay(40);
  accZ = mpu.getAccelerationX();
  accZ = map(accZ, -17000, 17000, -150, 150);
  accZMin = accZ * 20;
  accZMax = accZ * 20;

  if (accZ > 5 && accZ < 120) {
    analogWrite(D5, accZMax);
    analogWrite(D6, 0);
    analogWrite(D7, 0);
    analogWrite(D8, accZMax);
  }
  else  if (accZ < -5 && accZ > -120) {
    analogWrite(D5, 0);
    analogWrite(D6, -accZMin);
    analogWrite(D7, -accZMin);
    analogWrite(D8, 0);
  }
  else {
    analogWrite(D6, 0);
    analogWrite(D7, 0);
    analogWrite(D5, 0);
    analogWrite(D8, 0);
  }
}
