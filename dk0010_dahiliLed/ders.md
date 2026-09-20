---
dk_no: dk0010
portal_ders: "1.1"
kaynak_ak: [ak0010]
baslik: Kartın üzerindeki LED'i yakıp söndür
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.setup-loop      # ak havuzu
  - cpp.delay           # ak havuzu
  - hw.dahili-led       # ak havuzu
  - dk.neopixelwrite    # dk havuzu (Deneyap'a özgü)
  - dk.rgb-karisim      # dk havuzu (Deneyap'a özgü)
kara_kutu: [void]
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
board:
  kart: Deneyap Mini v2
  dahili_rgb_led: "D14 — pin dışarı çıkmıyor, yalnız neopixelWrite ile sürülür"
  mantik_gerilimi: 3.3V
  seri_hiz: 115200
kaynak_kod: "web_v1/script.js LED_CODE (portal Ders 1.1) + ak0010_dahiliLed"
---

## 1. Hedef
İlk dersin. Hiçbir şey kurman gerekmiyor: kartın üzerinde hazır duran renkli LED'i
yakıp söndüreceksin. Amaç iki şey — kartın bilgisayarına bağlanıp kod alabildiğini
görmek, ve yazdığın kodun **gerçek dünyada bir şey yaptığını** ilk kez görmek.

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu

Başka hiçbir şey gerekmez. Breadboard, LED, direnç, kablo — hiçbiri bu derste yok.

## 3. Parça tanıtımı
- **Deneyap Mini v2** — üzerinde küçük bir bilgisayar taşıyan kart. Yazdığın kodu
  bilgisayarından alır ve elektriği açıp kapatarak dünyaya bir şey yaptırır.
- **Dahili RGB LED** — kartın üzerinde hazır bağlı, üç renk üretebilen küçük bir LED.
  "RGB" = Red (kırmızı), Green (yeşil), Blue (mavi). Bu LED'in bacakları dışarı
  çıkmadığı için ona kablo takamazsın; sadece kodla konuşursun.
- **Type-C USB kablosu** — kartı bilgisayara bağlar. Hem elektrik verir hem kodu taşır.

## 4. Devre kurulumu
**Bu derste devre yok.** Tek yapman gereken kartı Type-C kabloyla bilgisayarına takmak.

İlk kez bağlıyorsan Arduino IDE'de iki ayarı yapman gerekir:
1. `Araçlar > Kart > Deneyap Kartlar > Deneyap Mini v2` seç.
2. `Araçlar > Port` altında kartın göründüğü portu seç.

Bu iki ayar bir kez yapılır; sonraki derslerde tekrar gerekmez.

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `void setup() {` | `setup()` bloğu başlar. |
| `// setup() içindeki satırlar kart açılınca sadece 1 kez çalışır` | `setup()` içindeki satırlar kart açılınca sadece bir kez çalışır. |
| `void loop() {` | `loop()` bloğu başlar. |
| `// loop() içindeki satırlar setup bitince sürekli baştan tekrar eder` | `loop()` içindeki satırlar `setup()` bitince sürekli baştan tekrar eder. |
| `neopixelWrite(RGBLED, 0, 0, 40);` | Dahili renkli LED'e renk gönderir: kırmızı 0, yeşil 0, mavi 40 — LED mavi yanar. |
| `delay(1000);` (birinci) | 1000 milisaniye, yani 1 saniye bekle. |
| `neopixelWrite(RGBLED, 0, 0, 0);` | Üç rengin üçü de 0 — LED söner. |
| `delay(1000);` (ikinci) | Yine 1 saniye bekle. |
| `}` (setup ve loop sonu) | `;` bir komutun bittiğini, `}` bloğun bittiğini gösterir. |

### İleri analiz [ileri]
`neopixelWrite`'taki üç sayı 0-255 arasında değer alır ve üç rengin **parlaklığını**
ayrı ayrı belirler. Üçünü karıştırarak başka renkler elde edilir: `(40, 0, 40)` mor,
`(40, 40, 0)` sarı, `(40, 40, 40)` beyaz gibi. Bu, ekranların ve telefon kameralarının
da kullandığı **toplamalı renk karışımı**dır — boya karıştırmaktan farklıdır, çünkü
burada ışık üst üste ekleniyor.

