# Donanım Referansı — Deneyap Mini v2 (DYMv2)

Kaynak: Deneyap'ın resmi 4 sayfası (Genel Bilgiler, Pin Tanımlamaları, Teknik Özellikler,
Uyarılar) + resmi pin diyagramı — Özgür tarafından 2026-09-03'te verildi.
`🏰 300-Projects/deneyapAtolyem/DYMv2_*.md` dosyalarının birleşimidir.

**Neden bu dosya var:** WebFetch bu projede güvenilmez çıktı verdi. Bundan sonra her
`ders.md`'nin `board:` bloğu **buraya** dayanmalı, tahmine ya da hatırlamaya değil.

---

## Çip ve genel özellikler

- ESP32-S2, tek çekirdek 240MHz Tensilica Xtensa LX7
- 4 MB SPI Flash · 2 MB PSRAM · 320 KB SRAM · 128 KB ROM
- 2.4 GHz Wi-Fi 802.11b/g/n, dahili PCB anten
- Dahili sıcaklık algılayıcı: −20 °C ile +110 °C
- Dahili adreslenebilir RGB LED — **D14**, pin dışarı çıkmıyor, yalnız `neopixelWrite` ile
  sürülür (`digitalWrite` ile çalışmaz — board sızmasının bilinen istisnalarından biri)
- Genel amaçlı buton (**GPKEY**, aynı zamanda **D13**) — sistemi manuel yükleme moduna
  (BOOT) da sokar; 10K pull-up ile lojik "1" (3.3V) seviyesinde tutulur
- Boyut: 50.00 mm × 20.32 mm × 12.96 mm, 6 g (pinler lehimli)
- Genel amaçlı 21 pin (bkz. aşağıdaki sayım notu)

---

## ⚠️ Kaynaklar arası çelişkiler — çözülmeden kullanılmasın

1. **USB konnektör tipi.** `Teknik Özellikler` sayfası **"USB Mikro-B"** yazıyor, ama
   resmi pin diyagramı 7 numaralı öğeyi **"TİP-C USB KONNEKTÖR"** diye etiketliyor ve
   konnektörün çizimi de Type-C şeklinde. dk'nin kendi `malzeme.md`'si de zaten
   **Type-C** kablo listeliyor. **Sonuç: Type-C güvenilir kabul edildi**, "Mikro-B"
   muhtemelen eski bir Deneyap Mini revizyonundan kalma güncellenmemiş metin. `ders.md`
   içinde USB tipi geçerse Type-C yaz, ama fiziksel sette elindeki kartla bir kez
   doğrula.
2. **A7 var mı yok mu.** Pin diyagramı sol sütunda 8 analog pin gösteriyor gibi
   okunabilir (A0…A7), ama üç metin kaynağı da (Pin Tanımlamaları, Teknik Özellikler,
   Uyarılar) tutarlı şekilde **A0–A6 (7 pin)** diyor ve toplamlar da buna göre kapanıyor
   (aşağıdaki sayım notuna bak). **Sonuç: A0–A6 güvenilir kabul edildi, A7 board:
   bloklarında kullanılmasın** — diyagramdaki 8. öğe muhtemelen okuma hatası ya da
   ayrı bir işaretleme, doğrulanmadan derse girmez.

---

## Sayım doğrulaması (iç tutarlılık kontrolü)

- **Analog giriş = 9:** A0–A6 (7) + DA0 + DA1 (2, bunlar da analog giriş olarak
  kullanılabiliyor) = 9 ✓ (`Teknik Özellikler`: "9 x Analog Giriş Pini")
