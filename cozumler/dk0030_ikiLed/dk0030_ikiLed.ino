/* dk0030 çözümleri — öğrenciye gösterilmez. */

// Çözüm 1: İki LED birlikte yanar, sonra birlikte söner.
const int birinciLed = D5;
const int ikinciLed = D6;

void setup() {
  pinMode(birinciLed, OUTPUT);
  pinMode(ikinciLed, OUTPUT);
}

void loop() {
  digitalWrite(birinciLed, HIGH);
  digitalWrite(ikinciLed, HIGH);
  delay(300);
  digitalWrite(birinciLed, LOW);
  digitalWrite(ikinciLed, LOW);
  delay(300);
}

/*
  Çözüm 2: Her iki delay(300) satırı delay(100) olur.
  Çözüm 3: Örneğin birinciLed adı kirmiziLed, ikinciLed adı yesilLed yapılır;
  dört kullanımın tamamı aynı adla değiştirilir.
*/
