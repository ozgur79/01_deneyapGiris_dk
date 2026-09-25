# Backlog Log

Append-only. Hiçbir şey silinmez.

## 2026-09-03
- Kurulum (Faz 0) tamamlandı: CLAUDE.md, AGENTS.md, backlog.md, backlog-log.md, notes.md,
  cozumler/, Test-Gunlugu.md, malzeme.md, .gitignore, git init, GitHub public repo, ilk
  commit + push.
- Tur 01 (`dk0020_hariciLed`) denetlendi. Özgür Deneyap Mini v2'nin resmi pin
  tanımlamalarını verdi, Ortak kartın gerçek `pins_arduino.h`'sini okuyup doğruladı:
  `D5` etiketi GPIO39'dur, GPIO5 değil. dk'nin ilk taslağı çıplak `pinMode(5, OUTPUT)`
  yazmıştı — bu, kod derlenir ama board üzerinde "D5" yazan pini değil GPIO5'i sürer,
  LED donanımda hiç yanmazdı; hata Faz 3'e (donanım testi) kadar görünmeyecekti. Ortak
  commit öncesi doğrudan düzeltti: `.ino`, `ders.md` (frontmatter + §4/§5/§6/§7/§8/§9),
  `cozumler/.ino` — tüm çıplak `5`/`6` → `D5`/`D6`. Kalıcı kural CLAUDE.md/AGENTS.md
  Tuzaklar'a yazıldı, knowledge notu: `🧠 500-Knowledge/ESP32-Deneyap-Pin-Numaralandirma.md`
  (zihinEv). Tur 01 artık commit'e hazır.
- Tur 01 commit'lendi ve push'landı (`25dd18e`) — `dk0020_hariciLed` + `cozumler/` +
  `kimlik_dk.txt`.
- `Donanim-Referans-DYMv2.md` eklendi — Deneyap'ın 4 resmi sayfası + pin diyagramı tek
  dosyada birleştirildi, bundan sonra her `board:` bloğu buna dayanacak (WebFetch güvenilmez
  çıktı verdiği için). İki kaynak-içi çelişki bulunup dosyada işaretlendi: (1) Teknik
  Özellikler "USB Mikro-B" diyor, pin diyagramı "TİP-C" diyor — Type-C güvenilir kabul
  edildi (diyagram çizimi + dk'nin malzeme.md'si de Type-C diyor), fiziksel sette
  doğrulanmalı; (2) pin diyagramı A7 gösteriyor gibi okunabiliyor ama üç metin kaynağı da
  A0–A6 (7 pin) diyor ve analog(9)/dijital(21) toplamları yalnız A0–A6 ile tutuyor — A7
  board: bloklarında kullanılmayacak.

## 2026-09-06
- **dk0010_dahiliLed üretildi** (portal Ders 1.1). Klasörde daha önce yoktu. Kaynak
  ak0010 + portalın test edilmiş Ders 1.1 kodu; kod aynen korundu.
- **dk0020_hariciLed §8 doktrine uyduruldu** (board bağlamı, "pin verme" kısıtı, sabit
  not, "Yanındaki yetişkine" kartı, "AI zorunlu değil" cümlesi).
- **CLAUDE.md/AGENTS.md**: AI Yoldaşı doktrini (üç katman: §6 Sorun giderme -> yetişkin
  kartı -> AI bonus) + seri hız 115200 + sınıf varsayan ifadelerin uyarlanması kuralı.
- **Açık soru:** Ders 1.1'de `pinMode(LED_BUILTIN, OUTPUT)` gerekli mi — `neopixelWrite`
  ayrı bir isim (`RGBLED`) kullanıyor. Kartta doğrulanacak, Arda'ya soru olarak gidecek.
- **Öneri:** `cpp.neopixelwrite` kazanım id'si (dk önerir, ak ekler).- **Kazanım havuzu ikiye ayrıldı (Özgür kararı).** `kazanimlar-dk.md` açıldı: yalnız
  Deneyap'a özgü, `dk.` önekli id'ler. Ortak kavramların tek kaynağı hâlâ ak. dk0010'un
  frontmatter'ı `onerilen_kazanim` alanından gerçek id'lere geçti.
