#include <Servo.h>
#include <NewPing.h>

//motor pinleri
#define SolMotorileri 13
#define SolMotorGeri 15
#define SagMotorileri 12
#define SagMotorGeri 14

//sensör pinleri
#define Trigger 0
#define Echo 2
#define Maksimum_uzaklik 100

Servo servo;                                     //servo motor tanımlama
NewPing sonar(Trigger, Echo, Maksimum_uzaklik);  //ultrasonik sensör tanımlama

//kullanılacak eleman tanımı
unsigned int uzaklik;
unsigned int on_uzaklik;
unsigned int sol_uzaklik;
unsigned int sag_uzaklik;
unsigned int zaman;

void setup() {
  //motor çıkışları
  pinMode(SolMotorileri, OUTPUT);
  pinMode(SolMotorGeri, OUTPUT);
  pinMode(SagMotorileri, OUTPUT);
  pinMode(SagMotorGeri, OUTPUT);
  servo.attach(RX); //servo pin tanımı
}

void loop() {
  delay(500);
  servo.write(90);
  sensor_olcum();
  on_uzaklik = uzaklik;
  if (on_uzaklik > 35 || on_uzaklik == 0) {
    ileri();
  }
  else {
    dur();
    servo.write(180);
    delay(500);
    sensor_olcum();
    sol_uzaklik = uzaklik;
    servo.write(0);
    delay(500);
    sensor_olcum();
    sag_uzaklik = uzaklik;
    servo.write(90);
    delay(300);
    if (sag_uzaklik > sol_uzaklik) {
      geri();
      delay(200);
      sag();
      delay(300);
      ileri();
    }
    else if (sol_uzaklik > sag_uzaklik) {
      geri();
      delay(200);
      sol();
      delay(300);
      ileri();
    }
    else {
      geri();
    }
  }
}

// robotun yön komutları
void ileri() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);
}

void geri() {
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}

void sol() {
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);

}

void sag() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}

void dur() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, LOW);
}

// sensörün mesafe ölçümü
void sensor_olcum() {
  delay(50);
  zaman = sonar.ping();
  uzaklik = zaman / US_ROUNDTRIP_CM;
}
