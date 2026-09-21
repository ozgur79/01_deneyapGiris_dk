/* dk0050 çözümleri — öğrenciye gösterilmez. */

const int led = D9;
const int buton = D10;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buton, INPUT);
  Serial.begin(115200); // Çözüm 2 için
}

void loop() {
  // Çözüm 1: mantık tersine çevrildi -- basılı değilken yanık, basılıyken sönük.
  if (digitalRead(buton) == 1) {
    digitalWrite(led, LOW);
    Serial.println("BASILI");     // Çözüm 2
  } else {
    digitalWrite(led, HIGH);
    Serial.println("BASILI DEGIL"); // Çözüm 2
  }

  // Çözüm 3 (ayrı bir örnek olarak, yukarıdaki loop() yerine denenir):
  // if (digitalRead(buton) == 1) {
  //   digitalWrite(led, HIGH);
  //   delay(200);
  //   digitalWrite(led, LOW);
  //   delay(200);
  // } else {
  //   digitalWrite(led, LOW);
  // }
}

/*
  Çözüm 1: if ve else içindeki digitalWrite satırları (HIGH/LOW) birbiriyle yer değiştirir.
  Çözüm 2: Serial.begin(115200) setup() içine, Serial.println çağrıları if/else'in
    içine, ilgili digitalWrite satırının altına eklenir.
  Çözüm 3: LED'i yanıp söndürmek için if bloğunun içine kısa bir delay(200) ile
    digitalWrite(led, LOW) + delay(200) çifti eklenir; else bloğu LED'i sabit söndürür.
    Bu, butona basılı tutulduğu sürece loop() her turunda LED'i tekrar yakıp söndürür.
*/
