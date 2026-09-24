/*
  dk0090 — Kumanda kolu ile motor yönü ve hızını ayarla
  Ne öğreneceğiz: dk0080'de sabit yazdığımız hız ve yönü, dk0060/dk0070'te
    okumayı öğrendiğimiz joystick Y değerine bağlamak. Kol öne/arkaya ne
    kadar itilirse motorlar o kadar hızlı döner; ortadayken motorlar durur.
  Devre: Motor sürücü ve kumanda kolu aynı I2C hattını paylaşır (adres 0x16
    ve 0x1A). Motor sürücünün beslemesi seri bağlı 2 x 18650 pildir; pil
    hattındaki çıt çıt anahtar motor gücünü açıp kapatır. Ayrıntı için ders.md §4.
  Motor yönü: dk0080'deki gibi motorlar araca karşılıklı takılı. Bu yüzden
    MOTOR2'ye her zaman MOTOR1'in tersi olan yön gönderilir (1 - yon).
  Güvenlik: motorlar pil takılıyken beklenmedik anda dönebilir; kartı/motor
    sürücüsünü masada, tekerlekler havada dururken test et.

  Şimdilik kara kutu (sonra açacağız):
    Deneyap_CiftKanalliMotorSurucu.h / DualMotorDriver -> Motor sürücüyle konuşan hazır araç.
    Deneyap_KumandaKolu.h / Joystick -> Kumanda koluyla konuşan hazır araç.
    begin(0x16) / begin(0x1A) -> İki modülü kendi adresleriyle başlatır.
    yRead() -> Kolun Y yönündeki o anki değerini verir.
    map() -> Bir sayı aralığını başka aralığa çevirir.
    constrain() -> Bir sayıyı verilen alt/üst sınır içinde tutar.
    MotorDrive(motor, hız, yön) -> Motoru verilen hız (%) ve yönde döndürür.
    CheckMotorError() -> Motorlarda hata olup olmadığını bildirir.

  Kaynak: D:\Atolye\Deneyap\arsiv\dyminiV2501kk_deneyapMotorSurucu_2Motor\dyminiV2501kk_deneyapMotorSurucu_2Motor.ino
    Bu ders kaynağın öğretim hâlidir: 540/480 eşikleri, ölü bölge ve
    CheckMotorError aynen korunur. İki bilinçli sapma var: MOTOR2'nin yönü
    (1 - yon, LEGO araçtaki karşılıklı montaj yüzünden, dk0080 testi) ve
    maxHiz (kaynakta 70 idi; Özgür'ün çocuk güvenliği kararıyla 20'ye
    düşürüldü, bkz. aşağıdaki not).
  Güvenlik hızı (Özgür, 2026-09-24): Kaynaktaki %70 sınırı yalnız donanımsal
    bir tavan (pil gerilimi ~8,4V'u motor için ~6V'a yaklaşık sınırlamak
    içindi). Bu ders ayrıca %20'lik İKİNCİ, daha sıkı bir sınır (maxHiz=20)
    kullanır: Özgür aracı test ederken ileri/geri geçişlerin çok sert
    olduğunu, çocuğun elindeyken aracın fırlayıp masadan düşebileceğini
    gördü. map'in hedef aralığı da 0-100 yerine doğrudan 0-maxHiz yapıldı:
    böylece kolun küçük bir hareketi bile hızı 0-100'e eşleyip sonra
    kırpmak yerine, hızı kolun hareketiyle orantılı ve yumuşak artırır.
*/

// --- KAVRAM ---
// Akış: joystick'i oku -> eşiklere göre yön belirle -> aralığı hıza çevir ->
// hızı sınırla -> motorlara uygula -> hatayı kontrol et -> ekrana yaz.
// 540/480 eşikleri ve ölü bölge kaynak kodun davranışıdır. maxHiz ve map'in
// hedef aralığı (0-maxHiz) ise kaynaktan bilinçli bir sapmadır: çocuk
// güvenliği için hız %20 ile sınırlandı (Özgür, 2026-09-24).
#include <Deneyap_CiftKanalliMotorSurucu.h>
#include <Deneyap_KumandaKolu.h>

DualMotorDriver MotorSurucu;
Joystick KumandaKolu;

const uint16_t ileriEsik = 540;
const uint16_t geriEsik  = 480;
const int maxHiz = 20;  // guvenlik siniri (Ozgur, 2026-09-24); donanimsal ust sinir %70'ti

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
  uint16_t yEkseni = KumandaKolu.yRead(); // önce kolu oku
  int hiz = 0;
  int yon = 1;  // 1: ileri, 0: geri

  if (yEkseni > ileriEsik) {
    // İleri: joystick aralığını doğrudan 0-maxHiz'e dönüştür (0-100 değil)
    hiz = map(yEkseni, ileriEsik, 1020, 0, maxHiz);
    hiz = constrain(hiz, 0, maxHiz); // emniyet: map sınır dışına taşarsa kırpar
    yon = 1;
  } else if (yEkseni < geriEsik) {
    // Geri: joystick aralığını doğrudan 0-maxHiz'e dönüştür (0-100 değil)
    hiz = map(yEkseni, geriEsik, 0, 0, maxHiz);
    hiz = constrain(hiz, 0, maxHiz); // emniyet: map sınır dışına taşarsa kırpar
    yon = 0;
  }

  // Ölü bölgede (480-540 arası) hız 0 kalır; iki motor da durur.
  MotorSurucu.MotorDrive(MOTOR1, hiz, yon);
  MotorSurucu.MotorDrive(MOTOR2, hiz, 1 - yon); // MOTOR2 karşılıklı takılı: yönü ters çevir
                                                // (1 - 1 = 0, 1 - 0 = 1)

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  Serial.print("Y ekseni: ");
  Serial.print(yEkseni);
  Serial.print(" | Hiz: %");
  Serial.println(hiz);

  delay(20);
}

// --- SEN YAP ---
// 1) ileriEsik/geriEsik değerlerini (540/480) birlikte değiştir; önce tahmin et,
//    sonra kolu iterek gözlemle. Ölü bölge büyüdü mü küçüldü mü?
// 2) maxHiz değerini 20'den küçük bir sayıya indir (örn. 10). Kolu sonuna
//    kadar itince Seri Monitör'deki "Hiz: %" değeri kaç ile sınırlanıyor?
//    maxHiz'i 20'nin ÜSTÜNE çıkarma — bu güvenlik sınırıdır.
// 3) delay(20) süresini büyüt. Kolu hızlıca ileri-geri oynattığında motorların
//    tepkisi ile Seri Monitör'deki sayıların güncellenme hızı nasıl değişiyor?
