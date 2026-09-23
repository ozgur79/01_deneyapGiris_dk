/*
  dk0060 — Joystick kolunu oku
  Ne öğreneceğiz: butonun iki durumundan sonra, hareket eden kolun değişen
    değerini okuyup Seri Monitör'de gözlemlemek.
  Malzeme: Deneyap Mini v2, Type-C USB kablosu, Deneyap Kumanda Kolu.
  Bağlantı: Joystick'in karta nasıl bağlandığı kaynak .ino'da yazmıyor.
    Bilinmeyen bağlantı için pin numarası uydurulmaz; ders.md §4'e bak.

  Şimdilik kara kutu (sonra açacağız):
    Deneyap_KumandaKolu.h -> Joystick'i kullanmamızı sağlayan hazır kod.
    Joystick KumandaKolu -> Hazır kodun joystick aracına verdiğimiz ad.
    begin(0x1A) -> Kaynaktaki adresle joystick ile iletişimi başlatır.
    yRead() -> Kolun Y yönündeki o anki değerini verir.
    uint16_t -> Okunan tam sayıyı saklayan veri türü.
*/

// --- KAVRAM ---
// dk0050'de buton yalnız basılı/basılı değil diyordu. Joystick'in Y ekseninde
// kol hareket ettikçe değişen bir sayı okuruz. Bu kod, ışığı değiştirmez;
// okuduğu sayıyı Seri Monitör'de görünür yapar.
// Seri Monitör hızı karttaki Serial.begin(115200) ile aynı olmalıdır.
#include <Deneyap_KumandaKolu.h>

Joystick KumandaKolu;

void setup() {
  Serial.begin(115200);       // bilgisayara yazı göndermeyi başlat
  KumandaKolu.begin(0x1A);    // kaynaktaki adresle joystick'i başlat
}

void loop() {
  uint16_t yEkseni = KumandaKolu.yRead(); // o andaki Y değerini oku
  Serial.print("Y Ekseni: ");             // etiketi yaz, aynı satırda kal
  Serial.println(yEkseni);               // sayıyı yaz, yeni satıra geç
  delay(100);                            // ekrandaki satırlar arasına zaman koy
}

// --- SEN YAP ---
// 1) "Y Ekseni: " etiketini değiştir. Değer yine görünür mü?
// 2) delay süresini büyütüp küçült. Hangi durumda kol hareketini izlemek kolay?
// 3) Kaynaktaki xRead() çağrısını incele. X değerini de ayrı bir satırda
//    göstermeyi dene; hangi satırın okuma, hangisinin yazdırma işi yaptığını bul.
