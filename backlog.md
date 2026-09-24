# Backlog

- [ ] **12 modüllü portal yeniden numaralandırma + dk0120'nin meydan okumadan
  standart derse dönüşü (2026-09-24):**
  - Portal-Ders-Haritasi.md 12 modüllü yapıya taşındı (Özgür kararı, tam
    gerekçe dosyanın içinde: müfredat 100'ü aşan derse büyüdü). Tüm dk
    derslerinin `portal_ders`/`portal_ders_not` alanları güncellendi:
    dk0010 1.1 (değişmedi) · dk0020 1.2 (değişmedi) · dk0030 1.3→1.4 ·
    dk0040 1.4→2.1 · dk0050 2.1→3.1 · dk0060 3.1→6.1 · dk0070 3.2→6.2 ·
    dk0080 4.1→7.1 · dk0090 4.2→8.1 · dk0100 4.3→8.2 · dk0110 5.1→9.1 ·
    dk0120 5.2→9.2. dk0110'un `onkosul` alanındaki eski "portal 1.6" göndermesi
    (ders.md + .ino), yeni şemada `for`/döngüler dersinin artık sabit bir
    numarası olmadığı için "Modül 2 aday bandı" diye güncellendi.
  - `dk0120_daireVeSRota` **meydan okuma formatından geri alındı.** Özgür
    dokuz bölümlü standart ders istedi. Ana `.ino` artık tek bir yay çizen
    basit bir kod (`hizIc=10`/`hizDis=18`, başlangıç değeri); büyük daire/
    küçük daire/S rota §9 SEN YAP'ta kademeli görevler, çözümleri
    `cozumler/`'de. `cozumler/`'deki eski kod Özgür'ün testinde "olmamış"
    çıktı (küçük dairedeki %3 iç hız şüpheli, muhtemelen tekerlek dönmüyordu);
    yeni çözüm dosyası tüm sayıları "BAŞLANGIÇ DEĞERİ — kalibre et" diye
    işaretler, doğrulanmış değer uydurulmadı — Özgür'ün yeni testini bekliyor.
  - Test-Gunlugu.md güncellendi (dk0120 satırı "SEN YAP biçimine çevrildi,
    test bekliyor"). Commit atılmadı.

- [ ] **Numara yer değiştirme + meydan okuma dönüşümü + %20 uyarısı (2026-09-24):**
  Özgür'ün test sonuçlarına göre (dk0090/dk0100 %20 ile onaylandı, dörtgen/üçgen
  onaylandı, daire+S rota "olmamış"):
  - `dk0120_dortgenUcgen` → `dk0110_dortgenUcgen` (portal 5.1), `dk0110_daireVeSRota`
    → `dk0120_daireVeSRota` (portal 5.2). Klasör, `cozumler/` ve `.ino` adları,
    `dk_no`/`portal_ders` alanları, iki dersin birbirine yaptığı göndermeler
    (`dk0110`'da artık dk0100'ün pivot dönüşüne, `dk0120`'de dk0110'a gönderme
    var) güncellendi. Eski `dk0120_dortgenUcgen`/`dk0110_daireVeSRota` klasör
    adları repoda kalmadı (grep ile doğrulandı, yalnız Test-Gunlugu/backlog'da
    tarihsel not var).
  - `dk0120_daireVeSRota` (artık bu ad) **meydan okuma (challenge)** formatına
    çevrildi: adım adım ders değil; ders.md hedef + ipuçları + iskelet kod +
    "yanındaki yetişkine" + AI Yoldaşı (meydan-okuma uyumlu, cevap vermeyen)
    yapısında. Ana `.ino` bir iskelet (TODO blokları, çalışır ama hareket
    üretmez); tam çözüm yalnız `cozumler/dk0120_daireVeSRota`'da.
  - dk0090, dk0100, dk0110, dk0120'nin dördünde de §1 Hedef'te ya da kod
    başındaki yorumda "araç en fazla %20 hızla gider, ... ama 70'i geçme"
    cümlesi eklendi (portal bir tadım dilimi, öğrenci önceki dersleri görmemiş
    olabilir gerekçesiyle).
  - Test-Gunlugu.md ve backlog.md güncellendi. Commit atılmadı.

- [ ] **SORU — Ortak'a: `for` için ak kazanım id'si açılmalı mı? (2026-09-24)**
  `dk0110_dortgenUcgen` (eski adı `dk0120_dortgenUcgen`), `for` döngüsünü kara
  kutu OLARAK DEĞİL, önkoşul (portal 1.6, Döngüler) olarak kullanıyor.
  `D:\Atolye\Arduino\01_arduinoGiris_ak\kazanimlar.md` kontrol edildi,
  `for`/döngü için hiçbir id yok. İş emri "yeni id uydurma, soru olarak yaz"
  dediği için buraya yazıldı — yeni id **açılmadı**. Karar Özgür'e/Ortak'a ait.

- [ ] **Oturum 4 dersleri yazıldı, teste hazır (2026-09-24):** İş emri
  `is-emri-dk-oturum4.md` (zihinEv/Ortak) uygulandı.
  - `dk0100_legoArac` → `dk0100_kumandaSagaSola` (4.3) olarak yeniden
    yazıldı: eski `cozumler/dk0100_legoArac`'taki X-ekseni pivot dönüş kodu
    artık dersin **ana kodu**; `saveEsik` yazım hatası `sagaEsik` olarak
    düzeltildi. LEGO/powerbank/montaj bilgileri eski dk0100'den taşındı.
  - `dk0110_daireVeSRota` (5.1, kumandasız, sabit kod): iki tekerlek farklı
    hızda döndürülerek büyük daire → küçük daire → S rota çizdiriliyor.
    Tüm hız/süre sayıları **başlangıç değeri** olarak işaretlendi, uydurulmadı.
  - `dk0120_dortgenUcgen` (5.2, kumandasız): önce "90° dönmek kaç ms sürüyor"
    kalibrasyonu, sonra `for` ile dörtgen (4×90°) ve üçgen (3×120°, dış açı).
    `for` bu derste kara kutu değil, önkoşuldur (yukarıdaki soru maddesine bak).
  - Üçünün de `.ino` + `ders.md` + `cozumler/` dosyaları var. `Portal-Ders-Haritasi.md`
    (Ortak tarafından güncellendi) tek kaynak olarak kullanıldı.
  - **Ek talimat aynı oturumda uygulandı (Özgür, çok sert hareket geri
    bildirimi):** `dk0090`/`dk0100`'de `maxHiz`/`donusHizi` 70'ten 20'ye
    düşürüldü; `map`'in hedef aralığı 0-100'den doğrudan 0-`maxHiz`'e
    değiştirildi (kaynaktan bilinçli sapma, gerekçesiyle kod yorumunda ve
    ders.md'de yazılı). `dk0110`/`dk0120`'deki başlangıç hızları da 20'yi
    geçmeyecek şekilde güncellendi. `%70` (donanımsal) ile `%20` (güvenlik)
    sınırları ders.md'lerde ayrı ayrı açıklandı. `malzeme.md`'ye 3D basılı
    LEGO tabla (7x11 frame) ve kumanda kolu/motor sürücünün taktığı 5x7
    frame bilgisi eklendi; dk0100'ün montaj yer tutucusu bu bilgiyle
    kısmen dolduruldu, adım sırası hâlâ Özgür'den bekleniyor.
  - `Test-Gunlugu.md` güncellendi: dk0090/dk0100 "çalışıyor ama sert, hız
    düşürüldü, yeniden test gerekiyor" olarak işaretlendi; dk0110/dk0120
    için yeni "teste hazır" satırları açıldı.
  - Çıplak pin taraması yapıldı (aşağıda rapor edilecek). Commit atılmadı.

- [ ] **Oturum 3 dersleri yazıldı, teste hazır (2026-09-24) — kısmen güncel değil,
  bkz. Oturum 4 maddesi yukarıda:** `dk0100_legoArac`, Oturum 4'te
  `dk0100_kumandaSagaSola` olarak yeniden adlandırıldı/yazıldı; bu maddedeki
  `dk0100_legoArac` referansları artık geçerli değil. İş emri
  `is-emri-dk-oturum3.md` (zihinEv/Ortak) uygulandı — `dk0080_motorSurucu`
  (4.1, motor sürücü tek başına), `dk0090_kumandaIleriGeri` (4.2, kumanda kolu →
  motor yön/hız, kaynağın birebir öğretim hâli) ve `dk0100_legoArac` (5.1,
  LEGO araç — kod dk0090 ile aynı). Üçünün de `.ino` + `ders.md` +
  `cozumler/` dosyaları var. `dk0100`'ün SEN YAP görevi (X ekseniyle yerinde
  dönüş) `cozumler/dk0100_legoArac`'ta ayrı bir kod olarak çözüldü; bu kod
  kaynakta yoktu, dk tarafından tasarlandı ve **hiç kartta denenmedi**
  (`MOTOR1=sol/MOTOR2=sağ` varsayımı doğrulanmalı). `dk0100`'ün LEGO montaj
  adımları Özgür'den bekleniyor, yer tutucu bırakıldı — uydurulmadı.
  Powerbank'ın karta bağlantısı (Type-C USB) Özgür tarafından oturum
  içinde teyit edildi ve `malzeme.md` + `dk0100/ders.md`'ye işlendi.
  `Test-Gunlugu.md`'de dört "teste hazır" satırı açıldı. Çıplak pin taraması
  yapıldı, sıfır sonuç (bu üç ders yalnız I2C adresi kullanıyor, dijital pin
  yok). Commit atılmadı — Ortak denetleyecek, sonra Özgür kartta test edecek.

- [x] **Oturum 2 donanım/doğrulama açığı — kapandı (Özgür, 2026-09-24):**
  Kumanda kolu karta I2C kablosuyla bağlanır; kablo Deneyap Mini v2'deki ve
  kumanda kolundaki I2C soketlerine takılır (SDA/SCL'e tek tek jumper
  çekilmez), adres `0x1A`. `dk0060`/`dk0070` §4 (ve ilgili sorun giderme/
  yetişkin kartı satırları) bu bilgiyle güncellendi.

- [x] **Pedagojik revizyon:** `dk0050`'nin dokuz bölümlü öğretim akışı
  `dk0060` ve `dk0070`'ye uygulandı: kavram yorumları, satır satır
  açıklama, kara kutu promptları, belirtiye göre sorun giderme,
  ipuçlu sınav ve kademeli `SEN YAP` görevleri genişletildi.
  `cozumler/` dosyaları görev yanıtlarını içerir. Kodun temel davranışı
  korunur; kullanıcı kart testinin geçtiğini bildirdi.

- [x] **Oturum 2 portal numarası açık — kapandı (Özgür, 2026-09-24):** Tek kaynak artık
  `Portal-Ders-Haritasi.md`. `dk0060` = `3.1`, `dk0070` = `3.2`. Frontmatter'daki
  `portal_ders` ve `portal_ders_not` alanları güncellendi.

- [x] **Oturum 2 dersleri yazıldı (2026-09-23; kart testi sonradan geçti):** `dk0060_joystickOku`
  ana kaynak olarak `arsiv/200kkDegerleriniSeriPorttanOkuma.ino` kullanır; dahili LED dosyası
  yalnız yardımcı kaynaktır. `dk0070_joystickLedParlaklik` kümülatif D5 harici LED devresini
  korur ve 540 → 0–255 eşlemesini kaynak davranışıyla taşır. Test günlüğüne iki teste hazır
  satır eklendi. Bu, test öncesi teslim kaydıdır; sonraki test sonucu yukarıda kayıtlıdır.

- [x] **`portal_ders` (dk0050) — Ortak çözdü, 2026-09-21:** Özgür'ün kararıyla yeni modül
  açıldı — **Modül 2: Dijital Giriş / Sensörler**
  (`zihinEv/🏰 300-Projects/deneyapAtolyem/Modul2-Mufredat.md`). dk0050 = **2.1**.
  `ders.md` frontmatter'ı güncellendi (`portal_ders: "2.1"`). dk'nin bu alana dokunmasına
  gerek yok, doldu.

- **İlk dilim / Oturum 1, ders 3 tamamlandı (2026-09-18):** Seri port dersi
  `dk0040_ledDurumunuYaz` kartta test edildi, onaylandı; portal karşılığı `1.4`,
  kaynak `ak0110`.

- **Tur 02 teslim edildi:** `dk0030_ikiLed`, Özgür tarafından 2026-09-11'de derlendi ve
  kartta çalıştı. Kaynak paketi ardışık `ak0030` + `ak0040` + `ak0050`; iki LED D5/D6 ve
  `const int` isimleriyle çalışır.

- **Kapandı (Özgür, 2026-09-21):** dk0010'daki `pinMode(LED_BUILTIN, OUTPUT)` sorusu
  çözüldü — `neopixelWrite` pini `pinMode`/`digitalWrite` ile değil kendi içinde sürüyor
  (`Donanim-Referans-DYMv2.md`'deki D14/RGBLED notuyla tutarlı), yani satır **işlevsizdi**.
  Çalışma alanında bu satırı (yorum olarak) geri getiren, `OUTPUT`'u kara kutuya ekleyen ve
  rengi kırmızıya çeviren commit'lenmemiş bir deneme bulundu; hepsi geri alındı, dosya
  test edilmiş/commit'li haline (mavi) döndü.

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
  **Kapandı (2026-09-21):** (b) doğru değil, ama gerekçe farklı çıktı — `neopixelWrite`
  pini `pinMode`'dan tamamen bağımsız kendi içinde sürüyor, `LED_BUILTIN`/`RGBLED`
  aynı pin olsun olmasın satır **işlevsiz**. Kod'dan çıkarıldı.
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
