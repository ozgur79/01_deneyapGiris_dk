---
dk_no: dk0110
portal_ders: "9.1"
portal_ders_not: "Portal-Ders-Haritasi.md tek kaynak (Özgür, 2026-09-24): dk0110 = 5.1 idi. Önceki bir sürümde bu ders dk0120/5.2 idi; Özgür'ün kartta test edip onaylamasının ardından dörtgen/üçgen önce, daire+S rota sonra gelecek şekilde yer değiştirildi. Aynı gün 12 modüllü yapıya taşındı: dk0110 eski 5.1'den 9.1'e taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
onkosul: "Portal-Ders-Haritasi.md'nin (2026-09-24, 12 modüllü yapı) Modül 2 aday bandındaki `for`/döngüler dersi (portal_ders '2.2+', henüz kesin numara verilmedi) — bu ders `for`'u kara kutu OLARAK DEĞİL, bilinen bir kavram olarak kullanır. İlk dilim bir tadım dilimi olduğu için o ders dilimde henüz üretilmedi; tam müfredatta bu dersten önce gelecektir."
kazanim_notu: "`for` için ak'nin kazanimlar.md dosyasında bir id yok (kontrol edildi, 2026-09-24). Yeni id uydurulmadı; Ortak'a soru olarak backlog.md'ye yazıldı."
baslik: Kodla dörtgen ve üçgen çiz
duzey: 0-temel
unite: 5-LEGO Projeleri (rotayı kodla çizdirme)
kazanimlar: [cpp.setup-loop, cpp.delay, cpp.const-int, cpp.if-else, cpp.serial-begin, cpp.serial-println]
kara_kutu: [void, Deneyap_CiftKanalliMotorSurucu, DualMotorDriver, MotorSurucu.begin, MotorSurucu.MotorDrive, MotorSurucu.CheckMotorError, MOTOR1, MOTOR2]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Çift Kanallı Motor Sürücü, 2 adet 6V LEGO uyumlu DC motor, 2 adet 18650 pil + seri bağlı pil yuvası, çıt çıt anahtar (pil hattında), jumper kablolar, 5V powerbank, LEGO gövde parçaları]
board:
  kart: Deneyap Mini v2
  motor_surucu_i2c_adresi: "0x16"
  kumanda_kolu: "Bu derste bağlı/kullanılan bir modül değil."
  guc_kaynagi_1: "Deneyap kart: 5V powerbank, Type-C USB kablosuyla karta bağlanır."
  guc_kaynagi_2: "Motor sürücü: seri bağlı 2 x 18650 pil (~8,4V dolu), çıt çıt anahtar üzerinden, kartın beslemesinden ayrı."
  motor_yonu: "Motorlar araca karşılıklı takılı (dk0080 Özgür testi). Düz gitmek MOTOR1 yön 1 + MOTOR2 yön 0 ister; yerinde dönüş MOTOR1 ve MOTOR2'ye AYNI yön değeri (ikisi de 1) gönderilerek yapılır — dk0100'deki sağa dönüş çözümüyle tutarlı."
  sayilar_notu: "Araç en fazla %20 hızla gider (hizDuz=15, hizDon=20). hizDuz=15 dk0080'in test edilmiş değeridir. sureDuz, hizDon ve özellikle sureDon90 BAŞLANGIÇ DEĞERİDİR; sureDon90 kartta kalibre edilmeden dörtgenin köşeleri 90° olmaz. sureDon120, sureDon90'dan oranla hesaplanır, yine de kartta doğrulanmalıdır. İki ayrı hız tavanı var: donanımsal tavan %70 (pil gerilimi yüzünden), güvenlik tavanı %20 (Özgür'ün 2026-09-24 kararı, çocuk güvenliği). Bu derste geçerli olan sınır %20'dir; hiçbir hız bunu geçmez, 70'in üstüne asla çıkılmaz."
  seri_hiz: 115200
  guvenlik_notu: "Araç yerde, geniş ve boş bir alanda çalıştırılır; masada çalıştırılmaz. İlk deneme yine tekerlekler havadayken yapılır."
