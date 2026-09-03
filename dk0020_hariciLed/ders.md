---
dk_no: dk0020
portal_ders: "1.2"
kaynak_ak: [ak0020]
baslik: Harici LED'i yakıp söndür
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.setup-loop
  - cpp.delay
  - cpp.pinmode
  - cpp.digitalwrite
  - cpp.blok-noktalivirgul
  - hw.harici-led-devre
kara_kutu: [void, OUTPUT]
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
kaynak_kod: ak0020_hariciLed/ak0020_hariciLed.ino
---

## 1. Hedef
Ders 1.1'de kartın üzerindeki hazır LED'i yaktın. Bu sefer LED kartın üzerinde değil,
senin kurduğun bir devrenin üzerinde. Bir LED'i, bir direnci ve birkaç kabloyu doğru
sırayla bağlayıp aynı yakıp-söndürme işini kendi devrende çalıştıracaksın — ve bunu
Ders 1.1'de görmediğin yeni bir komutla, `digitalWrite` ile yapacaksın.

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu
- 1 LED
- 1 adet 220 ohm direnç
- breadboard
- 2 jumper kablo

## 3. Parça tanıtımı
- **LED** — iki bacaklı küçük ışık kaynağı; bacaklarından biri uzun, biri kısa.
- **Direnç** — LED'e giden akımı sınırlayan, üzerinde renkli çizgiler olan parça.
- **Breadboard** — kabloları lehim yapmadan birbirine bağlamana yarayan delikli tahta.
- **Jumper kablo** — breadboard, LED, direnç ve kart arasında bağlantı kuran kablo.

## 4. Devre kurulumu
Her adım tek bir eylem; sırayla ve atlamadan uygula.

1. LED'i breadboard'a tak.
2. LED'in uzun bacağından (+) bir jumper kabloyla kartın **D5** pinine bağlan (kart üzerinde
   "D5" yazan pin).
3. LED'in kısa bacağını (−) 220 ohm dirence bağla.
4. Direncin diğer ucundan bir jumper kabloyla kartın GND pinine bağlan.

Metin şeması: LED uzun bacak (+) → D5, kısa bacak (−) → 220 ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `// LED'in iki bacağı var: uzun bacak (+) ve kısa bacak (-) - yönü önemlidir, ters takarsan LED yanmaz` | LED'in iki bacağı var: uzun bacak (+) ve kısa bacak (−) — yönü önemlidir, ters takarsan LED yanmaz. |
| `// Direnç, LED'e çok fazla akım gitmesini engeller ve LED'i korur` | Direnç, LED'e çok fazla akım gitmesini engeller ve LED'i korur. |
| `void setup() {` | `{` ve `}` arasındaki satırlar o fonksiyona ait koddur; bu blok "başlangıç" bloğudur. |
| `pinMode(D5, OUTPUT);` | D5 pinini, açıp kapatabileceğimiz bir pin yap. `pinMode`'u Ders 1.1'den hatırlıyorsun — orada `LED_BUILTIN` içindi, burada D5 pini için aynı işi yapıyor. **`D5` kartın üzerinde yazan pin adıdır — düz `5` yazsaydık kart bunu farklı bir pin sanırdı, bu yüzden Deneyap'ta pin isimleri hep `D` ile başlar.** |
| `}` (setup sonu) | `;` işareti bir komutun bittiğini gösterir; `}` bloğun bittiğini gösterir. |
| `void loop() {` | loop() içindeki satırlar setup bitince sürekli baştan tekrar eder. |
| `digitalWrite(D5, HIGH);` | **Yeni komut.** `digitalWrite(pin, HIGH)` o pine gerilim gönderir, pin "açık" olur → LED yanar. Ders 1.1'de dahili LED'i `neopixelWrite` ile yakmıştın; o üç kanala (kırmızı/yeşil/mavi) 0-255 arası sayı gönderip renk ayarlıyordu. `digitalWrite` bundan daha basit: pini sadece iki durumda tutar, açık ya da kapalı — renk yok. |
| `delay(1000);` | 1000 milisaniye (1 saniye) bekle. |
| `digitalWrite(D5, LOW);` | `digitalWrite(pin, LOW)` pinin gerilimini keser, pin "kapalı" olur → LED söner. |
| `delay(1000);` | 1 saniye bekle. |

### İleri analiz [ileri]
Direncin değeri Ohm Kanunu'yla (V = I × R) hesaplanır. Bu devrede kart 3.3V verir
(bkz. `board.mantik_gerilimi`), direnç 220 ohm'dur (bkz. `board.direnc`) — bu ikisi
LED'den geçen akımı güvenli bir seviyede tutacak şekilde seçilmiştir (yaklaşık 15 mA).
Farklı bir board'da mantık gerilimi farklıysa (örn. 5V), aynı akımı elde etmek için
farklı bir direnç değeri gerekir — bu yüzden gerilim ve direnç değeri board'a özgüdür,
dersten derse değişebilir.

## 6. Çalıştır ve gözlemle
Kod karta yüklendikten sonra, breadboard üzerindeki LED saniyede bir yanıp söner:
1 saniye yanık, 1 saniye sönük, sürekli tekrar — Ders 1.1'deki dahili LED ile aynı
ritim, ama ışık artık kartın üzerinde değil, senin kurduğun devrede.

### Sorun giderme
- **LED hiç yanmıyor, ters bağlanmış olabilir** → LED'in iki bacağını yer değiştirip
  tekrar dene; LED yönlü bir parçadır, ters takılırsa yanmaz.
