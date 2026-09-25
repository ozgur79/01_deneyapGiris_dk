/*
  dk0150 — Trafik lambası
  Ne öğreneceğiz: Üç LED'i bir trafik lambası işi için birlikte kullanmak; sürelerin
    kodun anlamını değiştirdiğini görmek
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu, kırmızı LED, sarı LED, yeşil LED
    (setinde yoksa 3 LED yeter, rolleri pin adından ayırt edilir), 3 adet 220 ohm
    direnç, breadboard, 6 jumper kablo (Ders 1.4'ün D5/D6 devresi aynen kullanılır)
  Devre: Kırmızı LED uzun bacak (+) -> D5, kısa bacak (-) -> 220 ohm direnç -> GND
         Sarı LED    uzun bacak (+) -> D6, kısa bacak (-) -> 220 ohm direnç -> GND
         Yeşil LED   uzun bacak (+) -> D9, kısa bacak (-) -> 220 ohm direnç -> GND

  Şimdilik kara kutu (sonra açacağız):
    void    -> "fonksiyon" konusunda açılacak
    OUTPUT  -> buton dersinde, INPUT ile birlikte açılacak
  Bunlara şimdilik dokunma, sırası gelince tek tek açacağız.

  kaynak: ak0070_trafikLambasi (D:\Atolye\Arduino\01_arduinoGiris_ak)
*/

// --- KAVRAM ---
// Her LED'e adıyla sesleniyoruz; sayı yerine renk adını yazmak kodu okumayı kolaylaştırır
// Her adımda üç LED'in de durumunu yazıyoruz: kırmızı uzun, yeşil orta, sarı kısa bekler
const int kirmizi = D5;
const int sari = D6;
const int yesil = D9;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(sari, OUTPUT);
  pinMode(yesil, OUTPUT);
}

void loop() {
  // Dur: kırmızı yanar, diğer iki LED söner
  digitalWrite(kirmizi, HIGH);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, LOW);
  delay(4000);

  // Geç: yeşil yanar, diğer iki LED söner
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, HIGH);
  delay(3000);

  // Hazırlan: sarı yanar, diğer iki LED söner
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, HIGH);
  digitalWrite(yesil, LOW);
  delay(1000);
}

// --- SEN YAP ---
// 1) Süreleri değiştir. Kırmızı daha uzun, sarı daha kısa, yeşil ortada kalacak başka
//    üç sayı seç. Trafik lambasının davranışı nasıl değişti?
// 2) Türkiye'deki sırayı kur: kırmızı -> kırmızı+sarı -> yeşil -> sarı -> kırmızı.
//    Kırmızı+sarı adımında iki LED'i aynı anda HIGH yap. Her adımda üç LED'in de
//    durumunu yazmayı unutma.

// --- MERAK KÖŞESİ ---
// OUTPUT neyi söylüyor? (2. tur)
// Ders 1.4'te (dk0030) OUTPUT'u ikinci bir pin için de yazmıştın: her pin kendi
// görevini kendi pinMode satırında alır. Bu derste üç pine de OUTPUT yazıyoruz, çünkü
// üçünde de yakıp söndürebileceğimiz birer LED var.
// OUTPUT'un daha ayrıntılı açıklaması buton dersinde (INPUT ile birlikte) gelecek.
