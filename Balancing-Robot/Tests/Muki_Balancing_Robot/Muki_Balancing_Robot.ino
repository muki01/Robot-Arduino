#include "MPU6050.h"
#include <Wire.h>
MPU6050 mpu;

//PID constants
double kp = 8;
double ki = 0;
double kd = 1;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double cumError, rateError;
double motorPower;

int accZ = 0;

#define Motor1PWMPin1   13
#define Motor1PWMPin2   15
#define Motor2PWMPin1   12
#define Motor2PWMPin2   14

void setup() {
  pinMode(Motor1PWMPin1   , OUTPUT);
  pinMode(Motor1PWMPin2   , OUTPUT);
  pinMode(Motor2PWMPin1   , OUTPUT);
  pinMode(Motor2PWMPin2   , OUTPUT);
  setMotors(0);
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
  delay(0);
  accZ = mpu.getAccelerationX();
  accZ = map(accZ, -17000, 17000, -150, 150);
  computePID();
}

void setMotors(int MotorPWM ) {
  if (MotorPWM >= 0) {
    analogWrite(Motor1PWMPin1   , 0);
    analogWrite(Motor1PWMPin2   , MotorPWM);
    analogWrite(Motor2PWMPin1   , 0);
    analogWrite(Motor2PWMPin2   , MotorPWM);
  }
  else {
    analogWrite(Motor1PWMPin2   , 0);
    analogWrite(Motor1PWMPin1   , -MotorPWM);
    analogWrite(Motor2PWMPin2   , 0);
    analogWrite(Motor2PWMPin1   , -MotorPWM);

  }
}

double computePID() {
  currentTime = millis();                //get current time
  elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation

  error = accZ - 0;                                // determine error
  cumError += error * elapsedTime;                // compute integral
  rateError = (error - lastError) / elapsedTime; // compute derivative

  motorPower = kp * error + ki * cumError + kd * rateError;          //PID output
  setMotors(motorPower );

  lastError = error;                                //remember current error
  previousTime = currentTime;                        //remember current time
}
