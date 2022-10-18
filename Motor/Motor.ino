void setup() {
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);

}

void loop() {
  digitalWrite(D5,HIGH);
  digitalWrite(D6,LOW);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,LOW);
  delay(3000);
  digitalWrite(D5,LOW);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,LOW);
  delay(3000);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,HIGH);
  delay(3000);
  digitalWrite(D5,LOW);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,LOW);
  digitalWrite(D8,HIGH);
  delay(3000);
  digitalWrite(D5,LOW);
  analogWrite(D6,150);
  digitalWrite(D7,LOW);
  analogWrite(D8,150);
  delay(5000);
  digitalWrite(D5,LOW);
  analogWrite(D6,255);
  digitalWrite(D7,LOW);
  analogWrite(D8,150);
  delay(5000);
}
