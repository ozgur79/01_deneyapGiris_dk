# Backlog

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
