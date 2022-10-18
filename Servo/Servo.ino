#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(3);  //D4
  servo.write(0);
  delay(2000);
}

void loop() {
  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
  servo.write(90);
  delay(1000);
}
