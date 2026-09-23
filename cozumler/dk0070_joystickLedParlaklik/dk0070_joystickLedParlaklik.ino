/* dk0070 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: eşik değişirse map'in giriş alt sınırı da birlikte güncellenir.
   Çözüm 2: küçük parlaklığı sıfırlama sınırı değiştirilir.
   Çözüm 3: X ekseni için ayrı örnek aşağıdaki yorumda bulunur. */
#include <Deneyap_KumandaKolu.h>
Joystick KumandaKolu;
const int ledPin = D5;
uint8_t ileri = 0;

void setup() {
  Serial.begin(115200);
  KumandaKolu.begin(0x1A);
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 0);
}

void loop() {
  uint16_t yEkseni = KumandaKolu.yRead();
  ileri = 0;
  if (yEkseni > 600) {
    ileri = map(yEkseni, 600, 1020, 0, 255); // Çözüm 1
  }
  if (ileri < 20) {
    ileri = 0; // Çözüm 2
  }
  analogWrite(ledPin, ileri);
  Serial.print("Y Ekseni: ");
  Serial.print(yEkseni);
  Serial.print(" | LED parlaklik: ");
  Serial.println(ileri);
  delay(20);
}

/* Çözüm 3 — yukarıdaki loop() yerine denenir:
void loop() {
  uint16_t xEkseni = KumandaKolu.xRead();
  ileri = 0;
  if (xEkseni > 540) {
    ileri = map(xEkseni, 540, 1020, 0, 255);
  }
  if (ileri < 10) {
    ileri = 0;
  }
  analogWrite(ledPin, ileri);
  Serial.print("X Ekseni: ");
  Serial.print(xEkseni);
  Serial.print(" | LED parlaklik: ");
  Serial.println(ileri);
  delay(20);
}
*/
