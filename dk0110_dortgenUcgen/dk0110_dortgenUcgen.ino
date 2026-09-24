/*
  dk0110 — Kodla dörtgen ve üçgen çiz
  Ne öğreneceğiz: bir kenar = düz git + yerinde dön (dk0100'deki pivot
    dönüş mantığı). Dörtgeni 4 kere, üçgeni 3 kere tekrarlayarak çizeceğiz
    — ama bu kez tekrarı elle kopyala-yapıştır yapmadan, `for` döngüsüyle
    yazacağız.
  ÖNKOŞUL: `for` bu derste KARA KUTU DEĞİLDİR — döngü fikrinin (Modül 2
    aday bandındaki `for`/döngüler dersi) bilindiği varsayılır. İlk dilim
    bir tadım dilimi olduğu için o ders henüz üretilmedi; tam müfredatta
    bu dersten önce gelecektir.
  Kalibrasyon: sureDon90 sabiti KESİN DEĞİL — "90° dönmek kaç ms sürüyor?"
    sorusunu kartında deneyerek bulman gerekir. Ayrıntı için ders.md §5.
  Üçgende dönüş açısı: araç her köşede İÇ açı (60°) kadar değil, DIŞ açı
    (120°) kadar döner. sureDon120, sureDon90'dan oranla hesaplanır ama
    kartta ayrıca doğrulanmalıdır.
  Devre: kumanda kolu bu derste bağlı/kullanılan bir modül değil. Motor
    sürücü I2C soketinden (0x16), seri bağlı 2 x 18650 pil + çıt çıt anahtar
    ile beslenir; kart araçta 5V powerbank'tan Type-C USB ile beslenir.
  Güvenlik: Araç en fazla %20 hızla gider (hizDuz, hizDon). Bunu
    değiştirebilirsin ama 70'i geçme — kaynak motorların dayanabileceği
    donanımsal tavan %70'tir (pil gerilimi yüzünden), %20 ise Özgür'ün
    çocuk güvenliği için koyduğu ayrı, daha sıkı bir sınırdır (2026-09-24).
    Araç yerde, geniş ve boş bir alanda çalıştırılır; masada çalıştırılmaz.
    İlk deneme yine tekerlekler havadayken yapılır.
*/

#include <Deneyap_CiftKanalliMotorSurucu.h>

DualMotorDriver MotorSurucu;

const int hizDuz    = 15;   // dk0080'in test edilmiş hızı
const int sureDuz   = 1500; // ms, bir kenar boyu -- BAŞLANGIÇ DEĞERİ, kalibre et
const int hizDon     = 20;  // pivot dönüş hızı; güvenlik tavanı (20), üstüne çıkılmaz
const int sureDon90  = 500; // ms, 90 derece dönüş -- KALİBRE ET (ders.md §5)
const int sureDon120 = sureDon90 * 120 / 90; // dış açı 120°; 90°'den oranla hesaplandı, kartta doğrula

void setup() {
  Serial.begin(115200);

  if (!MotorSurucu.begin(0x16)) {
    Serial.println("Motor surucuye I2C baglantisi basarisiz");
    while (1) delay(100);
  }

  Serial.println("Sistem hazir.");
}

void loop() {
  Serial.println("Dortgen");
  for (int kenar = 0; kenar < 4; kenar++) {
    // duz git
    MotorSurucu.MotorDrive(MOTOR1, hizDuz, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDuz, 0);
    delay(sureDuz);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);

    // yerinde don, ~90 derece
    MotorSurucu.MotorDrive(MOTOR1, hizDon, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDon, 1);
    delay(sureDon90);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);
  }

  delay(2000); // dortgen ile ucgen arasinda bekleme

  Serial.println("Ucgen");
  for (int kenar = 0; kenar < 3; kenar++) {
    // duz git
    MotorSurucu.MotorDrive(MOTOR1, hizDuz, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDuz, 0);
    delay(sureDuz);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);

    // yerinde don, ~120 derece (dis aci)
    MotorSurucu.MotorDrive(MOTOR1, hizDon, 1);
    MotorSurucu.MotorDrive(MOTOR2, hizDon, 1);
    delay(sureDon120);

    // dur
    MotorSurucu.MotorDrive(MOTOR1, 0, 1);
    MotorSurucu.MotorDrive(MOTOR2, 0, 1);
    delay(300);
  }

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  delay(3000); // yeniden baslamadan once bekleme
}

// --- SEN YAP ---
// 1) ders.md §5'teki kalibrasyon adımlarını izleyerek sureDon90'ı kendi
//    aracında ayarla. Dörtgenin köşeleri gerçekten ~90 derece mi oluyor?
// 2) for döngüsündeki tekrar sayısını (4, 3) değiştirmeden, yalnız
//    sureDuz'u değiştirerek dörtgeni büyüt/küçült.
// 3) for döngüsünü kullanarak bir BEŞGEN çizmeyi dene: 5 kenar, dış açı
//    360/5 = 72 derece. Kaç kere tekrarlanmalı, dönüş süresi nasıl
//    hesaplanmalı? Çözüm cozumler/'de.
