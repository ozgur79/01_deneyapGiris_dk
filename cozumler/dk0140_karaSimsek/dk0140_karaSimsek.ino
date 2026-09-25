/* dk0140 çözümleri — öğrenciye gösterilmez. */

// Çözüm 1: Desen ters yönde başlar (led4 -> led1 -> led4).
const int led1 = D5;
const int led2 = D6;
const int led3 = D9;
const int led4 = D10;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // 1. adım: sadece led4 yanık
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(300);

  // 2. adım: sadece led3 yanık
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  delay(300);

  // 3. adım: sadece led2 yanık
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(300);

  // 4. adım: sadece led1 yanık (sol uca vardık)
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(300);

  // 5. adım: geri dönüyoruz, sadece led2 yanık
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(300);

  // 6. adım: sadece led3 yanık; buradan sonra loop başa döner ve led4 yanar
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);
  delay(300);
}

/*
  Çözüm 2 (sayma görevi, kod yok): 5. LED eklenince adım sayısı 6'dan 8'e çıkar
  (1-2-3-4-5-4-3-2), her adımda digitalWrite satırı 4'ten 5'e çıkar. Toplam
  8 x (5 + 1 delay) = 48 satır. Mevcut kod 6 x (4 + 1) = 30 satır; fark 18 satır.

  Çözüm 3: Dört delay(300) satırının tümü delay(100) olur. const int ile isim
  verildiği için pin satırlarına dokunmak gerekmez, yalnız delay satırları değişir.
*/
