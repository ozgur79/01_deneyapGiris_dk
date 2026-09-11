# Backlog

- **Tur 02 teslim edildi:** `dk0030_ikiLed`, Özgür tarafından 2026-09-11'de derlendi ve
  kartta çalıştı. Kaynak paketi ardışık `ak0030` + `ak0040` + `ak0050`; iki LED D5/D6 ve
  `const int` isimleriyle çalışır.

- **Açık soru:** dk0010'daki `pinMode(LED_BUILTIN, OUTPUT)` satırı korunuyor. Özgür'den
  `LED_BUILTIN` ile `RGBLED` ilişkisinin kart düzeyinde cevabı gelmedi; test edilmiş kod
  teori uğruna değiştirilmeyecek.

- Faz 0 (kurulum) tamamlandı ve denetlendi. Üç düzeltme uygulandı (AGENTS.md sync atfı,
  malzeme listesi, ardışıklık kuralı).
- **Tur 01 denetlendi, bir düzeltmeyle onaylandı — commit'e hazır.** İş emri:
  `girdi/tur-01-ak0020.md`. `ak0020_hariciLed` → Deneyap `dk0020_hariciLed`
  (portal Ders 1.2). Üretilen dosyalar: `dk0020_hariciLed/dk0020_hariciLed.ino`,
  `dk0020_hariciLed/ders.md`, `cozumler/dk0020_hariciLed/dk0020_hariciLed.ino`.
  Kart farkları: **D5** pini (portal taslağından, Özgür donanımda doğrulayacak),
  3.3V, 220 ohm. `digitalWrite` bu derste ilk kez öğretiliyor (Ders 1.1'de
  `neopixelWrite` görülmüştü, `digitalWrite` değil). `const int` kullanılmadı
  (ak0050'ye ait, atlama olur).
- **Düzeltme (Ortak tarafından doğrudan uygulandı, commit öncesi, tamamlandı):** kod
  çıplak `pinMode(5, ...)`/`digitalWrite(5, ...)` kullanıyordu. Deneyap Mini v2'de
  D-etiketleri GPIO numarasıyla örtüşmüyor — `pins_arduino.h`'de `D5 = GPIO39`. Çıplak
  `5` yazılırsa kart GPIO5'i sürer, board üzerinde "D5" yazan pini değil; LED donanımda
  hiç yanmazdı. Dört yerde düzeltildi: `.ino` (kod + yorumlar + SEN YAP), `ders.md`
  (frontmatter `harici_led_pin: "D5"` + açıklama notu, §4/§5/§6/§7/§8/§9), `cozumler/.ino`
  — §8'deki kara kutu promptu da dahil, hiçbir çıplak `5`/`6` kalmadı (grep ile doğrulandı).
  Kalıcı kural `CLAUDE.md`/`AGENTS.md` Tuzaklar bölümüne yazıldı — bkz.
  `🧠 500-Knowledge/ESP32-Deneyap-Pin-Numaralandirma.md`.

## 2026-09-06 — ak'den gelen ve portalla ilgili maddeler

- **PORTALDA OLASI HATA — bildirilecek (yüksek öncelik).** `web_v1/assets/js/lesson-1-2.js`
  Ders 1.2'nin kodu `const int LED_PIN = 5;` yazıyor — **çıplak sayı**. Aynı dersin
  Adım 3 metni ise LED'in **D5** pinine bağlanacağını söylüyor. Deneyap Mini v2'de
  (ESP32-S2) kart üzerindeki "D5" etiketi fiziksel olarak **GPIO39**'dur, GPIO5 değil
  (`pins_arduino.h`; bkz. `Donanim-Referans-DYMv2.md` pin tablosu ve Tuzaklar).
  Yani metin D5 diyor, kod GPIO5 sürüyor — çocuk devreyi metne göre kurarsa LED yanmaz
  ve evde bu hatayı ayıklayamaz. Bizim `dk0020_hariciLed.ino` doğru: `pinMode(D5, OUTPUT)`.
  **Arda/Alfred'e iletilecek**, dayatma değil bulgu olarak.
- **AI Yoldaşı doktrini yürürlükte** (ak `CLAUDE.md`'de tam metin): üç katmanlı destek,
  dört parçalı prompt (rol + `board:` bağlamı + görev + "cevabı verme"), AI asla pin/
  direnç/bağlantı söylemez, "devren haklıdır" sabit notu, §6'da en az 3-5 ayrı semptom,
  §8'e "Yanındaki Yetişkine" kartı.
- **Seri hız dk'de 115200** (Arduino tarafı 9600). Özgür 2026-09-06'da teyit etti;
  board'a özgü gerçek olduğu için `board:` bloğuna girer.
- **"Arkadaşınla karşılaştır" ifadeleri porte edilirken uyarlanır.** ak0030 SEN YAP 3 ve
  ak0040'ın AI promptları sınıf bağlamı varsayıyor; evde arkadaş yok. Aile bireyiyle ya
  da kendi tekrarıyla (gündüz/akşam) değiştirilir.
- **Adım 4 (devre kurma) videosu Arda'nın işi** — Özgür 2026-09-06'da netleştirdi.
  Bizden içerik beklenmiyor, takip maddesi olarak duruyor.

## 2026-09-06 — Deneyap tarafı denetimi + dk0010/dk0020

**Yapılanlar**

- **dk0010_dahiliLed üretildi** (portal Ders 1.1 karşılığı). Daha önce **hiç yoktu** —
  dk klasöründe sadece dk0020 vardı. Kaynak: `ak0010_dahiliLed` + portalın Ders 1.1
  kodu (`web_v1/script.js`, `LED_CODE`). **Kod portaldaki hâliyle korundu**, teori
  uğruna değiştirilmedi: o sürüm gerçek öğrenciyle test edilmiş, bizimki edilmedi.
- **dk0020_hariciLed §8 yeniden yazıldı** — AI Yoldaşı doktrinine uyduruldu: promptlara
  `board:` bağlamı gömüldü (Deneyap Mini v2, D5, 3.3V, 220 ohm), hata giderme promptuna
  "bana pin numarası verme" kısıtı eklendi, §8 başına sabit not ("AI'ın dediği devrende
  çalışmıyorsa AI yanılmıştır") ve "AI zorunlu değil" cümlesi girdi, **"Yanındaki
  yetişkine" kartı** eklendi.
- **CLAUDE.md + AGENTS.md**'ye AI Yoldaşı doktrini ve seri hız (115200) kuralı yazıldı.

**Denetimde çıkan, karar bekleyen maddeler**

- **`cpp.neopixelwrite` kazanım id'si öneriliyor.** dk kendi başına ekleyemez
  (`kazanimlar.md` tek kaynak, ak'de). dk0010'un frontmatter'ında `onerilen_kazanim`
  alanında duruyor. Özgür onaylarsa ak tarafına eklenir.
- **SORU — Ders 1.1'deki `pinMode(LED_BUILTIN, OUTPUT)` satırı gerekli mi?**
  Kod `LED_BUILTIN` pinini çıkış yapıyor ama eylem `neopixelWrite(RGBLED, ...)` ile
  yapılıyor, yani **iki farklı isim** kullanılıyor. `neopixelWrite` adreslenebilir LED'i
  sürer ve normalde `pinMode` gerektirmez. İki ihtimal: (a) `LED_BUILTIN == RGBLED` ve
  satır zararsız ama gereksiz, (b) farklı pinler ve satır alakasız bir pini çıkış
  yapıyor. **Kartta doğrulanmalı** — Arda/Alfred'e soru olarak iletilecek. Bu doğrulanana
  kadar satır dk0010'da **korundu** (test edilmiş koddan teori uğruna sapılmaz).
- **Yakınsama tespiti (bilgi):** portalın Ders 1.1'indeki AI promptlarından ikisi
  (Prompt 2.1 frekans hesabı, Prompt 2.2 gözün algı sınırı) bizim **ak0030 (eşik)**
  dersimizin tam konusu. Arda aynı fikri prompt olarak, biz ders olarak kurmuşuz.
  dk0010'un `[ileri]` bloğuna ve §7'ye bu bağ eklendi.

**Sıradaki port turları (ak'de hazır, dk'ye geçmedi):** ak0030 (hız/eşik) · ak0040
(iki LED) · ak0050 (`const int`) · ak0060 (kara şimşek). ak0030 ve ak0040'ta
"arkadaşınla karşılaştır" ifadeleri var, port sırasında uyarlanacak.

## 2026-09-06 (oturum kapanışı) — Özgür'ün kararları

- **dk0010 ve dk0020 gözden geçirildi, "şimdilik olmuş görünüyor" (Özgür).** Bu bir
  **inceleme onayı**, kart testi değil — dk kuralı gereği bir ders Özgür kartta test
  edene kadar bitmiş sayılmaz. Bu yüzden **commit atılmadı**; `Test-Gunlugu.md`'de ikisi
  de "teste hazır" olarak duruyor. Kartta denendikten sonra commit'lenecek.
- **`cpp.neopixelwrite` ak havuzuna EKLENMEDİ (Özgür):** *"neopixelWrite'ın ak'de yeri
  yok, Arduino farklı bir ekosistem."* Yerine **ikinci havuz açıldı**: `kazanimlar-dk.md`,
  yalnız Deneyap'a özgü id'ler için, `dk.` önekiyle. dk0010 artık `dk.neopixelwrite` ve
  `dk.rgb-karisim` kullanıyor. Ortak kavramlar hâlâ ak'nin havuzundan geliyor —
  sınır kuralı `CLAUDE.md`/`AGENTS.md`'de.
- **ak geriye dönük güncellenmeyecek (Özgür).** AI Yoldaşı doktrini ak0060'tan itibaren
  geçerli; ak0010-ak0050'nin §8'leri eski hâliyle kalıyor. **Sonuç dk'ya iş çıkarıyor:**
  o beş ders porte edilirken board bağlamlı promptlar, "Yanındaki yetişkine" kartı ve
  sabit not **dk tarafında** yazılacak — kaynak `ders.md`'de olmayacak, dk üretecek.
