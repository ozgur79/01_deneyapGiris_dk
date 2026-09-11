/*
  dk0010 — çözüm örneği

  SEN YAP 1) Üç sayı sırayla kırmızı, yeşil, mavi. Mavi yerine yeşil yakmak için
  ÜÇÜNCÜ sayı (mavi) 0 yapılır, İKİNCİ sayı (yeşil) 40 yapılır. Sadece yanan satır
  değişir; söndüren satır (0, 0, 0) zaten üç rengi de kapattığı için aynı kalır.
  Sık yapılan hata: sadece bir sayıyı 40 yapıp diğerini 0'a çekmeyi unutmak — o zaman
  LED yeşil değil turkuaz (yeşil + mavi) yanar. Bu "hata" aslında iyi bir keşiftir,
  öğrenci renk karışımını kendi bulmuş olur.

  SEN YAP 2) İki delay() satırındaki 1000 sayısı değiştirilir. İkisini birden
  değiştirmek gerekir; yalnız birini değiştirmek yanma ve sönme sürelerini farklı yapar
  (bu da SEN YAP 3'ün cevabıdır).

  SEN YAP 3) İki delay() farklı olunca LED'in ritmi değişir: örneğin delay(200) /
  delay(1500) kısa bir "çakma" üretir. Buradan çıkarılacak fikir: her delay kendinden
  ÖNCEKİ duruma aittir — birinci delay LED yanıkken, ikincisi sönükken bekler.

  Aşağıdaki kod SEN YAP 1 ve 3'ün birlikte uygulanmış hâlidir: yeşil, kısa yanma,
  uzun sönme.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  neopixelWrite(RGBLED, 0, 40, 0); // kırmızı 0, yeşil 40, mavi 0 -> yeşil
  delay(200);                      // kısa yanma
  neopixelWrite(RGBLED, 0, 0, 0);  // söner
  delay(1500);                     // uzun sönük kalma
}
