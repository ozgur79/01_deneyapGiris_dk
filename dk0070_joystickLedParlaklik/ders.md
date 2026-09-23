---
dk_no: dk0070
portal_ders: null
portal_ders_not: "Modul2-Mufredat.md konuyu yalnız 2.2+ aday kapsamı olarak listeliyor; kesin numara tahmin edilmedi."
kaynak_ak: []
baslik: Joystick ile LED parlaklığını değiştir
duzey: 0-temel
unite: 2-Girdi okuma
kazanimlar: [cpp.setup-loop, cpp.pinmode, cpp.const-int, cpp.if-else, cpp.serial-begin, cpp.serial-println, hw.harici-led-devre]
kara_kutu: [void, Deneyap_KumandaKolu, Joystick, KumandaKolu.begin, KumandaKolu.yRead, uint16_t, uint8_t, map, analogWrite]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Kumanda Kolu, 1 LED, 1 adet 220 ohm direnç, breadboard, jumper kablolar]
board:
  kart: Deneyap Mini v2
  kumanda_kolu_i2c_adresi: "0x1A"
  harici_led_pin: "D5"
  mantik_gerilimi: 3.3V
  led_direnc: 220 ohm
  seri_hiz: 115200
  pin_notu: "D5 kart üzerindeki etikettir; çıplak GPIO/pin sayısı kullanılmaz. dk0050 LED'i D9'a bağlatmıştı: bu derste LED/direnç devresi sökülmez, yalnız LED'in kart tarafındaki jumper'ı D9'dan D5'e taşınır. Joystick pinleri kaynakta verilmediği için uydurulmaz."
kaynak_kod: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2500kkHariciLedParlaklik\\dyminiV2500kkHariciLedParlaklik.ino (ana kaynak)"
yardimci_kaynak: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2500kkDahiliLedParlaklik\\dyminiV2500kkDahiliLedParlaklik.ino (karşılaştırma için yardımcı)"
---

## 1. Hedef

`dk0060`'da joystick'in Y değerini yalnız ekranda gördün. Şimdi aynı sayı
Oturum 1'den kalan harici LED'in parlaklığını değiştirecek. `dk0050`'deki
buton LED'i açık/kapalı yapıyordu; burada ışığın **ne kadar** yandığını
gözlemleyeceksin. Ekranda hem okunan sayı hem LED'e gönderilen parlaklık
sayısı görünecek; ikisini birlikte takip edebilirsin.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Kumanda Kolu
- Oturum 1'deki harici LED, 220 ohm direnç, breadboard ve jumper kablolar

## 3. Parça tanıtımı

- **Harici LED:** `dk0020`'de kurduğun ışık. Kısa bacağı direnç üzerinden
  GND'ye, uzun bacağı çıkış pinine bağlıdır.
- **Joystick:** `dk0060`'da Y değeri Seri Monitör'de değişen kol. Aynı
  sayıyı bu kez bir çıkışa dönüştürüyorsun.
- **Parlaklık değeri:** Kodun LED'e gönderdiği 0–255 aralığındaki sayı;
  ekrandaki `LED parlaklik` etiketinin yanına da yazılır.

## 4. Devre kurulumu

1. USB kablosunu çıkar; kablolara enerjiliyken dokunma.
2. LED ve direnç devresini breadboard'dan sökme. Son yaptığın `dk0050`'de
   LED'in uzun bacağı **D9**'a gidiyordu. Yalnız LED'in kart tarafındaki
   jumper'ını D9'dan **D5**'e taşı; uzun bacağın D5'e, kısa bacağın
   220 ohm direnç üzerinden GND'ye bağlı olduğunu doğrula. `dk0070`
   kodu D5'i sürer; jumper D9'da kalırsa LED tepki vermez.
3. Joystick bağlantısını `dk0060` için **doğrulanmış set yönergesiyle**
   kurulmuş hâliyle koru. Kaynak `.ino`, modülün kablo/soket sırasını
   söylemiyor. Bu bilgi doğrulanmadan yeni bir pin veya bağlantı çizimi
   eklemek güvenilir olmaz; yönerge elinde yoksa burada dur.
4. Kartı Type-C USB ile bilgisayara bağla.

