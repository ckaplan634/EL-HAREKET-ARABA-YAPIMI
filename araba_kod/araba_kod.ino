
// Gerekli kütüphaneleri ekleyin
// Gerekli tüm kütüphane linklerini video açıklamasında bulabilirsiniz.
#include <SPI.h>      // nRF24L01 + ile iletişim kurmak için SPI kitaplığı
#include "RF24.h"     // nRF24L01 + 'in ana kütüphanesi

// Motorların etkin pinlerini tanımla
const int enbA = 3;
const int enbB = 5;
// Motorların kontrol pimlerini tanımlayın
// Motorlar ters yönde dönerse, aşağıdaki pin numaralarının pozisyonlarını değiştirebilirsiniz.
const int IN1 = 2;    // Sağ Motor (-)
const int IN2 = 4;    // Sağ Motor (+)
const int IN3 = 7;   // Sol Motor (+)
const int IN4 = 6;    // Sol Motor (-)

// Motor hızları için değişken tanımlayın
// İki motorun her biri için bir değişken tanımladım
// Bu sayede iki motor arasındaki dönüş hızı farkını senkronize edebilirsiniz.
int RightSpd = 130;
int LeftSpd = 150;

// Yön için paket tanımla (X ekseni ve Y ekseni)
int data[2];

// RF24 kütüphanesinden nesne tanımlayın - 9 ve 10, CE ve CSN sinyallerinin bağlı olduğu dijital pin numaralarıdır.
RF24 radio(9,10);

// İletişim için bir boru adresi oluşturun
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  // Motor pimlerini OUTPUT olarak tanımlayın
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();                   // nRF24 iletişimini başlat       
  radio.openReadingPipe(1, pipe);   // Programın veri alacağı vericinin adresini ayarlar.
  radio.startListening();             
  }

void loop(){
  if (radio.available()){
    radio.read(data, sizeof(data));

    if(data[0] > 380){
                                                      //ileri //           
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    
    if(data[0] < 310){
                                               //geriye             
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
     
    if(data[1] > 180){
                                        //sola
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }

    if(data[1] < 110){
                                          //sağa
      analogWrite(enbA, RightSpd);
      analogWrite(enbB, LeftSpd);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }

    if(data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160){
                     //dur
      analogWrite(enbA, 0);
      analogWrite(enbB, 0);
    }
  }
}
