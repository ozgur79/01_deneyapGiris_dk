/* dk0080 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: delay(500) büyüdükçe araç her adımda daha uzun yol alır, küçüldükçe kısalır.
   Çözüm 2: Çok küçük hızlarda (örn. 8) motorlar aracı hareket ettirmeye yetmeyebilir;
     hız arttıkça araç belirgin şekilde hızlanır. Aracın hangi değerde kıpırdamaya
     başladığı pile ve araca göre değişir; bunu öğrenci kendisi gözlemler. %70 üst
     sınırı geçilmez.
   Çözüm 3: MOTOR2'nin ileri adımındaki yön 1 yapılırsa iki motor aracı artık aynı
     yöne itmez; araç düz gitmek yerine kendi etrafında döner. Sebep: motorlar
     karşılıklı takılı olduğu için aynı yön değeri tekerlekleri zıt yöne çevirir.
   Aşağıdaki kod Çözüm 3'ü gösterir; Çözüm 1 ve 2 yalnızca sayı değişikliğidir. */
#include <Deneyap_CiftKanalliMotorSurucu.h>

DualMotorDriver MotorSurucu;

const int hiz = 15;

void setup() {
  Serial.begin(115200);

  if (!MotorSurucu.begin(0x16)) {
    Serial.println("Motor surucuye I2C baglantisi basarisiz");
    while (1) delay(100);
  }

  Serial.println("Sistem hazir.");
}

void loop() {
  Serial.println("Ileri (MOTOR2 yonu degistirildi)");
  MotorSurucu.MotorDrive(MOTOR1, hiz, 1);
  MotorSurucu.MotorDrive(MOTOR2, hiz, 1); // Çözüm 3: 0 -> 1, araç kendi etrafında döner
  delay(500);

  Serial.println("Dur");
  MotorSurucu.MotorDrive(MOTOR1, 0, 1);
  MotorSurucu.MotorDrive(MOTOR2, 0, 1);
  delay(500);

  Serial.println("Geri");
  MotorSurucu.MotorDrive(MOTOR1, hiz, 0);
  MotorSurucu.MotorDrive(MOTOR2, hiz, 1);
  delay(500);

  Serial.println("Dur");
  MotorSurucu.MotorDrive(MOTOR1, 0, 0);
  MotorSurucu.MotorDrive(MOTOR2, 0, 0);
  delay(500);

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }
}