Metin şeması: LED uzun bacak (+) → D5; kısa bacak (−) → 220 ohm direnç → GND.
Joystick bağlantısı, doğrulanmış modül yönergesine göre ayrıca korunur.

## 5. Kod açıklaması

Bu kez akış beş parçalıdır: **oku → karar ver → sayıyı dönüştür → LED'e
uygula → ekrana yaz**. Hangi aşamada hata olduğunu iki ekrandaki sayıdan
ve LED'den ayrı ayrı anlayabilirsin.

| kod satırı | açıklama |
| --- | --- |
| `#include <Deneyap_KumandaKolu.h>` | **Kara kutu:** joystick'in hazır komutlarını getirir; kütüphane içi ileride açılacak. |
| `Joystick KumandaKolu;` | **Kara kutu:** joystick aracı için `KumandaKolu` adını oluşturur; sınıf/nesne ileride açılacak. |
| `const int ledPin = D5;` | Kart üzerindeki D5 etiketine `ledPin` adı verir; `const` bu adı sabit tutar. |
| `uint8_t ileri = 0;` | **Kara kutu `uint8_t`:** parlaklık sayısını saklayan türdür; veri türleri ileride açılacak. Başlangıç değeri 0'dır. |
| `void setup() {` | `setup()` başlangıçta bir kez çalışır. **Kara kutu `void`:** bölüm sonunda değer döndürülmez; fonksiyonlarda açılacak. |
| `Serial.begin(115200);` | Seri Monitör'e yazmayı başlatır; monitör de bu hızda olmalı. |
| `KumandaKolu.begin(0x1A);` | **Kara kutu:** kaynakta kullanılan I2C adresiyle joystick iletişimini başlatır. |
| `pinMode(ledPin, OUTPUT);` | D5'i LED için çıkış yapar; `dk0020`'deki fikri yeniden kullanır. |
| `analogWrite(ledPin, 0);` | **Kara kutu `analogWrite`:** LED'e parlaklık değeri uygular; başlangıçta 0 gönderir. |
| `void loop() {` | İçindeki adımlar tekrar tekrar çalışır. |
| `uint16_t yEkseni = KumandaKolu.yRead();` | **Kara kutular:** `yRead()` Y sayısını verir; `uint16_t` okunan tam sayıyı saklar. `dk0060`'daki okuma adımıdır. |
| `ileri = 0;` | Her turda önce parlaklığı sıfırlar. Böylece koşul gerçekleşmezse önceki turun değeri kalmaz. |
| `if (yEkseni > 540) {` | Y değeri kaynaktaki 540 eşiğini geçerse dönüşüm yapılır; geçmezse `ileri` 0 kalır. |
| `ileri = map(yEkseni, 540, 1020, 0, 255);` | **Kara kutu `map`:** kaynakta 540–1020 aralığını 0–255 parlaklık aralığına çevirir. |
| `if (ileri < 10) { ileri = 0; }` | Kaynakta 10'dan küçük sonuçlar 0 yapılır; bunun nedeni kaynakta açıklanmıyor. |
| `analogWrite(ledPin, ileri);` | Hesaplanan değeri harici LED'e uygular. |
| `Serial.print(...)` ve `Serial.println(ileri);` | Önce Y değerini, sonra LED'e gönderilen değeri aynı satırda gösterir; `println` satırı bitirir. |
| `delay(20);` | Bir sonraki okuma için kısa süre bekler. |

### İleri analiz [ileri]

Kolu bırakınca `ileri = 0` her tur yeniden çalışır. Bu satır silinirse
Y değeri eşiğin altına indiğinde önceki parlaklık değeri kalabilir. Kodda
önce ölçüm, sonra karar, sonra çıkış olması bu yüzden önemlidir.

`map` aralığı kaynakta **540–1020** olarak yazılmış. Kaynak, gerçek
joystick'in her zaman bu sınırda kalacağını söylemiyor; aralık dışı
okumaların nasıl göründüğünü kartta izlemek gerekir. 540 eşiğinin,
0–255 eşlemesinin ve 10'dan küçük değerleri sıfırlamanın **neden**
seçildiği de kaynakta açıklanmıyor. Burada onları kaynak davranışı
olarak öğretiyoruz. Dahili RGB LED örneği yalnız karşılaştırma
kaynağıdır; bu ders harici D5 LED devresini kullanır.

## 6. Çalıştır ve gözlemle

