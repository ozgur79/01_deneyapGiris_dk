/*
  dk0020 — Çözümler (öğrenciye gösterilmez, sadece kontrol için)

  SEN YAP 1) LED'i ters bağla, ne oluyor gözlemle.
    -> Kod değişmez. LED yönlü bir parça olduğu için ters bağlanınca hiç yanmaz;
       bu satırlar aynen çalışır ama LED karanlıkta kalır.

  SEN YAP 2) Pini D5'ten D6'ya taşı.
    -> Aşağıdaki kod, hem devre (fiziksel kablo D6'ya taşınır) hem kodun HER
       ÜÇ yerinde de (pinMode + iki digitalWrite) D5 yerine D6 yazılmasını gösterir.

  SEN YAP 3) 3 saniye yanık, 1 saniye sönük.
    -> delay(1000) yerine delay(3000) (yanıkken) ve delay(1000) (sönükken) kalır;
       değişen sadece HIGH'tan sonraki bekleme süresi.
*/

// --- Çözüm 2: D5 -> D6 ---
void setup() {
  pinMode(D6, OUTPUT);
}

void loop() {
  digitalWrite(D6, HIGH);
  delay(1000);
  digitalWrite(D6, LOW);
  delay(1000);
}

/*
// --- Çözüm 3: 3 saniye yanık, 1 saniye sönük (D5 üzerinde) ---
void setup() {
  pinMode(D5, OUTPUT);
}

void loop() {
  digitalWrite(D5, HIGH);
  delay(3000);
  digitalWrite(D5, LOW);
  delay(1000);
}
*/
