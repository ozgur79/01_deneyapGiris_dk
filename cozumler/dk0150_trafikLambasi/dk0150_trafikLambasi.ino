/* dk0150 çözümleri — öğrenciye gösterilmez. */

// Çözüm 2: Türkiye sırası (kırmızı -> kırmızı+sarı -> yeşil -> sarı -> kırmızı).
const int kirmizi = D5;
const int sari = D6;
const int yesil = D9;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(sari, OUTPUT);
  pinMode(yesil, OUTPUT);
}

void loop() {
  // Dur: yalnız kırmızı
  digitalWrite(kirmizi, HIGH);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, LOW);
  delay(4000);

  // Hazırlan: kırmızı + sarı birlikte
  digitalWrite(kirmizi, HIGH);
  digitalWrite(sari, HIGH);
  digitalWrite(yesil, LOW);
  delay(1000);

  // Geç: yalnız yeşil
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, HIGH);
  delay(3000);

  // Yavaşla: yalnız sarı
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, HIGH);
  digitalWrite(yesil, LOW);
  delay(1000);
}

/*
  Çözüm 1 (sayı seçimi, kod yok): Örnek: kırmızı delay(5000), sarı delay(500),
  yeşil delay(3000) — kırmızı daha uzun, sarı daha kısa, yeşil ortada kalır.
*/
