---
dk_no: dk0120
portal_ders: "9.2"
portal_ders_not: "Portal-Ders-Haritasi.md tek kaynak (Özgür, 2026-09-24): dk0120 = 9.2 (12 modüllü yapı). Bu ders aynı gün beş biçim değiştirdi: adım adım ders → meydan okuma (challenge) → adım adım + SEN YAP çözümlü → adım adım + SEN YAP çözümsüz → şimdiki hâli, HİÇ KOD İÇERMEYEN bir görev kartı. Özgür'ün gerekçesi: 'öğrenci kendi kanatlarıyla uçup görevi tamamlasın.' `.ino` dosyası kaldırıldı; klasörde yalnız bu ders.md var."
kaynak_ak: []
baslik: "Kodla yay çiz: iki tekerlek, iki hız"
duzey: 0-temel
unite: 9-Robot Araç: Kodla Rota
kazanimlar: []
kara_kutu: []
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Çift Kanallı Motor Sürücü, 2 adet 6V LEGO uyumlu DC motor, 2 adet 18650 pil + seri bağlı pil yuvası, çıt çıt anahtar (pil hattında), jumper kablolar, 5V powerbank, LEGO gövde parçaları]
board:
  kart: Deneyap Mini v2
  motor_surucu_i2c_adresi: "0x16"
  kumanda_kolu: "Bu görevde bağlı/kullanılan bir modül değil; araç kumandasız, kodla hareket eder."
  guc_kaynagi_1: "Deneyap kart: 5V powerbank, Type-C USB kablosuyla karta bağlanır."
  guc_kaynagi_2: "Motor sürücü: seri bağlı 2 x 18650 pil (~8,4V dolu), çıt çıt anahtar üzerinden, kartın beslemesinden ayrı."
  motor_yonu: "Motorlar araca karşılıklı takılı (dk0080 Özgür testi): araç düz ileri gitmek için MOTOR1 yön 1 + MOTOR2 yön 0 ister."
  hiz_siniri: "Araç en fazla %20 hızla gider. Bunu kendi kodundaki hız sabitlerinden ayarlarsın, ama 70'i geçme — donanımsal tavan bu (pil gerilimi yüzünden); %20 Özgür'ün çocuk güvenliği için koyduğu ayrı, daha sıkı bir sınırdır (2026-09-24)."
  seri_hiz: 115200
  guvenlik_notu: "Araç yerde, geniş ve boş bir alanda çalıştırılır; masada çalıştırılmaz. İlk deneme tekerlekler havadayken, çıt çıt anahtar kapalıyken kod yüklenip sonra açılarak yapılır."
kaynak_kod: "Bu görev kartı KOD İÇERMEZ. Öğrenci dk0080, dk0100 ya da dk0110'daki kodlardan birini başlangıç noktası seçip kendi kodunu yazar (Özgür kararı, 2026-09-24)."
---

## 1. Görev

Aracını kodla sürdür, kumanda kullanma. Sırayla şunları başar:

1. Aracın **bir yay** (eğri bir hat) çizmesini sağla.
2. Yayı **büyük bir daireye** dönüştür.
3. Aynı fikirle **küçük bir daire** çizdir.
4. İki yayı art arda kullanarak bir **S rota** çizdir.

Bu kart sana kod vermiyor. Aşağıdaki ipucu, başlangıç noktaları ve kurallarla
kendi kodunu yazacaksın.

## 2. Malzemeler ve devre

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Çift Kanallı Motor Sürücü
- 2 adet 6V LEGO uyumlu DC motor
- 2 adet 18650 pil, seri bağlı pil yuvasında
- Çıt çıt anahtar ve jumper kablolar
- 5V powerbank
- LEGO gövde parçaları (kumanda kolu **kullanılmaz**)

Devre `dk0110`/`dk0080` ile aynıdır: motor sürücü karta I2C soketinden
bağlı (adres `0x16`), seri bağlı 2 x 18650 pil + çıt çıt anahtar ile
besleniyor, kart 5V powerbank'a Type-C USB ile bağlı.

## 3. Kavram ipucu

İki tekerlek **aynı yönde ama farklı hızda** dönerse araç düz gitmez,
**yavaş** dönen tarafa doğru kıvrılır — yay çizer. Hız farkı büyüdükçe yay
keskinleşir (daire küçülür); fark küçüldükçe daire büyür. S rota, iki
yayın **art arda**, aradaki hızlar **yer değiştirerek** gelmesidir.

## 4. Nereden başlarsın?

Sıfırdan yazmana gerek yok. Daha önceki üç dersten biri sana bir başlangıç
noktası verebilir — hangisinin bu göreve en yakın olduğuna kendin karar ver:

- **`dk0080`** — motor sürücüyü kumandasız, sabit hız/yönle sürmüştün.
- **`dk0100`** — iki motora **aynı** yön değeri vererek yerinde döndürmüştün
  (pivot dönüş).
- **`dk0110`** — kumandasız, `for` ile tekrarlanan düz git + dönüş kalıbı
  kullanmıştın.

Hangisindeki kodu açıp başlangıç noktası olarak alabileceğini düşün: bu
görevde motorlara **farklı** hız vermen gerekiyor, ama yön mantığı hangi
dersteki gibi?

