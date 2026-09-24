/* dk0110 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: kalibrasyon deneyseldir, kod değişmez (ders.md §5).
   Çözüm 2: sureDuz büyütülünce dörtgen büyür, küçültülünce küçülür (kod aynı).
   Çözüm 3: beşgen — 5 kenar, dış açı 360/5 = 72 derece. sureDon72,
     sureDon90'dan oranla hesaplanır (90'lık kalibrasyona dayanır). */
#include <Deneyap_CiftKanalliMotorSurucu.h>

DualMotorDriver MotorSurucu;

const int hizDuz    = 15;
const int sureDuz   = 1500;
const int hizDon     = 20; // güvenlik tavanı, üstüne çıkılmaz
const int sureDon90  = 500; // kendi kalibrasyonunla değiştir
const int sureDon72  = sureDon90 * 72 / 90; // Çözüm 3: dış açı 360/5 = 72 derece

void setup() {
  Serial.begin(115200);

  if (!MotorSurucu.begin(0x16)) {
    Serial.println("Motor surucuye I2C baglantisi basarisiz");
    while (1) delay(100);
  }

  Serial.println("Sistem hazir.");
}

void loop() {
  Serial.println("Besgen");
  for (int kenar = 0; kenar < 5; kenar++) { // Çözüm 3: 5 tekrar
    // duz git
    MotorSurucu.MotorDrive(MOTOR1, hizDuz, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDuz, 0);
    delay(sureDuz);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);

    // yerinde don, ~72 derece (dis aci, 360/5)
    MotorSurucu.MotorDrive(MOTOR1, hizDon, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDon, 1);
    delay(sureDon72);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);
  }

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  delay(3000);
}
