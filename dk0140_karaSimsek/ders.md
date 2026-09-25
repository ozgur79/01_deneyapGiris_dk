---
dk_no: dk0140
portal_ders: "1.5"
kaynak_ak: [ak0060]
baslik: Kara şimşek (elle)
duzey: 0-temel
unite: 0-LED
kazanimlar:
  - cpp.const-int
  - cpp.coklu-cikis
  - cpp.kod-tekrari
  - hw.coklu-led
kara_kutu: [void, OUTPUT]
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 4 LED
  - 4 adet 220 ohm direnç
  - breadboard
  - 8 jumper kablo
board:
  kart: Deneyap Mini v2
  led_pinleri: ["D5", "D6", "D9", "D10"]
  pin_notu: "D5 ve D6, Ders 1.4'ün (dk0030) devresinden devam eder. Üçüncü ve dördüncü LED için D7/D8 kullanılmadı çünkü I2C'ye ayrılmış (yalnız I2C uyumlu bağlantı); D13 kullanılmadı çünkü GPKEY/BOOT butonuyla paylaşılıyor. D9 ve D10 genel amaçlı dijital I/O pinleri olduğu için seçildi. Bkz. Donanim-Referans-DYMv2.md pin tablosu."
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
kaynak_kod: ak0060_karaSimsek/ak0060_karaSimsek.ino
---

## 1. Hedef
Ders 1.4'te (dk0030) iki LED'i sırayla yakmış, birine "isim" vermiştin. Bu derste dört
LED'i yan yana dizip aralarında gidip gelen bir ışık yapacaksın — eski dizilerdeki
"kara şimşek" efekti. Devre kolay, asıl olay kodda: her adımda dört LED'in de ne
yapacağını tek tek yazacaksın ve kod uzayacak. **Bu uzunluk bir kaza değil, dersin
konusu.**

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu
- 4 LED
- 4 adet 220 ohm direnç
- breadboard
- 8 jumper kablo

## 3. Parça tanıtımı
Yeni parça yok — Ders 1.4'te tanıdığın LED ve dirençten iki tane daha ekliyorsun, toplam
dört. **Her LED'in kendi direnci olmalı**; birden fazla LED tek dirence bağlanırsa hepsi
sönük yanar ve desen zor görünür. LED'leri breadboard'a soldan sağa, yan yana ve
aralarında eşit boşluk olacak şekilde diz — desenin gidip geldiğini görebilmen buna
bağlı.

## 4. Devre kurulumu
Ders 1.4'ün D5/D6 devresi duruyorsa sökme. Üçüncü ve dördüncü LED için şunları ekle:
1. Dört LED'i breadboard'a soldan sağa yan yana tak (birinci ve ikinci zaten duruyor
   olabilir).
2. Soldaki LED'in uzun bacağından (+) **D5**'e bağlan.
3. Sıradakilerin uzun bacaklarını sırayla **D6**, **D9** ve **D10**'a bağlan.
4. Her LED'in kısa bacağını (−) kendi 220 ohm direncine, her direncin diğer ucunu
   GND'ye bağlan.

Metin şeması:
- 1. LED (+) → D5, (−) → 220 ohm direnç → GND
- 2. LED (+) → D6, (−) → 220 ohm direnç → GND
- 3. LED (+) → D9, (−) → 220 ohm direnç → GND
- 4. LED (+) → D10, (−) → 220 ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `// Dört LED'i dört ayrı pine bağlarsan dördünü de ayrı ayrı yönetebilirsin` | Dört LED dört ayrı pine bağlanırsa dördü de ayrı ayrı yönetilebilir. |
| `// Her adımda dört LED'in de ne yapacağını tek tek yazıyoruz: biri HIGH, üçü LOW` | Her adımda dört LED'in de durumu tek tek yazılır: biri `HIGH`, üçü `LOW`. |
| `// Desen gidip geliyor: 1-2-3-4-3-2, sonra baştan` | Desen gidip gelir: 1-2-3-4-3-2, sonra başa döner. |
| `const int led1 = D5;` (ve led2/led3/led4) | D5, D6, D9 ve D10 pinlerine `led1`-`led4` adları verilir. İsim verme (`const int`) kavramını Ders 1.4'te görmüştün. |
| `pinMode(led1, OUTPUT);` (dört satır) | Dört pinin dördü de çıkış moduna alınır; her pinin kendi satırı vardır. |
| `digitalWrite(led1, HIGH);` | O adımda yanacak LED'in pini açılır. |
| `digitalWrite(led2, LOW);` | O adımda yanmayacak LED'lerin pinleri kapatılır. |
| `delay(300);` | O adımın görüntüsü 300 milisaniye ekranda kalır. |
| `}` (setup ve loop sonu) | `;` bir komutun bittiğini, `}` bloğun bittiğini gösterir. |