- **Dijital I/O = 21:** D0–D12 (13) + D13/GPKEY (1) + A0–A6'nın dijital kullanımı (7) =
  21 ✓ (`Genel Bilgiler`: "21 adet pin", `Teknik Özellikler`: "21 x Dijital Giriş/Çıkış
  Pini")
- Bu iki toplam yalnız **A0–A6** (A7 değil) varsayımıyla tutuyor — çelişki notundaki
  kararı doğrular.

---

## Pin tablosu (D-etiketi tek doğru referans)

| D-etiketi | Alternatif isim | İşlev | Not |
|---|---|---|---|
| D0 | RX | UART giriş | Kod yüklerken harici bağlantı yapma |
| D1 | TX | UART çıkış | Kod yüklerken harici bağlantı yapma |
| D2 | PWM0 | PWM çıkış | |
| D3 | PWM1 | PWM çıkış | |
| D4 | MOSI | SPI veri çıkış | |
| D5 | MISO | SPI veri giriş | **GPIO39** (fiziksel) — `pins_arduino.h`'den doğrulandı, D-etiketi GPIO numarasıyla örtüşmüyor (bkz. Tuzaklar) |
| D6 | SCLK | SPI clock | |
| D7 | SCL | I2C clock | 10K pull-up; yalnız I2C uyumlu harici bağlantı yapılabilir |
| D8 | SDA | I2C veri | 10K pull-up; yalnız I2C uyumlu harici bağlantı yapılabilir |
| D9 | — | dijital I/O | |
| D10 | SS | SPI seçim | |
| D11 | DA1 | analog çıkış (DAC) | dijital I/O olarak da kullanılabilir |
| D12 | DA0 | analog çıkış (DAC) | dijital I/O olarak da kullanılabilir |
| D13 | GPKEY / BOOT | buton, dijital I/O | 10K pull-up; kod yüklerken harici bağlantı yapma |
| D14 | RGBLED | dahili RGB LED | pin dışarı çıkmıyor, yalnız `neopixelWrite` |
| A0–A6 | T0–T6 | analog giriş + kapasitif algılama | hepsi dijital I/O olarak da kullanılabilir |

Tüm **D0–D12** PWM pini olarak kullanılabilir.

**Tuzak — D-etiketi ≠ GPIO numarası (bu dört sayfada yazmıyor, `pins_arduino.h`'den
bulundu):** ESP32-S2'de kart üzerindeki "D5" yazısı fiziksel olarak GPIO39'dur, GPIO5
değil (Uno'nun aksine). `ders.md`/`.ino` içinde **asla çıplak sayı** (`pinMode(5,...)`)
yazılmaz, her zaman `D` önekli makro (`pinMode(D5,...)`) kullanılır. Bkz.
`🧠 500-Knowledge/ESP32-Deneyap-Pin-Numaralandirma.md` (zihinEv), `dk0020_hariciLed`
denetiminde bulundu.

---

## Elektriksel değerler

- **Lojik seviye:** "0" = 0V, "1" = 3.3V. **5V toleranslı DEĞİL** — 5V sinyal harici
  devreye asla verilmez.
- **5V pin:** doğrudan USB girişine bağlı, 500mA–1000mA kaynak tavsiye edilir, harici
  ünite beslemede kullanılabilir.
- **3V3 pin:** DC-DC dönüştürücü üzerinden 3.3V / 1A çıkış, harici ünite beslemede
  kullanılabilir.
- **ADC:** 13-bit çözünürlük, ~2.60V gerilimde maksimum değer **8191**'i verir (A0–A6,
  DA0, DA1 için geçerli).
- **DAC:** 8-bit çözünürlük (DA0, DA1).

---

## Kod yükleme sırasında dokunulmayacak pinler

- **D13 (BT/GPKEY):** yükleme sırasında harici bağlantı yapılmaz; yükleme bitince
  serbest.
- **TX (D1) / RX (D0):** yükleme sırasında harici bağlantı yapılmaz; UART için
  kullanılmıyorsa yükleme sonrası serbest.
- **SDA (D8) / SCL (D7):** yalnız I2C uyumlu bağlantıya izin var, başka hiçbir harici
  bağlantı yapılmaz.

---

Bağlantılı: `dk-Faz-Talimatlari.md` (Karar 9/11 — board sızması, iki bilinen istisna) ·
zihinEv `🧠 500-Knowledge/Port-Edilebilir-Ders-Paketi.md` ·
zihinEv `🧠 500-Knowledge/ESP32-Deneyap-Pin-Numaralandirma.md`
