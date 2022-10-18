#include <MPU6050_tockn.h> //https://github.com/tockn/MPU6050_tockn
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);

  //MPU sensör başlatma ayarları. İlk başlamada kartı stabil tutun. Gyro ofsetleri belirler.
  Wire.begin();
  mpu6050.begin();
  Serial.println("MPU-6050 sensör bulundu kartı oynatmadan bekleyin");
  mpu6050.calcGyroOffsets(true);
}

void loop() { 
  mpu6050.update();//verileri güncellemek için gerekli
  Serial.print("aci_X : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print(" aci_Y : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print(" aci_Z : ");
  Serial.println(mpu6050.getAngleZ());
  delay(100);
}