- **LED yanmıyor, pin uyuşmazlığı olabilir** → kodda yazan pinin (`D5`) ve jumper kablonun
  karta bağlı olduğu pinin (kart üzerinde "D5" yazan yer) aynı olduğundan emin ol.
- **LED hiç yanmıyor, direnç eksik ya da yanlış olabilir** → devrede 220 ohm direnç
  olduğundan emin ol; direnç yoksa ya da devre yanlış kurulduysa LED yanmayabilir.
- **Kablolar breadboard'da yanlış sırada olabilir** → breadboard'daki delikler küçük
  gruplar halinde birbirine bağlıdır; LED'in bacağı, direncin ucu ve jumper kablo aynı
  grupta (aynı satırda) olmalı. §4'teki şemayı tekrar kontrol et.
- **Kod yüklenmiyor** → `Araçlar > Kart > Deneyap Kartlar > Deneyap Mini v2` ve
  `Araçlar > Port` seçimlerini doğrula; USB kablosunun veri kablosu olduğundan (yalnızca
  şarj kablosu olmadığından) emin ol.
- **`delay(1000)` bir saniye mi, bin saniye mi diye şüphe ediyorsan** → `delay()`
  değeri her zaman milisaniye cinsindendir, 1000 milisaniye 1 saniyeye eşittir.

## 7. Mini sınav
1. [temel] LED'in hangi bacağı karta, hangisi dirence bağlanır?
   - A) Uzun bacak karta, kısa bacak dirence ✅
   - B) Kısa bacak karta, uzun bacak dirence
   - C) İkisi de karta bağlanır
   - D) İkisi de dirence bağlanır
   - ipucu: KAVRAM yorumundaki "+" ve "−" işaretlerine bak.

2. [temel] Bu derste direncin görevi nedir?
   - A) LED'i daha parlak yapmak
   - B) LED'e giden akımı sınırlayıp LED'i korumak ✅
   - C) Pin numarasını değiştirmek
   - D) delay() süresini kısaltmak
   - ipucu: Direnç kelimesinin "engellemek" anlamıyla ilişkisini düşün.

3. [temel] Bu derste LED hangi pine bağlıdır?
   - A) D13
   - B) D6
   - C) D5 ✅
   - D) D0
   - ipucu: `pinMode()` satırındaki isme bak.

4. [temel] `digitalWrite(D5, HIGH);` satırı ne yapar?
   - A) D5 pinine gerilim gönderir, LED yanar ✅
   - B) D5 pininin modunu ayarlar
   - C) 5 saniye bekler
   - D) LED'e renk gönderir
   - ipucu: Ders 1.1'deki `neopixelWrite` ile karıştırma — bu komut daha basit, sadece açık/kapalı.

5. [ileri] LED'i ters taksaydın (bacakları yer değiştirseydin) ne olurdu?
   - A) LED daha parlak yanardı
   - B) LED hiç yanmazdı ✅
   - C) Direnç yanardı
   - D) Kart bozulurdu
   - ipucu: LED yönlü bir parçadır — akım sadece tek yönde geçer.

6. [ileri] Bu devrede mantık gerilimi 3.3V, direnç 220 ohm. Farklı bir kartta mantık
   gerilimi 5V olsaydı, aynı LED için genelde ne beklenir?
   - A) Aynı direnç değeri her board'da kullanılır
   - B) Direnç değeri board'un gerilimine göre yeniden hesaplanır ✅
   - C) Direnç hiç gerekmez
   - D) LED'in bacak yönü değişir
   - ipucu: Ohm Kanunu'nda gerilim değişirse ne değişir?

## 8. AI Yoldaşı promptları

### Ders promptları
- [temel] **Kavramsal** — "Sen sabırlı bir öğretmensin. Öğrenciye LED'in neden yönlü
  bir parça olduğunu, su borusundaki tek yönlü bir vana benzetmesiyle buldurmaya
  çalış. Cevabı söyleme, önce bir soru sor."
- [temel] **digitalWrite vs neopixelWrite** — "Sen sabırlı bir öğretmensin. Öğrenci
  bir önceki derste `neopixelWrite` ile renkli bir LED yaktı, şimdi `digitalWrite` ile
  basit bir LED yakıyor. İkisi arasındaki farkı doğrudan söyleme; öğrenciye 'biri renk
  gönderiyor, öteki sadece açıp kapatıyor' fikrine kendi kendine ulaşacağı bir soru sor."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Öğrenci LED'i taktı ama
  yanmıyor. Önce hangi üç şeyi kontrol etmesi gerektiğini (yön, pin numarası, direnç)
  sorular sorarak buldur, cevabı doğrudan verme."
- [ileri] **Pekiştirme** — "Sen ileri seviye bir mentorsun. Öğrenciye direncin neden
  gerekli olduğunu, Ohm Kanunu'nu (V = I × R) hiç adını vermeden, 'gerilim sabitken
  direnç artarsa akıma ne olur' sorusuyla düşündür. Formülü sen söyleme, öğrenci
  kendi cümlesiyle ifade etsin."

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
1) LED'in bacaklarını yer değiştirerek tak (ters bağla). Ne oluyor, gözlemle.
2) LED'in kablosunu D5'ten D6'ya taşı. Kodda da neyi değiştirmen gerekiyor?
   Değiştir ve çalıştır.
3) LED'i 3 saniye yanık, 1 saniye sönük kalacak şekilde çalıştır. Hangi satırları,
   nasıl değiştirmen gerekiyor?
