---
dk_no: dk0150
portal_ders: "1.6"
kaynak_ak: [ak0070]
baslik: Trafik lambası
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.const-int
  - cpp.coklu-cikis
  - cpp.delay
  - hw.coklu-led
kara_kutu: [void, OUTPUT]
merak_kosesi: OUTPUT (2. tur)
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 3 LED (varsa kırmızı, sarı, yeşil; aynı renkteyse rolleri pin adından ayırt edilir)
  - 3 adet 220 ohm direnç
  - breadboard
  - 6 jumper kablo
board:
  kart: Deneyap Mini v2
  kirmizi_led_pin: "D5"
  sari_led_pin: "D6"
  yesil_led_pin: "D9"
  pin_notu: "D5/D6 Ders 1.4'ten (dk0030) devam eder. Üçüncü LED için D7/D8 kullanılmadı çünkü I2C'ye ayrılmış (yalnız I2C uyumlu bağlantı); D13 kullanılmadı çünkü GPKEY/BOOT butonuyla paylaşılıyor. D9 genel amaçlı dijital I/O pini olduğu için seçildi. Bkz. Donanim-Referans-DYMv2.md pin tablosu."
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
kaynak_kod: ak0070_trafikLambasi/ak0070_trafikLambasi.ino
---

## 1. Hedef
Ders 1.4'te (dk0030) iki LED'i sırayla yakmış, ismini vermiştin. Bu derste üç LED'i
kırmızı/sarı/yeşil rolleriyle gerçek bir trafik lambası gibi çalıştıracaksın: kırmızı 4
saniye, yeşil 3 saniye, sarı 1 saniye yanacak. Yeni bir kod komutu öğrenmeyeceksin;
önceki derslerde öğrendiklerini tek bir işte birleştireceksin. Sayılar değişince kod
bozulmaz, lambanın anlamı değişir.

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu
- Kırmızı, sarı ve yeşil LED (setinde bu renkler yoksa 3 LED yeter)
- 3 adet 220 ohm direnç
- Breadboard
- 6 jumper kablo

## 3. Parça tanıtımı
Yeni parça yok. Her renk için bir LED ve **kendi 220 ohm direnci** var. Kırmızı LED
durmayı, yeşil LED geçmeyi, sarı LED hazırlanmayı gösterecek. Setinde üç farklı renkte
LED yoksa sorun değil — aynı renkte üç LED de kullanabilirsin, hangisinin hangi rolü
oynadığını koddaki isimden (`kirmizi`/`sari`/`yesil`) ve bağlı olduğu pinden ayırt
edersin.

## 4. Devre kurulumu
Ders 1.4'ün D5/D6 devresi duruyorsa sökme; bu ikisine kırmızı ve sarı rollerini
vereceksin. Üçüncü LED (yeşil) için:
1. Üçüncü LED'i breadboard'a tak.
2. Uzun bacağından (+) bir jumper kabloyla kartın **D9** pinine bağlan.
3. Kısa bacağını (−) üçüncü 220 ohm dirence bağla.
4. Direncin diğer ucunu GND'ye bağla.

Metin şeması:
- Kırmızı LED (+) → D5, (−) → 220 ohm direnç → GND
- Sarı LED (+) → D6, (−) → 220 ohm direnç → GND
- Yeşil LED (+) → D9, (−) → 220 ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `const int kirmizi = D5;` | D5 pinine `kirmizi` adı verilir. İsim verme (`const int`) kavramını Ders 1.4'te görmüştün. |
| `const int sari = D6;` | D6 pinine `sari` adı verilir. |
| `const int yesil = D9;` | D9 pinine `yesil` adı verilir. |
| `pinMode(kirmizi, OUTPUT);` | Kırmızı LED'in bağlı olduğu pin, açılıp kapatılacak çıkış olur. |
| `digitalWrite(kirmizi, HIGH);` | Kırmızı LED'in pini açılır; kırmızı LED yanar. |
| `digitalWrite(sari, LOW);` | Sarı LED'in pini kapanır; sarı LED söner. |
| `digitalWrite(yesil, LOW);` | Yeşil LED'in pini kapanır; yeşil LED söner. |
| `delay(4000);` | Kırmızı ışığın durumu 4000 milisaniye, yani 4 saniye sürer. |
| `delay(3000);` | Yeşil ışığın durumu 3000 milisaniye, yani 3 saniye sürer. |
| `delay(1000);` | Sarı ışığın durumu 1000 milisaniye, yani 1 saniye sürer. |