Bir tam tur (yanma + sönme) iki `delay()` sürer: 1000 + 1000 = 2000 milisaniye, yani
LED iki saniyede bir kez yanıp sönüyor. Buradan frekans çıkar: `1000 / (2 × delay)`.
`delay(10)` yazarsan saniyede 50 tur olur ve gözün artık sönmeyi seçemez — LED sürekli
yanıyormuş gibi görünür. Bu sınıra **görme eşiği** denir; kendisi ayrı bir dersin konusu.

## 6. Çalıştır ve gözlemle
Kod karta yüklendikten sonra kartın üzerindeki küçük LED bir saniye mavi yanar, bir
saniye söner ve bunu sürekli tekrar eder. Kartı elinden bırakıp uzaktan bak — LED çok
küçüktür ama karanlıkta rahat görünür.

### Sorun giderme
- **`Araçlar > Port` altında hiçbir port görünmüyor** → Kabloyu çıkarıp tekrar tak ve
  menüyü yeniden aç. Hâlâ yoksa kablo bir **veri kablosu** olmayabilir: bazı USB
  kabloları sadece şarj eder, veri taşımaz. Başka bir kabloyla dene.
- **Port görünüyor ama yükleme hata veriyor** → `Araçlar > Kart` altında **Deneyap
  Mini v2** seçili mi kontrol et. Yanlış kart seçiliyken kod derlenir ama karta uymaz.
- **"Deneyap Kartlar" menüde hiç yok** → Kart desteği kurulu değil; Arduino IDE'nin
  Kart Yöneticisi'nden Deneyap kartları kurulmalı. Bu kurulum bir kez yapılır.
- **Yükleme bitti ama LED hiç yanmıyor** → Kodun gerçekten yüklendiğinden emin ol:
  IDE'nin altındaki yeşil "Yükleme tamamlandı" yazısını gördün mü? Görmediysen kod hâlâ
  eski hâliyle çalışıyordur.
- **LED yanıyor ama beklediğin renkte değil** → `neopixelWrite`'taki üç sayının sırası
  kırmızı, yeşil, mavidir. Sıralamayı karıştırmış olabilirsin.
- **LED çok sönük görünüyor** → Üçüncü sayı (mavi) 40; bu bilerek düşük tutulmuş bir
  değer. 255'e kadar artırabilirsin ama LED çok yakından bakınca gözü rahatsız eder.

## 7. Mini sınav
1. [temel] `setup()` içindeki satırlar ne zaman çalışır?
   - A) Sürekli tekrar eder
   - B) Kart açılınca sadece bir kez
   - C) Hiç çalışmaz
   - D) Sen butona basınca
   - ipucu: KAVRAM'daki ilk yorum satırı.

2. [temel] `neopixelWrite(RGBLED, 0, 0, 40)` satırında LED hangi renkte yanar?
   - A) Kırmızı
   - B) Yeşil
   - C) Mavi
   - D) Beyaz
   - ipucu: Üç sayının sırası kırmızı, yeşil, mavi.

3. [temel] `neopixelWrite(RGBLED, 0, 0, 0)` ne yapar?
   - A) LED'i beyaz yakar
   - B) LED'i söndürür
   - C) Kartı kapatır
   - D) 0 saniye bekler
   - ipucu: Üç rengin de parlaklığı sıfırsa geriye ne kalır?

4. [temel] Bu derste devre kurmadın. Neden?
   - A) Devre kurmak yasak
   - B) Kullandığımız LED zaten kartın üzerinde hazır bağlı
   - C) Kart devre kabul etmez
   - D) Kablo yok
   - ipucu: §3 Parça tanıtımı.

5. [ileri] LED'i mor yakmak isteseydin üç sayıyı nasıl verirdin?
   - A) `(40, 40, 0)`
   - B) `(0, 40, 40)`
   - C) `(40, 0, 40)`
   - D) `(0, 0, 0)`
   - ipucu: Mor, kırmızı ile mavinin karışımıdır.

