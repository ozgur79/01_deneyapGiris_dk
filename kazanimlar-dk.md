# Kazanımlar — Deneyap'a özgü

**Bu dosya ikinci havuzdur, birinci değil.** Ortak kavramların (setup/loop, delay, değişken,
karar yapısı, döngü...) tek kaynağı hâlâ
`D:\Atolye\Arduino\01_arduinoGiris_ak\kazanimlar.md`'dir — dk oradan **okur**, kopyalamaz,
oraya kendi başına yazmaz.

Burası yalnız **Arduino'da karşılığı olmayan**, Deneyap Mini v2'ye / ESP32 ekosistemine
özgü kazanımlar içindir.

**Açılma gerekçesi (Özgür, 2026-09-06):** dk0010 için `cpp.neopixelwrite` id'si önerildi
ve ak havuzuna eklenmesi istendi. Özgür reddetti: *"neopixelWrite'ın ak'de yeri yok,
Arduino farklı bir ekosistem."* Doğru — ak'nin havuzu Arduino Uno müfredatının kazanım
kaydıdır; oraya hiçbir Arduino dersinde geçmeyecek bir id koymak havuzu kirletir ve
ak'nin müfredat denetimini yanıltır. Ama id'nin bir yerde durması da gerekiyor, yoksa
dk dersleri kazanım kaydı olmadan üretilir. Çözüm: **iki havuz, net sınır.**

## Sınır kuralı

| kazanım nereye ait? | nerede kayıtlı |
| --- | --- |
| Her iki kartta da geçerli kavram (`setup/loop`, `delay`, `pinMode`, `digitalWrite`, `const int`, döngü, karar...) | **ak** — `kazanimlar.md`. dk okur, eklemez. |
| Yalnız Deneyap/ESP32'de var, Arduino müfredatında hiç geçmeyecek | **dk** — bu dosya. |

Tereddütte kalınırsa **ak varsayılandır**. Bir kavram ileride Arduino tarafında da
öğretilecekse burası yanlış yerdir; Özgür'e sorulur.

## Tablo

| id | tanım | ilk öğretildiği ders |
|----|-------|------------------------|
| dk.neopixelwrite | `neopixelWrite(RGBLED, kirmizi, yesil, mavi)` ile kartın dahili adreslenebilir renkli LED'ine üç sayıyla renk gönderilir; üç sayı 0-255 arası parlaklıktır, üçü de 0 ise LED söner | dk0010 |
| dk.rgb-karisim | Üç rengin (kırmızı/yeşil/mavi) farklı parlaklıklarda karıştırılmasıyla başka renkler elde edilir — toplamalı renk karışımı, boya karıştırmaktan farklıdır | dk0010 |

## Önek kuralı

Deneyap'a özgü id'ler **`dk.`** önekiyle yazılır (`cpp.` / `hw.` değil). Sebep: bir
`ders.md` frontmatter'ına bakan kişi, id'nin hangi havuzdan geldiğini önekten anlasın.
`cpp.` ve `hw.` önekleri ak havuzuna aittir, burada kullanılmaz.
