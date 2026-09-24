---
dk_no: dk0060
portal_ders: "6.1"
portal_ders_not: "Portal-Ders-Haritasi.md 12 modüllü yapıya taşındı (Özgür, 2026-09-24): dk0060 eski 3.1'den 6.1'e taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
baslik: Joystick kolunu oku
duzey: 0-temel
unite: 2-Girdi okuma
kazanimlar: [cpp.setup-loop, cpp.delay, cpp.serial-begin, cpp.serial-println, hw.seri-port]
kara_kutu: [void, Deneyap_KumandaKolu, Joystick, KumandaKolu.begin, KumandaKolu.yRead, uint16_t]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Kumanda Kolu]
board:
  kart: Deneyap Mini v2
  kumanda_kolu_i2c_adresi: "0x1A"
  seri_hiz: 115200
  pin_notu: "Joystick, karta I2C kablosuyla bağlanır: kablo, Deneyap Mini v2'deki ve kumanda kolundaki I2C soketlerine takılır (SDA/SCL pinlerine tek tek jumper çekilmez). Bağlantı bilgisi Özgür, 2026-09-24."
kaynak_kod: "D:\\Atolye\\Deneyap\\arsiv\\200kkDegerleriniSeriPorttanOkuma\\200kkDegerleriniSeriPorttanOkuma.ino (ana kaynak)"
yardimci_kaynak: "D:\\Atolye\\Deneyap\\arsiv\\dyminiV2500kkDahiliLedParlaklik\\dyminiV2500kkDahiliLedParlaklik.ino (yalnız yardımcı; bu derste LED sürülmez)"
---

## 1. Hedef

`dk0050`'de butonun yalnız iki durumu vardı: basılı ya da bırakılmış. Bu derste
kolu az ya da çok hareket ettireceksin; kartın okuduğu sayı Seri Monitör'de
değişecek. Böylece kartın bir hareketi **ölçülebilir bir değere** çevirdiğini
göreceksin. `dk0040`'ta öğrendiğin Seri Monitör bu kez LED durumunu değil,
joystick'in Y eksenini gösterecek.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Kumanda Kolu
- Oturum 1'den kalan LED, direnç ve breadboard devresi yerinde durabilir;
  bu dersin kodu LED'i sürmez.

## 3. Parça tanıtımı

- **Joystick / kumanda kolu:** Parmağınla farklı yönlere itebildiğin parçadır.
  Buton gibi yalnız iki durum bildirmek yerine hareketi bir sayı olarak okutabilir.
- **Y ekseni:** Bu derste takip ettiğimiz hareket yönüdür. Kolu hareket ettirdikçe
  ekrandaki sayının nasıl değiştiğini deneyerek bulacaksın.
- **Seri Monitör:** Kartın gönderdiği `Y Ekseni: ...` satırlarını bilgisayarda gösterir;
  joystick'e fiziksel olarak bağlı yeni bir parça değildir.

## 4. Devre kurulumu

1. Bilgisayara bağlı kartın enerjisini kes; kablo takıp çıkarırken kartı çalışır
   durumda bırakma.
2. Oturum 1'deki harici LED ve direnç devresini sökme. Bu ders onu kullanmasa da
   bir sonraki derste yeniden gerekecek.
3. Kumanda kolunu karta **I2C kablosuyla** bağla: kablonun bir ucu Deneyap Mini
   v2 üzerindeki I2C soketine, öbür ucu kumanda kolundaki I2C soketine takılır.
   SDA/SCL pinlerine (D7/D8) tek tek jumper çekilmez — tek kablo, iki soket.
   Modülün I2C adresi `0x1A`'dır (`begin(0x1A)`).
4. Kartı Type-C USB kablosuyla bilgisayara bağla.

## 5. Kod açıklaması

Kod yukarıdan aşağıya başlar: araç hazırlanır, `setup()` bir kez çalışır,
`loop()` tekrar eder. Her tekrarın sonunda ekrana yeni bir satır gelir.