6. [ileri] `delay(1000)` yerine `delay(10)` yazarsan ne olur?
   - A) LED daha yavaş yanıp söner
   - B) LED hiç yanmaz
   - C) LED o kadar hızlanır ki göz sönmeyi seçemez, sürekli yanıyor görünür
   - D) Kart bozulur
   - ipucu: Değişen LED mi, gözün mü?

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı sana kartın hangi pinini kullanacağını, hangi ayarı
> yapacağını ya da devrenin nasıl kurulacağını **söylemez** — bunlar sadece bu derste
> yazar. **AI'ın dediği kartında çalışmıyorsa AI yanılmıştır, kartın haklıdır.**
> AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6'daki Sorun giderme ve aşağıdaki
> "Yanındaki Yetişkine" kartıyla tamamlayabilirsin.

### Ders promptları
- [temel] **Kavramsal** — "Sen sabırlı bir öğretmensin. Deneyap Mini v2 kartıyla
  çalışıyorum. Kodumda `setup()` ve `loop()` adında iki bölüm var. Cevabı doğrudan
  söylemeden, bir tiyatro oyunu ya da günlük hayat benzetmesiyle bu iki bölümün farkını
  anlamamı sağlayacak bir soru sor."
- [temel] **Renk karışımı** — "Sen sabırlı bir öğretmensin. Deneyap Mini v2'nin dahili
  renkli LED'ini `neopixelWrite(RGBLED, 0, 0, 40)` ile mavi yakıyorum. Üç sayının ne
  anlama geldiğini bana **söyleme**; 'bu üç sayıdan hangisini değiştirirsen renk nasıl
  değişir' diye deneyerek bulmam için bir soru sor."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Deneyap Mini v2 kartıma
  kod yüklemeye çalışıyorum ama kartın LED'i hiç yanmıyor. **Bana ayar adımlarını ya
  da menü yolunu verme** — onlar dersimde zaten yazıyor. Bunun yerine 'kod gerçekten
  karta ulaştı mı' sorusundan başlayarak, neyi hangi sırayla kontrol etmem gerektiğini
  soru sorarak buldur."
- [ileri] **Görme eşiği** — "Sen meraklı bir rehbersin. Deneyap Mini v2'de LED'imin
  bekleme süresini `delay(10)` yaptığımda LED hiç sönmüyormuş gibi sürekli yanıyor
  görünüyor. Kartım mı bozuldu, gözlerim mi beni kandırıyor? Cevabı doğrudan verme;
  insan gözünün algı sınırıyla ilgili küçük bir ipucu ve bir düşünme sorusu ver."

### Kara kutu promptları
- [temel] **`void` nedir?** — "Sen meraklı bir öğretmensin. Kodumda `void setup()` ve
  `void loop()` yazıyor ama `void` kelimesinin ne işe yaradığını bilmiyorum. Cevabı
  verme; 'bu kelime bir şeyin olmadığını mı, yoksa bir şeyin nasıl davranacağını mı
  anlatıyor olabilir?' gibi bir soruyla merak uyandır. Bu konu ileride ayrı bir derste
  tam açılacak — şimdilik sadece merak bırak, tam açıklama verme."

### Yanındaki yetişkine
- [temel] **Yardım etmek isteyen büyüğe** — Bu kart çocuğa değil, yanındaki yetişkine
  yazıldı; AI gerekmez, internet gerekmez.

  > *Bu ilk ders ve takılırsa büyük ihtimalle devrede değil, bilgisayarda takılır.*
  > *Cevabı söylemeyin, şu üç şeyi sırayla sorun:*
  > 1. *Arduino IDE'de `Araçlar > Port` altında bir port görünüyor mu?*
  > 2. *`Araçlar > Kart` altında "Deneyap Mini v2" seçili mi?*
  > 3. *Yükleme bittiğinde ekranın altında "Yükleme tamamlandı" yazısı çıktı mı?*
  >
  > *Port hiç görünmüyorsa en sık sebep kablodur: bazı USB kabloları sadece şarj eder,*
  > *veri taşımaz. Elinizde başka bir Type-C kablo varsa onunla deneyin.*

## 9. SEN YAP
1) LED'i mavi yerine yeşil yak. `neopixelWrite`'taki üç sayıdan hangisini değiştirmen
   gerekiyor? Değiştir ve çalıştır.
2) `delay(1000)` yazan iki satırdaki 1000 sayısını değiştir; LED'i daha hızlı ya da
   daha yavaş yakıp söndür.
3) İki `delay()` değerini birbirinden farklı yap (ör. yanma kısa, sönme uzun).