### İleri analiz [ileri]
Bir adımda yalnız bir LED yanıyor olsa bile üç `digitalWrite` satırı vardır. Bu satırlar
önceki adımdan kalan durumları temizler: yeni adımın resmini baştan çizer.

Başlangıç kodunda kırmızı, yeşil ve sarı için süreler sırasıyla 4000, 3000 ve 1000'dir.
Bu sayılar elektronik bir zorunluluk değildir; projenin kararıdır. Aynı kodda süreleri
değiştirerek daha aceleci ya da daha sakin görünen bir trafik lambası yapabilirsin.

### Merak Köşesi: OUTPUT (2. tur)
Ders 1.4'te (dk0030) ikinci bir pin için de `OUTPUT` yazmıştın: her pin kendi görevini
kendi `pinMode` satırında alır. Bu derste üç pine de `OUTPUT` yazıyoruz, çünkü üçünde de
yakıp söndürebileceğimiz birer LED var. `OUTPUT`'un daha ayrıntılı açıklaması buton
dersinde, `INPUT` ile birlikte gelecek — bu yalnızca ikinci turdu.

## 6. Çalıştır ve gözlemle
Kodu yüklediğinde kırmızı 4 saniye yanar, sonra yeşil 3 saniye yanar, sonra sarı 1
saniye yanar. `loop()` başa dönünce tekrar kırmızı yanar. Gözünle üç sürenin eşit
olmadığını fark et.

### Sorun giderme
- **Hiçbir LED yanmıyor** → Kod karta yüklenmemiş olabilir; `Araçlar > Kart > Deneyap
  Kartlar > Deneyap Mini v2` ve `Araçlar > Port` seçimlerini doğrula.
- **Yalnız bir renk hiç yanmıyor** → O LED ters takılmış olabilir; uzun bacağın pine,
  kısa bacağın dirence gittiğini kontrol et.
- **Renkler yanlış sırada yanıyor** → Kabloların D5, D6 ve D9 sırasını kodla
  karşılaştır. Kırmızı D5, sarı D6, yeşil D9'dadır.
- **LED'ler çok sönük yanıyor** → LED'ler aynı direnci paylaşıyor olabilir; her LED'in
  kendi 220 ohm direnci olmalı.
- **Bir renk diğerlerinden çok kısa ya da uzun yanıyor** → O rengin hemen altındaki
  `delay` sayısını kontrol et.

## 7. Mini sınav
1. [temel] `const int sari = D6;` satırı ne yapar?
   - A) Sarı LED'i 6 saniye yakar
   - B) D6 pinine `sari` adını verir
   - C) 6 LED'i aynı anda yakar
   - D) Sarı LED'i kapatır
   - ipucu: Bu satırdaki isim bir süre değil, pin adıdır.

2. [temel] Kırmızı ışık yanarken sarı ve yeşil LED'e ne yazılır?
   - A) İkisine de `LOW`
   - B) İkisine de `HIGH`
   - C) Birine `HIGH`, birine `LOW`
   - D) Hiçbir şey yazılmaz
   - ipucu: Her adımda üç LED'in de durumu yazılır.

3. [temel] `delay(1000);` kaç saniye bekletir?
   - A) 10 saniye
   - B) 100 saniye
   - C) 1 saniye
   - D) Hiç bekletmez
   - ipucu: 1000 milisaniye 1 saniyedir.

4. [ileri] Kırmızı ışığın 4 saniye yerine 6 saniye yanması için hangi satırı
   değiştirmelisin?
   - A) `delay(4000);` satırını `delay(6000);` yapmalısın
   - B) `pinMode(kirmizi, OUTPUT);` satırını silmelisin
   - C) `digitalWrite(sari, LOW);` satırını `HIGH` yapmalısın
   - D) `const int kirmizi = D5;` satırını değiştirmelisin
   - ipucu: Süreyi belirleyen satır `delay` ile başlar.

