/* dk0090 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: ileriEsik/geriEsik birlikte değiştirilirse ölü bölge genişler/daralır.
   Çözüm 2: maxHiz düşürülünce Seri Monitör'deki "Hiz: %" bu yeni sınırda kırpılır.
   Çözüm 3: delay büyütülünce hem motor tepkisi hem ekran güncellemesi yavaşlar. */
#include <Deneyap_CiftKanalliMotorSurucu.h>
#include <Deneyap_KumandaKolu.h>

DualMotorDriver MotorSurucu;
Joystick KumandaKolu;

const uint16_t ileriEsik = 600; // Çözüm 1: ölü bölge genişletildi (480-600)
const uint16_t geriEsik  = 480;
const int maxHiz = 10;           // Çözüm 2: güvenlik sınırı olan 20'nin de altına düşürüldü

void setup() {
  Serial.begin(115200);

  if (!MotorSurucu.begin(0x16)) {
    Serial.println("Motor surucuye I2C baglantisi basarisiz");
    while (1) delay(100);
  }

  if (!KumandaKolu.begin(0x1A)) {
    Serial.println("Kumanda kolu bulunamadi");
    while (1) delay(100);
  }

  Serial.println("Sistem hazir.");
}

void loop() {
  uint16_t yEkseni = KumandaKolu.yRead();
  int hiz = 0;
  int yon = 1;

  if (yEkseni > ileriEsik) {
    hiz = map(yEkseni, ileriEsik, 1020, 0, maxHiz);
    hiz = constrain(hiz, 0, maxHiz);
    yon = 1;
  } else if (yEkseni < geriEsik) {
    hiz = map(yEkseni, geriEsik, 0, 0, maxHiz);
    hiz = constrain(hiz, 0, maxHiz);
    yon = 0;
  }

  MotorSurucu.MotorDrive(MOTOR1, hiz, yon);
  MotorSurucu.MotorDrive(MOTOR2, hiz, 1 - yon); // karşılıklı montaj

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  Serial.print("Y ekseni: ");
  Serial.print(yEkseni);
  Serial.print(" | Hiz: %");
  Serial.println(hiz);

  delay(100); // Çözüm 3: 20 -> 100, güncelleme gözle daha kolay izlenir
}
