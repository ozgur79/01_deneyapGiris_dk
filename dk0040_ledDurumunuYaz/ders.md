---
dk_no: dk0040
portal_ders: "1.4"
kaynak_ak: [ak0110]
baslik: LED durumunu Seri Monitör'e yaz
duzey: 0-temel
unite: 1-LED-ve-Seri-Port
kazanimlar:
  - cpp.setup-loop
  - cpp.delay
  - cpp.pinmode
  - cpp.digitalwrite
  - cpp.const-int
  - cpp.serial-begin
  - cpp.serial-println
  - hw.harici-led-devre
kara_kutu: [void, OUTPUT, "Serial nesnesi ve noktalı yazım"]
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
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
  seri_hiz: 115200
  pin_notu: "Kod D5 makrosunu kullanır; kart üzerindeki D-etiketi fiziksel GPIO numarası değildir."
kaynak_kod: ak0110_ledDurumunuYaz/ak0110_ledDurumunuYaz.ino
---

## 1. Hedef

Harici LED'in yanıp sönmeye devam ederken kartın ne yaptığını bilgisayarda da göreceksin.
LED yanınca Seri Monitör'de `YANDI`, sönünce `SONDU` yazacak. Bu dersin yeni fikri,
çalışan kartın bilgisayara yazı gönderebilmesidir.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- 1 LED
- 1 adet 220 ohm direnç
- breadboard
- 2 jumper kablo

## 3. Parça tanıtımı

Yeni elektronik parça yok. `dk0020` dersindeki LED, direnç ve breadboard devresini yeniden
kullanacaksın. **Seri Monitör**, kartın gönderdiği yazıları bilgisayarda gösteren Arduino IDE
penceresidir; devreye takılan bir parça değildir.

## 4. Devre kurulumu

`dk0020` devren duruyorsa sökme. Yeniden kuracaksan sırayı izle:

1. LED'i breadboard'a tak.
2. LED'in uzun bacağını (+) jumper kabloyla kart üzerinde **D5** yazan pine bağla.
3. LED'in kısa bacağını (−) 220 ohm dirence bağla.
4. Direncin diğer ucunu jumper kabloyla GND'ye bağla.
5. Kartı Type-C USB kablosuyla bilgisayara bağla.

Metin şeması: LED uzun bacak (+) → D5, kısa bacak (−) → 220 ohm direnç → GND

## 5. Kod açıklaması

| kod satırı | açıklama |
| --- | --- |
| `const int led = D5;` | Kart üzerinde D5 yazan pine `led` adı verilir. Pin adı bir kez yazıldığı için kod daha kolay okunur. |
| `void setup() {` | **Kara kutu:** `void`, bu kod bölümünün sonunda değer verilmediğini belirtir; fonksiyon konusunda tam açılacak. |
| `pinMode(led, OUTPUT);` | **Kara kutu:** `OUTPUT`, pinin dışarıya elektrik göndereceğini belirtir; buton dersinde `INPUT` ile birlikte tam açılacak. |
| `Serial.begin(115200);` | Kartın bilgisayara yazı göndereceği seri bağlantıyı 115200 hızında başlatır. Bu satır yalnız bir kez gereken başlangıç ayarı olduğu için `setup()` içindedir. |
| `digitalWrite(led, HIGH);` | D5 çıkışını açık yapar; LED yanar. |
| `Serial.println("YANDI");` | Seri Monitör'e `YANDI` gönderir ve sonraki yazı için yeni satıra geçer. |
| `delay(1000);` | LED ve yazının bu durumunu 1000 milisaniye korur. |
| `digitalWrite(led, LOW);` | D5 çıkışını kapatır; LED söner. |
| `Serial.println("SONDU");` | Seri Monitör'e `SONDU` gönderir ve yeni satıra geçer. |

**Kara kutu — `Serial` ve noktalı yazım:** `Serial`, kartın bilgisayarla seri iletişim
kurmasını sağlayan hazır araçtır; noktadan sonraki ad bu araca hangi işi yaptıracağını
seçer. Bu yapının nasıl oluşturulduğu fonksiyon konusunda tam açılacak.