| kod satırı | açıklama |
| --- | --- |
| `#include <Deneyap_KumandaKolu.h>` | **Kara kutu:** hazır joystick komutlarını programa getirir; kütüphanenin içi ileride açılacak. |
| `Joystick KumandaKolu;` | **Kara kutu:** hazır joystick aracını `KumandaKolu` adıyla kullanmamızı sağlar; sınıf/nesne konusu ileride açılacak. |
| `void setup() {` | `setup()` başlangıçta bir kez çalışır. **Kara kutu `void`:** bu kod bölümünün sonunda değer döndürülmediğini belirtir; fonksiyon konusunda açılacak. |
| `Serial.begin(115200);` | Kartın Seri Monitör'e yazı göndermesini başlatır; monitör hızı da aynı olmalı. |
| `KumandaKolu.begin(0x1A);` | **Kara kutu:** kaynakta kullanılan I2C adresiyle joystick iletişimini başlatır; adresin neden bu olduğu kaynakta açıklanmıyor. |
| `void loop() {` | İçindeki komutlar `setup()` bittikten sonra sürekli tekrarlanır. |
| `uint16_t yEkseni = KumandaKolu.yRead();` | **Kara kutu `yRead()`:** Y yönünün o anki sayısını verir. **Kara kutu `uint16_t`:** bu sayıyı saklamak için seçilmiş tam sayı türüdür; veri türleri ileride açılacak. `yEkseni` sayı için verdiğimiz addır. |
| `Serial.print("Y Ekseni: ");` | Önce açıklayıcı etiketi yazar; satırı bitirmez, böylece sayı hemen arkasına gelir. |
| `Serial.println(yEkseni);` | Okunan sayıyı yazar ve sonraki ölçüm için yeni satıra geçer. |
| `delay(100);` | Ölçümler arasına 100 milisaniye koyar; ekrandaki satırlar biraz daha izlenebilir olur. |

### İleri analiz [ileri]

Ana kaynak aynı modülden `swRead()`, `xRead()` ve `yRead()` çağırıyor. Bu
ders yalnız Y eksenini seçti; önce **bir değerin okunması → ekrana yazılması**
zincirini görünür kılmak istiyoruz. X ekseni `SEN YAP` görevi olarak kalıyor.
Kolu ilk konumuna döndürüp birkaç kez yeniden ölç: sayı her denemede tamamen
aynı mı? Gözlemini kaydet; kaynakta merkez veya uç değer için kesin sayı verilmedi.

## 6. Çalıştır ve gözlemle

Kodu karta yükle, Seri Monitör'ü aç ve **115200** hızını seç. Önce kolu
bırakılmış hâlde izle, sonra bir yöne yavaşça it, bırak ve öbür yöne it.
Her durumda `Y Ekseni:` satırını oku. Hangi harekette sayı yükseliyor,
hangisinde düşüyor? Bunu kartında gözlemle; kaynakta yönün sayısal işareti
tanımlanmadığı için önceden kesin sonuç verilmez.

### Sorun giderme

- **Kod `Deneyap_KumandaKolu.h` bulunamadı diye derlenmiyor:** Bu bir
  bağlantı hatası değil; gereken kütüphane geliştirme ortamında bulunmuyor.
  Kütüphane kurulumunu doğrulamadan karta yükleme adımına geçme.
- **Kod yüklendi ama Seri Monitör boş:** Önce doğru karta ve porta yüklediğini,
  sonra monitörü açtığını kontrol et. Başka bir kod yüklüyse `Y Ekseni:` çıkmaz.
- **Karakterler bozuk:** `Serial.begin(115200)` ile monitörde seçili hızın aynı
  olduğunu karşılaştır.
- **Etiket görünüyor, sayı hiç değişmiyor:** Kolu gerçekten Y yönünde oynatıp
  yeniden dene; ardından I2C kablosunun her iki soketine (kart + kumanda kolu)
  tam oturduğunu kontrol et. SDA/SCL'e tek tek jumper çekilmiş olmamalı.
- **Beklenmedik veya hiç sayı yok:** `KumandaKolu.begin(0x1A)` ve `yRead()`
  yazımını ana kaynakla karşılaştır. Kaynakta başarısız başlatmayı bildirip
  bildirmediği gösterilmiyor; yalnız ekrana bakarak bağlantı arızasını
  kesin teşhis edemezsin.
- **Kod karta yüklenmiyor:** Kart modeli, port ve USB kablosunun veri aktarımı
  yapabildiğini kontrol et.

## 7. Mini sınav

1. [temel] Buton ile joystick arasındaki bu derste gördüğün fark nedir?
   - A) İkisi de yalnız açık/kapalı bildirir
   - B) Joystick hareketi değişen bir sayı olarak gözlenebilir
   - C) Joystick yalnız LED yakar
   - D) Buton Seri Monitör'ü açar
   - ipucu: `dk0050`'deki `digitalRead` sonucuyla `yRead()` sonucunu karşılaştır.

2. [temel] `yRead()` sonucu hangi değişkende saklanıyor?
   - A) `KumandaKolu`
   - B) `yEkseni`
   - C) `Serial`
   - D) `setup`
   - ipucu: Eşittir işaretinin solundaki ada bak.

3. [temel] `Serial.print` neden `Serial.println`'den önce geliyor?
   - A) Etiketle değeri aynı satırda tutmak için
   - B) LED'i yakmak için
   - C) Joystick'e güç vermek için
   - D) Kod yüklemek için
   - ipucu: Ekranda `Y Ekseni:` ile sayının yerleşimine bak.

