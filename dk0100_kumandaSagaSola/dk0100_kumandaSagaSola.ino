/*
  dk0100 — Kumandayla sağa/sola dön
  Ne öğreneceğiz: dk0090'da kolu ileri/geri ittin, araç düz gitti. Bu derste
    kolu ileri/geri itmeden, yalnız yana (X ekseni) ittiğinde aracın yerinde
    dönmesini sağlayacaksın. İki motoru zıt yönde döndürürsen araç bir yerden
    ötekine gitmez, kendi ekseni etrafında döner — buna **pivot dönüş** denir.
  Devre: dk0090 ile aynı — motor sürücü (0x16) ve kumanda kolu (0x1A) aynı
    I2C hattında. Motor sürücü seri bağlı 2 x 18650 pilden, çıt çıt anahtar
    üzerinden beslenir. Kart araçta 5V powerbank'tan Type-C USB ile beslenir.
    Ayrıntı için ders.md §4.
  Motor yönü: motorlar araca karşılıklı takılı (dk0080/dk0090'daki Özgür
    testi). MOTOR2'ye burada da `1 - yon` gönderilir.
  Açık varsayım: MOTOR1'in sol, MOTOR2'nin sağ motor olduğu kartta
    doğrulanmadı. Joystick sağa itilince araç sola dönerse ders.md §6'daki
    çözüm iki dönüş dalını yer değiştirir.
  Güvenlik: motorlar pil takılıyken beklenmedik anda dönebilir; ilk deneme
    tekerlekler havadayken yapılır.

  Şimdilik kara kutu (sonra açacağız):
    dk0090'daki tüm kara kutular geçerli: DualMotorDriver, Joystick, begin(),
    yRead(), map(), constrain(), MotorDrive(), CheckMotorError().
    KumandaKolu.xRead() -> Kolun X yönündeki o anki değerini verir (YENİ).
*/

// --- KAVRAM ---
// dk0090'da yalnız Y okunuyordu. Burada Y ölü bölgedeyken (araç ileri/geri
// gitmiyorken) X ekseni devreye girer: X sağa/sola itilince iki motor ZIT
// yönde döner, araç yerinde döner. Y ölü bölgede değilken davranış dk0090
// ile birebir aynıdır; X bu durumda dönüşe karışmaz.
#include <Deneyap_CiftKanalliMotorSurucu.h>
#include <Deneyap_KumandaKolu.h>

DualMotorDriver MotorSurucu;
Joystick KumandaKolu;

const uint16_t ileriEsik = 540;
const uint16_t geriEsik  = 480;
const uint16_t sagaEsik  = 540; // X ekseni için aynı eşikler yeniden kullanıldı
const uint16_t solaEsik  = 480;
const int maxHiz = 20;     // guvenlik siniri (Ozgur, 2026-09-24); donanimsal ust sinir %70'ti
const int donusHizi = 20;  // pivot donus icin de ayni guvenlik sinirinin uzerine cikilmaz

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
    // İleri: iki motor aynı hız/yönde (dk0090 ile aynı)
    int hiz = constrain(map(yEkseni, ileriEsik, 1020, 0, maxHiz), 0, maxHiz);
    hizSol = hiz; hizSag = hiz; yonSol = 1; yonSag = 1;
  } else if (yEkseni < geriEsik) {
    // Geri: iki motor aynı hız/yönde (dk0090 ile aynı)
    int hiz = constrain(map(yEkseni, geriEsik, 0, 0, maxHiz), 0, maxHiz);
    hizSol = hiz; hizSag = hiz; yonSol = 0; yonSag = 0;
  } else if (xEkseni > sagaEsik) {
    // Y ölü bölgede, X sağa itildi: yerinde sağa dön (pivot)
    hizSol = donusHizi; yonSol = 1; // sol motor ileri
    hizSag = donusHizi; yonSag = 0; // sağ motor geri
  } else if (xEkseni < solaEsik) {
    // Y ölü bölgede, X sola itildi: yerinde sola dön (pivot)
    hizSol = donusHizi; yonSol = 0; // sol motor geri
    hizSag = donusHizi; yonSag = 1; // sağ motor ileri
  }
  // Y ve X ikisi de ölü bölgedeyse hızSol=hızSag=0 kalır, araç durur.

  MotorSurucu.MotorDrive(MOTOR1, hizSol, yonSol);     // MOTOR1 = sol (varsayım)
  MotorSurucu.MotorDrive(MOTOR2, hizSag, 1 - yonSag); // MOTOR2 = sağ (varsayım); karşılıklı
                                                       // takılı olduğu için yön ters çevrilir

  if (MotorSurucu.CheckMotorError() == 1) {
    Serial.println("HATA! Lutfen motorlari kontrol edin");
  }

  Serial.print("Y: "); Serial.print(yEkseni);
  Serial.print(" | X: "); Serial.print(xEkseni);
  Serial.print(" | Sol: "); Serial.print(hizSol);
  Serial.print(" | Sag: "); Serial.println(hizSag);

  delay(20);
}

// --- SEN YAP ---
// 1) donusHizi değerini değiştir (örn. 10 ve 18). Aracın dönüş hızı ve
//    kontrolü nasıl değişiyor? 20'yi geçme — bu güvenlik sınırıdır.
// 2) sagaEsik/solaEsik değerlerini birlikte değiştir. Kolun ne kadar yana
//    itilmesi gerektiği (ölü bölgenin genişliği) nasıl değişiyor?
// 3) Zemine bantla bir kare ya da daire çiz. Aracı yalnız kumandayla (ileri/
//    geri/sağa/sola) sürüp bandı takip etmeyi dene. Bunun tek bir "doğru"
//    kodu yok — gözlemini ve denemeni kendi cümlenle anlat.
