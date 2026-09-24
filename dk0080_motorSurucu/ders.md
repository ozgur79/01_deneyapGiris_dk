---
dk_no: dk0080
portal_ders: "7.1"
portal_ders_not: "Portal-Ders-Haritasi.md 12 modüllü yapıya taşındı (Özgür, 2026-09-24): dk0080 eski 4.1'den 7.1'e taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
baslik: Motor sürücü ile iki motoru döndür
duzey: 0-temel
unite: 4-Motor
kazanimlar: [cpp.setup-loop, cpp.delay, cpp.const-int, cpp.if-else, cpp.serial-begin, cpp.serial-println]
kara_kutu: [void, Deneyap_CiftKanalliMotorSurucu, DualMotorDriver, MotorSurucu.begin, MotorSurucu.MotorDrive, MotorSurucu.CheckMotorError, MOTOR1, MOTOR2]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Çift Kanallı Motor Sürücü, 2 adet 6V LEGO uyumlu DC motor, 2 adet 18650 pil + seri bağlı pil yuvası, çıt çıt anahtar (pil hattında), jumper kablolar, LEGO araç gövdesi]
board:
  kart: Deneyap Mini v2
  motor_surucu_i2c_adresi: "0x16"
  besleme: "Seri bağlı 2 x 18650 pil (dolu hâlde ~8,4V). Kartın kendi beslemesinden ayrıdır; motor sürücü bu pil setinden beslenir. Pil hattında bir çıt çıt anahtar var; anahtar pil yuvasının jumper hattına lehimlidir; hattın hazır jumper uçları motor sürücünün vidalı besleme girişine tornavidayla sıkıştırılır (Özgür, 2026-09-24)."
  motor_yonu: "Motorlar araca karşılıklı (ayna gibi) takılı: araç ileri = MOTOR1 yön 1 + MOTOR2 yön 0; geri = MOTOR1 0 + MOTOR2 1. Özgür bunu LEGO araçta test ederek belirledi (2026-09-24); montaj farklıysa ters çıkabilir."
  test_degerleri: "hiz = 15, her adım 500 ms. Özgür bu değerleri LEGO araçta test edip onayladı (2026-09-24)."
  max_hiz_notu: "Kaynak kod hızı %70 ile sınırlar (bu derste kullanılan 15 bu sınırın çok altındadır); bu, motorlara giden gerilimi yaklaşık 6V'ta tutmayı amaçlayan yaklaşık bir sınırdır. Kesin 6V için donanımsal gerilim düşürücü gerekir — kaynak kod bunu böyle söylüyor, gerekçe uydurulmadı."
  seri_hiz: 115200
  guvenlik_notu: "Motorlar pil takılıyken beklenmedik anda dönebilir. Bu derste ve dk0090/dk0100'de kart/motor sürücü masada, tekerlekler ya da hareketli parça havada dururken test edilir. Bu bir pedagoji kararıdır, kaynakta yazmaz."
kaynak_kod: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2501kk_deneyapMotorSurucu_2Motor\\dyminiV2501kk_deneyapMotorSurucu_2Motor.ino (alt küme — kumanda kolu çıkarıldı; begin(0x16), MotorDrive, CheckMotorError aynen korunur)"
---

## 1. Hedef

Şimdiye kadar kart LED yaktı, LED söndürdü, sayı okudu. Bu derste ilk kez kartın
dışarıya **hareket** verdiğini göreceksin: LEGO aracın iki motoru, kodun söylediği
hızda ve yönde dönecek. Araç yarım saniye ileri, yarım saniye geri gidecek.
`dk0090`'da bu aracı kumanda koluyla süreceksin. Önce motor sürücünün tek başına
nasıl çalıştığını gör.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Çift Kanallı Motor Sürücü
- 2 adet 6V LEGO uyumlu DC motor
- 2 adet 18650 pil, seri bağlı pil yuvasında
- Çıt çıt anahtar (pil ile motor sürücü arasında) ve jumper kablolar
- LEGO araç gövdesi (motorlar gövdeye takılı)

## 3. Parça tanıtımı

- **Motor sürücü:** Kartın doğrudan süremeyeceği kadar akım çeken motorları
  sürmek için aradaki modül. Kart ona I2C üzerinden "şu hızda, şu yönde dön"
  komutu gönderir; motoru asıl döndüren akımı ayrı bir pil kaynağından alır.
- **DC motor:** Güç verilince dönen, yönü değişince ters dönen motor türü.
- **2 x 18650 pil:** Motor sürücünün güç kaynağı. Kartın kendisi USB'den ya da
  kendi beslemesinden ayrı olarak çalışmaya devam eder; motorlar bu pillerden
  güç alır.
