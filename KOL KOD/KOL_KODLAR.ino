// CUMA KAPLAN BUAYA KADAR GELDIYSENİZ HERŞEY YOLUNDA DEMEKTIR KODU YÜKLEYİN VE NOKTAYI KOYUN :)

// Gerekli kütüphaneleri ekleyin
// Gerekli tüm kütüphane linklerini video açıklamasında bulabilirsiniz.
#include <SPI.h>        // nRF24L01 + ile iletişim kurmak için SPI kitaplığı
#include "RF24.h"       // nRF24L01 + 'in ana kütüphanesi
#include "Wire.h"      // İletişim kurmak için
#include "I2Cdev.h"     // MPU6050 ile iletişim kurmak için
#include "MPU6050.h"    // MPU6050'nin ana kütüphanesi


// Gyro ve Accelerometer'a erişmek ve onu hareket ettirmek için nesneyi tanımlayın (Gyro verilerini kullanmıyoruz)
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Yön için paket tanımla (X ekseni ve Y ekseni)
int data[2];

// RF24 kütüphanesinden nesne tanımlama - 9 ve 10, CE ve CSN sinyallerinin bağlı olduğu dijital pin numaralarıdır.
RF24 radio(9,10);

// İletişim için bir boru adresi oluşturun                                   
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void){
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();              // MPU nesnesini başlat
  radio.begin();                 // nRF24 iletişimini başlat   
  radio.openWritingPipe(pipe);   // Programın veri göndereceği alıcının adresini ayarlar.
}

void loop(void){
  
// Bu fonksiyon ile eksenlerin ivmelenme ve gyro değerleri alınır.
  // Otomobil eksenini farklı bir şekilde kontrol etmek istiyorsanız, eksen komutunu harita komutundan değiştirebilirsiniz.
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

// İki yönlü kontrolde, MPU6050'nin X ekseni (veri [0]) robotun ileri ve geri hareket etmesini sağlar.
  // Y ekseni (veri [0]) robotun sağa ve sola dönmesini sağlar.
  data[0] = map(ax, -17000, 17000, 300, 400 ); // X ekseni verilerini gönder
  data[1] = map(ay, -17000, 17000, 100, 200); // Y ekseni verilerini gönder
  radio.write(data, sizeof(data));
}