4. [temel] `Serial.begin(115200)` ile Seri Monitör'deki hız farklı olursa
   önce neyi kontrol edersin?
   - A) Direnç rengini
   - B) İki hızın eşleşmesini
   - C) LED'in yönünü
   - D) X eksenini
   - ipucu: `dk0040`'ta da aynı kural vardı.

5. [ileri] Ana kaynak X ve buton değerlerini de okurken bu ders niçin yalnız Y'yi gösteriyor?
   - A) Önce tek bir okuma ve yazma zincirini izleyebilmek için
   - B) Modülde X yok diye
   - C) Seri Monitör X yazamaz diye
   - D) Buton kartı kapatır diye
   - ipucu: §5 İleri analiz'e bak.

6. [ileri] `delay(100)` büyürse ekrandaki yeni ölçümlere ne olur?
   - A) Daha seyrek gelirler
   - B) LED parlaklaşır
   - C) I2C adresi değişir
   - D) Kartın pini değişir
   - ipucu: Her `loop()` tekrarı arasındaki beklemeyi düşün.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme; doğrulanmamış bağlantıyı AI'a tamamlattırma.

### Ders promptları

- [temel] **İki durumdan sayıya:** "Sen sabırlı bir öğretmensin. Bağlam: Deneyap
  Mini v2'de butonun iki durumunu öğrendim; şimdi Deneyap Kumanda Kolu'nun Y
  değerini Seri Monitör'de 115200 hızında izliyorum. Bana pin numarası, direnç
  değeri, menü yolu veya bağlantı tarifi verme. İki durum ile değişen sayı
  arasındaki farkı bulduracak bir soru sor; cevabı söyleme."
- [temel] **Etiket ve sayı:** "Sen öğrenme koçumsun. Bağlam: Deneyap Mini v2,
  seri hız 115200; kodum `Serial.print` ile etiket, `Serial.println` ile Y
  sayısını gösteriyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. İki yazma satırının sırası değişirse ekranda ne olacağını
  tahmin ettiren bir soru sor; cevabı verme."
- [temel] **Hata ayıklama:** "Sen hata ayıklama koçumsun. Bağlam: Deneyap Mini v2'de
  joystick Y değeri Seri Monitör'de görünmüyor; hız 115200. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Önce derleme, sonra
  yükleme, sonra ekrandaki belirtiyi ayıran soruları sırayla sor; cevabı verme."

### Kara kutu promptları

- [temel] **Kütüphane ve Joystick aracı:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de `Deneyap_KumandaKolu.h` ve `Joystick KumandaKolu` yazıyorum.
  Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Hazır
  araç ile o araca verdiğim adın işlerini ayırmamı sağlayan bir soru sor;
  cevabı söyleme, sınıf/nesne konusu ileride açılacak."
- [temel] **`begin(0x1A)` ve `yRead()`:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de kumanda kolu `begin(0x1A)` ile başlatılıyor, `yRead()`
  Y değerini veriyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. Başlatma ile tekrar tekrar okuma arasındaki farkı düşündüren
  bir soru sor; cevabı söyleme, I2C ileride açılacak."
- [temel] **`uint16_t` ve `void`:** "Sen meraklı bir öğretmensin. Bağlam:
  Deneyap Mini v2 kodumda `uint16_t yEkseni` ve `void loop()` var. Bana pin
  numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Bir sayıyı
  saklamakla kod bölümünün sonunda değer döndürmek arasındaki farkı düşündüren
  bir soru sor; cevabı söyleme, veri türleri/fonksiyonlar ileride açılacak."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kod derlenip yüklendi mi, yoksa kütüphane hatasında mı durdu?
2. Seri Monitör'de `Y Ekseni:` etiketi var mı, hız 115200 mü?
3. Kolu Y yönünde oynatınca sayı değişiyor mu? Değişmiyorsa I2C kablosunun
   kart ve kumanda kolu üzerindeki soketlere tam oturduğunu kontrol edin.

## 9. SEN YAP

1. `Serial.print("Y Ekseni: ");` satırındaki etiketi kendine göre değiştir.
   Sayının hâlâ aynı satırda kaldığını gözlemle; sayıyı okuyan satıra dokunma.
2. `delay(100)` değerini önce büyüt, sonra küçült. Kolu benzer hızda oynatıp
   satırların yenilenmesini karşılaştır; hangi değişiklik gözlemi kolaylaştırdı?
3. Ana kaynaktaki `xRead()` çağrısını bul. Y'yi okuyan satırın benzerini
   kullanarak X değerini de oku ve ayrı bir `Serial.println` satırında göster.
   Hangi satırın **okuduğunu**, hangisinin **yazdığını** kendi sözlerinle anlat.