- **Çıt çıt anahtar:** Bir kez basınca açılan, bir daha basınca kapanan anahtar.
  Pil hattının üzerinde durur. Motorların gücünü kablo sökmeden açıp kapatırsın.

## 4. Devre kurulumu

1. Bilgisayara bağlıysa kartın enerjisini kes; kablo takıp çıkarırken kartı
   çalışır durumda bırakma.
2. Motor sürücüyü karta **I2C soketinden** bağla — kumanda kolunda olduğu gibi
   tek kablo, iki soket; SDA/SCL'e tek tek jumper çekilmez. Modülün I2C adresi
   `0x16`'dır.
3. LEGO araca takılı iki motoru motor sürücünün motor çıkışlarına bağla.
   Motorlar gövdeye **karşılıklı** takılıdır: biri sağda, biri solda, birbirinin
   aynadaki görüntüsü gibi.
4. Seri bağlı 2 x 18650 pil yuvasının jumper hattında **çıt çıt anahtar**
   lehimli olarak hazır gelir. Hattın jumper uçlarını motor sürücünün vidalı
   besleme girişine takıp tornavidayla sık. Bu besleme karttan **ayrıdır**; kart kendi güç kaynağını kullanmaya
   devam eder.
5. **Güvenlik:** Çıt çıt anahtar **kapalı** olsun. Aracı, tekerlekleri havada
   kalacak şekilde masaya koy (altına bir kutu koyman yeterli). Motorlar kod
   yüklenir yüklenmez dönmeye başlayabilir.
6. Kartı Type-C USB kablosuyla bilgisayara bağla, kodu yükle, sonra anahtarı aç.

## 5. Kod açıklaması

Akış dört adımdan oluşur: **ileri → dur → geri → dur**. Her adım yarım saniye
sürer, sonra akış baştan başlar.

**Neden iki motorun yön değeri farklı?** Motorlar araca karşılıklı takılı: sağdaki
motor, soldakinin aynadaki görüntüsü gibi durur. İkisine de aynı yön değerini (`1`)
gönderirsen motorlar kendi eksenlerinde aynı yöne döner, ama tekerlekler aracı
**zıt** yönlere iter ve araç kendi etrafında döner. Aracın düz ileri gitmesi için
MOTOR1'e `1`, MOTOR2'ye `0` gönderilir. Geri giderken ikisinin değeri birden ters
çevrilir.

| kod satırı | açıklama |
| --- | --- |
| `#include <Deneyap_CiftKanalliMotorSurucu.h>` | **Kara kutu:** motor sürücünün hazır komutlarını programa getirir. |
| `DualMotorDriver MotorSurucu;` | **Kara kutu:** hazır motor sürücü aracını `MotorSurucu` adıyla kullanmamızı sağlar. |
| `const int hiz = 15;` | Motorlara gönderilecek hız yüzdesi (%15). Bu değer LEGO araçta denendi. Kaynak kodun %70 üst sınırını hiçbir zaman geçme. |
| `void setup() {` | `setup()` başlangıçta bir kez çalışır. **Kara kutu `void`:** bölüm sonunda değer döndürülmez. |
| `Serial.begin(115200);` | Seri Monitör'e yazmayı başlatır. |
| `MotorSurucu.begin(0x16)` | **Kara kutu:** kaynaktaki adresle motor sürücüyle iletişimi başlatır; başarısızsa `false` döner. |
| `while (1) delay(100);` | Bağlantı başarısız olursa kod burada bekler, `loop()`'a hiç geçmez. |
| `void loop() {` | İçindeki adımlar tekrar tekrar çalışır. |
| `MotorSurucu.MotorDrive(MOTOR1, hiz, 1);` | **Kara kutu `MotorDrive`:** birinci motoru `hiz` yüzdesinde, `1` yönünde döndürür. |
| `MotorSurucu.MotorDrive(MOTOR2, hiz, 0);` | İkinci motoru aynı hızda ama `0` yönünde döndürür. Motorlar karşılıklı takılı olduğu için araç yine **ileri** gider. |
| `delay(500);` | Motorlar bu hızda yarım saniye (500 ms) dönmeye devam eder. |
| `MotorSurucu.MotorDrive(MOTOR1/2, 0, 1);` | Hız 0 gönderilince motor durur; yön parametresi bu durumda etkisizdir. |
| `MotorDrive(MOTOR1, hiz, 0);` + `MotorDrive(MOTOR2, hiz, 1);` | İleri adımının tam tersi: araç **geri** gider. |
| `MotorSurucu.CheckMotorError()` | **Kara kutu:** motor sürücüde hata olup olmadığını bildirir; `1` ise hata var demektir. |

### İleri analiz [ileri]

