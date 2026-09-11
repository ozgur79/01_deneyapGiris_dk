---
dk_no: dk0030
portal_ders: "1.3 — İki LED yarısı"
kaynak_ak: [ak0030, ak0040, ak0050]
baslik: İki LED'i sırayla yak
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.delay
  - hw.gorme-esigi
  - cpp.coklu-cikis
  - hw.coklu-led
  - cpp.const-int
kara_kutu: [void, OUTPUT]
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 2 LED
  - 2 adet 220 ohm direnç
  - breadboard
  - 4 jumper kablo
board:
  kart: Deneyap Mini v2
  birinci_led_pin: "D5"
  ikinci_led_pin: "D6"
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
  seri_hiz: 115200
  pin_notu: "Kodda pinler D5 ve D6 makrolarıyla yazılır; kart üzerindeki D-etiketleri fiziksel GPIO numaraları değildir."
---

## 1. Hedef

dk0020'de kurduğun LED devresi yerinde kalsın. Önce iki `delay()` değerini küçültüp gözünün
artık sönmeyi seçemediği hızı bulacaksın. Sonra ikinci LED'i D6'ya ekleyecek, iki LED'i
birbirinin zıttı durumda çalıştıracak ve pinlere sayı yerine anlamlı isimler vereceksin.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- 2 LED
- 2 adet 220 ohm direnç
- breadboard ve 4 jumper kablo

## 3. Parça tanıtımı

Yeni parça yok. İkinci LED'in de kendi direnci olmalı; iki LED'i tek dirençle bağlamak ikisini
de kararsız ve sönük gösterebilir. Birinci LED D5'te, ikinci LED D6'da çalışacak.

## 4. Devre kurulumu

dk0020'nin D5 devresi duruyorsa sökme. İkinci LED için şunları ekle:

1. İkinci LED'i breadboard'a tak.
2. Uzun bacağını (+) bir jumper kabloyla kart üzerinde **D6** yazan pine bağla.
3. Kısa bacağını (−) ikinci 220 ohm dirence bağla.
4. Direncin öbür ucunu GND'ye bağla.

Metin şeması:

- Birinci LED uzun bacak (+) → D5, kısa bacak (−) → 220 ohm direnç → GND
- İkinci LED uzun bacak (+) → D6, kısa bacak (−) → 220 ohm direnç → GND

## 5. Kod açıklaması

| kod satırı | açıklama |
| --- | --- |
| `const int birinciLed = D5;` | D5 pinine `birinciLed` adı verilir. `const`, bu adın karşılığındaki pinin değişmeyeceğini söyler. |
| `const int ikinciLed = D6;` | D6 pinine `ikinciLed` adı verilir. Kart üzerindeki D-etiketini kullanırız. |
| `void setup() {` | **Kara kutu:** `void`, bu kod bölümünün sonunda bir değer vermediğini anlatır; şimdilik `setup` ve `loop` adlarının önünde durduğunu bilmen yeterli. |
| `pinMode(birinciLed, OUTPUT);` | Birinci LED'in pinini elektrik gönderen çıkış yapar. **Kara kutu:** `OUTPUT`, pinin bilgi almak yerine dışarıya elektrik vereceğini işaretler. |
| `pinMode(ikinciLed, OUTPUT);` | İkinci pin için de ayrı ayar gerekir; iki çıkış birbirinden bağımsızdır. |
| `digitalWrite(birinciLed, HIGH);` ve `digitalWrite(ikinciLed, LOW);` | Birinci LED yanarken ikincisi söner. Buna zıt durum denir. |
| `delay(300);` | Bu zıt durumu 300 milisaniye korur. Sayı küçüldükçe yanıp sönme hızlanır. |
| Sonraki iki `digitalWrite` | Durumlar yer değiştirir: birinci söner, ikinci yanar. |

Bir tam tur iki bekleme sürer. `delay(300)` için tur 600 milisaniyedir. İki LED birer kez
yanıp sönerken gözün bir süre sonra tek tek sönmeleri seçemeyebilir. Buna **görme eşiği**
denir; değişen LED değil, gözün hızlı değişimi ayırabilme sınırıdır. Bu sınır kişiye ve
ortam ışığına göre değişebilir.

### İleri analiz [ileri]

Pin numarasını her kullanımda yazmak yerine bir kez isim vermek, kabloyu taşıdığında yalnız
o isim satırını değiştirmeni sağlar. İsimler kartı yavaşlatmaz; derleme sırasında pin
karşılıklarıyla değiştirilir. `delay()` ise çalışırken programı bekletir; bu nedenle iki LED'e
tamamen bağımsız, farklı ritimler bu derste kurulamaz.

## 6. Çalıştır ve gözlemle

Kodu yüklediğinde birinci LED yanarken ikinci LED sönük kalır; 300 milisaniye sonra yer
değiştirirler. İlk iki `delay()` değerini 100 yapıp aynı gözlemi tekrarla. Gündüz ve akşam
aynı deneyi yaparak gözünün eşiğinin değişip değişmediğini not et.

### Sorun giderme

- **İki LED de hiç yanmıyor** → Kartın kodu aldığını kontrol et; ardından her iki direncin de
  GND'ye ulaştığını denetle.
- **Yalnız bir LED yanıyor** → O LED'in uzun bacağı, direnci ve kendi `pinMode` satırı var mı
  sırayla kontrol et.
- **İki LED aynı anda yanıyor** → Aynı beklemeden önceki iki `digitalWrite` satırında biri
  `HIGH`, öteki `LOW` olmalı.
- **İkinci LED hiç tepki vermiyor** → Devrede kablonun kart üzerinde D6 yazan yerde, kodun ise
  `ikinciLed = D6` olduğundan emin ol.