kaynak_kod: "Kaynakta bu davranış yok. dk0100'ün pivot dönüş kalıbı ve dk0080'in sabit-kod kalıbı birleştirilerek dk tarafından tasarlandı; begin/MotorDrive/CheckMotorError dışında yeni API kullanılmadı."
---

## 1. Hedef

`dk0100`'de kolu yana ittiğinde aracın yerinde döndüğünü (pivot dönüş)
öğrenmiştin. Bu derste kumanda kolu yok: araç kodla, kendi kendine köşeli
şekiller çizecek — **dörtgen** ve **üçgen**. Bir kenar = düz git + yerinde
dön. Dört kenarı da tek tek kopyala-yapıştır yazmak yerine, bunu **4 kere
tekrar et** diye söyleyen bir yapı kullanacaksın: `for` döngüsü.

**Güvenlik:** Araç en fazla **%20** hızla gider. Bunu `hizDuz`/`hizDon`
satırlarından değiştirebilirsin, ama **70'i geçme** — bu, motorların
kaldırabileceği donanımsal tavandır; %20 ise Özgür'ün çocuk güvenliği için
koyduğu ayrı, daha sıkı bir sınırdır.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Çift Kanallı Motor Sürücü
- 2 adet 6V LEGO uyumlu DC motor
- 2 adet 18650 pil, seri bağlı pil yuvasında
- Çıt çıt anahtar ve jumper kablolar
- 5V powerbank
- LEGO gövde parçaları (kumanda kolu bu derste **kullanılmaz**)

## 3. Parça tanıtımı

- **`for` döngüsü:** "Şu işi N kere tekrarla" demenin bir yolu. Bu ders onu
  kara kutu olarak göstermiyor — döngü fikrini (bir bloğun tekrar tekrar
  çalışması) zaten biliyorsun varsayılıyor; burada yeni olan, bunu `for`
  yazımıyla ifade etmek.
- **Dış açı:** Bir çokgenin köşesinde aracın **döndüğü** açı, köşenin **iç**
  açısı değildir. Kare gibi dört köşeli bir şekilde her köşe 90° döner
  (iç açı da 90° olduğu için fark görünmez), ama üçgende iç açı 60°
  olduğu hâlde araç her köşede **120°** döner — bunu §5'te anlatıyoruz.

## 4. Devre kurulumu

1. Motor sürücüyü karta I2C soketinden bağla (adres `0x16`); kumanda kolu
   bağlı olmak zorunda değil.
2. Seri bağlı 2 x 18650 pil yuvasının (çıt çıt anahtarı lehimli) jumper
   uçlarını motor sürücünün vidalı besleme girişine tornavidayla sık.
3. Kartı 5V powerbank'a Type-C USB kablosuyla bağla.
4. **Güvenlik:** Çıt çıt anahtar kapalıyken kodu yükle. Önce tekerlekleri
   havada tutarak dene, sonra aracı **geniş, boş bir alana** koy.

## 5. Kod açıklaması

### Kalibrasyon adımı — önce bunu yap

Kod `sureDon90` sabitiyle "motorları şu kadar milisaniye döndür" diyor,
ama bu süre kaç **derece** döndürdüğünü kaynaktan bilmiyoruz — çünkü bu
bilgi hiçbir kaynakta yok, kartına özgü. Kalibrasyon şöyle yapılır:

1. Kodu, `sureDon90` için tahmini bir değerle (örn. 500) karta yükle.
2. Aracı geniş bir alana koy, çalıştır, **ilk dönüşü** izle: yaklaşık 90°
   mi döndü, az mı döndü, çok mu döndü?
3. Az döndüyse `sureDon90`'ı büyüt, çok döndüyse küçült. Kodu yeniden
   yükle, tekrar izle.
4. Dönüş gözle 90°'ye yakın görünene kadar tekrarla. Bu **tahmin et →
   dene → ayarla** döngüsüdür; sayı kaynaktan gelmez, senin karttan
   ölçtüğün bir değerdir.