## 5. Güvenlik ve hız kuralı

Araç en fazla **%20** hızla gider. Kendi kodundaki hız sabitlerini
ayarlayabilirsin ama **70'i geçme** — bu, motorların kaldırabileceği
donanımsal tavandır; %20 ise Özgür'ün çocuk güvenliği için koyduğu ayrı,
daha sıkı bir sınırdır. Araç **yerde**, geniş ve boş bir alanda çalışır;
masada değil. Çıt çıt anahtar kapalıyken kodu yükle, ilk denemeyi
tekerlekler havadayken yap.

**Karşılıklı montaj kuralı:** Motorlar araca karşılıklı takılı. Araç düz
ileri gitmek için `MOTOR1` yön `1` + `MOTOR2` yön `0` ister (`dk0080`'de
doğrulandı). Bu görevde iki motora **farklı hız** vereceksin ama yön
mantığını bu kuraldan sapmadan kur.

## 6. Kalibrasyon döngüsü

Doğru hız ve süre değerleri pilin o anki doluluğuna, zemine ve aracının
montajına bağlıdır — aynı kod dolu pille daha büyük bir daire çizebilir,
pil azaldıkça daire küçülebilir ya da araç hiç dönmeyebilir. Tek bir
"doğru cevap" yok. Her adımı şu döngüyle çöz:

> **Tahmin et → dene → gözle → bir değeri değiştir → tekrar dene.**

Her denemeden sonra ne gördüğünü (yayın büyüklüğü, tekerleğin dönüp
dönmediği, aracın hangi tarafa kıvrıldığı) kısaca not et.

## 7. Mini sınav

1. [temel] İki motor aynı yönde ama farklı hızda dönerse araç ne yapar?
   - A) Düz gider
   - B) Yavaş tarafa doğru kıvrılır
   - C) Durur
   - D) Geri gider
   - ipucu: §3 Kavram ipucu'na bak.

2. [temel] Hız farkı büyüdükçe yay ne olur?
   - A) Büyür
   - B) Küçülür (keskinleşir)
   - C) Değişmez
   - D) Kare olur
   - ipucu: §3'e bak.

3. [temel] Araç düz ileri gitmek için MOTOR1/MOTOR2'ye ne gönderilir?
   - A) İkisine de aynı yön değeri
   - B) MOTOR1 yön 1, MOTOR2 yön 0
   - C) İkisine de hız 0
   - D) Yalnız MOTOR1'e komut
   - ipucu: §5'teki "Karşılıklı montaj kuralı"na bak.

4. [temel] Bu görevde hız sabitlerin için üst sınır nedir?
   - A) %70
   - B) %20
   - C) %100
   - D) Sınır yok
   - ipucu: §5 Güvenlik ve hız kuralı'na bak.

5. [ileri] Doğru hız/süre değerleri neden tek bir sayı olarak verilmiyor?
   - A) Kaynak kod gizli tutulduğu için
   - B) Pilin doluluğuna, zemine ve montaja göre değiştiği için
   - C) I2C adresi her seferinde değiştiği için
   - D) Seri Monitör hızı sabit olmadığı için
   - ipucu: §6 Kalibrasyon döngüsü'ne bak.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa bu görevi §4'teki
> başlangıç noktaları ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın
> dediği devrende/kartında çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan
> pin numarası, direnç değeri, menü yolu, bağlantı tarifi, hazır kod ya da hazır
> hız/süre sayısı isteme — bu görevde doğru değeri AI değil, senin kartın belirler.

- [temel] **Başlangıç noktası seçmek:** "Sen bir görev koçusun, bana asla kod
  veya sayı vermezsin. Bağlam: Deneyap Mini v2'de aracımı kodla yay/daire/S
  rota çizdirmem gerekiyor; dk0080, dk0100 ve dk0110'daki kodları biliyorum.
  Bana hazır kod verme. Hangi dersin yön mantığının bu göreve en yakın
  olduğunu kendim bulmamı sağlayacak bir soru sor."
- [temel] **Hız farkını kurmak:** "Sen bir kalibrasyon koçusun, bana sayı
  vermezsin. Bağlam: İki motoruma farklı hız vermeye çalışıyorum ama araç
  hâlâ düz gidiyor. Bana doğrudan bir sayı söyleme; kodumda kontrol etmem
  gereken şeyi soru sorarak buldur."
- [temel] **Kalibrasyon:** "Sen bir kalibrasyon koçusun, bana sayı vermezsin.
  Bağlam: Az önce gözlemlediğim şeyi sana anlatacağım — sonra bana hangi
  değeri hangi yöne değiştirmem gerektiğini düşündürecek bir soru sor, kendim
  karar vereyim."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı ya da sayıyı söylemeyin, sırayla şunları sorun:

1. Kod yüklenmeden önce çıt çıt anahtar kapalı, tekerlekler havada mıydı?
2. Hangi dersteki (dk0080/dk0100/dk0110) kodu başlangıç noktası seçti, neden?
3. Bir değeri değiştirip yeniden denedikten sonra aradaki farkı (yay
   büyüdü mü küçüldü mü, tekerlek döndü mü) birlikte gözlemlediniz mi?
4. Araç geniş, boş bir alanda mı denendi?
