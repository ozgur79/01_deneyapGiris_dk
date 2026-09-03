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
