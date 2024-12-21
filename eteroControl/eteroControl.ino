#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <SoftwareSerial.h>

SoftwareSerial btSerial(11, 12); // RX | TX
Adafruit_MPU6050 mpu;

char moveFB; // Gerakan maju/mundur
char moveRL; // Gerakan kiri/kanan

void setup() {
  btSerial.begin(38400);
  Serial.begin(9600);
  Wire.begin();

  if (!mpu.begin()) {
    Serial.println("Gagal menemukan chip MPU6050. Periksa koneksi dan alamat I2C.");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  Serial.println("MPU6050 siap digunakan.");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Konversi dan pemetaan nilai accelerometer
  int accX = map((int)a.acceleration.x, -10, 10, 180, 0);
  int accY = map((int)a.acceleration.y, -10, 10, 180, 0);

  // Logika gerakan kiri/kanan
  if (accY < 50) {
    moveRL = 'L'; // Kiri
  } else if (accY >= 50 && accY <= 130) {
    moveRL = 'N'; // Netral
  } else if (accY > 130) {
    moveRL = 'R'; // Kanan
  }

  // Logika gerakan maju/mundur
  if (accX < 80) {
    moveFB = 'B'; // Mundur
  } else if (accX >= 80 && accX <= 130) {
    moveFB = 'M'; // Stabil
  } else if (accX > 130) {
    moveFB = 'F'; // Maju
  }

  // Gabungkan data untuk dikirim
  String dataToSend = String(moveFB) + String(moveRL) + "\n";

  // Kirim data melalui Bluetooth
  btSerial.print(dataToSend);
  Serial.print("Dikirim: ");
  Serial.println(dataToSend);

  delay(50); // Delay untuk stabilitas komunikasi
}