5. [ileri] Kırmızı+sarı adımından sonra yeşile geçerken kaç `digitalWrite` satırının
   değeri değişir?
   - A) 1
   - B) 2
   - C) 3
   - D) Hiçbiri
   - ipucu: Her adımda üç LED'in de durumu yazılır; hangilerinin durumu gerçekten
     farklı?

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı sana devrenin nasıl kurulacağını, hangi pine
> bağlayacağını ya da hangi direnci kullanacağını **söylemez** — bunlar zaten bu derste
> yazıyor. **AI'ın dediği devrende/kartında çalışmıyorsa AI yanılmıştır, devren
> haklıdır.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6'daki Sorun giderme
> ve aşağıdaki "Yanındaki Yetişkine" kartıyla tamamlayabilirsin.

### Ders promptları
- [temel] **Süreler** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5'te kırmızı, D6'da sarı, D9'da yeşil LED ve her
  biri için 220 ohm direnç kullanan bir trafik lambası yaptım. Süreleri değiştirmek
  istiyorum. Bana pin numarası, direnç değeri veya bağlantı tarifi verme; sayı da
  verme. Kırmızının uzun, sarının kısa kalması için hangi `delay` satırlarını
  karşılaştırmam gerektiğini sorularla buldur."
- [temel] **Kod okuma** — "Sen bir kod okuma koçusun. Deneyap Mini v2'de D5, D6 ve
  D9'a bağlı üç LED'im var; kodumda her adımda üç `digitalWrite` satırı yazıyorum. Bana
  pin numarası veya bağlantı tarifi verme. Önceki adımdan kalan bir LED durumunun
  sonraki adımı neden etkileyebileceğini sorularla fark ettir."
- [ileri] **Birlikte yanma** — "Sen ileri seviye bir mentorsun. Deneyap Mini v2'de
  kırmızı, sarı ve yeşil LED'li trafik lambama kırmızı+sarı adımını eklemek istiyorum.
  Pin numarası, direnç değeri veya bağlantı tarifi verme. Her LED'in o adımdaki
  durumunu kendim bulmam için 'hangileri yanacak, hangisi sönecek' diye sorular sor."

### Yanındaki yetişkine
Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. LED'in uzun bacağı doğru yöne mi bakıyor?
2. Koddaki renk adıyla (kirmizi/sari/yesil) kablonun bağlı olduğu pin (D5/D6/D9)
   uyuşuyor mu?
3. Her LED'in kendi direnci var mı?

Üçü de doğruysa birlikte gözlem yapın.

### Kara kutu promptları
- [temel] **`void` nedir?** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında üç LED'le bir trafik lambası yazdım, `void setup()` ve `void loop()`
  görüyorum. Bana pin numarası, direnç değeri veya bağlantı tarifi verme. Cevabı
  vermeden, `void`'in bir şeyin olup olmadığını mı yoksa bir şeyin nasıl davranacağını
  mı anlattığını düşündürecek bir soru sor; konu ileride tam açılacak."
- [temel] **`OUTPUT` nedir?** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında üç pine de `pinMode(..., OUTPUT)` yazdım. Bana pin numarası, direnç değeri
  veya bağlantı tarifi verme. Cevabı vermeden, bir pinin dışarı elektrik verme ya da
  dışarıdan bilgi alma görevi olabileceğini düşündürecek bir soru sor; konu buton
  dersinde açılacak."

## 9. SEN YAP
1. Süreleri değiştir. Kırmızı daha uzun, sarı daha kısa, yeşil ortada kalacak başka üç
   sayı seç. Trafik lambasının davranışı nasıl değişti?
2. Türkiye'deki sırayı kur: kırmızı → kırmızı+sarı → yeşil → sarı → kırmızı.
   Kırmızı+sarı adımında iki LED'i aynı anda `HIGH` yap. Her adımda üç LED'in de
   durumunu yaz.
