/*
  dk0010 — Kartın üzerindeki LED'i yakıp söndür
  Ne öğreneceğiz: setup() bir kez çalışır, loop() sürekli tekrar eder; kartın üzerinde
    hazır duran renkli LED'i yakıp söndürmek. Devre kurmana gerek yok.
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu (başka hiçbir şey gerekmez)
  Devre: yok — bu kartta renkli (RGB) LED zaten kartın üzerinde hazır bağlı

  Şimdilik kara kutu (sonra açacağız):
    void    -> "fonksiyon" konusunda açılacak
    OUTPUT  -> buton dersinde, INPUT ile birlikte açılacak
  Bunlara şimdilik dokunma, sırası gelince tek tek açacağız.

  kaynak: ak0010_dahiliLed (D:\Atolye\Arduino\01_arduinoGiris_ak) + portalın Ders 1.1
          kodu (web_v1/script.js, LED_CODE). Kod portaldaki hâliyle korundu — o sürüm
          gerçek öğrenciyle test edildi, teori uğruna değiştirilmedi.
*/

// --- KAVRAM ---
void setup() {
  // setup() içindeki satırlar kart açılınca sadece 1 kez çalışır
}

void loop() {
  // loop() içindeki satırlar setup bitince sürekli baştan tekrar eder
  neopixelWrite(RGBLED, 0, 0, 40); // dahili renkli LED'e renk gönder: kırmızı 0, yeşil 0, mavi 40 -> mavi yanar
  delay(1000);                     // 1000 milisaniye (1 saniye) bekle
  neopixelWrite(RGBLED, 0, 0, 0);  // üç rengin üçü de 0 -> LED söner
  delay(1000);                     // 1 saniye bekle
}

// --- SEN YAP ---
// 1) LED'i mavi yerine yeşil yak. neopixelWrite'taki üç sayıdan hangisini
//    değiştirmen gerekiyor? Değiştir ve çalıştır.
// 2) delay(1000) yazan iki satırdaki 1000 sayısını değiştir; LED'i daha hızlı ya da
//    daha yavaş yakıp söndür.
// 3) İki delay() değerini birbirinden farklı yap (ör. yanma kısa, sönme uzun).
