/* dk0060 SEN YAP çözümleri — öğrenci dersinde gösterilmez.
   Çözüm 1: Y etiketini değiştir.
   Çözüm 2: Beklemeyi büyütüp küçült; fiziksel gözlemi öğrenci yapar.
   Çözüm 3: Kaynaktaki xRead() ile X'i de oku. */
#include <Deneyap_KumandaKolu.h>
Joystick KumandaKolu;

void setup() {
  Serial.begin(115200);
  KumandaKolu.begin(0x1A);
}

void loop() {
  uint16_t yEkseni = KumandaKolu.yRead();
  uint16_t xEkseni = KumandaKolu.xRead(); // Çözüm 3: okuma
  Serial.print("Kolun Y degeri: ");       // Çözüm 1: etiket
  Serial.println(yEkseni);
  Serial.print("X Ekseni: ");
  Serial.println(xEkseni);               // Çözüm 3: yazdırma
  delay(200);                            // Çözüm 2: önce 200, sonra 50 dene
}
