---
dk_no: dk0160
portal_ders: "2.2"
kaynak_ak: [ak0115]
baslik: Trafik lambası rengini yazsın
duzey: 0-temel
unite: 1-LED-ve-Seri-Port
kazanimlar:
  - cpp.const-int
  - cpp.coklu-cikis
  - cpp.delay
  - cpp.serial-begin
  - cpp.serial-println
  - hw.coklu-led
kara_kutu: [void, OUTPUT, "Serial ve noktalı yazım"]
malzeme:
  - Deneyap Mini v2 kartı
  - Type-C USB kablosu
  - 3 LED (varsa kırmızı, sarı, yeşil; aynı renkteyse rolleri pin adından ayırt edilir)
  - 3 adet 220 ohm direnç
  - breadboard
  - 6 jumper kablo
board:
  kart: Deneyap Mini v2
  kirmizi_led_pin: "D5"
  sari_led_pin: "D6"
  yesil_led_pin: "D9"
  seri_hiz: 115200
  mantik_gerilimi: 3.3V
  direnc: 220 ohm
kaynak_kod: ak0115_trafikLambasiYazsin/ak0115_trafikLambasiYazsin.ino
---

## 1. Hedef
Ders 1.6'da (dk0150) kurduğun trafik lambasını değiştirmeden ona bir katman
ekleyeceksin. Kırmızı LED yanarken Seri Monitör'de `KIRMIZI`, yeşil yanarken `YESIL`,
sarı yanarken `SARI` yazacak. Yeni bir komut öğrenmeyeceksin; Ders 2.1'de (dk0040)
öğrendiğin seri yazıyı tanıdığın bir devrede kullanacaksın.

## 2. Malzemeler
- Deneyap Mini v2 kartı
- Type-C USB kablosu
- Kırmızı, sarı ve yeşil LED (setinde bu renkler yoksa 3 LED yeter)
- 3 adet 220 ohm direnç
- Breadboard
- 6 jumper kablo

## 3. Parça tanıtımı
Yeni parça yok. Ders 1.6'daki üç LED'li trafik lambası devresi aynen kullanılır. Her
LED'in kendi direnci vardır. Seri Monitör de Ders 2.1'de kullandığın Arduino IDE
penceresidir; devreye takılan bir parça değildir.

## 4. Devre kurulumu
Ders 1.6'nın D5/D6/D9 devresi duruyorsa hiçbir şeye dokunma — bu ders yalnız kod
ekliyor, devre aynen kalıyor.

Metin şeması:
- Kırmızı LED (+) → D5, (−) → 220 ohm direnç → GND
- Sarı LED (+) → D6, (−) → 220 ohm direnç → GND
- Yeşil LED (+) → D9, (−) → 220 ohm direnç → GND

## 5. Kod açıklaması
| kod satırı | açıklama |
| --- | --- |
| `// Trafik lambasının bildiğimiz koduna (Ders 1.6), yanan rengi yazan Serial.println satırları ekliyoruz` | Ders 1.6'nın kodu korunur; her renk adımına bir yazı satırı eklenir. |
| `// Her renk yazısı, o rengin LED durumları ayarlandıktan hemen sonra gönderilir` | Ekrandaki ad ile fiziksel olarak yanan LED aynı rengi gösterir. |
| `const int kirmizi = D5;` | D5 pinine `kirmizi` adı verilir (Ders 1.4'te öğrendiğin isim verme). |
| `Serial.begin(115200);` | Kartın bilgisayara 115200 hızında yazı göndermesini başlatır — Ders 2.1'deki aynı hız. |
| `Serial.println("KIRMIZI");` | Kırmızı LED ayarlandıktan sonra ekrana `KIRMIZI` yazar. |
| `Serial.println("YESIL");` | Yeşil LED ayarlandıktan sonra ekrana `YESIL` yazar. |
| `Serial.println("SARI");` | Sarı LED ayarlandıktan sonra ekrana `SARI` yazar. |

`YESIL` Türkçe karakter kullanmadan yazıldı — `KIRMIZI` ve `SARI` zaten ASCII'dir. Bazı
bilgisayarlarda `YEŞİL` içindeki `Ş` bozuk görünebilir; bu, LED'in veya kodun bozuk
olduğu anlamına gelmez.

### İleri analiz [ileri]
Ders 1.6'daki `const int`, `pinMode`, `digitalWrite` ve `delay` satırları aynı sırada
duruyor. Yeni katman yalnızca bir `Serial.begin` ve üç `Serial.println` satırıdır. Bu
sayede değişikliğin hangi davranışı eklediği kolayca görülebilir.

`Serial.println` satırı üç LED'in durumu ayarlandıktan sonra gelir. Satır daha erken
yazılırsa ekranda yeni renk görünürken devrede önceki renk çok kısa süre daha kalabilir.

## 6. Çalıştır ve gözlemle
Kodu yükle, Seri Monitör'ü aç ve hızı **115200** seç. Kırmızı LED 4 saniye yanarken
`KIRMIZI`, yeşil LED 3 saniye yanarken `YESIL`, sarı LED 1 saniye yanarken `SARI`
görünür. Sonra sıra baştan başlar.

### Sorun giderme
- **Hiçbir LED yanmıyor** → Kod karta yüklenmemiş olabilir; `Araçlar > Kart > Deneyap
  Kartlar > Deneyap Mini v2` ve `Araçlar > Port` seçimlerini doğrula.
- **Yalnız bir renk yanmıyor** → O LED ters takılmış olabilir; uzun bacağın pine, kısa
  bacağın kendi direncine gittiğini kontrol et.
- **Yanan renk ile ekrandaki ad farklı** → `Serial.println` satırı yanlış renk adımına
  konmuş olabilir; yazı satırını hemen üstündeki üç `digitalWrite` ile karşılaştır.
- **Seri Monitör boş** → Seri Monitör kapalı ya da yanlış port seçili olabilir; monitörü
  açıp kodu yüklediğin portu seç.
- **Ekrandaki yazılar anlamsız karakterlerden oluşuyor** → Seri Monitör hızı kodla
  eşleşmiyordur; kodda ve monitörde **115200** seçili olduğunu kontrol et.
- **LED'ler sönük yanıyor** → Üç LED aynı direnci paylaşıyor olabilir; her LED'in kendi
  220 ohm direnci olmalı.

## 7. Mini sınav
1. [temel] Kırmızı LED yanarken Seri Monitör'de ne yazmalıdır?
   - A) SARI
   - B) YESIL
   - C) KIRMIZI
   - D) SONDU
   - ipucu: Yazı, yanan LED'in renk adıdır.

