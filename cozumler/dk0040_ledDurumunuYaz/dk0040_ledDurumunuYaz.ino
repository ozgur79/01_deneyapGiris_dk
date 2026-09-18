/* dk0040 çözümleri — öğrenciye gösterilmez. */

const int led = D5;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(led, HIGH);
  Serial.println("ISIK ACIK");
  delay(2000);

  digitalWrite(led, LOW);
  Serial.println("ISIK KAPALI");
  delay(500);
}

/*
  Çözüm 1: HIGH'tan sonraki bekleme 2000, LOW'dan sonraki bekleme 500 olur.
  Çözüm 2: Örnek mesajlar ISIK ACIK ve ISIK KAPALI olarak yukarıda gösterildi.
  Çözüm 3: Mesaj digitalWrite satırından uzaklaştırıldığında ekrandaki bilgi LED'in
  güncel durumuyla aynı anda değişmez; gözlemden sonra ilgili satırın hemen altına alınır.
*/