### İleri analiz [ileri]
`loop()` içinde **6 adım** var; her adım **4 satır `digitalWrite` + 1 satır `delay`** =
5 satır. Toplam **30 satır**, ve bunların 24'ü birbirinin neredeyse aynısı — sadece
hangi LED'in `HIGH` olduğu değişiyor.

Desen neden 6 adım, 8 değil? Çünkü gidip gelirken **uçlar tekrar edilmez**: 1-2-3-4-3-2
dizisinden sonra `loop()` başa döner ve 1 yanar. Diziye sondan bir de 1 eklenirse 1. LED
her turda iki kat uzun yanar ve desen aksar.

Beş LED'e çıkarsan adım sayısı 8 olur (1-2-3-4-5-4-3-2) ve her adım 5 `digitalWrite`
ister: 8 × 6 = **48 satır**. Yani bir LED eklemek koda 18 satır ekliyor. Bu büyüme,
ilerideki döngü konusunun neden var olduğunu anlatan asıl sebeptir.

## 6. Çalıştır ve gözlemle
Kod yüklendiğinde ışık soldan sağa yürür, sağ uca varınca geri döner ve bunu sürekli
tekrar eder. Her LED 300 milisaniye yanık kalır. Doğru çalışıyorsa uçlardaki LED'ler
diğerleriyle **aynı sürede** yanar — biri daha uzun yanıyorsa desende bir adım fazladır.

### Sorun giderme
- **Bir LED hiç yanmıyor, diğer üçü çalışıyor** → Sırayla üç şey: o LED'in `pinMode`
  satırı yazılmış mı, LED ters mi takılmış, kablo doğru pinde mi.
- **Işık soldan sağa gitmiyor, sırası karışık** → LED'lerin fiziksel dizilişi kodun
  sırasıyla uyuşmuyor. Breadboard'da soldan sağa D5-D6-D9-D10 sırası korunmalı.
- **Uçtaki LED diğerlerinden uzun yanıyor** → Desende fazla bir adım var; gidiş-dönüşte
  uçlar tekrar edilmez.
- **Hepsi aynı anda yanıp sönüyor** → Bir adımda birden fazla `digitalWrite` `HIGH`
  bırakılmış olabilir; her adımda tam bir tane `HIGH` olmalı.
- **Hepsi çok sönük yanıyor** → Dört LED tek dirence bağlanmış olabilir; her LED'in
  kendi direnci olmalı.
- **Hiçbiri yanmıyor** → GND bağlantısı kopuk olabilir; dört direncin de GND'ye
  ulaştığını kontrol et.
- **Kod yüklenmiyor** → `Araçlar > Kart > Deneyap Kartlar > Deneyap Mini v2` ve
  `Araçlar > Port` seçimlerini doğrula.

## 7. Mini sınav
1. [temel] `loop()` içinde kaç adım var?
   - A) 4
   - B) 6
   - C) 8
   - D) 30
   - ipucu: Yorum satırlarındaki "1. adım", "2. adım" ifadelerini say.

2. [temel] Her adımda neden dört tane `digitalWrite` satırı var?
   - A) Dört LED'in de o adımdaki durumu tek tek yazılıyor
   - B) Her LED dört kez yakılıyor
   - C) Dört farklı renk için
   - D) Kart dört satır ister
   - ipucu: Bir LED yanarken diğer üçüne ne oluyor?

3. [temel] Işık sağ uca vardıktan sonra ne olur?
   - A) Söner ve program durur
   - B) Baştan sağ uca atlar
   - C) Geri döner, soldan devam eder
   - D) Dördü birden yanar
   - ipucu: Desen 1-2-3-4-3-2.

4. [temel] `const int led3 = D9;` satırı ne yapar?
   - A) D9 pinine `led3` adını verir
   - B) 3 numaralı LED'i 9 kez yakar
   - C) 9 milisaniye bekler
   - D) Üçüncü LED'i açar
   - ipucu: Ders 1.4'te (dk0030) öğrendiğin satır.

5. [ileri] Desende sondan bir kez daha 1. adım eklenseydi ne olurdu?
   - A) Hiçbir sorun olmaz
   - B) Kod derlenmez
   - C) 1. LED her turda iki kat uzun yanar, desen aksar
   - D) 4. LED hiç yanmaz
   - ipucu: `loop()` bittikten sonra hangi adım gelir?