Kodu karta yükle, Seri Monitör hızını **115200** seç. Joystick bırakılmışken
Y ve `LED parlaklik` değerlerini not et. Kolu ileri itip Y değerinin 540'ı
geçip geçmediğine bak. Parlaklık sayısı artıyorsa LED'e bak; ikisi birlikte
değişiyor mu? Kolu bırakınca yeniden gözlemle. Kaynaktaki “ileri” yönünü
modül üzerinde fiziksel deneyle doğrula.

### Sorun giderme

- **Kütüphane bulunamadığı için kod derlenmiyor:** `Deneyap_KumandaKolu.h`
  geliştirme ortamında yoktur. Bu aşamada devreyi değiştirerek sorun çözülmez;
  önce kütüphanenin kurulumunu doğrula.
- **Seri Monitör boş:** Kodun gerçekten yüklendiğini, doğru portu ve
  monitörün açık olduğunu kontrol et. Hız 115200 olmalı.
- **Y değeri değişmiyor:** Önce `dk0060` ile aynı davranışın görülüp
  görülmediğine bak. Joystick'in doğrulanmış bağlantısını kontrol et;
  bilinmeyen pinleri deneme yanılmayla değiştirme.
- **Y değişiyor ama `LED parlaklik` hep 0:** Y değeri 540'ı geçiyor mu?
  `if` koşulunu ve her turun başındaki `ileri = 0` satırını incele.
- **Parlaklık sayısı 0'dan büyük ama LED sönük:** Okuma/eşleme kısmı
  çalışıyor demektir. `dk0050`'den kalan jumper hâlâ D9'da mı?
  LED'in yönünü, D5 bağlantısını, 220 ohm direnci ve GND hattını
  §4'teki şemayla karşılaştır.
- **LED sürekli yanık veya kol bırakılınca sönmüyor:** `ileri = 0` satırının
  `loop()` başında durduğunu ve `analogWrite(ledPin, ileri)` satırının
  her tur çalıştığını kontrol et.
- **LED birden zıplıyor / kısık aralık görünmüyor:** Ekrandaki Y ve
  parlaklık sayılarını birlikte izle; 540 eşiği ve 10'dan küçük sonuçları
  sıfırlayan satırın kaynak davranışı olduğunu unutma.
- **Kod yüklenmiyor:** Kart modeli, port ve veri aktaran USB kablosunu kontrol et.

## 7. Mini sınav

1. [temel] `dk0060`'daki Y değeri bu derste neye dönüştürülüyor?
   - A) LED parlaklık değerine
   - B) USB port numarasına
   - C) Direncin değerine
   - D) Kart adına
   - ipucu: `map` satırının son iki sayısına bak.

2. [temel] `yEkseni` 540'ı geçmezse `ileri` ne olur?
   - A) Önceki değerde kalır
   - B) Bu tur başında verilen 0 değerinde kalır
   - C) Kendiliğinden 255 olur
   - D) Seri hızına eşit olur
   - ipucu: `loop()` başındaki iki satırın sırasına bak.

3. [temel] LED'e hesaplanan parlaklığı hangi satır uygular?
   - A) `yRead()`
   - B) `analogWrite(ledPin, ileri)`
   - C) `Serial.print(...)`
   - D) `delay(20)`
   - ipucu: Okuma, yazdırma ve çıkış uygulama işlerini ayır.

4. [temel] Ekranda Y değişiyor ve parlaklık 120 yazıyor; LED sönük.
   İlk hangi kısmı kontrol edersin?
   - A) Harici LED devresini
   - B) Seri hızını
   - C) Y okuma satırını
   - D) `delay` süresini
   - ipucu: Ekrandaki iki sayı zaten hangi aşamaların çalıştığını gösteriyor?

5. [ileri] `ileri = 0` satırı her tur başında neden var?
   - A) Eşik altında eski parlaklık kalmasın diye
   - B) I2C adresi değişsin diye
   - C) Seri Monitör kapanmasın diye
   - D) LED pini giriş olsun diye
   - ipucu: Kolu ileri itip geri bıraktığında ne olacağını düşün.

