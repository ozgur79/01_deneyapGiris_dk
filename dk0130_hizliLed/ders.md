---
dk_no: dk0130
portal_ders: "1.3"
kaynak_ak: [ak0030]
baslik: LED'i hızlandır
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.delay
  - hw.gorme-esigi
kara_kutu: [void, OUTPUT]
merak_kosesi: void (1. tur)
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 1 LED
  - 1 adet 220 ohm direnç
  - breadboard
  - 2 jumper kablo
board:
  kart: Deneyap Mini v2
  harici_led_pin: "D5"
  harici_led_pin_not: "Kod D5 makrosunu kullanır, çıplak GPIO numarası (39) değil — D-etiketleri board'a özgüdür, GPIO numaralarıyla örtüşmez."
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
kaynak_kod: ak0030_hizliLed/ak0030_hizliLed.ino
---

## 1. Hedef
Ders 1.2'de kurduğun devre aynen duruyor. Bu sefer devreye değil, koddaki bekleme
süresine dokunacaksın: LED'i **saniyede 1 → 5 → 10 → 25 → 50 kez** yakıp söndürüp
**artık söndüğünü göremediğin hızı** kendin bulacaksın. O hızı ders sana vermeyecek,
sen bulacaksın.

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu
- 1 LED
- 1 adet 220 ohm direnç
- breadboard
- 2 jumper kablo

## 3. Parça tanıtımı
Bu derste yeni parça yok — Ders 1.2'de tanıdığın LED, direnç, breadboard ve jumper kablo
kullanılıyor. Devre kuruluysa hiç sökme.

## 4. Devre kurulumu
Ders 1.2'nin devresi aynen kullanılır. Devren sökülmüşse yeniden kur:
1. LED'i breadboard'a tak.
2. LED'in uzun bacağından (+) bir jumper kabloyla kartın **D5** pinine bağlan (kart üzerinde
   "D5" yazan pin).
3. LED'in kısa bacağını (−) 220 ohm dirence bağla.
4. Direncin diğer ucundan bir jumper kabloyla kartın GND pinine bağlan.

Metin şeması: LED uzun bacak (+) → D5, kısa bacak (−) → 220 ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `// delay() içindeki sayı milisaniye cinsindendir: 1000 bir saniye, 500 yarım saniyedir` | `delay()` içindeki sayı milisaniye cinsindendir: 1000 bir saniye, 500 yarım saniyedir. |
| `// delay() içindeki sayı küçüldükçe LED daha sık yanıp söner` | `delay()` içindeki sayı küçüldükçe LED daha sık yanıp söner. |
| `// Bir tam tur (bir yanma + bir sönme) iki delay() sürer: 500 + 500 = bir saniye,` | Bir tam tur (bir yanma + bir sönme) iki `delay()` sürer: 500 + 500 = bir saniye. |
| `// yani LED saniyede 1 kez yanıp sönüyor` | Yani LED saniyede 1 kez yanıp sönüyor. |
| `void setup() {` | `{` ve `}` arasındaki satırlar o fonksiyona ait koddur; bu blok "başlangıç" bloğudur. |
| `pinMode(D5, OUTPUT);` | D5 pinini, açıp kapatabileceğimiz bir pin yap. |
| `void loop() {` | loop() içindeki satırlar setup bitince sürekli baştan tekrar eder. |
| `digitalWrite(D5, HIGH);` | D5 pinine gerilim gönder -> LED yanar. |
| `delay(500);` (birinci) | Yarım saniye boyunca hiçbir şey yapma, LED yanık kalsın. |
| `digitalWrite(D5, LOW);` | D5 pininin gerilimini kes -> LED söner. |
| `delay(500);` (ikinci) | Yarım saniye boyunca hiçbir şey yapma, LED sönük kalsın. |
| `}` (setup ve loop sonu) | `;` işareti bir komutun bittiğini, `}` bloğun bittiğini gösterir. |

### İleri analiz [ileri]
Bir tam tur (yan + sön) iki `delay()` sürer, yani `2 × delay` milisaniye. Saniyede kaç
tur olduğu buradan çıkar: `frekans = 1000 / (2 × delay)`, birimi hertz (Hz).

| delay | bir tur | frekans |
| --- | --- | --- |
| 500 ms | 1000 ms | 1 Hz |
| 250 ms | 500 ms | 2 Hz |
| 100 ms | 200 ms | 5 Hz |
| 50 ms | 100 ms | 10 Hz |
| 20 ms | 40 ms | 25 Hz |
| 10 ms | 20 ms | 50 Hz |

Ters yönde de kullanılır: hedef hızdan `delay` değerini bulmak için
`delay = 1000 / (2 × hedef hız)`. Saniyede 25 kez istiyorsan `1000 / 50 = 20` ms.

Gözün bu turları tek tek ayırt edemez hâle geldiği sınıra **görme eşiği** (kaynaşma
frekansı) denir. LED gerçekte hâlâ sönüyor — değişen LED değil, gözün. Bu yüzden eşik
kişiden kişiye, hatta aynı kişide gündüz/gece farklı çıkabilir; tek bir "doğru sayı"
yoktur.

