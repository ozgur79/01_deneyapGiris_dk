---
dk_no: dk0090
portal_ders: "8.1"
portal_ders_not: "Portal-Ders-Haritasi.md 12 modüllü yapıya taşındı (Özgür, 2026-09-24): dk0090 eski 4.2'den 8.1'e taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
baslik: Kumanda kolu ile motor yönü ve hızını ayarla
duzey: 0-temel
unite: 4-Motor
kazanimlar: [cpp.setup-loop, cpp.delay, cpp.const-int, cpp.if-else, cpp.serial-begin, cpp.serial-println]
kara_kutu: [void, Deneyap_CiftKanalliMotorSurucu, DualMotorDriver, Deneyap_KumandaKolu, Joystick, MotorSurucu.begin, KumandaKolu.begin, KumandaKolu.yRead, MotorSurucu.MotorDrive, MotorSurucu.CheckMotorError, MOTOR1, MOTOR2, uint16_t, map, constrain]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Kumanda Kolu, Deneyap Çift Kanallı Motor Sürücü, 2 adet 6V LEGO uyumlu DC motor, 2 adet 18650 pil + seri bağlı pil yuvası, çıt çıt anahtar (pil hattında), jumper kablolar, LEGO araç gövdesi]
board:
  kart: Deneyap Mini v2
  kumanda_kolu_i2c_adresi: "0x1A"
  motor_surucu_i2c_adresi: "0x16"
  i2c_paylasim_notu: "Kumanda kolu ve motor sürücü aynı I2C hattını paylaşır; ikisi de kendi adresiyle begin() ile başlatılır, hattı bölüşmek için ekstra bir ayar gerekmez."
  besleme: "Motor sürücü seri bağlı 2 x 18650 pilden beslenir (~8,4V dolu), kartın beslemesinden ayrıdır. Pil hattında çıt çıt anahtar var; anahtar pil yuvasının jumper hattına lehimlidir; hattın hazır jumper uçları motor sürücünün vidalı besleme girişine tornavidayla sıkıştırılır (Özgür, 2026-09-24)."
  motor_yonu: "Motorlar araca karşılıklı takılı (dk0080'deki Özgür testi, 2026-09-24). Kod MOTOR2'ye 1 - yon gönderir; kaynak koddan tek sapma budur."
  max_hiz_notu: "İki AYRI sınır var. (1) Donanımsal tavan %70: kaynak kodun kendi notu, motorlara giden gerilimi ~6V'ta tutmayı amaçlar (2 dolu 18650 pil ~8,4V verir); kesin 6V için gerilim düşürücü gerekir. (2) Güvenlik tavanı %20 (maxHiz=20): Özgür aracı test ederken ileri/geri geçişlerin çok sert olduğunu, çocuğun elindeyken aracın fırlayıp masadan düşebileceğini gördü (2026-09-24) ve bu ders için ikinci, daha sıkı bir sınır koydu. Bu derste geçerli olan sınır %20'dir, %70 yalnız donanımın kaldırabileceği üst tavandır. map'in hedef aralığı da 0-100 yerine 0-maxHiz yapıldı: kolun küçük hareketi bile hızı orantılı ve yumuşak artırsın diye (kaynaktan bilinçli sapma)."
  seri_hiz: 115200
  guvenlik_notu: "Motorlar pil takılıyken beklenmedik anda dönebilir. Kart/motor sürücü masada, tekerlekler havada dururken test edilir."
kaynak_kod: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2501kk_deneyapMotorSurucu_2Motor\\dyminiV2501kk_deneyapMotorSurucu_2Motor.ino (ana kaynak — birebir öğretim hâli)"
---

## 1. Hedef

`dk0080`'de motorlara hız ve yönü sabit yazdın. `dk0060`/`dk0070`'te ise
joystick'in Y değerini okuyup LED parlaklığına çevirmiştin. Bu ders ikisini
birleştiriyor: kolu ittiğin kadar motorlar hızlanacak, kolu bıraktığında
duracak, kolu geriye ittiğinde motorlar ters dönecek.