6. [ileri] Kaynakta 10'dan küçük sonuçlar 0 yapılıyor. Kaynağa dayanarak
   kesin olarak hangisi söylenebilir?
   - A) Kod bu sonuçları sıfırlıyor; seçimin nedeni açıklanmıyor
   - B) Bütün joystick'ler aynı değeri üretir
   - C) LED yalnız belirli renkte çalışır
   - D) 10 sayısı I2C adresidir
   - ipucu: §5 İleri analiz'de davranışla gerekçe ayrılmıştır.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme; doğrulanmamış joystick bağlantısını
> AI'a tamamlattırma.

### Ders promptları

- [temel] **Girdi → çıktı:** "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini
  v2'de 3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli harici LED
  ve joystick var; Seri Monitör hızı 115200. Y değerini LED parlaklığına
  dönüştürüyorum. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. Okuma, dönüştürme ve çıkış uygulama adımlarını sıralatacak
  tek bir soru sor; cevabı söyleme."
- [temel] **İki sayıyla teşhis:** "Sen hata ayıklama koçumsun. Bağlam: Deneyap
  Mini v2'de D5 pininde 220 ohm dirençli LED var; joystick Y değeri ile
  LED parlaklık değeri 115200 hızındaki Seri Monitör'de yazıyor. LED
  yanmıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. Ekrandaki iki sayıya bakarak sorunun hangi aşamada
  olabileceğini bulduracak sorular sor; cevabı doğrudan verme."
- [ileri] **Eşik deneyi:** "Sen deney tasarlatan bir öğretmensin. Bağlam:
  Deneyap Mini v2'de joystick Y değeri 540'ın üstündeyken D5'teki
  dirençli LED için 0–255 arası değer hesaplanıyor. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Eşik değişmeden
  önce bir tahmin, sonra bir gözlem istemeni sağlayacak soru sor; cevabı verme."

### Kara kutu promptları

- [temel] **Joystick aracı ve çağrıları:** "Sen meraklı bir öğretmensin.
  Bağlam: Deneyap Mini v2'de `Deneyap_KumandaKolu.h`, `Joystick KumandaKolu`,
  `begin(0x1A)` ve `yRead()` kullanıyorum. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. Hazır araç, başlatma ve her turda
  okuma işlerini ayıran bir soru sor; cevabı söyleme, ayrıntılar ileride açılacak."
- [temel] **`map` ve `analogWrite`:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de 3.3V mantık seviyesinde, D5 pinindeki 220 ohm
  dirençli harici LED'i sürüyorum; `map` Y değerini 0–255'e çeviriyor,
  `analogWrite` parlaklığı uyguluyor. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. Hesap yapmakla ışığı değiştirmek
  arasındaki farkı düşündüren bir soru sor; cevabı verme."
- [temel] **Sayı türleri ve `void`:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2 kodunda `uint16_t yEkseni`, `uint8_t ileri` ve `void loop()`
  var. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi
  verme. İki farklı sayıyı saklamakla kod bölümünün sonunda değer
  döndürmemek arasındaki farkı düşündüren soru sor; cevabı verme."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kod derlendi ve yüklendi mi; Seri Monitör'de iki sayı görünüyor mu?
2. Kolu ileri ittiğinizde Y değeri 540'ı, parlaklık değeri 0'ı geçiyor mu?
3. İki sayı değiştiği hâlde LED sönükse `dk0020`'deki D5, LED yönü,
   direnç ve GND düzeni hâlâ aynı mı?

## 9. SEN YAP

1. `if (yEkseni > 540)` eşiğini değiştirmeden önce LED'in hangi noktada
   yanmaya başlayacağını tahmin et. Eşiği değiştirdiğinde `map` satırının
   giriş alt sınırını da aynı yeni değere getir; Y ve parlaklık sayılarını
   birlikte izle, tahmininle karşılaştır.
2. `if (ileri < 10)` satırındaki küçük değer sınırını değiştir.
   `analogWrite` ve `Serial.println(ileri)` satırlarına dokunmadan
   kısık ışığın ne zaman sıfıra döndüğünü gözlemle.
3. `dk0060`'da gördüğün `xRead()` çağrısını kullanarak X eksenini
   yeni giriş yap. Hangi satırın **ölçtüğünü**, hangisinin **aralığı
   çevirdiğini**, hangisinin **LED'e uyguladığını** göster. Kodu
   değiştirirken kaynakta olmayan fiziksel bağlantı bilgisi ekleme.
