/*
  dk0080 — Motor sürücü ile iki motoru döndür
  Ne öğreneceğiz: LEGO aracın iki motorunu, kumanda kolu olmadan, sabit bir
    hızla önce ileri, sonra durdurup geri sürmek.
  Devre: Motor sürücü karta I2C soketinden bağlıdır, adres 0x16. Motorlar
    sürücünün motor çıkışlarına bağlıdır. Motor sürücünün beslemesi kart
    değil, seri bağlı 2 x 18650 pildir; pil ile sürücü arasındaki çıt çıt
    anahtar motor gücünü açıp kapatır. Ayrıntı için ders.md §4'e bak.
  Motor yönü: motorlar araca karşılıklı (ayna gibi) takılı. Bu yüzden araç
    ileri giderken MOTOR1'e 1, MOTOR2'ye 0 gönderilir.
  Güvenlik: motorlar pil takılıyken beklenmedik anda dönebilir; çıt çıt
    anahtarı kapalıyken kod yükle, aracı tekerlekleri havada test et.

  Şimdilik kara kutu (sonra açacağız):
    Deneyap_CiftKanalliMotorSurucu.h -> Motor sürücüyü kullanmamızı sağlayan hazır kod.
    DualMotorDriver MotorSurucu -> Hazır kodun motor sürücüye verdiğimiz ad.
    begin(0x16) -> Kaynaktaki adresle motor sürücüyle iletişimi başlatır.
    MotorDrive(motor, hız, yön) -> Belirtilen motoru verilen hız (%) ve yönde (1: ileri, 0: geri) döndürür.
    MOTOR1 / MOTOR2 -> Sürücünün iki motor çıkışının adları.
    CheckMotorError() -> Motorlarda hata olup olmadığını bildirir.
*/

// --- KAVRAM ---
// dk0060/dk0070'te joystick'ten okuduğumuz sayıyı LED'e uyguluyorduk.
// Burada okuma yok: hızı ve yönü biz kodda sabit yazıyoruz, sürücü de
// iki motoru o hızda/yönde döndürüyor. Sıra: ileri -> dur -> geri -> dur
// -> baştan başla. İki motor karşılıklı takılı olduğu için "aracın ileri
// gitmesi" = MOTOR1 yön 1 + MOTOR2 yön 0.
#include <Deneyap_CiftKanalliMotorSurucu.h>

DualMotorDriver MotorSurucu;

const int hiz = 15;  // LEGO araçta denenmiş hız (%15); üst sınır %70'tir, onu geçme

void setup() {
  Serial.begin(115200);           // bilgisayara yazı göndermeyi başlat

  if (!MotorSurucu.begin(0x16)) { // kaynaktaki adresle motor sürücüyü başlat
    Serial.println("Motor surucuye I2C baglantisi basarisiz");
    while (1) delay(100);         // bağlantı yoksa burada dur
  }

  Serial.println("Sistem hazir.");
}

void loop() {
  Serial.println("Ileri");
  MotorSurucu.MotorDrive(MOTOR1, hiz, 1);  // sol/sağ motor ters takılı:
  MotorSurucu.MotorDrive(MOTOR2, hiz, 0);  // araç ileri = MOTOR1 1, MOTOR2 0
  delay(500);                              // yarım saniye ileri

  Serial.println("Dur");
  MotorSurucu.MotorDrive(MOTOR1, 0, 1);    // hız 0: motor durur
  MotorSurucu.MotorDrive(MOTOR2, 0, 1);
  delay(500);

  Serial.println("Geri");
  MotorSurucu.MotorDrive(MOTOR1, hiz, 0);  // ileri'nin tam tersi:
  MotorSurucu.MotorDrive(MOTOR2, hiz, 1);  // araç geri = MOTOR1 0, MOTOR2 1
  delay(500);

  Serial.println("Dur");
  MotorSurucu.MotorDrive(MOTOR1, 0, 0);
  MotorSurucu.MotorDrive(MOTOR2, 0, 0);
  delay(500);

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }
}

// --- SEN YAP ---
// 1) İleri ve geri adımlarındaki delay(500) sürelerini büyült/küçült. Araç ne kadar
//    yol aldı?
// 2) hiz değerini 15'ten farklı sayılarla dene (örn. 8 ve 30). Araç hangi değerde
//    hiç kıpırdamıyor, hangisinde belirgin hızlanıyor? 70'i geçme.
// 3) Sadece MOTOR2'nin ileri adımındaki yönü 0'dan 1'e çevir. Araç ne yaptı? Neden?