### Merak Köşesi: void (1. tur)
`void`, `setup` ve `loop` listelerinin adının önünde duruyor ve "bu liste bitince geriye
bir sonuç vermeyecek" der. Bu derste listelerin *içindeki* sayıyı (delay değerlerini)
değiştirdin, adlarına hiç dokunmadın. Listenin kendisini, yani `void`'in tam olarak ne
işe yaradığını, ileride "fonksiyon" dersinde tam açacağız — bu sadece ilk turdu.

## 6. Çalıştır ve gözlemle
Kod ilk hâliyle yüklendiğinde LED yarım saniye yanık, yarım saniye sönük kalır —
Ders 1.2'deki ritmin iki katı hızında. SEN YAP'taki sayıları küçülttükçe yanıp sönme
hızlanır; bir yerden sonra göz sönmeyi seçemez ve LED sürekli yanıyormuş gibi görünür.
Çok hızlandırınca LED biraz **daha sönük** görünür, çünkü zamanın yarısında kapalıdır.

### Sorun giderme
- **LED hiç yanmıyor** → LED'in uzun bacağı D5'e, kısa bacağı dirence bakıyor mu
  kontrol et; LED yönlü bir parçadır, ters takılırsa yanmaz.
- **LED hızlanmıyor** → İki `delay()` satırından yalnız birini değiştirmiş olabilirsin;
  ikisi de aynı sayı olmalı.
- **Kodu değiştirdin ama LED aynı davranıyor** → Değişikliği karta yeniden yüklemen
  gerekir; dosyayı kaydetmek yetmez.
- **"Sürekli yanıyor" mu, "hâlâ sönüyor" mu emin olamıyorsan** → Gözünü LED'den ayırıp
  başını yavaşça sağa sola sallayarak bak; sönme varsa ışık kesik kesik bir iz bırakır.
- **Kod yüklenmiyor** → `Araçlar > Kart > Deneyap Kartlar > Deneyap Mini v2` ve
  `Araçlar > Port` seçimlerini doğrula; USB kablosunun veri kablosu olduğundan (yalnızca
  şarj kablosu olmadığından) emin ol.

## 7. Mini sınav
1. [temel] `delay(250)` kaç saniyelik bekleme yapar?
   - A) 250 saniye
   - B) 25 saniye
   - C) Çeyrek saniye
   - D) 2,5 saniye
   - ipucu: 1000 milisaniye 1 saniyeye eşit.

2. [temel] Bu derste devrede ne değişti?
   - A) LED'in pini değişti
   - B) Direncin değeri değişti
   - C) Devrede hiçbir şey değişmedi, sadece koddaki sayı değişti
   - D) LED'in yönü değişti
   - ipucu: §4'te "Ders 1.2'nin devresi aynen kullanılır" yazıyor.

3. [temel] `delay()` sayısını küçültürsen LED ne yapar?
   - A) Daha sık yanıp söner
   - B) Daha seyrek yanıp söner
   - C) Hiç yanmaz
   - D) Rengi değişir
   - ipucu: KAVRAM'daki ikinci yorum satırına bak.

4. [temel] LED çok hızlandığında sürekli yanıyormuş gibi görünüyor. Gerçekte ne oluyor?
   - A) LED artık sönmüyor
   - B) LED hâlâ sönüyor ama göz bunu ayırt edemiyor
   - C) Kart komutları atlıyor
   - D) Direnç ısınıp LED'i açık tutuyor
   - ipucu: Değişen LED mi, gözün mü?

5. [ileri] `delay` 20 ms iken LED saniyede kaç kez yanıp söner?
   - A) 20
   - B) 25
   - C) 50
   - D) 100
   - ipucu: Bir tur iki `delay()` sürer; `1000 / (2 × 20)`.

6. [ileri] LED'in saniyede 5 kez yanıp sönmesini istiyorsun. `delay` kaç olmalı?
   - A) 5
   - B) 100
   - C) 200
   - D) 500
   - ipucu: `delay = 1000 / (2 × hedef hız)`.

7. [ileri] Aynı devrede iki kişi farklı eşik değerleri buldu. Bu neyi gösterir?
   - A) Biri kodu yanlış yazmıştır
   - B) Kartlardan biri bozuktur
   - C) Görme eşiği kişiden kişiye değişir, tek doğru sayı yoktur
   - D) Direnç değerleri farklıdır
   - ipucu: Sınırı koyan LED değil, göz.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı sana devrenin nasıl kurulacağını, hangi pine
> bağlayacağını ya da hangi direnci kullanacağını **söylemez** — bunlar zaten Ders 1.2'de
> yazıyor, bu derste devre değişmiyor. **AI'ın dediği devrende/kartında çalışmıyorsa AI
> yanılmıştır, devren haklıdır.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi
> §6'daki Sorun giderme ve aşağıdaki "Yanındaki Yetişkine" kartıyla tamamlayabilirsin.

