/*
  dk0050 — Butona basınca LED yansın
  Ne öğreneceğiz: bir butonun basılı olup olmadığını digitalRead ile okumak, if/else ile
    karar vermek ve karara göre LED'i yakıp söndürmek
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu, 1 LED, 1 adet 220 ohm direnç,
    1 buton, 1 adet 10K ohm direnç, breadboard, jumper kablolar
  Devre: LED uzun bacak (+) -> D9
         LED kısa bacak (-) -> 220 ohm direnç -> GND
         Buton bir ucu -> 3.3V
         Buton diğer ucu -> D10 VE (10K ohm direnç ile) GND (pull-down: buton basılı
           değilken D10'u LOW'da sabit tutar, aksi halde pin ne okuyacağını bilemez)

  Şimdilik kara kutu (sonra açacağız):
    void -> Kod bölümünün sonunda değer döndürülmediğini belirtir; fonksiyon konusunda
            tam açılacak.

  Bu ders bir önceki dersten kalan sözü tutuyor: OUTPUT'un yanında artık INPUT de var —
  ikisi birlikte, kara kutu değil, gerçek kavram olarak açıklanıyor.

  kaynak: D:\Atolye\Deneyap\arsiv\dyminiV2010LedButon\dyminiV2010LedButon.ino (ham)
*/

// --- KAVRAM ---
// pinMode(pin, INPUT) o pini "okuma" pini yapar -- OUTPUT'un tam tersi. OUTPUT bir pine
// elektrik gönderir (LED'i yakmak gibi); INPUT bir pinden elektrik OKUR (buton basılı mı diye).
// digitalRead(pin) o pinin o an HIGH mi LOW mu olduğunu söyler; sonuç 1 (HIGH) ya da 0 (LOW) olur.
// if (...) { } içindeki kod parantez içindeki koşul doğruysa çalışır; else { } içindeki kod
// koşul yanlışsa çalışır -- ikisinden yalnız biri çalışır, asla ikisi birden değil.
const int led = D9;
const int buton = D10;

void setup() {
  pinMode(led, OUTPUT);   // led pinini çıkış yap -- dışarıya elektrik gönderecek
  pinMode(buton, INPUT);  // buton pinini giriş yap -- dışarıdan elektrik okuyacak
}

void loop() {
  if (digitalRead(buton) == 1) {
    digitalWrite(led, HIGH); // buton basılı (1) -> LED yansın
  } else {
    digitalWrite(led, LOW);  // buton basılı değil (0) -> LED sönsün
  }
}

// --- SEN YAP ---
// 1) Mantığı tersine çevir: buton basılı değilken LED yansın, basılınca sönsün.
//    Hangi satırları değiştirmen gerekiyor?
// 2) dk0040'ta öğrendiğin Serial.println'i kullanarak buton basılıyken Seri Monitör'e
//    "BASILI", basılı değilken "BASILI DEGIL" yazdır (Serial.begin(115200) eklemeyi unutma).
// 3) LED'i, buton basılı tutulduğu sürece 200 milisaniye aralıklarla yanıp söndür; buton
//    bırakılınca LED sönük kalsın.
