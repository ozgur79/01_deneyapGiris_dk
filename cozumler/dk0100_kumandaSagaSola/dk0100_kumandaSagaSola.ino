/* dk0100 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: donusHizi düşürülünce dönüş yavaşlar ama daha kontrollü olur;
     yükselince dönüş hızlanır. 70'i geçilmez.
   Çözüm 2: sagaEsik/solaEsik birlikte değiştirilince ölü bölge genişler/daralır,
     kolu yana itmenin "eşiği" değişir.
   Çözüm 3 (bant takip): tek doğru kod yok, deneyimsel bir görevdir; bu dosyaya
     kod eklenmedi. Öğrenci aracı kumandayla sürüp gözlemini yazar. */
#include <Deneyap_CiftKanalliMotorSurucu.h>
#include <Deneyap_KumandaKolu.h>

DualMotorDriver MotorSurucu;
Joystick KumandaKolu;

const uint16_t ileriEsik = 540;
const uint16_t geriEsik  = 480;
const uint16_t sagaEsik  = 600; // Çözüm 2: ölü bölge genişletildi
const uint16_t solaEsik  = 420;
const int maxHiz = 20;    // guvenlik siniri
const int donusHizi = 12; // Çözüm 1: güvenlik sınırının (20) da altında, daha yavaş/kontrollü dönüş

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
  uint16_t xEkseni = KumandaKolu.xRead();
  int hizSol = 0, hizSag = 0;
  int yonSol = 1, yonSag = 1;

  if (yEkseni > ileriEsik) {
    int hiz = constrain(map(yEkseni, ileriEsik, 1020, 0, maxHiz), 0, maxHiz);
    hizSol = hiz; hizSag = hiz; yonSol = 1; yonSag = 1;
  } else if (yEkseni < geriEsik) {
    int hiz = constrain(map(yEkseni, geriEsik, 0, 0, maxHiz), 0, maxHiz);
    hizSol = hiz; hizSag = hiz; yonSol = 0; yonSag = 0;
  } else if (xEkseni > sagaEsik) {
    hizSol = donusHizi; yonSol = 1;
    hizSag = donusHizi; yonSag = 0;
  } else if (xEkseni < solaEsik) {
    hizSol = donusHizi; yonSol = 0;
    hizSag = donusHizi; yonSag = 1;
  }

  MotorSurucu.MotorDrive(MOTOR1, hizSol, yonSol);
  MotorSurucu.MotorDrive(MOTOR2, hizSag, 1 - yonSag);

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  Serial.print("Y: "); Serial.print(yEkseni);
  Serial.print(" | X: "); Serial.print(xEkseni);
  Serial.print(" | Sol: "); Serial.print(hizSol);
  Serial.print(" | Sag: "); Serial.println(hizSag);

  delay(20);
}