`sureDon120` bu kalibre edilmiş `sureDon90`'dan **oranla** (120/90)
hesaplanır — ama bu oran yalnız bir varsayımdır (dönüş süresi ile açı
doğru orantılı kabul edilir); üçgeni çizip köşelerin gerçekten ~120°
olup olmadığını ayrıca kartta doğrulaman gerekir.

### `for` döngüsü ve kenar mantığı

| kod satırı | açıklama |
| --- | --- |
| `for (int kenar = 0; kenar < 4; kenar++) {` | `kenar` adında bir sayaç 0'dan başlar, her turda 1 artar, 4'e ulaşınca döngü biter — blok içindeki kod **4 kere** çalışır. |
| `MotorSurucu.MotorDrive(MOTOR1, hizDuz, 1);` / `MotorDrive(MOTOR2, hizDuz, 0);` | `dk0080`'deki gibi düz gitme; kenarın uzunluğunu `sureDuz` belirler. |
| `MotorDrive(MOTOR1, hizDon, 1);` / `MotorDrive(MOTOR2, hizDon, 1);` | Yerinde dönüş: iki motora **aynı** yön değeri (`1`) gönderilir — `dk0100`'ün sağa dönüş çözümüyle aynı mantık. |
| `delay(sureDon90);` (dörtgende) / `delay(sureDon120);` (üçgende) | Dönüşün ne kadar süreceğini belirler; tek fark dörtgenle üçgen arasında budur. |
| `}` | Döngü burada kapanır; `kenar` tekrar kontrol edilip blok yeniden çalışır ya da döngü biter. |

Dörtgen ve üçgen kodu neredeyse aynıdır — tek fark tekrar sayısı (4/3) ve
dönüş süresidir (`sureDon90`/`sureDon120`). Bu, `for`'un asıl faydasını
gösterir: aynı bloğu farklı sayıda tekrarlamak için kopyala-yapıştır
yapmana gerek yok, yalnızca sayıyı değiştiriyorsun.

### İleri analiz [ileri]

Üçgende neden 120°? Bir çokgeni tamamen çizip başa dönmek için aracın
toplam **360°** dönmesi gerekir (tam tur). Üçgende 3 köşe var: 360° / 3 =
**120°** her köşede. Dörtgende 4 köşe var: 360° / 4 = **90°**. Bu, iç
açıdan (üçgende 60°, dörtgende 90°) farklı bir hesaptır — dış açı, "aracın
yönünü ne kadar değiştirdiği"dir.

## 6. Çalıştır ve gözlemle

Kalibrasyonu tamamladıktan sonra kodu yükle, aracı geniş bir alana koy.
Önce dörtgeni izle: dört kenar, dört dönüş, başa dönüş. Sonra üçgeni izle.
Seri Monitör'deki `"Dortgen"`/`"Ucgen"` etiketleriyle aracın hangi şekli
çizdiğini takip et.

### Sorun giderme

`dk0080`'deki sorun giderme maddeleri burada da geçerlidir. Ek olarak:

- **Dörtgenin köşeleri 90°'den çok farklı:** `sureDon90` kalibre edilmemiş
  olabilir; §5'teki kalibrasyon adımlarını tekrarla.
- **Üçgen kapanmıyor, araç başladığı noktaya dönmüyor:** `sureDon120`'nin
  `sureDon90`'dan doğru hesaplandığını kontrol et; ayrıca zemin kayganlığı
  ve pil doluluğu her dönüşte küçük farklar yaratabilir — bu, "araç nerede
  olduğunu bilmiyor, yalnız süre sayıyor" gerçeğinin bir sonucudur.
- **Şekil zamanla bozuluyor (ilk tur iyi, sonrakiler kötü):** Pil zayıfladıkça
  motor hızı düşebilir, bu da süreyle ayarlanan açı ve mesafeyi kaydırır.

## 7. Mini sınav