`SONDU` özellikle Türkçe karakter kullanılmadan yazıldı. `SÖNDÜ` bazı ekranlarda bozuk
görünürse LED kodu bozulmuş değildir; yazı karakterleri uyuşmamıştır.

### İleri analiz [ileri]

`Serial.begin(115200)` bağlantıyı bir kez başlattığı için `setup()` içindedir.
`Serial.println(...)` ise her LED durumu değiştiğinde yeniden çalışmalıdır; bu yüzden
`loop()` içindedir. Kaynaktaki `Serial.print` mesajları aynı satırda birleştiriyordu.
`Serial.println` her mesajdan sonra yeni satıra geçtiği için değişimleri izlemek kolaylaşır.

## 6. Çalıştır ve gözlemle

Kodu karta yükle, Seri Monitör'ü aç ve hızı **115200** seç. LED bir saniye yanarken
`YANDI`, bir saniye sönerken `SONDU` görünür. Işık ve ekrandaki mesaj birlikte değişir.

### Sorun giderme

- **LED hiç yanmıyor** → LED'in uzun bacağının D5 tarafında, kısa bacağının direnç tarafında
  olduğunu kontrol et; sonra direncin GND'ye ulaştığını doğrula.
- **LED yanıyor ama Seri Monitör boş** → Önce kodun karta yüklendiğini, sonra doğru kartın
  bağlı olduğu portu ve doğru Seri Monitör penceresini açtığını kontrol et.
- **Ekranda anlamsız işaretler var** → Kodda `Serial.begin(115200)` yazdığını ve Seri
  Monitör hızının da 115200 olduğunu karşılaştır.
- **`YANDISONDU` aynı satırda uzuyor** → İki mesaj satırında da `Serial.println` yazdığını,
  `Serial.print` kalmadığını kontrol et.
- **Yazı geliyor ama LED tepki vermiyor** → Kod ve kablonun ikisinin de kart üzerinde D5
  yazan pini kullandığını kontrol et; çıplak pin sayısı kullanma.
- **Işık ile mesaj aynı anda değişmiyor** → Her `Serial.println` satırının ilgili
  `digitalWrite` satırının hemen altında, `delay` satırından önce olduğunu doğrula.
- **Mesajda Türkçe harfler bozuk** → `YANDI` ve `SONDU` gibi Türkçe karakter içermeyen
  kısa mesajlarla yeniden dene.
- **Kod yüklenmiyor** → Kart modelini ve portu doğrula; USB kablosunun yalnız şarj değil,
  veri aktarımı da yapan bir kablo olduğundan emin ol.

## 7. Mini sınav

1. [temel] Kartın gönderdiği `YANDI` ve `SONDU` yazıları nerede görülür?
   - A) Breadboard üzerinde
   - B) Seri Monitör'de
   - C) LED'in içinde
   - D) Direncin üzerinde
   - ipucu: Arduino IDE'de açtığın pencerenin adını düşün.

2. [temel] `Serial.println("YANDI");` ne yapar?
   - A) LED'i yakar
   - B) `YANDI` yazıp yeni satıra geçer
   - C) Bir saniye bekler
   - D) D5 pinini çıkış yapar
   - ipucu: LED'i yakan satır `digitalWrite` ile başlar.

3. [temel] Seri Monitör'de hangi hız seçilmelidir?
   - A) 220
   - B) 1000
   - C) 9600
   - D) 115200
   - ipucu: `Serial.begin(...)` parantezinin içine bak.

4. [temel] `Serial.begin(115200)` neden `setup()` içindedir?
   - A) Bağlantıyı bir kez başlatmak yeterli olduğu için
   - B) LED'i sürekli yakmak için
   - C) Her saniye hızı değiştirmek için
   - D) Direnci korumak için
   - ipucu: `setup()` kaç kez çalışır?