- **dk0010/dk0020 inceleme onayı aldı, kart testi bekliyor — commit atılmadı.**

## 2026-09-11
- Özgür, dk0010 ve dk0020'nin kart testinden geçtiğini bildirdi. Test-Günlüğü iki ders için
  derlendi/kartta çalıştı alanlarını `evet` olarak kaydetti; sorun yok (`—`).
- Mini sınavlardaki öğrenciye görünen doğru cevap işaretleri kaldırıldı. Cevap anahtarları
  öğretmenAnahtar deposunda ayrı tutuldu ve `python kontrol.py` ile denetlendi.
- Tur 02 için `dk0030_ikiLed` yazıldı: ak0030 + ak0040 + ak0050 ardışık paketi,
  D5/D6 makroları, AI Yoldaşı doktrini ve yetişkin kartı eklendi. Kart testi bekliyor;
  bu turda commit atılmadı.
- Özgür, dk0030'ün 2026-09-11'de derlendiğini ve kartta çalıştığını bildirdi. Test Günlüğü
  güncellendi; sorun yok (`—`).

## 2026-09-18
- Seri port dersi `dk0040_ledDurumunuYaz` (Oturum 1, ders 3) kartta test edildi,
  onaylandı; portal karşılığı `1.4`, kaynak `ak0110`.
- dk0050 kararları geldi: buton sette var (`malzeme.md` güncellendi),
  `cpp.digitalread`/`cpp.if-else`/`hw.buton-devre` ak `kazanimlar.md`'ye eklendi
  (commit `d4a293d`). dk0050 için iş emri Ev'de yazıldı, sırada.