2. [temel] `Serial.println("SARI");` satırı kodda nereye yerleştirilir?
   - A) Sarı LED'in durumları ayarlandıktan hemen sonra
   - B) `const int` satırlarının arasına
   - C) Kırmızı adımının başına
   - D) Kodun dışına
   - ipucu: Ekrandaki ad ile yanan LED aynı anda değişmeli.

3. [temel] Seri Monitör hangi hızda açılmalıdır?
   - A) 220
   - B) 1000
   - C) 9600
   - D) 115200
   - ipucu: `Serial.begin(...)` parantezinin içine bak.

4. [temel] Bu dersin devresi hangi eski dersle aynıdır?
   - A) Dahili LED (1.1)
   - B) Trafik lambası (1.6)
   - C) Hız merdiveni (1.3)
   - D) Kara şimşek (1.5)
   - ipucu: Üç renkli devreyi daha önce nerede kurdun?

5. [ileri] Bu derste Ders 1.6'nın koduna eklenen satırlar hangileridir?
   - A) Bir `Serial.begin` ve üç `Serial.println`
   - B) Üç yeni `const int`
   - C) Altı yeni `digitalWrite`
   - D) Üç yeni `pinMode`
   - ipucu: Eski kod ile yeni kodu yan yana karşılaştır.

6. [ileri] `Serial.println("YESIL");` satırı LED durumlarından önce yazılırsa hangi
   uyumsuzluk görülebilir?
   - A) Yazı yeni rengi gösterirken devre çok kısa süre önceki renkte kalabilir
   - B) Direnç değeri değişir
   - C) Seri hız kendiliğinden artar
   - D) D9 kaybolur
   - ipucu: Kod satırları yukarıdan aşağıya çalışır.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı sana devrenin nasıl kurulacağını, hangi pine
> bağlayacağını ya da hangi direnci kullanacağını **söylemez** — bunlar zaten bu derste
> yazıyor, devre Ders 1.6'dan hiç değişmedi. **AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.** AI Yoldaşı zorunlu değildir; erişimin
> yoksa dersi §6'daki Sorun giderme ve aşağıdaki "Yanındaki Yetişkine" kartıyla
> tamamlayabilirsin.

### Ders promptları
- [temel] **Eşleştirme** — "Sen sabırlı bir öğretmensin. Bağlam: Deneyap Mini v2
  kartında, 3.3V mantık seviyesinde, D5'te kırmızı, D6'da sarı, D9'da yeşil LED, her
  biri için 220 ohm direnç ve seri hız 115200 olan bir trafik lambam var. Bana pin
  numarası, direnç değeri veya bağlantı tarifi verme. Yanan LED ile Seri Monitör'deki
  renk adını eşleştirmeme yardım et; bir tam turu adım adım gözlemleten sorular sor,
  cevabı söyleme."
- [temel] **Hata giderme** — "Sen bir hata ayıklama koçusun. Bağlam: Deneyap Mini v2
  kartında, D5/D6/D9'da üç LED'li, seri hızı 115200 olan bir trafik lambam var. LED
  renkleri doğru ama ekrandaki adlar yanlış sırada. Bana pin, direnç veya bağlantı
  tarifi verme. Cevabı söylemeden her `Serial.println` satırının çevresindeki kodu
  karşılaştırmamı sağlayan sorular sor."
- [ileri] **Kod karşılaştırma** — "Sen ileri seviye bir mentorsun. Bağlam: Deneyap Mini
  v2 kartında D5/D6/D9'da üç LED'li trafik lambam var, seri hız 115200. Ders 1.6'daki
  eski kodla bu yeni kod arasındaki tek katmanı bulmama yardım et. Pin, direnç veya
  bağlantı tarifi verme, cevabı da verme; aynı kalan ve eklenen satırları kendim
  ayırmam için sorular sor."

### Yanındaki yetişkine
Bu kart çocuğa değil, yanındaki yetişkine yazıldı; AI ve internet gerekmez. Cevabı
söylemeyin, sırayla şunları sorun:

1. Fiziksel olarak hangi renk yanıyor?
2. Seri Monitör'de hangi ad görünüyor?
3. O yazı satırının hemen üstünde hangi LED durumları ayarlanmış?

Üç cevabı çocukla birlikte karşılaştırın.

**Kara kutu hatırlatması:** `void` ve `OUTPUT` Ders 1.4/1.6'da, `Serial` ve noktalı
yazım Ders 2.1'de (dk0040) açıklandı; burada yeniden anlatılmıyor.

## 9. SEN YAP
1. Sarı LED'in 1 saniye yerine 2 saniye yanmasını sağla.
2. Seri Monitör'deki `SARI` yazısının da LED ile aynı anda göründüğünü gözlemle.
