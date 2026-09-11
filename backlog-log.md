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
