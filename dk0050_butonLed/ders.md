---
dk_no: dk0050
portal_ders: "3.1"
portal_ders_not: "Modul1-Mufredat.md'deki 1.1-1.6 hedef listesinde karşılığı yoktu.
  Özgür'e soruldu (2026-09-21): yeni Modül 2 (Dijital Giriş / Sensörler) açıldı,
  bkz. Modul2-Mufredat.md. dk0050 = 2.1 (o zamanki 5 modüllü yapıda).
  Portal-Ders-Haritasi.md 12 modüllü yapıya taşındı (Özgür, 2026-09-24): dk0050
  eski 2.1'den 3.1'e taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
kaynak_ak_planlanan: ak02xx
baslik: Butona basınca LED yansın
duzey: 0-temel
unite: 2-Buton
kazanimlar:
  - cpp.setup-loop
  - cpp.pinmode
  - cpp.digitalwrite
  - cpp.const-int
  - cpp.digitalread
  - cpp.if-else
  - hw.buton-devre
kara_kutu: [void]
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 1 LED
  - 1 adet 220 ohm direnç
  - 1 buton
  - 1 adet 10K ohm direnç
  - breadboard
  - jumper kablolar
board:
  kart: Deneyap Mini v2
  led_pin: "D9"
  buton_pin: "D10"
  mantik_gerilimi: 3.3V
  led_direnc: 220 ohm
  buton_direnc: 10K ohm
  buton_devre_tipi: "harici pull-down direnç (pinMode INPUT; dahili INPUT_PULLUP kullanılmadı, kaynak kod bilinçli olarak INPUT yazıyor ve digitalRead==1'i 'basılı' kabul ediyor -- bu yalnız buton 3.3V'a bağlıyken ve pull-down dirençle GND'ye çekiliyken doğrudur)"
  pin_notu: "Ham kaynak (dyminiV2010LedButon.ino) A0/A1 kullanıyordu; bu derste analogRead/analogWrite hiç kullanılmadığından (yalnız dijital pinMode/digitalWrite/digitalRead) analog pin olmasının işlevsel bir gerekçesi yoktu. dk0020/dk0030/dk0040 ile aynı aileden (D5/D6) ama farklı, boşta olan D9/D10'a çevrildi. Diğer D-pinlerdeki gibi kod her zaman D<n> makrosuyla yazılır, çıplak sayı yazılmaz."
kaynak_kod: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2010LedButon\\dyminiV2010LedButon.ino (ham)"
---

## 1. Hedef
Şimdiye kadar kart hep senin yazdığın kodun dediğini yaptı — LED hep aynı ritimde yanıp
söndü. Bu derste kart ilk kez **dışarıdan bir bilgiyi okuyor**: butona basıp basmadığını.
Bastığında LED yanacak, bıraktığında sönecek — kartın kararını sen, parmağınla, o anda
veriyorsun.

## 2. Malzemeler
- Deneyap Mini v2 kartı ve Type-C USB kablosu
- 1 LED
- 1 adet 220 ohm direnç
- 1 buton
- 1 adet 10K ohm direnç
- breadboard
- jumper kablolar

## 3. Parça tanıtımı
- **Buton** — üzerine basınca içindeki iki bacak çiftini birbirine bağlayan parça;
  basılı değilken bacaklar birbirinden ayrıdır.
- **10K ohm direnç** — burada LED'i korumuyor, butonun bağlı olduğu pini basılı
  değilken sabit bir seviyede (LOW) tutuyor. Bkz. §5 "İleri analiz" — bu direnç
  olmadan pin ne okuyacağını bilemez.

## 4. Devre kurulumu
`dk0020`'deki LED devresi (uzun bacak → pin, kısa bacak → 220 ohm direnç → GND) burada
da geçerli, yalnız pin **D5 değil D9**. Sırayla kur:

1. LED'i breadboard'a tak.
2. LED'in uzun bacağını (+) jumper kabloyla kart üzerinde **D9** yazan pine bağla.
3. LED'in kısa bacağını (−) 220 ohm dirence, direncin diğer ucunu GND'ye bağla.
4. Butonu breadboard'a tak.
5. Butonun bir ucunu kart üzerinde **3V3** yazan pine bağla.
6. Butonun aynı ucunu (breadboard'da aynı satırdaki deliklerden) hem kart üzerinde
   **D10** yazan pine, hem de 10K ohm dirence bağla.
7. 10K ohm direncin diğer ucunu GND'ye bağla.
8. Kartı Type-C USB kablosuyla bilgisayara bağla.

Metin şeması:
LED uzun bacak (+) → D9, kısa bacak (−) → 220 ohm direnç → GND
Buton bir ucu → 3V3; diğer ucu → D10 **ve** 10K ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `const int led = D9;` | Kart üzerinde D9 yazan pine `led` adı verilir. |
| `const int buton = D10;` | Kart üzerinde D10 yazan pine `buton` adı verilir. |
| `void setup() {` | **Kara kutu:** `void`, bu kod bölümünün sonunda değer verilmediğini belirtir; fonksiyon konusunda tam açılacak. |
| `pinMode(led, OUTPUT);` | led pinini çıkış yapar — dışarıya elektrik gönderip LED'i sürecek. |
| `pinMode(buton, INPUT);` | **Yeni komut.** buton pinini giriş yapar — dışarıdan elektrik okuyacak. `OUTPUT`'un tam tersi: pin artık veri göndermiyor, veri okuyor. |
| `void loop() {` | loop() içindeki satırlar setup bitince sürekli baştan tekrar eder. |
| `if (digitalRead(buton) == 1) {` | **Yeni komut.** `digitalRead(buton)` buton pininin o anki durumunu okur: 1 (HIGH) ya da 0 (LOW). Buton basılıyken pin 3.3V'a bağlanır, `digitalRead` 1 döner; koşul doğru olur ve `{` ile başlayan blok çalışır. |
| `digitalWrite(led, HIGH);` | Koşul doğruysa (buton basılı) çalışır: LED'i yakar. |
| `} else {` | Koşul yanlışsa (buton basılı değil) bu satırdan sonraki blok çalışır. |
| `digitalWrite(led, LOW);` | LED'i söndürür. |
| `}` (iki kez) | İlk `}` if bloğunu, ikincisi else bloğunu kapatır. |

### İleri analiz [ileri]
Buton basılı değilken pin neden 10K ohm dirençle GND'ye bağlı? Çünkü `INPUT` modundaki
bir pin, hiçbir şeye bağlı değilse ("havada asılı" — floating) çevredeki elektrik
gürültüsünü rastgele HIGH ya da LOW okuyabilir. 10K ohm direnç, buton basılı değilken
pini sabit bir şekilde GND'ye ("çeker"), yani LOW'a bağlar — buna **pull-down** direnç
denir. Buton basılınca pin doğrudan 3.3V'a bağlanır ve HIGH okunur; direnç yüksek değerli
(10K ohm) olduğu için bu anda LED tarafına değil GND'ye çok az akım kaçar, kısa devre
oluşmaz. Bazı devrelerde bunun tersi kurulur (**pull-up**, pin varsayılan HIGH, buton
basılınca LOW) — bu ders o yolu seçmedi, kaynak kod `digitalRead(...) == 1`'i "basılı"
kabul ettiği için pull-down kuruldu.

## 6. Çalıştır ve gözlemle
Kodu karta yükle. Butona basılı tuttuğun sürece LED yanar; bıraktığın anda söner.

### Sorun giderme
- **LED hiç yanmıyor (butona basınca da)** → LED devresini `dk0020`'deki gibi kontrol et:
  uzun bacak D9'a, kısa bacak dirence, direnç GND'ye.
- **LED sürekli yanık, butona basmak fark etmiyor** → Butonun 3V3'e giden ucunu kontrol
  et; pull-down direnç yanlışlıkla 3V3'e bağlanmış olabilir, GND'ye gitmesi gerekiyor.
- **LED hiç yanmıyor, butona basınca da değişmiyor** → 10K ohm direncin GND'ye ulaştığını,
  butonun D10 ve 3V3 ile aynı breadboard sırasında olduğunu kontrol et.
- **LED titrek yanıyor ya da kararsız davranıyor** → 10K ohm direnç eksik olabilir; pin
  havada asılı kalınca rastgele okuma yapar. §5 İleri analiz'e bak.
- **Buton her zaman basılıymış gibi davranıyor** → Butonun iki bacağının breadboard'da
  gerçekten ayrı satırlarda (basılmadan bağlı olmayan) olduğunu kontrol et; bazı butonlar
  dört bacaklıdır, çapraz bacaklar zaten içeriden bağlıdır.
- **Kod yüklenmiyor** → Kart modelini ve portu doğrula; USB kablosunun veri kablosu
  olduğundan emin ol.

## 7. Mini sınav
1. [temel] `digitalRead(buton)` ne yapar?
   - A) buton pinine elektrik gönderir
   - B) buton pininin o anki durumunu (HIGH/LOW) okur
   - C) LED'i yakar
   - D) 1 saniye bekler
   - ipucu: `digitalWrite` "yazar", bunun adı "read" — okur.

2. [temel] `if (...) { } else { }` yapısında ne olur?
   - A) İki blok da her zaman çalışır
   - B) Koşul doğruysa yalnız `if` bloğu, yanlışsa yalnız `else` bloğu çalışır
   - C) `else` bloğu hiç çalışmaz
   - D) Koşul her zaman yok sayılır
   - ipucu: KAVRAM yorumundaki "ikisinden yalnız biri" cümlesine bak.

