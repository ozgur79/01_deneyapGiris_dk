/*
  dk0130 — LED'i hızlandır
  Ne öğreneceğiz: Yanıp sönmeyi hızlandırmanın bir sınırı vardır; o sınırdan sonra göz
    sönmeyi ayırt edemez ve LED sürekli yanıyormuş gibi görünür
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu, 1 LED, 1 adet 220 ohm direnç,
    breadboard, 2 jumper kablo (Ders 1.2'nin devresi aynen kullanılır, sökmene gerek yok)
  Devre: LED'in uzun bacağı (+) -> Deneyap Mini v2 D5 pini
         LED'in kısa bacağı (-) -> 220 ohm direnç -> Deneyap Mini v2 GND

  Şimdilik kara kutu (sonra açacağız):
    void    -> "fonksiyon" konusunda açılacak
    OUTPUT  -> buton dersinde, INPUT ile birlikte açılacak
  Bunlara şimdilik dokunma, sırası gelince tek tek açacağız.

  kaynak: ak0030_hizliLed (D:\Atolye\Arduino\01_arduinoGiris_ak)
*/

// --- KAVRAM ---
// delay() içindeki sayı milisaniye cinsindendir: 1000 bir saniye, 500 yarım saniyedir
// delay() içindeki sayı küçüldükçe LED daha sık yanıp söner
// Bir tam tur (bir yanma + bir sönme) iki delay() sürer: 500 + 500 = bir saniye,
// yani LED saniyede 1 kez yanıp sönüyor
void setup() {
  pinMode(D5, OUTPUT); // D5 pinini, açıp kapatabileceğimiz bir pin yap
}

void loop() {
  digitalWrite(D5, HIGH); // D5 pinine gerilim gönder -> LED yanar
  delay(500);             // yarım saniye yanık kal
  digitalWrite(D5, LOW);  // D5 pininin gerilimini kes -> LED söner
  delay(500);             // yarım saniye sönük kal
}

// --- SEN YAP ---
// 1) LED'i sırayla şu hızlarda yakıp söndür. Her hız için iki delay() satırındaki sayıyı
//    İKİSİNİ BİRDEN değiştir, karta yükle ve LED'e bak:
//       saniyede  1 kez  ->  delay(500)
//       saniyede  5 kez  ->  delay(100)
//       saniyede 10 kez  ->  delay(50)
//       saniyede 25 kez  ->  delay(20)
//       saniyede 50 kez  ->  delay(10)
// 2) Hangi hızdan sonra LED'in söndüğünü artık göremiyorsun, sürekli yanıyor gibi
//    görünüyor? O hızı defterine yaz.
// 3) Bulduğun hızı bir aile bireyinle karşılaştır, ya da aynı denemeyi kendin gündüz ve
//    akşam tekrarla. Aynı hızı mı buldun?

// --- MERAK KÖŞESİ ---
// void ne demek?
// setup ve loop birer "iş listesi". void, listenin adının önünde durur ve "bu liste
// bitince geriye bir sonuç vermeyecek" der. Bu derste listelerin içindeki sayıyı
// değiştirdin, adlarına hiç dokunmadın.
// Listenin kendisini ileride "fonksiyon" dersinde tam açacağız.