1. [temel] `for (int kenar = 0; kenar < 4; kenar++)` bloğu kaç kere çalışır?
   - A) 3
   - B) 4
   - C) Sonsuz
   - D) 1
   - ipucu: Sayaç 0'dan başlar, 4'e ulaşınca durur.

2. [temel] Bir kenar hangi iki adımdan oluşur?
   - A) Düz git + yerinde dön
   - B) Sadece dön
   - C) Sadece düz git
   - D) Dur + dur
   - ipucu: §1 Hedef'e bak.

3. [temel] `sureDon90` değeri nereden geliyor?
   - A) Kaynak koddan
   - B) Kartta kalibre edilerek bulunur
   - C) I2C adresinden
   - D) `for` döngüsünden
   - ipucu: §5'teki "Kalibrasyon adımı"na bak.

4. [temel] Üçgende araç her köşede kaç derece döner?
   - A) 60°
   - B) 90°
   - C) 120°
   - D) 180°
   - ipucu: §5 İleri analiz'deki 360°/köşe sayısı hesabına bak.

5. [ileri] Dörtgen ile üçgen kodu arasındaki tek fark nedir?
   - A) Motor sürücü adresi
   - B) Tekrar sayısı ve dönüş süresi
   - C) `for` yerine `while` kullanımı
   - D) Seri hız
   - ipucu: §5'teki kod tablosunun son satırlarına bak.

6. [ileri] Şekil zamanla neden bozulabilir?
   - A) `for` döngüsü hatalı çalıştığı için
   - B) Araç nerede olduğunu bilmiyor, yalnız süre sayıyor; pil/zemin değişimi süreyle açı/mesafe ilişkisini kaydırır
   - C) I2C adresi değiştiği için
   - D) Seri Monitör kapandığı için
   - ipucu: §6 Sorun giderme'nin son maddesine bak.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme.

### Ders promptları

- [temel] **Tekrar sayısından şekle:** "Sen sabırlı bir öğretmensin. Bağlam:
  `for` döngüsünü zaten biliyorum; şimdi Deneyap Mini v2'de bir aracı
  `for (int kenar = 0; kenar < 4; kenar++)` ile dörtgen çizdiriyorum. Bana
  pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Tekrar
  sayısı ile şeklin kenar sayısı arasındaki ilişkiyi düşündüren bir soru
  sor; cevabı söyleme."
- [temel] **İç açı - dış açı:** "Sen öğrenme koçumsun. Bağlam: Üçgen
  çizen aracım her köşede 120° dönüyor, ama üçgenin iç açısı 60°. Bana pin
  numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. Aracın
  'döndüğü açı' ile şeklin 'iç açısı' arasındaki farkı buldurtacak bir
  soru sor; cevabı verme."
- [temel] **Kalibrasyon mantığı:** "Sen hata ayıklama koçumsun. Bağlam:
  `sureDon90` değerim aracımı tam 90° döndürmüyor. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Tahmin et - dene -
  ayarla döngüsünü nasıl kuracağımı soru sorarak buldur."

### Kara kutu promptları

`dk0080`'deki kara kutu promptları burada da geçerlidir; yeni bir kara
kutu eklenmedi (`for` bu derste kara kutu değildir).

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kalibrasyon adımları (§5) yapıldı mı, `sureDon90` ayarlandı mı?
2. Dörtgenin dört köşesi de gözle benzer açıda mı dönüyor?
3. Üçgen başladığı noktaya yakın bir yere geri dönüyor mu?

## 9. SEN YAP

1. §5'teki kalibrasyon adımlarını izleyerek `sureDon90`'ı kendi aracında
   ayarla. Dörtgenin köşeleri gerçekten ~90° mi oluyor?
2. `for` döngüsündeki tekrar sayısını (4, 3) değiştirmeden, yalnız
   `sureDuz`'u değiştirerek dörtgeni büyüt/küçült.
3. `for` döngüsünü kullanarak bir **beşgen** çizmeyi dene: 5 kenar, dış açı
   360/5 = 72°. Kaç kere tekrarlanmalı, dönüş süresi nasıl hesaplanmalı?
   Çözüm `cozumler/`'de.
