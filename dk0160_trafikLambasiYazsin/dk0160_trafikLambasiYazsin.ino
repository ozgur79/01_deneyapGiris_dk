/*
  dk0160 — Trafik lambası rengini yazsın
  Ne öğreneceğiz: Bildiğimiz trafik lambasına (Ders 1.6), yanan rengi bilgisayara
    yazdırma katmanı eklemek
  Malzeme: Deneyap Mini v2 kartı, Type-C USB kablosu, kırmızı LED, sarı LED, yeşil LED
    (setinde yoksa 3 LED yeter), 3 adet 220 ohm direnç, breadboard, 6 jumper kablo
    (Ders 1.6'nın D5/D6/D9 devresi aynen kullanılır)
  Devre: Kırmızı LED uzun bacak (+) -> D5, kısa bacak (-) -> 220 ohm direnç -> GND
         Sarı LED    uzun bacak (+) -> D6, kısa bacak (-) -> 220 ohm direnç -> GND
         Yeşil LED   uzun bacak (+) -> D9, kısa bacak (-) -> 220 ohm direnç -> GND

  Şimdilik kara kutu (sonra açacağız):
    void                    -> "fonksiyon" konusunda açılacak
    OUTPUT                  -> buton dersinde, INPUT ile birlikte açılacak
    Serial ve noktalı yazım -> "fonksiyon" konusunda açılacak (Ders 2.1'de tanıştın)
  Bunlara şimdilik dokunma, sırası gelince tek tek açacağız.

  kaynak: ak0115_trafikLambasiYazsin (D:\Atolye\Arduino\01_arduinoGiris_ak)
*/

// --- KAVRAM ---
// Trafik lambasının bildiğimiz koduna (Ders 1.6), yanan rengi yazan Serial.println satırları ekliyoruz
// Her renk yazısı, o rengin LED durumları ayarlandıktan hemen sonra gönderilir
// Seri Monitör 115200 hızında açılır; LED ile ekrandaki renk adı aynı anda değişir
const int kirmizi = D5;
const int sari = D6;
const int yesil = D9;

void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(sari, OUTPUT);
  pinMode(yesil, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Dur: kırmızı yanar, diğer iki LED söner
  digitalWrite(kirmizi, HIGH);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, LOW);
  Serial.println("KIRMIZI");
  delay(4000);

  // Geç: yeşil yanar, diğer iki LED söner
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, LOW);
  digitalWrite(yesil, HIGH);
  Serial.println("YESIL");
  delay(3000);

  // Hazırlan: sarı yanar, diğer iki LED söner
  digitalWrite(kirmizi, LOW);
  digitalWrite(sari, HIGH);
  digitalWrite(yesil, LOW);
  Serial.println("SARI");
  delay(1000);
}

// --- SEN YAP ---
// 1) Sarı LED'in 1 saniye yerine 2 saniye yanmasını sağla.
// 2) Seri Monitör'deki SARI yazısının da LED ile aynı anda göründüğünü gözlemle.
