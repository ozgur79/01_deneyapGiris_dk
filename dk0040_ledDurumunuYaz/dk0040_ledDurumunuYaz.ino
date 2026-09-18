/*
  dk0040 — LED durumunu Seri Monitör'e yaz
  Malzeme: Deneyap Mini v2, Type-C USB kablosu, 1 LED, 1 adet 220 ohm direnç,
    breadboard, 2 jumper kablo
  Devre: LED uzun bacak (+) -> D5
         LED kısa bacak (-) -> 220 ohm direnç -> GND

  Şimdilik kara kutu:
    void                    -> Kod bölümünün sonunda değer döndürülmediğini belirtir;
                               fonksiyon konusunda tam açılacak.
    OUTPUT                  -> Pinin dışarıya elektrik göndereceğini belirtir;
                               buton dersinde INPUT ile birlikte tam açılacak.
    Serial ve noktalı yazım -> Kartın bilgisayara yazı gönderen hazır aracını kullanır;
                               noktalı yazım fonksiyon konusunda tam açılacak.

  kaynak: ak0110_ledDurumunuYaz
*/

// --- KAVRAM ---
// Kart çalışırken bilgisayara yazı gönderebilir; gönderilen yazıları Seri Monitör gösterir.
// 115200, kart ile Seri Monitör'ün ortak konuşma hızıdır; iki tarafta da aynı olmalıdır.
// Serial.println, tırnak içindeki yazıyı gönderir ve sonraki yazı için yeni satıra geçer.
const int led = D5;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(led, HIGH);
  Serial.println("YANDI");
  delay(1000);

  digitalWrite(led, LOW);
  Serial.println("SONDU");
  delay(1000);
}

// --- SEN YAP ---
// 1) LED'i 2 saniye yanık, yarım saniye sönük bırak.
// 2) YANDI ve SONDU yerine kendi iki kısa durum mesajını yazdır.
// 3) Mesaj satırlarından birini ilgili digitalWrite satırının altından başka yere taşı;
//    ışıkla yazının zamanlamasını gözlemle, sonra satırı eski yerine getir.
