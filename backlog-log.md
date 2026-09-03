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
