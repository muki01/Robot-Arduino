#include <Wire.h>
#include "MPU6050.h"

double Kp = 2200;
double Ki = 0;
double Kd = 40;

#define Motor1PWMPin1   13
#define Motor1PWMPin2   15
#define Motor2PWMPin1   12
#define Motor2PWMPin2   14
#define sampleTime  0.01
MPU6050 mpu;
int16_t accY, accZ, gyroX;
double motorPower, gyroRate;
double accAngle, gyroAngle, currentAngle, prevAngle = 0, error, prevError = 0, errorSum = 0;

void setMotors(int MotorPWM ) {
  if (MotorPWM >= 0) {
    analogWrite(Motor1PWMPin1   , MotorPWM);
    analogWrite(Motor1PWMPin2   , 0);
    analogWrite(Motor2PWMPin1   , MotorPWM);
    analogWrite(Motor2PWMPin2   , 0);
  }
  else {
    analogWrite(Motor1PWMPin2   , -MotorPWM);
    analogWrite(Motor1PWMPin1   , 0);
    analogWrite(Motor2PWMPin2   , -MotorPWM);
    analogWrite(Motor2PWMPin1   , 0);
  }
}

void setup() {
  pinMode(Motor1PWMPin1   , OUTPUT);
  pinMode(Motor1PWMPin2   , OUTPUT);
  pinMode(Motor2PWMPin1   , OUTPUT);
  pinMode(Motor2PWMPin2   , OUTPUT);
  setMotors(0);
  Serial.begin(115200);
  Wire.begin();
  analogWriteRange(255);
  mpu.initialize();
  mpu.setXAccelOffset(-1400);
  mpu.setYAccelOffset(-449);
  mpu.setZAccelOffset(1826);
  mpu.setXGyroOffset(89);
  mpu.setYGyroOffset(-72);
  mpu.setZGyroOffset(41);
}
unsigned int lastTempUpdate = 0;
bool periodicFunc() {
  if ((millis() - lastTempUpdate) > (sampleTime * 1000)) {
    lastTempUpdate = millis();
    accAngle = atan2(accY, accZ) * RAD_TO_DEG;
    gyroRate = map(gyroX, -32768, 32767, -250, 250);
    gyroAngle = (float)gyroRate * sampleTime;
    currentAngle = 0.9934 * (prevAngle + gyroAngle) + 0.0066 * (accAngle);
    
    error = currentAngle - 0;
    errorSum = errorSum + error;
    errorSum = constrain(errorSum, -300, 300);

    motorPower = Kp * (error) + Ki * (errorSum) * sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;
    
    prevAngle = currentAngle;
    motorPower = constrain(motorPower, -255, 255);

    //motorPower = motorPower * 2;
    setMotors(motorPower );
    
  }
}
void loop() {
  accY = mpu.getAccelerationX();
  accZ = mpu.getAccelerationZ();
  gyroX = mpu.getRotationX();
  periodicFunc();
}