**Güvenlik:** Araç en fazla **%20** hızla gider. Bunu `maxHiz` satırından
değiştirebilirsin, ama **70'i geçme** — bu, motorların kaldırabileceği
donanımsal tavandır; %20 ise Özgür'ün çocuk güvenliği için koyduğu ayrı,
daha sıkı bir sınırdır.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Kumanda Kolu
- Deneyap Çift Kanallı Motor Sürücü
- 2 adet 6V LEGO uyumlu DC motor
- 2 adet 18650 pil, seri bağlı pil yuvasında
- Çıt çıt anahtar ve jumper kablolar (`dk0080`'deki gibi)
- LEGO araç gövdesi (`dk0080`'deki, motorlar takılı)

## 3. Parça tanıtımı

- **Ölü bölge:** Joystick'in Y değeri 480 ile 540 arasındaysa kod motorları
  durdurur. Kol tam ortadayken elin ufak titremesi motorları rastgele
  hareket ettirmesin diye bu aralık bilerek bırakılır.
- **`map` + `constrain`:** `dk0070`'te `map` bir aralığı başka bir aralığa
  çeviriyordu. Burada aynı fikir kullanılıyor, ama sonuç ek olarak
  `constrain` ile `maxHiz` sınırının üstüne çıkmayacak şekilde kırpılıyor.

## 4. Devre kurulumu

1. Bilgisayara bağlıysa kartın enerjisini kes.
2. `dk0080`'deki motor sürücü, motor ve pil bağlantısını aynen koru.
3. Kumanda kolunu `dk0060`'daki gibi I2C kablosuyla bağla: kablo kartın ve
   kumanda kolunun I2C soketlerine takılıdır, SDA/SCL'e tek tek jumper
   çekilmez. Motor sürücü (`0x16`) ve kumanda kolu (`0x1A`) aynı I2C hattını
   paylaşır; ikisini de aynı anda bağlı tutabilirsin.
4. **Güvenlik:** Çıt çıt anahtar **kapalı** olsun. Aracı tekerlekleri havada
   kalacak şekilde masaya koy.
5. Kartı Type-C USB kablosuyla bilgisayara bağla, kodu yükle, sonra anahtarı aç.

## 5. Kod açıklaması

Akış yedi adımdır: **oku → yön/eşik belirle → aralığı hıza çevir → hızı
sınırla → motorlara uygula → hatayı kontrol et → ekrana yaz**.

| kod satırı | açıklama |
| --- | --- |
| `DualMotorDriver MotorSurucu;` / `Joystick KumandaKolu;` | **Kara kutu:** iki hazır aracı kendi adlarıyla kullanmamızı sağlar. |
| `const uint16_t ileriEsik = 540;` / `geriEsik = 480;` | Y değerinin ileri/geri kararını verdiği eşikler; aradaki bölge ölü bölgedir. |
| `const int maxHiz = 20;` | `dk0080`'deki sabit hızın burada üst sınıra dönüşmüş hâli. Kaynakta 70 idi; Özgür'ün güvenlik kararıyla 20'ye düşürüldü. |
| `MotorSurucu.begin(0x16)` / `KumandaKolu.begin(0x1A)` | **Kara kutu:** iki modülü kendi I2C adresleriyle başlatır; biri başarısız olursa kod orada bekler. |
| `uint16_t yEkseni = KumandaKolu.yRead();` | Her turda önce kolun Y değeri okunur — `dk0060`'daki aynı satır. |
| `int hiz = 0; int yon = 1;` | Her turun başında hız sıfırlanır, yön varsayılan olarak ileri kabul edilir. |
| `if (yEkseni > ileriEsik) {` | Y değeri 540'ı geçtiyse ileri hareket hesaplanır. |
| `hiz = map(yEkseni, ileriEsik, 1020, 0, maxHiz);` | **Kara kutu `map`:** 540-1020 aralığını doğrudan 0-`maxHiz` hıza çevirir. Kaynakta hedef aralık 0-100'dü; burada 0-`maxHiz` yapıldı ki kolun küçük bir hareketi bile hızı yumuşak ve orantılı artırsın (0-100'e eşleyip sonra kırpmak, kolu azıcık ittiğinde hızın hemen tavana çıkmasına yol açardı). |
| `hiz = constrain(hiz, 0, maxHiz);` | **Kara kutu `constrain`:** artık bir emniyet katıdır — `map` zaten `maxHiz`'e eşliyor, `constrain` sınır dışı bir değer sızarsa onu keser. |
| `} else if (yEkseni < geriEsik) {` | Y değeri 480'in altındaysa geri hareket hesaplanır, aynı `map`/`constrain` mantığıyla. |
| `MotorSurucu.MotorDrive(MOTOR1, hiz, yon);` | Hesaplanan hız ve yönü birinci motora uygular. |
| `MotorSurucu.MotorDrive(MOTOR2, hiz, 1 - yon);` | Aynı hızı ikinci motora uygular, ama yönü **ters çevirir**: `yon` 1 ise `1 - 1 = 0`, `yon` 0 ise `1 - 0 = 1`. Sebep `dk0080`'deki gibi: motorlar araca karşılıklı takılı; aynı yön değeri aracı kendi etrafında döndürürdü. |
| `MotorSurucu.CheckMotorError()` | Motorlarda hata olup olmadığını kontrol eder; `dk0080`'deki aynı çağrı. |
| `Serial.print(...)` | Y değerini ve hesaplanan hızı ekrana yazar. |
| `delay(20);` | Bir sonraki okuma için kısa süre bekler. |

### İleri analiz [ileri]

Ölü bölge olmasaydı, kol tam ortadayken bile okunan sayı 540'ın hafifçe üstüne
ya da 480'in hafifçe altına düşebilir ve motorlar istemeden dönebilirdi.
480-540 aralığı bu titremeyi yutan bir tampon bölgedir. `dk0070`'teki `if
(ileri < 10) { ileri = 0; }` satırı da benzer bir amaca hizmet ediyordu:
küçük/gürültülü değerleri sıfıra çekmek.

## 6. Çalıştır ve gözlemle

Kodu karta yükle, Seri Monitör'ü **115200** hızında aç. Kolu bırakılmış
hâlde motorların durduğunu doğrula. Kolu yavaşça ileri it: Y değeri 540'ı
geçince motorların dönmeye başladığını, `Hiz: %` değerinin arttığını gözlemle.
Aynısını geri yönde dene.

### Sorun giderme

- **Kütüphanelerden biri bulunamadığı için kod derlenmiyor:**
  `Deneyap_CiftKanalliMotorSurucu.h` ya da `Deneyap_KumandaKolu.h`
  geliştirme ortamında yok; kurulumu doğrulamadan devam etme.
- **"Motor surucuye I2C baglantisi basarisiz" ya da "Kumanda kolu
  bulunamadi":** İlgili modülün I2C kablosunun soketine tam oturduğunu
  kontrol et; iki modül de aynı hatta bağlıdır ama ayrı adreslerle konuşur.
- **Motorlar hiç dönmüyor, Seri Monitör "Hiz: %0" gösteriyor:** Kolu
  gerçekten 540'ı geçecek ya da 480'in altına inecek kadar itip itmediğini
  kontrol et; ölü bölge içindeysen bu normaldir.
- **Y değeri değişiyor ama motorlar tepki vermiyor:** Önce çıt çıt anahtarın
  açık olduğunu kontrol et, sonra 18650 pil yuvasının motor sürücüye bağlı
  ve dolu olduğunu kontrol et.
- **"HATA!" satırı çıkıyor:** `CheckMotorError()` bir sorun bildiriyor;
  motor bağlantılarını ve pil gücünü kontrol et.
- **Kol ileri iterken araç geri gidiyor (ya da tersi):** İki motorun
  kablosunu da ters çevir ya da koddaki `yon = 1` / `yon = 0` atamalarını
  yer değiştir.
- **Kolu itince araç düz gitmek yerine kendi etrafında dönüyor:** Motorlardan
  biri bu dersteki montajdan farklı yönde takılı. `MOTOR2` satırındaki
  `1 - yon` yerine `yon` yazmayı dene (`dk0080`'deki sorun giderme ile aynı).
- **Kod karta yüklenmiyor:** Kart modelini, portu ve USB kablosunun veri
  aktarabildiğini kontrol et.

## 7. Mini sınav

1. [temel] Kol tam ortadayken (480-540 arası) motorlar ne yapar?
   - A) Tam hızda dönerler
   - B) Durur
   - C) Rastgele yön değiştirirler
   - D) Hata verirler
   - ipucu: "Ölü bölge" tanımına bak.

2. [temel] `constrain(hiz, 0, maxHiz)` ne işe yarar?
   - A) Hızı 0 ile maxHiz arasına sıkıştırır
   - B) I2C adresini değiştirir
   - C) Y değerini okur
   - D) Motoru durdurur
   - ipucu: Fonksiyon adı "sınırlamak" anlamına gelir.

3. [temel] `MotorDrive`'a gönderilen `yon` değeri nereden geliyor?
   - A) Sabit bir sayıdan
   - B) `if`/`else if` bloklarında Y eşiklerine göre belirleniyor
   - C) `CheckMotorError()`'dan
   - D) `Serial.print`'ten
   - ipucu: `yon = 1;` ve `yon = 0;` satırlarının hangi bloklarda olduğuna bak.

4. [temel] Motor sürücü ve kumanda kolu nasıl aynı anda bağlı kalabiliyor?
   - A) Aynı I2C hattını farklı adreslerle (0x16 / 0x1A) paylaşarak
   - B) Farklı USB kabloları kullanarak
   - C) Sırayla bağlanıp sökülerek
   - D) Aynı pinlere jumperla bağlanarak
   - ipucu: `board:` bloğundaki `i2c_paylasim_notu`'na bak.

5. [ileri] `dk0080`'deki sabit `hiz` değişkeni bu derste neye dönüştü?
   - A) Bir üst sınıra (`maxHiz`)
   - B) Bir I2C adresine
   - C) Bir eşik değerine (540)
   - D) Kaldırıldı, hiç kullanılmıyor
   - ipucu: §5 tablosundaki `constrain` satırına bak.

6. [ileri] 480-540 ölü bölgesi olmasaydı ne olabilirdi?
   - A) Kol tam ortadayken bile küçük okuma titremeleri motorları hareket ettirebilirdi
   - B) I2C adresi değişirdi
   - C) Seri Monitör hızı düşerdi
   - D) Motorlar hiç dönmezdi
   - ipucu: §5 İleri analiz'e bak.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme.

### Ders promptları

- [temel] **Girdi → hareket:** "Sen sabırlı bir öğretmensin. Bağlam: Deneyap
  Mini v2'de joystick Y değerini motor hızı ve yönüne çeviriyorum; motor
  sürücü 0x16, kumanda kolu 0x1A adresinde, seri hız 115200. Bana pin
  numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Okuma,
  eşiğe bakma, aralık çevirme ve motora uygulama adımlarını sıralatacak
  tek bir soru sor; cevabı söyleme."
- [temel] **Ölü bölge:** "Sen öğrenme koçumsun. Bağlam: Kodumda Y değeri
  480-540 arasındayken motorlar duruyor. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. Bu aralığın neden sıfır değil de
  bir bant olduğunu düşündüren bir soru sor; cevabı verme."
- [temel] **Hata ayıklama:** "Sen hata ayıklama koçumsun. Bağlam: Deneyap
  Mini v2'de motor sürücü ve kumanda kolu I2C ile bağlı; kolu ittiğimde
  motorlar tepki vermiyor. Bana pin numarası, direnç değeri, menü yolu
  veya bağlantı tarifi verme. I2C bağlantısı, pil beslemesi ve ölü bölgeyi
  sırayla ayıran sorular sor; cevabı verme."

### Kara kutu promptları

- [temel] **`map` ve `constrain` birlikte:** "Sen meraklı bir öğretmensin.
  Bağlam: Kodumda `map(yEkseni, ileriEsik, 1020, 0, 100)` sonrasında
  `constrain(hiz, 0, maxHiz)` çağrılıyor. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. Aralık çevirmekle sonucu sınırlamak
  arasındaki farkı düşündüren bir soru sor; cevabı söyleme."
- [temel] **İki I2C modülü:** "Sen meraklı bir öğretmensin. Bağlam:
  `MotorSurucu.begin(0x16)` ve `KumandaKolu.begin(0x1A)` aynı programda
  yan yana duruyor. Bana pin numarası, direnç değeri, menü yolu veya
  bağlantı tarifi verme. İki farklı adresin aynı hatta nasıl karışmadan
  çalışabildiğini düşündüren bir soru sor; cevabı söyleme, I2C ileride
  tam açılacak."
- [temel] **`MotorDrive` ve `CheckMotorError`:** "Sen meraklı bir öğretmensin.
  Bağlam: Her turda `MotorDrive` ile motorları sürüyor, `CheckMotorError`
  ile hatayı kontrol ediyorum. Bana pin numarası, direnç değeri, menü yolu
  veya bağlantı tarifi verme. Motoru sürmekle motoru denetlemek arasındaki
  farkı düşündüren bir soru sor; cevabı söyleme."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kod yüklenmeden önce çıt çıt anahtar kapalı, tekerlekler havada mıydı?
2. Kol bırakılmışken motorlar duruyor mu, Seri Monitör "Hiz: %0" mu gösteriyor?
3. Kolu ileri/geri ittiğinizde Y değeri ve hız birlikte, tutarlı biçimde mi değişiyor?

## 9. SEN YAP

1. `ileriEsik`/`geriEsik` değerlerini (540/480) birlikte değiştir; önce
   ölü bölgenin nasıl değişeceğini tahmin et, sonra kolu iterek gözlemle.
2. `maxHiz` değerini 20'den küçük bir sayıya indir (örn. 10). Kolu sonuna
   kadar ittiğinde Seri Monitör'deki `Hiz: %` değeri kaçta sınırlanıyor?
   `maxHiz`'i 20'nin üstüne çıkarma — bu güvenlik sınırıdır.
3. `delay(20)` süresini büyüt. Kolu hızlıca ileri-geri oynattığında
   motorların tepkisi ile ekrandaki sayıların güncellenme hızı arasındaki
   ilişkiyi kendi cümlenle anlat.
