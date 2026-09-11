/*
  dk0030 — İki LED'i sırayla yak
  Devre: 1. LED uzun bacak (+) -> D5, kısa bacak (-) -> 220 ohm direnç -> GND
         2. LED uzun bacak (+) -> D6, kısa bacak (-) -> 220 ohm direnç -> GND
*/

// Her pine, kartın D-etiketiyle bir isim veriyoruz.
const int birinciLed = D5;
const int ikinciLed = D6;

void setup() {
  pinMode(birinciLed, OUTPUT);
  pinMode(ikinciLed, OUTPUT);
}

void loop() {
  digitalWrite(birinciLed, HIGH); // Birinci LED yanar.
  digitalWrite(ikinciLed, LOW);   // İkinci LED söner.
  delay(300);

  digitalWrite(birinciLed, LOW);  // Birinci LED söner.
  digitalWrite(ikinciLed, HIGH);  // İkinci LED yanar.
  delay(300);
}

// SEN YAP
// 1) İki LED'i aynı anda yakıp aynı anda söndür.
// 2) İki bekleme süresini 100 yap. Gözün sönmeyi ne zaman ayırt edemiyor?
// 3) birinciLed ve ikinciLed adlarını LED'lerinin gerçek renklerine göre değiştir.