- **Hızı değiştirdin ama görünüm aynı** → İki `delay()` satırını da değiştirdin mi ve kodu
  yeniden yükledin mi kontrol et.
- **Derleme `was not declared` diyor** → İsim satırını `setup` ve `loop` dışına, en üste yaz;
  kullandığın adı harf harfine aynı yaz.
- **LED'ler çok sönük** → Her LED'in kendi 220 ohm direnci olmalı; tek direnç kullanılmaz.

## 7. Mini sınav

1. [temel] İki LED kullanırken neden iki `pinMode` satırı gerekir?
   - A) Kart iki satır istemeden çalışmaz
   - B) Her LED ayrı bir pin kullandığı için
   - C) Her LED'in iki bacağı olduğu için
   - D) `delay()` iki kez yazıldığı için
   - ipucu: Her pinin ayarı kendine aittir.

2. [temel] Zıt durum ne demektir?
   - A) İki LED aynı anda yanar
   - B) İki LED aynı anda söner
   - C) Biri yanarken diğeri söner
   - D) LED'ler ters takılır
   - ipucu: Kodda birine `HIGH` yazılırken ötekine ne yazılıyor?

3. [temel] `const int ikinciLed = D6;` satırının görevi nedir?
   - A) D6'ya ikinci LED adını verir
   - B) İkinci LED'i hemen yakar
   - C) D6'yı GND yapar
   - D) 6 saniye bekler
   - ipucu: Bu satır `digitalWrite` değil.

4. [temel] `delay()` sayısını küçülttüğünde ne olur?
   - A) LED'ler daha seyrek yanar
   - B) LED'ler daha sık durum değiştirir
   - C) İkinci LED devreden çıkar
   - D) Direncin değeri değişir
   - ipucu: Bekleme süresi kısalıyor.

5. [ileri] LED hızlıyken sürekli yanıyor gibi görünüyorsa gerçekte ne olabilir?
   - A) LED hiç sönmüyordur
   - B) Gözün sönmeleri ayırt edemiyordur
   - C) Kart `delay` satırlarını atlıyordur
   - D) Direnç LED'i açık tutuyordur
   - ipucu: Sınırı koyan parça LED mi, göz mü?

6. [ileri] Birinci LED'in kablosunu D5'ten D6'ya taşırsan, isim kullanan kodda hangi satırı değiştirmek yeterlidir?
   - A) `const int birinciLed = D5;` satırı
   - B) İki `digitalWrite` satırı
   - C) İki `delay` satırı
   - D) Hiçbir satır
   - ipucu: D5 bilgisi kodda nerede bir kez yazıyor?

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme ve
> aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında çalışmıyorsa
> AI yanılmıştır, devren haklıdır.* AI'a pin numarası, direnç değeri, menü yolu veya bağlantı
> tarifi sordurma; bunları dersindeki devre şeması belirler.

### Ders promptları

- [temel] **Zıt durum** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, iki LED ve her biri için 220 ohm direnç kullanıyorum. Kodumda iki
  LED sırayla yanıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme.
  Cevabı doğrudan söylemeden, tahterevalli benzetmesiyle zıt durumun ne olduğunu bulduracak
  tek bir soru sor."
- [temel] **İsim verme** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, iki LED ve her biri için 220 ohm direnç kullanıyorum. Kodumda
  `const int` ile isim veriyorum. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. Cevabı söylemeden, telefon rehberi benzetmesiyle sayıya isim vermenin neden
  işime yarayacağını düşündürecek bir soru sor."
- [ileri] **Görme eşiği** — "Sen meraklı bir rehbersin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, iki LED ve her biri için 220 ohm direnç kullanıyorum. LED'ler çok
  hızlanınca sürekli yanıyor gibi görünüyor. Bana pin numarası, direnç değeri, menü yolu veya
  bağlantı tarifi verme. Cevabı söylemeden, gözün algı sınırı üzerine deney yapmamı sağlayacak
  bir soru sor."

### Kara kutu promptları

- [temel] **`void`** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, iki LED ve her biri için 220 ohm direnç kullanıyorum. Kodumda
  `void setup()` yazıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi
  verme. Cevabı vermeden, `void` kelimesinin kod bölümünün sonunda bir şey verip vermemesiyle
  ilgili olabileceğini düşündürecek bir soru sor; konu ileride açılacak."
- [temel] **`OUTPUT`** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, iki LED ve her biri için 220 ohm direnç kullanıyorum. Kodumda
  `OUTPUT` yazıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme.
  Cevabı vermeden, bir pinin dışarıya elektrik verme veya dışarıdan bilgi alma görevi
  olabileceğini düşündürecek bir soru sor; konu buton dersinde açılacak."

### Yanındaki yetişkine

Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. İki LED'in de uzun bacağı kendi kablosuna, kısa bacağı kendi direncine mi gidiyor?
2. Her LED'in ayrı direnci ve GND bağlantısı var mı?
3. Kodda iki LED için ayrı `pinMode` satırı ve her beklemede zıt `HIGH`/`LOW` durumu var mı?

## 9. SEN YAP

1. İki LED'i zıt değil, birlikte çalıştır: ikisi aynı anda yansın ve aynı anda sönsün.
2. İki `delay(300)` satırını önce `delay(100)`, sonra daha küçük aynı değerlere çevir. Gündüz
   ve akşam hangi değerde sönmeyi ayırt edemediğini not et.
3. `birinciLed` ve `ikinciLed` adlarını kendi LED'lerinin gerçek renklerine göre değiştir.
   Aynı adı kodun hangi yerlerinde değiştirdiğini say.
