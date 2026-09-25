/* dk0160 çözümleri — öğrenciye gösterilmez. */

// Çözüm 1: Sarı LED 1 saniye yerine 2 saniye yanar (delay(1000) -> delay(2000)).
const int kirmizi = D5;
const int sari = D6;
const int yesil = D9;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(sari, OUTPUT);
  pinMode(yesil, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(kirmizi, HIGH);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, LOW);
  Serial.println("KIRMIZI");
  delay(4000);

  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, HIGH);
  Serial.println("YESIL");
  delay(3000);

  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, HIGH);
  digitalWrite(yesil, LOW);
  Serial.println("SARI");
  delay(2000);
}

/*
  Çözüm 2 (gözlem, kod yok): Sarı LED yanarken Seri Monitör'de aynı anda "SARI"
  görünür; ışık ile yazı arasında gözle görülür bir gecikme olmamalı.
*/