Kaynak kod motorları kumanda koluyla sürüyordu; bu ders o kaynağın **alt
kümesi**dir — kumanda kolu tamamen çıkarıldı, `begin(0x16)`, `MotorDrive` ve
`CheckMotorError` aynen korundu. `dk0090`'da aynı üç çağrı, sabit sayılar
yerine joystick'ten okunan hız ve yönle çalışacak. `%70` sınırının neden tam
olarak bu sayı olduğu kaynakta açıklanmıyor; ders bu notu olduğu gibi taşıyor.
Bu dersteki `15` hızı ve yarım saniyelik adımlar ise kaynak koddan değil, LEGO araç
üzerinde yapılan denemeden geliyor. Bu değerler, masada kısa ve kontrollü bir
ileri-geri hareket için yeterli.

## 6. Çalıştır ve gözlemle

Kodu karta yükle, çıt çıt anahtarı aç, Seri Monitör'ü **115200** hızında aç.
Tekerleklerin önce ileri döndüğünü, sonra durup geri döndüğünü ve aradaki yarım
saniyelik durma anını gözlemle. Tekerlekler havadayken iki tekerleğin de aracı
**ileri** itecek yönde döndüğünü kontrol et, sonra aracı yere koy. Seri
Monitör'deki "Ileri"/"Dur"/"Geri" satırlarının motorların hareketiyle eşleştiğini
kontrol et.

### Sorun giderme

- **Kod `Deneyap_CiftKanalliMotorSurucu.h` bulunamadı diye derlenmiyor:**
  Kütüphane geliştirme ortamında yok; kurulumu doğrulamadan devam etme.
- **Seri Monitör'de "Motor surucuye I2C baglantisi basarisiz" yazıyor:**
  I2C kablosunun kart ve motor sürücü soketlerine tam oturduğunu kontrol et.
- **Seri Monitör "Sistem hazir" yazıyor ama motorlar hiç dönmüyor:** Önce çıt
  çıt anahtarın açık olduğunu kontrol et. Sonra 18650 pil yuvasının jumper uçlarının
  motor sürücüye bağlı olduğuna ve pillerin dolu olduğuna bak. I2C bağlantısı
  ile motor beslemesi ayrı devrelerdir.
- **Araç ileri gitmek yerine kendi etrafında dönüyor:** Motorlardan biri
  bu derstekinden farklı yönde takılmış ya da kablosu ters bağlanmış. Kablo
  sökmeden çözebilirsin: o motorun `MotorDrive` satırlarındaki yön değerlerini
  değiştir (`0` yerine `1`, `1` yerine `0`).
- **Yalnız bir motor dönüyor:** O motorun motor sürücü üzerindeki çıkışa
  ve kablolarına tam bağlı olduğunu kontrol et.
- **Motorlar dönüyor ama "HATA!" satırı çıkıyor:** `CheckMotorError()` bir
  sorun bildiriyor demektir; motor bağlantılarını ve pil gücünü kontrol et.
- **Motorlar vınlıyor ama araç kıpırdamıyor ya da çok güçsüz:** Pillerin dolu
  olduğunu kontrol et. `hiz`'i biraz artırabilirsin, ama %70 sınırının üstüne
  çıkarma.
- **Kod karta yüklenmiyor:** Kart modelini, portu ve USB kablosunun veri
  aktarabildiğini kontrol et.

## 7. Mini sınav

1. [temel] Bu derste motorlar hangi bilgiye göre dönüyor?
   - A) Joystick'ten okunan bir değere göre
   - B) Kodda sabit yazılmış hız ve yön değerlerine göre
   - C) LDR'den okunan ışık miktarına göre
   - D) Butona basılıp basılmadığına göre
   - ipucu: `dk0090`'a kadar joystick hiç kullanılmıyor.

2. [temel] `MotorDrive(MOTOR1, 0, 1)` çağrısında motor ne yapar?
   - A) Tam hızda ileri döner
   - B) Durur
   - C) Geri döner
   - D) Hata verir
   - ipucu: İkinci parametre hızdır; 0 ne anlama gelir?

3. [temel] Motor sürücünün gücü nereden gelir?
   - A) Kartın USB beslemesinden
   - B) Seri bağlı 2 x 18650 pilden
   - C) Kumanda kolundan
   - D) Bilgisayardan doğrudan
   - ipucu: §3 ve §4'teki besleme notuna bak.

4. [temel] `CheckMotorError()` ne işe yarar?
   - A) Motoru döndürür
   - B) Motorlarda hata olup olmadığını bildirir
   - C) I2C adresini değiştirir
   - D) Seri hızı ayarlar
   - ipucu: Fonksiyon adındaki "Error" (hata) kelimesine bak.

