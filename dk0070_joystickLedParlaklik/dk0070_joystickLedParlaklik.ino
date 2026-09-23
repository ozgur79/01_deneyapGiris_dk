/*
  dk0070 — Joystick ile LED parlaklığını değiştir
  Ne öğreneceğiz: dk0060'da gördüğümüz Y değerini harici LED'in ışığına
    dönüştürmek. Oturum 1'deki LED + direnç devresi yerinde kalır.
  Devre: dk0050'deki LED jumper'ını D9'dan D5'e taşı.
    LED uzun bacak (+) -> D5; kısa bacak (-) -> 220 ohm -> GND.
    Joystick bağlantı pinleri kaynak .ino'da yok; ders.md §4'e bak.

  Şimdilik kara kutu (sonra açacağız):
    Deneyap_KumandaKolu.h / Joystick -> Kumanda koluyla konuşan hazır araç.
    begin(0x1A) / yRead() -> Aracı başlatır / Y değerini okur.
    uint16_t / uint8_t -> Okunan ve parlaklık için kullanılan sayı türleri.
    map() -> Bir sayı aralığını başka aralığa çevirir.
    analogWrite() -> Hesaplanan parlaklığı harici LED'e uygular.

  Ana kaynak: D:\Atolye\Deneyap\arsiv\dyminiV2500kkHariciLedParlaklik\dyminiV2500kkHariciLedParlaklik.ino
*/

// --- KAVRAM ---
// Önce oku (yRead), sonra karar ver (if), aralığı dönüştür (map),
// LED'e uygula (analogWrite), sonucu ekranda göster (Serial).
// 540 eşiği, 540-1020 -> 0-255 dönüşümü ve 10'dan küçük sonuçların
// sıfırlanması kaynak kodun davranışıdır; nedenleri kaynakta açıklanmaz.
#include <Deneyap_KumandaKolu.h>

Joystick KumandaKolu;
const int ledPin = D5;
uint8_t ileri = 0;

void setup() {
  Serial.begin(115200);       // Seri Monitör'le aynı hız
  KumandaKolu.begin(0x1A);    // kaynakta kullanılan joystick adresi
  pinMode(ledPin, OUTPUT);    // D5'i LED için çıkış yap
  analogWrite(ledPin, 0);    // başlangıçta LED sönük
}

void loop() {
  uint16_t yEkseni = KumandaKolu.yRead(); // önce kolu oku
  ileri = 0;                             // her turda değeri sıfırla
  if (yEkseni > 540) {
    ileri = map(yEkseni, 540, 1020, 0, 255); // kaynak aralığını parlaklığa çevir
  }
  if (ileri < 10) {
    ileri = 0; // kaynak küçük sonuçları sıfırlıyor
  }
  analogWrite(ledPin, ileri); // hesaplanan değeri LED'e uygula
  Serial.print("Y Ekseni: ");
  Serial.print(yEkseni);
  Serial.print(" | LED parlaklik: ");
  Serial.println(ileri);
  delay(20);
}

// --- SEN YAP ---
// 1) Kaynaktaki 540 eşiğini ve map giriş alt sınırını birlikte değiştir;
//    önce tahmin et, sonra gözlemle.
// 2) Küçük değerleri sıfırlayan 10 eşiğini değiştir. LED ve ekrandaki
//    parlaklık değeri birlikte nasıl değişiyor?
// 3) dk0060'daki xRead() bilgisini kullanarak X ekseninden okunan değere
//    göre parlaklık ayarlamayı dene. Çözüm cozumler/ klasöründe olmalı.