5. [ileri] Neden `Serial.print` yerine `Serial.println` kullanıldı?
   - A) LED daha parlak yansın diye
   - B) Mesajlar ayrı satırlarda kolay izlensin diye
   - C) Pin değişsin diye
   - D) Bekleme kısalsın diye
   - ipucu: `ln`, yazıdan sonra yeni satıra geçilmesini sağlar.

6. [ileri] Mesaj satırı `digitalWrite` satırından çok sonra çalışırsa ne olur?
   - A) Direnç değeri değişir
   - B) LED ile ekrandaki bilgi farklı zamanlarda değişir
   - C) D5, D6 olur
   - D) LED'in yönü değişir
   - ipucu: Kod satırları yukarıdan aşağıya çalışır.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme ve
> aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında çalışmıyorsa
> AI yanılmıştır, devren haklıdır.* AI'a pin numarası, direnç değeri, menü yolu veya bağlantı
> tarifi sordurma; bunları dersindeki devre şeması belirler.

### Ders promptları

- [temel] **Durumu görünür yapma** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli bir LED kullanıyorum ve seri
  hız 115200. Kart LED'in durumunu Seri Monitör'e yazıyor. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. LED'e bakamadığım bir anda yazının ne işe yarayacağını
  düşündüren tek bir soru sor; cevabı söyleme."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli LED yanıp sönüyor; seri hız
  115200 olduğu hâlde Seri Monitör boş. Bana pin numarası, direnç değeri, menü yolu veya
  bağlantı tarifi verme. Yükleme, port ve monitör durumlarını sırayla kontrol etmemi sağlayan
  sorular sor; cevabı doğrudan verme."
- [ileri] **Zamanlama** — "Sen meraklı bir rehbersin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli LED kullanıyorum ve seri hız 115200.
  Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. `digitalWrite`,
  `Serial.println` ve `delay` satırlarının sırasının ışıkla yazıyı nasıl eşleştirdiğini
  bulduracak bir deney sorusu sor; cevabı söyleme."

### Kara kutu promptları

- [temel] **`void`** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli LED kullanıyorum ve seri hız 115200.
  Kodumda `void setup()` yazıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. `void` kelimesinin kod bölümünün sonunda değer verip vermemesiyle ilgili
  olabileceğini düşündüren bir soru sor; cevabı verme, konu fonksiyonlarda açılacak."
- [temel] **`OUTPUT`** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2 kartında,
  3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli LED kullanıyorum ve seri hız 115200.
  Kodumda `OUTPUT` yazıyor. Bana pin numarası, direnç değeri, menü yolu veya bağlantı tarifi
  verme. Pinin dışarıya elektrik vermesiyle dışarıdan bilgi alması arasındaki farkı düşündüren
  bir soru sor; cevabı verme, konu buton dersinde `INPUT` ile açılacak."
- [temel] **`Serial` ve nokta** — "Sen meraklı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5 pininde 220 ohm dirençli LED kullanıyorum ve seri hız
  115200. Kodumda `Serial.begin` ve `Serial.println` yazıyor. Bana pin numarası, direnç değeri,
  menü yolu veya bağlantı tarifi verme. Noktadan önceki adın araç, sonraki adın o araca verilen
  iş olabileceğini düşündüren bir soru sor; cevabı verme, yapı fonksiyonlarda tam açılacak."

### Yanındaki yetişkine

Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. LED gerçekten yanıp sönüyor mu; yani sorun ışıkta mı, yalnız yazıda mı?
2. Kod ile Seri Monitör aynı hızı mı gösteriyor?
3. Her mesaj satırı ilgili ışık değişiminin hemen altında mı?

## 9. SEN YAP

1. LED'i 2 saniye yanık, yarım saniye sönük bırak; iki bekleme süresini ayrı ayrı değiştir.
2. `YANDI` ve `SONDU` yerine kendi iki kısa durum mesajını yazdır.
3. Mesaj satırlarından birini ilgili `digitalWrite` satırının altından başka yere taşı.
   Işıkla yazının zamanlamasını gözlemle, sonra satırı eski yerine getir.