5. [ileri] Kaynak kodda kumanda kolu vardı, bu derste yok. Kod hangi üç
   çağrıyı aynen korudu?
   - A) `yRead`, `map`, `constrain`
   - B) `begin(0x16)`, `MotorDrive`, `CheckMotorError`
   - C) `digitalRead`, `digitalWrite`, `pinMode`
   - D) `analogRead`, `analogWrite`, `map`
   - ipucu: §5 İleri analiz'e bak.

6. [temel] Araç ileri giderken MOTOR1'e `1`, MOTOR2'ye `0` gönderiliyor. Neden
   iki motora farklı yön değeri veriliyor?
   - A) MOTOR2 bozuk olduğu için
   - B) Motorlar araca karşılıklı (ayna gibi) takılı; aynı değer tekerlekleri zıt yöne çevirir
   - C) Motor sürücü iki motora aynı değeri kabul etmediği için
   - D) Hız 15 olduğu için
   - ipucu: §5'teki "Neden iki motorun yön değeri farklı?" kısmına bak.

7. [ileri] `hiz` değeri neden 70'i geçmemeli?
   - A) Motor sürücü daha yüksek sayı kabul etmiyor
   - B) 2 dolu 18650 pilin verdiği ~8,4V'u motorlar için ~6V'a yaklaşık sınırlamak için
   - C) I2C adresi değişir
   - D) Seri Monitör hız sınırı yüzünden
   - ipucu: `board:` bloğundaki `max_hiz_notu`'na bak.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme.

### Ders promptları

- [temel] **Sabit komuttan harekete:** "Sen sabırlı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de I2C üzerinden bağlı bir motor sürücüyle iki motoru
  kodda sabit hız ve yönle döndürüyorum; seri hız 115200. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Kodda 'okuma' olmadığını,
  hız ve yönün nereden geldiğini buldurtacak bir soru sor; cevabı söyleme."
- [temel] **İleri/dur/geri sırası:** "Sen öğrenme koçumsun. Bağlam: Kodum
  motorları önce ileri, sonra durdurup geri döndürüyor, aralarda `delay`
  var. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi
  verme. `delay` süresi değişirse hareket sırasının nasıl değişeceğini
  tahmin ettiren bir soru sor; cevabı verme."
- [temel] **Hata ayıklama:** "Sen hata ayıklama koçumsun. Bağlam: Deneyap
  Mini v2'de I2C ile bağlı motor sürücü var; motorlar hiç dönmüyor. Bana
  pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. I2C
  bağlantısı, pil beslemesi ve motor kablo bağlantısını sırayla ayıran
  sorular sor; cevabı verme."

### Kara kutu promptları

- [temel] **Motor sürücü aracı:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de `Deneyap_CiftKanalliMotorSurucu.h` ve `DualMotorDriver
  MotorSurucu` yazıyorum. Bana pin numarası, direnç değeri, menü yolu veya
  bağlantı tarifi verme. Hazır araç ile ona verdiğim adın işlerini
  ayırmamı sağlayan bir soru sor; cevabı söyleme."
- [temel] **`MotorDrive` parametreleri:** "Sen meraklı bir öğretmensin.
  Bağlam: Kodumda `MotorDrive(MOTOR1, hiz, yon)` çağrısı var. Bana pin
  numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Üç
  parametrenin (motor, hız, yön) birbirinden farklı işler yaptığını
  düşündüren bir soru sor; cevabı söyleme."
- [temel] **`CheckMotorError`:** "Sen meraklı bir öğretmensin. Bağlam:
  Kodum her turda `CheckMotorError()` çağırıyor. Bana pin numarası, direnç
  değeri, menü yolu veya bağlantı tarifi verme. Bu çağrının motoru
  döndürmekle mi yoksa motoru denetlemekle mi ilgili olduğunu
  düşündüren bir soru sor; cevabı söyleme."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kod yüklenmeden önce motorlar/tekerlekler masada havada mı bırakıldı?
2. Seri Monitör'de "Motor surucuye I2C baglantisi basarisiz" yazıyor mu,
   yoksa "Sistem hazir" mi?
3. Çıt çıt anahtar açık mı?
4. Tekerlekler havadayken ikisi de aracı ileri itecek yönde mi dönüyor?

## 9. SEN YAP

1. İleri ve geri adımlarındaki `delay(500)` sürelerini önce büyüt, sonra küçült.
   Araç her adımda ne kadar yol aldı?
2. `hiz` değerini 15 yerine başka sayılarla dene (örneğin 8 ve 30). Araç hangi
   değerde hiç kıpırdamıyor, hangi değerde belirgin şekilde hızlanıyor? `hiz`'i
   %70 sınırının üstüne çıkarma.
3. Yalnız MOTOR2'nin **ileri** adımındaki yön değerini `0`'dan `1`'e çevir. Araç ne
   yaptı? Sebebini, §5'teki "Neden iki motorun yön değeri farklı?" bölümüne bakarak
   kendi cümlelerinle açıkla.
