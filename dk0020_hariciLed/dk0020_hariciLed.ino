/*
  dk0020 — Harici LED'i yakıp söndür
  Ne öğreneceğiz: LED'i Deneyap Mini v2 kartının dışında, kendi kurduğun bir devre
    üzerinde bağlayıp digitalWrite ile yakıp söndürmek
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu, 1 LED, 1 adet 220 ohm direnç,
    breadboard, 2 jumper kablo
  Devre: LED'in uzun bacağı (+) -> Deneyap Mini v2 D5 pini
         LED'in kısa bacağı (-) -> 220 ohm direnç -> Deneyap Mini v2 GND

  Şimdilik kara kutu (sonra açacağız):
    void    -> "fonksiyon" konusunda açılacak
    OUTPUT  -> buton dersinde, INPUT ile birlikte açılacak

  kaynak: ak0020_hariciLed (D:\Atolye\Arduino\01_arduinoGiris_ak)
*/

// --- KAVRAM ---
// LED'in iki bacağı var: uzun bacak (+) ve kısa bacak (-) - yönü önemlidir, ters
// takarsan LED yanmaz
// Direnç, LED'e çok fazla akım gitmesini engeller ve LED'i korur
void setup() {
  // { ve } arasındaki satırlar, o fonksiyona ait koddur; bu blok "başlangıç" bloğudur
  pinMode(D5, OUTPUT); // D5 pinini, açıp kapatabileceğimiz bir pin yap (Ders 1.1'den hatırla)
  // ; işareti, bir komutun bittiğini gösterir
}

void loop() {
  digitalWrite(D5, HIGH); // D5 pinine gerilim gönder -> LED yanar
  delay(1000);            // 1000 milisaniye (1 saniye) bekle
  digitalWrite(D5, LOW);  // D5 pininin gerilimini kes -> LED söner
  delay(1000);            // 1 saniye bekle
}

// --- SEN YAP ---
// 1) LED'in bacaklarını yer değiştirerek tak (ters bağla). Ne oluyor, gözlemle.
// 2) LED'in kablosunu D5'ten D6'ya taşı. Kodda da neyi değiştirmen gerekiyor?
//    Değiştir ve çalıştır.
// 3) LED'i 3 saniye yanık, 1 saniye sönük kalacak şekilde çalıştır. Hangi satırları
//    değiştirmen gerekiyor?