## 2026-09-21
- dk0050 (`dk0050_butonLed`, Oturum 1'in dördüncü ve son dersi) teslim edildi. İş emri
  `D:\zihinEv\🏰 300-Projects\deneyapAtolyem\is-emri-dk0050.md` (Ev'de, Atölye repo'sunda
  değil) uygulandı. `INPUT` bu derste ilk kez gerçek anlamıyla açıldı, `kara_kutu`
  alanından `OUTPUT` çıktı (dk0010'daki söz tutuldu). Devre **harici pull-down direnç**
  (10K ohm) ile kuruldu — kaynak kod `INPUT` yazıyordu (`INPUT_PULLUP` değil) ve
  `digitalRead(...)==1`'i "basılı" sayıyordu, bu yalnız pull-down ile tutarlı.
- İlk teslimde pin ham kaynaktaki gibi **A1/A0** bırakılmıştı. Özgür sordu: "led ve
  buton analog girişlerde, özel bir sebebi var mı, neden dijital girişlerde değil" —
  bu derste `analogRead`/`analogWrite` hiç kullanılmadığından analog pin olmasının
  işlevsel bir gerekçesi yoktu, yalnız ham kaynaktan miras kalmıştı. Özgür kararıyla
  boşta olan **D9 (LED) / D10 (buton)**'a çevrildi — dk0020/dk0030/dk0040 ile tutarlı.
- Özgür kartta test etti, geçti. Test Günlüğü `evet`/`evet` olarak güncellendi
  (`Özgür kartta test etti.`). Oturum 1 (dahili LED · harici LED · seri port · buton-LED)
  tamamen kapandı; Oturum 2 (joystick, ders 5-6) iş emri yazılabilir hâle geldi.
- Açık kalan iki soru backlog.md'ye taşındı: `portal_ders` belirsizliği (Modül 1
  listesinde buton dersine karşılık gelen madde yok) ve `malzeme.md`'deki 10K ohm
  pull-down direncinin sette olup olmadığının teyidi.

## 2026-09-23

- Oturum 2 için `dk0060_joystickOku` ve `dk0070_joystickLedParlaklik` üretildi.
- Birinci dersin ana kaynağı `arsiv/200kkDegerleriniSeriPorttanOkuma.ino` olarak kayda
  geçirildi; `dyminiV2500kkDahiliLedParlaklik.ino` yalnız yardımcı kaynak olarak belirtildi.
- İkinci ders `dyminiV2500kkHariciLedParlaklik.ino` kaynağındaki D5, 0x1A, 540 eşiği,
  0–255 eşlemesi ve 10'dan küçük değerleri sıfırlama davranışını taşır.
- Kesin portal numarası müfredatta verilmediği için iki derste `portal_ders` tahmin edilmedi;
  soru `backlog.md`'ye bırakıldı. İki ders test günlüğüne teste hazır olarak yazıldı.
- Commit atılmadı; kart testi çalıştırılmadı.
- Sonraki kullanıcı bildiriminde iki Oturum 2 dersinin testinin geçtiği belirtildi.
  `Test-Gunlugu.md` iki ders için kullanıcı bildirimi olarak güncellendi;
  asistanın ortamındaki `Deneyap_KumandaKolu.h` eksikliği nedeniyle yerel
  derleme yapılmış gibi gösterilmedi. Joystick'in doğrulanmış bağlantı
  yönergesi ve portal numaraları backlog'da açık kalır.

## 2026-09-25

- **dk0130_hizliLed üretildi** (portal 1.3, "LED'i hızlandır"). İş emri Ortak'tan
  (`D:\zihinEv\🏰 300-Projects\deneyapAtolyem\is-emri-dk0130.md`), Özgür onaylı. Kaynak
  `ak0030_hizliLed`; devre dk0020 ile aynı (LED + 220 ohm, D5). Hız merdiveni
  (1→5→10→25→50/sn) ve "eşiği sen bul" SEN YAP aynen korundu, eşik sayısı hiçbir dosyada
  verilmedi (görme eşiği kişiden kişiye değişir). Kara kutu `[void, OUTPUT]` dk0020 ile
  aynı; ak0030'daki "Merak Köşesi: void (1. tur)" hem `.ino` yorumuna hem `ders.md` §5'e
  eklendi. AI Yoldaşı promptları dk doktrinine göre bağlamlandı. Ortak denetledi, geçti.
- Test sırasında `.ino`'da SEN YAP'ın "saniyede 10 kez" adımı denenmiş, loop()'taki iki
  `delay()` 500'den 50'ye kalmış bulundu — yorumlarla ve ders.md'nin anlattığı ilk hâlle
  (saniyede 1 kez) uyuşmadığı fark edildi, Özgür 500'e geri aldı. Özgür kartta test etti,
  onayladı. `Test-Gunlugu.md` ve `Portal-Ders-Haritasi.md` (1.3 → ✅) güncellendi.
  Commit + push edildi.
- Aynı oturumda **dk0030 küçük düzeltme** (Ortak'tan iletilen, Özgür onaylı, kod
  değişmedi): `portal_ders: "1.4 — İki LED yarısı"` → `"1.4"` (açıklama `portal_ders_not`'a
  taşındı; Alfred artık bu alanı makine olarak okuyor, diğer 12 dk dersi zaten yalnız
  numara kullanıyormuş, taranıp doğrulandı). Görme eşiği tekrarı kısaltıldı: dk0130 (1.3)
  eşiği tam işlediği için dk0030'daki §5/§6/mini sınav ipucu/AI Yoldaşı promptu/§9 SEN
  YAP'taki "gündüz-akşam yeniden deney yap" ritüeli çıkarıldı, yerine "1.3'te bulduğun
  eşiği hatırla/kullan" geri bağlantısı kondu. `kazanimlar`'dan `hw.gorme-esigi`,
  `kaynak_ak`'tan `ak0030` çıkarıldı (`[ak0040, ak0050]` kaldı). `.ino` değişmedi, yeniden
  kart testi gerekmedi. dk0130 ile birlikte commit + push edildi.
- Yeni teslim düzeni not edildi (Özgür, 2026-09-25): dap ara katmanı kalktı, Alfred
  içeriği doğrudan bu depodan (`github.com/ozgur79/01_deneyapGiris_dk`) çekiyor;
  `Portal-Ders-Haritasi.md`'de `portal_ders` alanı olan ve ✅ olan dersler portala girer.
