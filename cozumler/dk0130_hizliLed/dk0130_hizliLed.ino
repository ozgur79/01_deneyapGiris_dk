/*
  dk0130 — Çözümler (öğrenciye gösterilmez, sadece kontrol için)

  SEN YAP 1) LED'i sırayla 1/5/10/25/50 kez-saniye hızlarında yakıp söndür.
    -> Devre ve dosya değişmez; her adımda iki delay() satırı da AŞAĞIDAKİ tabloya göre
       birlikte değiştirilir. Aşağıda her hız için tam kod bloğu var, kontrol içindir.

  SEN YAP 2) Sönmenin artık görünmediği hızı bul.
    -> Bu adımın kodu yoktur — gözlem ve karar öğrenciye aittir. Görme eşiği kişiden
       kişiye değiştiği için burada "doğru" bir sayı YAZILMAZ (ders.md de vermiyor).
       Test ederken beklenen aralık genelde delay(50) ile delay(20) arasıdır (10-25 Hz),
       ama bu bir kontrol referansıdır, öğrenciye söylenecek cevap değildir.

  SEN YAP 3) Bulduğun hızı bir aile bireyiyle ya da kendi tekrarınla karşılaştır.
    -> Kodu yok, gözlem adımı.
*/

// --- saniyede 1 kez ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(500);
  digitalWrite(D5, LOW);
  delay(500);
}

/*
// --- saniyede 5 kez ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(100);
  digitalWrite(D5, LOW);
  delay(100);
}
*/

/*
// --- saniyede 10 kez ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(50);
  digitalWrite(D5, LOW);
  delay(50);
}
*/

/*
// --- saniyede 25 kez ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(20);
  digitalWrite(D5, LOW);
  delay(20);
}
*/

/*
// --- saniyede 50 kez ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(10);
  digitalWrite(D5, LOW);
  delay(10);
}
*/
