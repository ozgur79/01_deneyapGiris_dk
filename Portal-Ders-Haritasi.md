---
title: Portal Ders Haritası — Deneyap Atölyem
updated: 2026-09-25
karar: "Özgür, 2026-09-24 — portal_ders numaraları bu dosyadan verilir; 12 modüllü yapıya taşındı"
---

# Portal Ders Haritası

**Bu dosya ne işe yarar:** Her dersin portalda hangi numarayla görüneceğini tek bir
yerde tutar. Zincir: **ak** (Arduino dersi) → **dk** (Deneyap'a uyarlanmış ders, `dk00x0`)
→ **dap** (doğrular, portal formatına çevirir, teslim eder; portala giden tek kapı) →
**Alfred/Arda** (portal).

dk'nin numarası (`dk0010`, `dk0020`…) **üretim sırasıdır** ve hiç değişmez. `portal_ders`
ise **öğrencinin gördüğü sıradır** (`1.1`, `8.2`…). İki numara bilerek birbirinden ayrı
tutulur.

**Kural:** dk, `ders.md` frontmatter'ındaki `portal_ders` değerini **bu tablodan** alır.
Ders burada yoksa alanı `null` bırakır ve Ortak'a sorar. Tahminle numara verilmez.

## 2026-09-24: 12 modüle taşındı

Numaralar önce ilk dilim için 5 modüle göre verilmişti. Müfredat 100'ü aşan derse
büyüyünce (`Mufredat-Tahmini.md`) numaralar 12 modüllü yapıya taşındı. Taşıma ilk dilim
yayına çıkmadan yapıldı. Portalda yayında olan tek dersler **1.1 ve 1.2** ve ikisinin
numarası değişmedi.

**Numara verme yöntemi:** Bir modülün ak planında (Yol-Haritası §5) belli bir sırası
varsa, ders o sıradaki yerini alır. Örneğin "iki LED" 1.4'tür, çünkü ak'de hız
merdiveni dersi ondan önce gelir. Bu yüzden numaralar arasında boşluk kalabilir;
boşluklar henüz üretilmemiş derslerin yeridir. **Yayındaki bir dersin numarası bir daha
değişmez.** Henüz yayına çıkmamış modüllerde yeni ders eklenirse numaralar kayabilir.

**Ana fikir:** LED ile motor mantığı (çıkış), butonla sensör mantığı (giriş) öğretilir;
seri port her modülde "kartın içinde ne oluyor?" sorusunun aracıdır.

| # | Modül | Yeni donanım / kavram | Bağlantı |
|---|-------|------------------------|----------|
| 1 | LED | LED, direnç · dijital çıkış | pin `D<n>` |
| 2 | LED + Seri Port | seri port · döngü, dizi, PWM, `millis()` 1. tur | USB |
| 3 | Buton | buton, pull-down · dijital giriş | pin `D<n>` |
| 4 | Buton + Seri Port | kenar tetikleme, debounce, `millis()` 2. tur | pin + USB |
| 5 | LDR (ayrı modül, Özgür onayladı) | LDR, gerilim bölücü · analog giriş (`analogRead`); kumanda kolunun sayı-eşik-map mantığının temeli | analog pin |
| 6 | Kumanda Kolu | Deneyap Kumanda Kolu | **I2C soket + kablo, `0x1A`** |
| 7 | Motor Sürücü | Deneyap Çift Kanallı Motor Sürücü + 2 LEGO DC motor | **I2C soket, `0x16`**; 2×18650 + çıt çıt anahtar |
| 8 | Robot Araç: Kumanda | aracı kumandayla sürmek | 6 + 7 |
| 9 | Robot Araç: Kodla Rota | rotayı kodla çizdirmek | 7 |
| 10 | Çizgi Algılayıcı | Deneyap Çift Kanallı Çizgi Algılayıcı | I2C |
| 11 | Kablosuz | ESP-NOW (iki kart) | — |
| 12 | LEGO Tema Projeleri | yeni kavram getirmez | — |

## Ders tablosu (üretilenler + kaynağı belli adaylar)

| portal_ders | Ders | dk | Eski no | Durum (2026-09-24) |
|-------------|------|----|---------|--------------------|
| 1.1 | Dahili RGB LED | `dk0010` | 1.1 | ✅ · **portalda yayında** |
| 1.2 | Harici LED devresi | `dk0020` | 1.2 | ✅ · **portalda yayında** |
| 1.3 | LED'i hızlandır (hız merdiveni) | `dk0130` | — | ✅ |
| 1.4 | İki LED | `dk0030` | 1.3 | ✅ |
| 1.5 | Kara şimşek (kod tekrarı) | `dk0140` | — | ✅ |
| 1.6 | Trafik lambası | `dk0150` | — | ✅ |
| 2.1 | LED durumunu seri porta yaz (YANDI/SÖNDÜ) | `dk0040` | 1.4 | ✅ |
| 2.2 | Trafik lambası rengini yazsın | `dk0160` | — | ✅ |
| 2.3+ | sayaç · `for` · `while` · `if`+`%` · rastgele · dizi · PWM · `Serial.read` · `millis()` | — | — | ⬜ ak Ünite 1 |
| 3.1 | Butona basınca LED yansın | `dk0050` | 2.1 | ✅ |
| 3.2+ | iki buton + `&&` · butonla trafik lambası … | — | — | ⬜ ak Ünite 2 |
| 4.1 | Buton durumunu seri porta yaz | — | 2.2 | ⬜ |
| 4.2+ | sayaç · kenar tetikleme · debounce · toggle · uzun basma · `millis()` 2. tur | — | — | ⬜ ak Ünite 3 |
| 5.1 | LDR: ışığı sayıya çevir | — | 2.3 | ⬜ |
| 5.2 | LDR → gece lambası | — | 2.4 | ⬜ |
| 6.1 | Kumanda kolunu oku | `dk0060` | 3.1 | ✅ |
| 6.2 | Kumanda kolu → LED parlaklığı | `dk0070` | 3.2 | ✅ |
| 7.1 | Araç sabit hızla ileri → dur → geri | `dk0080` | 4.1 | ✅ |
| 8.1 | Kumandayla ileri/geri | `dk0090_kumandaIleriGeri` | 4.2 | ✅ (%20) |
| 8.2 | Kumandayla sağa/sola | `dk0100_kumandaSagaSola` | 4.3 | ✅ (%20) |
| 9.1 | Kodla dörtgen ve üçgen (`for`, kalibrasyon) | `dk0110_dortgenUcgen` | 5.1 | ✅ |
| 9.2 | Kodla yay çiz: iki tekerlek, iki hız (SEN YAP: daire, S rota) | `dk0120_daireVeSRota` | 5.2 | 🔧 SEN YAP biçimine çevriliyor |
| 10.x · 11.x · 12.x | çizgi izleyen robot · ESP-NOW tadımı · LEGO tema projeleri | — | — | ❓ `Mufredat-Tahmini.md` |

`const int` (ak0050) ayrı ders değil; 1.4'te (dk0030) işleniyor (Ortak, 2026-09-25).

**İlk dilim (tadım, 12 ders):** 1.1 · 1.2 · 1.4 · 2.1 · 3.1 · 6.1 · 6.2 · 7.1 · 8.1 ·
8.2 · 9.1 · 9.2. Her modülden bir örnek alındığı için aralarda boşluk var. Tam müfredatta
önkoşul dersler (ör. 2.x'teki `for`) robot derslerinden önce gelir; bu yüzden robot
derslerinde önkoşul olarak kullanılırlar, kara kutu yapılmazlar.

## Sabit kurallar

**Güvenlik (Özgür, 2026-09-24):** Robot, çocuğun elinden fırlayıp masadan düşmemelidir.
Kumandalı derslerde hız en fazla **%20** olur ve `map` ile 0–maxHiz aralığına orantılı
dağıtılır. Öğrenciye dersin başında "%20, `maxHiz` satırından değiştirilir, 70'i geçme"
diye açıkça söylenir. Kodla rota çizilen derslerde hız %20'yi geçmez ve araç yerde
çalıştırılır. %70 ayrı bir sınırdır: pil gerilimi yüzünden konmuş donanım sınırıdır.

**Montaj (Özgür, 2026-09-24):** Kart ve breadboard, 3D baskı LEGO uyumlu bir tablayla
LEGO 7x11 frame'e takılır; kumanda kolu ve motor sürücü 5x7 frame'e takılır. Montaj
anlatımının biçimi (video mu, SVG mi) Alfred'e soruldu.

**Çıkarılanlar:** HC-SR04 (5 V sensör, 3,3 V kart; şimdilik yok) · ak'de motor dersi (S7/C).

---

Bağlantılı: `Mufredat-Tahmini.md` · `Modul1-Mufredat.md` / `Modul2-Mufredat.md` (eski 5
modüllü numaralar, tarihsel) · `🏰 300-Projects/arduinoMufredat/Yol-Haritasi.md` §5, §7,
§11–§13 · dk `backlog.md`