6. [ileri] Beş LED'lik bir kara şimşekte `loop()` içinde kaç `digitalWrite` satırı olur?
   - A) 20
   - B) 24
   - C) 40
   - D) 48
   - ipucu: 8 adım × her adımda 5 LED'in durumu.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı sana devrenin nasıl kurulacağını, hangi pine
> bağlayacağını ya da hangi direnci kullanacağını **söylemez** — bunlar zaten bu derste
> yazıyor. **AI'ın dediği devrende/kartında çalışmıyorsa AI yanılmıştır, devren
> haklıdır.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6'daki Sorun giderme
> ve aşağıdaki "Yanındaki Yetişkine" kartıyla tamamlayabilirsin.

### Ders promptları
- [temel] **Kavramsal** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5/D6/D9/D10 pinlerine bağlı dört LED ve her biri
  için 220 ohm direnç kullanıyorum. Gidip gelen bir ışık deseni yazdım ve kodum çok
  uzadı. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Daha
  kısa yazmanın yolunu söyleme; bunun yerine 'bu satırların hangileri gerçekten
  birbirinden farklı?' diye sorarak farkı kendim görmemi sağla."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Deneyap Mini v2'de
  D5/D6/D9/D10 pinlerine 220 ohm dirençlerle bağlı dört LED'im var; üçü çalışıyor, biri
  hiç yanmıyor. Bana pin numarası, direnç değeri veya bağlantı tarifi verme. Bunun
  yerine hangi üç şeyi sırayla kontrol etmem gerektiğini soru sorarak buldur."
- [ileri] **Pekiştirme** — "Sen ileri seviye bir mentorsun. Deneyap Mini v2'de dört
  LED'lik bir desenim var; her adım 4 satır, 6 adım = 30 satır. Beşinci LED eklersem
  kaç satır olacağını sen hesaplama; 'adım sayısı nasıl değişir, her adımda kaç satır
  olur' diye sorarak bana hesaplattır. Pin numarası ya da direnç değeri verme,
  gerekmiyor zaten."

### Yanındaki yetişkine
Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. Çalışmayan LED'in uzun bacağı doğru yöne mi bakıyor?
2. Koddaki pin adıyla (D5/D6/D9/D10) kablonun takılı olduğu pin aynı mı?
3. O LED'in direncinin iki ucu da breadboard'a tam oturmuş mu?

Üçü de doğruysa ve LED hâlâ yanmıyorsa §6 Sorun giderme'deki "Kod yüklenmiyor"
maddesine bakın.

### Kara kutu promptları
- [temel] **`void` nedir?** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında dört LED yakıp söndüren bir kod yazdım, `void setup()` ve `void loop()`
  görüyorum. Bana pin numarası, direnç değeri veya bağlantı tarifi verme. Cevabı
  vermeden, `void`'in bir şeyin olup olmadığını mı yoksa bir şeyin nasıl davranacağını
  mı anlattığını düşündürecek bir soru sor; konu ileride tam açılacak."
- [temel] **`OUTPUT` nedir?** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında dört LED'in dördüne de `pinMode(..., OUTPUT)` yazdım. Bana pin numarası,
  direnç değeri veya bağlantı tarifi verme. Cevabı vermeden, bir pinin dışarı elektrik
  verme ya da dışarıdan bilgi alma görevi olabileceğini düşündürecek bir soru sor; konu
  buton dersinde açılacak."

## 9. SEN YAP
1) Deseni ters yönde başlat: ışık soldan değil sağdan başlasın (led4'ten led1'e gidip
   geri dönsün). Kaç satırın yerini değiştirmen gerekti?
2) Beşinci bir LED eklesen, `loop()` içine kaç satır eklemen gerekirdi? Önce tahmin et,
   defterine yaz; sonra tek tek sayarak kontrol et. (Devreyi kurmana gerek yok, bu bir
   sayma görevi.)
3) Bekleme süresini 300'den 100'e düşür. Kaç satıra dokunman gerekti? Ders 1.4'te
   öğrendiğin isim vermeyi (`const int`) hatırla: bunu tek satırdan değiştirilebilir
   hâle getirebilir misin?

**Not:** Bu dersin kodu uzun ve satırların çoğu birbirinin neredeyse aynısı. Yazarken
hissettiğin o rahatsızlık haklı — aynı deseni çok daha kısa yazmanın bir yolu var. Onu
Modül 2'de (seri port) öğreneceğiz ve bu devreye geri dönüp aynı işi birkaç satırda
yapacağız.