### Ders promptları
- [temel] **Kavramsal** — "Sen sabırlı bir öğretmensin. Deneyap Mini v2 kartında, 3.3V
  mantık gerilimiyle D5 pinine bağlı bir LED'i çok hızlı yakıp söndürüyorum, artık
  sönmesini göremiyorum. Bana 'LED mi değişti, gözün mü?' diye sor ve sinema/çizgi film
  karelerinin nasıl hareket gibi göründüğünü hatırlatarak cevabı kendim bulayım. Cevabı
  sen söyleme. Bana pin numarası, direnç değeri ya da bağlantı tarifi verme."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Deneyap Mini v2'de D5
  pinine bağlı LED'imin `delay()` sayısını küçülttüm ama hızı değişmedi. Bana pin
  numarası, direnç değeri ya da bağlantı tarifi verme — devrem zaten kurulu ve doğru.
  Bunun yerine bana iki soru sor: koddaki kaç tane `delay()` satırı var, hepsini
  değiştirdim mi; ve değişikliği karta yeniden yükledim mi. Cevabı doğrudan verme."
- [ileri] **Pekiştirme** — "Sen ileri seviye bir mentorsun. Bana bir tam turun neden iki
  `delay()` sürdüğünü sorarak frekans formülünü (`1000 / (2 × delay)`) kendi
  cümlelerimle kurdurmaya çalış. Formülü sen yazma, önce 'bir tur ne kadar sürüyor' diye
  sor. Pin numarası ya da direnç değeri verme, gerekmiyor zaten."
- [ileri] **Tartışma** — "Sen meraklı bir tartışma arkadaşısın. Bana şunu sor: eşiği
  geçtikten sonra LED biraz daha sönük görünüyor, neden? Cevabı verme; 'zamanın ne
  kadarında açık, ne kadarında kapalı' diye düşündür."

### Yanındaki yetişkine
- [temel] **Yardım etmek isteyen büyüğe** — Bu kart çocuğa değil, yanındaki yetişkine
  yazıldı; AI gerekmez, internet gerekmez.

  > *Yardım etmek isterseniz cevabı söylemeyin, şu üçünü sırayla sorun:*
  > 1. *LED'in ışığı sence artık kesik kesik mi, yoksa sürekli mi yanıyor?*
  > 2. *Bu iki durumu ayırt edebilmek için gözünü ışıktan ayırıp başını yavaşça sağa sola
  >    sallamayı denedin mi?*
  > 3. *Bulduğun hızı bir kez daha, farklı bir saatte (örneğin akşam) tekrar dener misin —
  >    aynı hızı mı buluyorsun?*
  >
  > *Cevabı siz vermeyin, sadece bu üç soruyla gözlemini netleştirmesine yardım edin.*

### Kara kutu promptları
- [temel] **`void` nedir?** — "Sen meraklı bir öğretmensin. Öğrenci kodda `void setup()`
  ve `void loop()` yazdığını görüyor ama `void` kelimesinin ne işe yaradığını bilmiyor.
  Cevabı verme; öğrenciye 'bu kelime bir şeyin olmadığını mı, yoksa bir şeyin nasıl
  davranacağını mı anlatıyor olabilir?' gibi bir soruyla merak uyandır. Bu konu ileride
  ayrı bir derste tam açılacak, şimdilik sadece merak bırak, tam açıklama verme."
- [temel] **`OUTPUT` nedir?** — "Sen meraklı bir öğretmensin. Öğrenci `pinMode(D5, OUTPUT)`
  yazdığını görüyor ama `OUTPUT` kelimesinin tam olarak neyi ayarladığını bilmiyor.
  Cevabı verme; öğrenciye 'bir pin hem bilgi gönderebilir hem bilgi alabilir olsaydı,
  bu ikisini birbirinden ayırmak için kartın bir şey bilmesi gerekmez miydi?' gibi bir
  soruyla düşündür. Bu konu ileride buton dersinde `INPUT` ile birlikte tam açılacak,
  şimdilik sadece merak bırak, tam açıklama verme."

## 9. SEN YAP
1) LED'i sırayla şu hızlarda yakıp söndür. Her hız için iki `delay()` satırındaki sayıyı
   İKİSİNİ BİRDEN değiştir, karta yükle ve LED'e bak:

   | hedef hız | delay değeri |
   | --- | --- |
   | saniyede 1 kez | `delay(500)` |
   | saniyede 5 kez | `delay(100)` |
   | saniyede 10 kez | `delay(50)` |
   | saniyede 25 kez | `delay(20)` |
   | saniyede 50 kez | `delay(10)` |

2) Hangi hızdan sonra LED'in söndüğünü artık göremiyorsun, sürekli yanıyor gibi
   görünüyor? O hızı defterine yaz.
3) Bulduğun hızı bir aile bireyinle karşılaştır, ya da aynı denemeyi kendin gündüz ve
   akşam tekrarla. Aynı hızı mı buldunuz?