3. [temel] `INPUT` ile `OUTPUT` arasındaki fark nedir?
   - A) İkisi de aynı şeydir
   - B) `OUTPUT` pin elektrik gönderir, `INPUT` pin elektrik okur
   - C) `INPUT` yalnız LED'lerde kullanılır
   - D) `OUTPUT` yalnız butonlarda kullanılır
   - ipucu: `pinMode(led, OUTPUT)` ile `pinMode(buton, INPUT)` satırlarını karşılaştır.

4. [temel] Bu derste buton hangi pine bağlıdır?
   - A) D5
   - B) D9
   - C) D10
   - D) D13
   - ipucu: `const int buton = ...` satırına bak.

5. [ileri] 10K ohm direnç bu devrede olmasaydı ne olurdu?
   - A) LED daha parlak yanardı
   - B) Buton basılı değilken pin kararsız (havada asılı) okuma yapabilirdi
   - C) Buton hiç çalışmazdı, kart açılmazdı
   - D) Kod derlenmezdi
   - ipucu: §5 İleri analiz'deki "floating" kelimesine bak.

6. [ileri] Kodun mantığını tersine çevirip "buton basılı değilken LED yansın" istesen,
   hangi iki satırı değiştirirdin?
   - A) `pinMode` satırlarını
   - B) `if` ve `else` bloklarındaki `digitalWrite(led, HIGH/LOW)` satırlarını
   - C) `const int` satırlarını
   - D) `digitalRead` satırını silerdin
   - ipucu: Değişen şey "ne zaman" değil "ne yapılacağı".

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme ve
> aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'a pin numarası, direnç değeri, menü
> yolu veya bağlantı tarifi sordurma; bunları dersindeki devre şeması belirler.

### Ders promptları
- [temel] **INPUT/OUTPUT karşılaştırması** — "Sen sabırlı bir öğretmensin. Bağlam:
  Deneyap Mini v2 kartında, 3.3V mantık seviyesinde, D9 pininde 220 ohm dirençli bir
  LED ve D10 pininde 10K ohm pull-down dirençli bir buton kullanıyorum. Bana pin
  numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Bir pinin hem 'konuşan'
  hem 'dinleyen' taraf olabileceğini, kartın bu ikisini birbirinden nasıl ayırt etmesi
  gerektiğini düşündüren bir soru sor; cevabı söyleme."
- [temel] **if/else akışı** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında D10 pininde bir butonum, D9 pininde bir LED'im var. Kodda `if (...) { } else
  { }` kullanıyorum. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi
  verme. İki bloktan aynı anda ikisinin de çalışıp çalışamayacağını düşündüren bir soru
  sor; cevabı söyleme, kendim keşfedeyim."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Bağlam: Deneyap Mini v2
  kartında D10 pininde 10K ohm pull-down dirençli bir butonum, D9 pininde 220 ohm
  dirençli bir LED'im var ama LED butona basınca da tepki vermiyor. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Devreyi (LED, buton, pull-down
  direnç) hangi sırayla kontrol etmem gerektiğini soru sorarak buldur."
- [ileri] **Pull-down mantığı** — "Sen ileri seviye bir mentorsun. Bağlam: Deneyap Mini
  v2'de D10 pinine bağlı bir butonum var, pull-down direnç kullanıyorum. Bana pin
  numarası veya direnç değeri verme. Buton basılı değilken pinin GND'ye 'çekilmesi'
  gerekmeseydi ne olabileceğini, 'havada asılı kalmak' fikrinden yola çıkarak
  düşündüren bir soru sor; cevabı sen verme, ben kendi cümlemle ifade edeyim."

### Kara kutu promptları
- [temel] **`void`** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında
  D9 pininde bir LED, D10 pininde bir buton kullanıyorum. Kodumda `void setup()`
  yazıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme.
  `void` kelimesinin kod bölümünün sonunda değer verip vermemesiyle ilgili olabileceğini
  düşündüren bir soru sor; cevabı verme, konu fonksiyonlarda tam açılacak."

### Yanındaki yetişkine
Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. Butona bastığınızda gerçekten LED yanıyor mu, yoksa hiç tepki yok mu?
2. Butonun bir ucu 3V3'e, diğer ucu hem D10'a hem de dirence mi bağlı?
3. 10K ohm direncin diğer ucu GND'ye ulaşıyor mu?

## 9. SEN YAP
1. Mantığı tersine çevir: buton basılı değilken LED yansın, basılınca sönsün. Hangi
   satırları değiştirmen gerekiyor?
2. `dk0040`'ta öğrendiğin `Serial.println`'i kullanarak buton basılıyken Seri Monitör'e
   "BASILI", basılı değilken "BASILI DEGIL" yazdır (`Serial.begin(115200)` eklemeyi
   unutma).
3. LED'i, buton basılı tutulduğu sürece 200 milisaniye aralıklarla yanıp söndür; buton
   bırakılınca LED sönük kalsın.
