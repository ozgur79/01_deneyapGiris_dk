---
dk_no: dk0100
portal_ders: "8.2"
portal_ders_not: "Portal-Ders-Haritasi.md tek kaynak (Özgür, 2026-09-24): dk0100 = 4.3 idi. Eski 'LEGO araç' dersi (kodu dk0090 ile aynıydı) bu derse dönüştürüldü; 'LEGO araç' ayrı bir portal numarası olmaktan çıktı. Aynı gün 12 modüllü yapıya taşındı: dk0100 eski 4.3'ten 8.2'ye taşındı. Portalda henüz yayında değil, numara değişimi serbest."
kaynak_ak: []
baslik: Kumandayla sağa/sola dön
duzey: 0-temel
unite: 4-Motor
kazanimlar: [cpp.setup-loop, cpp.delay, cpp.const-int, cpp.if-else, cpp.serial-begin, cpp.serial-println]
kara_kutu: [void, Deneyap_CiftKanalliMotorSurucu, DualMotorDriver, Deneyap_KumandaKolu, Joystick, MotorSurucu.begin, KumandaKolu.begin, KumandaKolu.yRead, KumandaKolu.xRead, MotorSurucu.MotorDrive, MotorSurucu.CheckMotorError, MOTOR1, MOTOR2, uint16_t, map, constrain]
malzeme: [Deneyap Mini v2 kartı, Type-C USB kablosu, Deneyap Kumanda Kolu, Deneyap Çift Kanallı Motor Sürücü, 2 adet 6V LEGO uyumlu DC motor, 2 adet 18650 pil + seri bağlı pil yuvası, çıt çıt anahtar (pil hattında), jumper kablolar, 5V powerbank, LEGO gövde parçaları]
board:
  kart: Deneyap Mini v2
  kumanda_kolu_i2c_adresi: "0x1A"
  motor_surucu_i2c_adresi: "0x16"
  i2c_paylasim_notu: "Kumanda kolu ve motor sürücü aynı I2C hattını paylaşır; ikisi de kendi adresiyle begin() ile başlatılır."
  guc_kaynagi_1: "Deneyap kart: 5V powerbank, Type-C USB kablosuyla karta bağlanır (Özgür, 2026-09-24)."
  guc_kaynagi_2: "Motor sürücü: seri bağlı 2 x 18650 pil (~8,4V dolu), kartın beslemesinden tamamen ayrı. Pil hattında çıt çıt anahtar var; anahtar pil yuvasının jumper hattına lehimlidir; hattın hazır jumper uçları motor sürücünün vidalı besleme girişine tornavidayla sıkıştırılır."
  motor_yonu: "Motorlar araca karşılıklı takılı (dk0080 Özgür testi, 2026-09-24). Kod MOTOR2'ye 1 - yon gönderir."
  sol_sag_varsayimi: "MOTOR1'in sol, MOTOR2'nin sağ motor olduğu kartta doğrulanmadı. Joystick sağa itilince araç sola dönerse §6 Sorun giderme'deki çözüm iki dönüş dalını yer değiştirir."
  max_hiz_notu: "İki AYRI sınır var. (1) Donanımsal tavan %70: kaynak kodun kendi notu, motorlara giden gerilimi ~6V'ta tutmayı amaçlar. (2) Güvenlik tavanı %20 (maxHiz=20, donusHizi=20): Özgür aracı test ederken ileri/geri ve dönüşlerin çok sert olduğunu, çocuğun elindeyken aracın fırlayıp masadan düşebileceğini gördü (2026-09-24). Bu derste geçerli olan sınır %20'dir. map'in hedef aralığı da 0-100 yerine 0-maxHiz yapıldı (dk0090 ile aynı gerekçe: kolun küçük hareketi bile hızı orantılı/yumuşak artırsın)."
  seri_hiz: 115200
  guvenlik_notu: "Motorlar pil takılıyken beklenmedik anda dönebilir. İlk deneme tekerlekler havadayken, çıt çıt anahtar kapalıyken kod yüklenip sonra açılarak yapılır."
kaynak_kod: "Kaynakta bu davranış yok — dk0090'ın kaynağında (dyminiV2501kk_deneyapMotorSurucu_2Motor.ino) yalnız Y ekseni kullanılıyordu. X ekseniyle pivot dönüş dk tarafından tasarlandı (ilk olarak Oturum 3'te dk0100'ün SEN YAP çözümü olarak yazıldı, Oturum 4'te bu dersin ana koduna taşındı)."
---

## 1. Hedef

`dk0090`'da kolu ileri/geri ittin, araç düz gitti ya da geri geldi. Bu derste
kolu **yana** (X ekseni) ittiğinde aracın olduğu yerde dönmesini sağlayacaksın.
Fikir basit: iki motoru **zıt yönde** döndürürsen araç bir yerden ötekine
gitmez, kendi ekseni etrafında döner. Buna **pivot dönüş** denir.

**Güvenlik:** Araç en fazla **%20** hızla gider. Bunu `maxHiz`/`donusHizi`
satırlarından değiştirebilirsin, ama **70'i geçme** — bu, motorların
kaldırabileceği donanımsal tavandır; %20 ise Özgür'ün çocuk güvenliği için
koyduğu ayrı, daha sıkı bir sınırdır.

## 2. Malzemeler

- Deneyap Mini v2 kartı ve Type-C USB kablosu
- Deneyap Kumanda Kolu
- Deneyap Çift Kanallı Motor Sürücü
- 2 adet 6V LEGO uyumlu DC motor
- 2 adet 18650 pil, seri bağlı pil yuvasında
- Çıt çıt anahtar ve jumper kablolar
- 5V powerbank
- LEGO gövde parçaları

## 3. Parça tanıtımı

- **X ekseni:** Kumanda kolunun yana (sağa/sola) hareketini okuyan eksen.
  `dk0060`'da yalnız Y okumuştun; `xRead()` aynı mantıkla X'i okur.
- **Pivot dönüş:** İki tekerlek zıt yönde dönerse araç ileri/geri gitmeden
  kendi ekseni etrafında döner. Tek bir tekerlek durup öteki dönseydi araç
  geniş bir kavis çizerdi — bu ders o yolu değil, **yerinde dönüşü** seçti.
- **İki ayrı güç kaynağı:** Bu araçta kart ve motor sürücü **farklı**
  kaynaklardan beslenir. Kart, 5V powerbank'a Type-C USB kablosuyla bağlanır.
  Motor sürücü ise seri bağlı 2 x 18650 pilden, çıt çıt anahtar üzerinden
  beslenir. İkisi birbirine karışmaz: powerbank'ı söksen bile motor sürücü
  kendi piliyle motorları döndürmeye devam eder (kart iletişim kuramasa da).

## 4. Devre kurulumu ve montaj

**Elektronik bağlantılar** `dk0090` ile aynıdır:

1. Motor sürücüyü karta I2C soketinden bağla (adres `0x16`), motorları
   sürücünün çıkışlarına bağla. Seri bağlı 2 x 18650 pil yuvasının
   (çıt çıt anahtarı lehimli) jumper uçlarını motor sürücünün vidalı besleme
   girişine tornavidayla sık.
2. Kumanda kolunu karta I2C soketinden bağla (adres `0x1A`).
3. Kartı **5V powerbank'a Type-C USB kablosuyla** bağla.

**LEGO montajı:**

Şimdiye kadar netleşenler (Özgür, 2026-09-24):
- Deneyap kart ve breadboard, 3D yazıcıyla basılmış LEGO uyumlu bir **tabla**
  üzerinde duruyor; bu tabla LEGO **7x11** frame'e takılıyor.
- Deneyap Kumanda Kolu ve Deneyap Çift Kanallı Motor Sürücü modülleri LEGO
  **5x7** frame'e takılabiliyor.

> **[Özgür'den bekleniyor]** — Bu parçaların (tabla, 5x7 frame'ler, motorlar,
> powerbank, pil yuvası) aracın gövdesinde tam olarak nasıl bir araya
> geleceği, hangi sırayla monte edileceği burada Özgür'ün fotoğraf/adım
> setiyle tamamlanacak. Bu ders o gelene kadar montaj **sırasını**
> uydurmaz; yer tutucu olarak bırakılmıştır.

**Güvenlik:** Çıt çıt anahtar **kapalı** olsun, kodu öyle yükle. Aracı
tekerlekleri havada kalacak şekilde masaya koy, önce öyle dene; ancak bundan
sonra yere indir.

## 5. Kod açıklaması

Kod dört durumu ayırt eder: **ileri, geri, sağa dön, sola dön** (ve hiçbiri
değilse dur). Y ekseni önce kontrol edilir; Y ölü bölgedeyse (araç ileri/geri
gitmiyorsa) X ekseni devreye girer.

| kod satırı | açıklama |
| --- | --- |
| `uint16_t xEkseni = KumandaKolu.xRead();` | **Kara kutu `xRead()`:** kolun X yönündeki o anki değerini verir — `yRead()`'in X karşılığı. |
| `if (yEkseni > ileriEsik) { ... }` / `else if (yEkseni < geriEsik) { ... }` | `dk0090` ile birebir aynı: iki motor aynı hız ve yönde, araç düz gider. |
| `else if (xEkseni > sagaEsik) { ... }` | Y ölü bölgedeyken X sağa eşiği geçerse pivot sağa dönüş hesaplanır. |
| `hizSol = donusHizi; yonSol = 1;` / `hizSag = donusHizi; yonSag = 0;` | Sol motor ileri, sağ motor geri — araç sağa döner (MOTOR1=sol, MOTOR2=sağ varsayımıyla). |
| `else if (xEkseni < solaEsik) { ... }` | Aynı mantığın X sola dönüşü; yönler ters çevrilir. |
| `MotorSurucu.MotorDrive(MOTOR2, hizSag, 1 - yonSag);` | `dk0090`'daki gibi MOTOR2'nin yönü ters çevrilir; bu, pivot dönüşte de geçerlidir. |

### İleri analiz [ileri]

Bu kod `if`/`else if` zincirini dört yola ayırıyor: ileri, geri, sağ pivot,
sol pivot. Aynı anda ikisi birden gerçekleşemez — Y ölü bölgede değilse X
hiç okunmuş gibi davranır, kod ona hiç bakmaz. Bu, `dk0090`'daki tek `if`/
`else if` zincirinin dört dallı hâlidir; fikir aynı, dal sayısı arttı.

## 6. Çalıştır ve gözlemle

Çıt çıt anahtar kapalıyken kodu yükle, tekerlekleri havada tutarak anahtarı
aç. Kolu sağa it: bir tekerlek ileri, öteki geri dönmeli, araç yerinde
dönmeli. Kolu sola it, tersini gözlemle. Sonra Y ekseniyle ileri/geri dene.

### Sorun giderme

`dk0090`'daki tüm sorun giderme maddeleri burada da geçerlidir. Ek olarak:

- **Kolu sağa itince araç sola dönüyor (ya da tersi):** `sol_sag_varsayimi`
  kartta doğrulanmadı. Kodda `xEkseni > sagaEsik` ve `xEkseni < solaEsik`
  bloklarının **içindeki** `yonSol`/`yonSag` atamalarını birbiriyle
  değiştir (sağa bloğundakini sola bloğuna, sola bloğundakini sağa
  bloğuna taşı).
- **Kolu sağa/sola itince araç ileri/geri gidiyor:** `sagaEsik`/`solaEsik`
  ile `ileriEsik`/`geriEsik` karıştırılmış olabilir; X okumasının doğru
  değişkene (`xEkseni`) atandığını kontrol et.
- **Araç dönüyor ama çok hızlı/kontrolsüz:** `donusHizi` değerini düşür.
- **Pivot dönüş hiç çalışmıyor, araç yalnız ileri/geri gidiyor:** Kolu tam
  yana, Y ekseni ortadayken (ölü bölgede) itip itmediğini kontrol et; Y
  ölü bölgede değilse kod X'e hiç bakmaz.

## 7. Mini sınav

1. [temel] İki motor zıt yönde döndüğünde araç ne yapar?
   - A) Düz ileri gider
   - B) Yerinde döner (pivot dönüş)
   - C) Durur
   - D) Hata verir
   - ipucu: §1 Hedef'teki tanıma bak.

2. [temel] `xRead()` hangi eksendeki değeri okur?
   - A) Y (ileri/geri)
   - B) X (sağa/sola)
   - C) I2C adresini
   - D) Motor hızını
   - ipucu: `dk0060`'daki `yRead()`'in X karşılığı.

3. [temel] X ekseni ne zaman dönüş için kullanılır?
   - A) Her zaman
   - B) Yalnız Y ekseni ölü bölgedeyken
   - C) Yalnız araç geri giderken
   - D) Yalnız kod başlarken
   - ipucu: `if`/`else if` zincirindeki sıraya bak.

4. [temel] `donusHizi` neyi belirler?
   - A) İleri/geri gitme hızını
   - B) Pivot dönüş sırasındaki motor hızını
   - C) I2C adresini
   - D) Seri Monitör hızını
   - ipucu: Değişkenin yalnızca sağa/sola bloklarında kullanıldığına bak.

5. [ileri] Kod aynı anda hem ileri gitmeyi hem pivot dönmeyi yapabilir mi?
   - A) Evet, ikisi birlikte çalışır
   - B) Hayır; `if`/`else if` zinciri yalnız bir dalı çalıştırır
   - C) Yalnız `maxHiz` düşükse
   - D) Yalnız `donusHizi` yüksekse
   - ipucu: §5 İleri analiz'e bak.

6. [ileri] MOTOR1/MOTOR2'nin hangisinin sol, hangisinin sağ olduğu neden
   kesin değil?
   - A) Kart bunu otomatik algılıyor
   - B) Kartta doğrulanmadı; montaja göre değişebilir
   - C) `xRead()` bunu söylemiyor diye
   - D) I2C adresi bunu belirliyor
   - ipucu: `board:` bloğundaki `sol_sag_varsayimi`'na bak.

## 8. AI Yoldaşı promptları

> **Önce bunu oku.** AI Yoldaşı zorunlu değildir; erişimin yoksa dersi §6 Sorun giderme
> ve aşağıdaki yetişkin kartıyla tamamlayabilirsin. *AI'ın dediği devrende/kartında
> çalışmıyorsa AI yanılmıştır, devren haklıdır.* AI'dan pin numarası, direnç değeri,
> menü yolu veya bağlantı tarifi isteme.

### Ders promptları

- [temel] **İki eksenden dört yola:** "Sen sabırlı bir öğretmensin. Bağlam:
  Deneyap Mini v2'de joystick Y ekseniyle ileri/geri, X ekseniyle yerinde
  sağa/sola dönüş yapan bir araç kodluyorum; motor sürücü 0x16, kumanda
  kolu 0x1A. Bana pin numarası, direnç değeri, menü yolu veya bağlantı
  tarifi verme. Kodun aynı anda kaç farklı hareketi seçebileceğini
  düşündüren bir soru sor; cevabı söyleme."
- [temel] **Pivot dönüş mantığı:** "Sen öğrenme koçumsun. Bağlam: İki
  motoru zıt yönde döndürünce aracım yerinde dönüyor. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Neden tek motoru
  durdurmak yerine ikisini de zıt yönde döndürdüğümü düşündüren bir soru
  sor; cevabı verme."
- [temel] **Hata ayıklama:** "Sen hata ayıklama koçumsun. Bağlam: Kolu
  sağa ittiğimde aracım beklediğimin tersine dönüyor. Bana pin numarası,
  direnç değeri, menü yolu veya bağlantı tarifi verme. Hangi motorun
  hangi tarafta olduğunu ve kod içindeki yön atamalarını sırayla
  kontrol ettiren sorular sor; cevabı verme."

### Kara kutu promptları

- [temel] **`xRead()`:** "Sen meraklı bir öğretmensin. Bağlam: Kodumda
  `KumandaKolu.yRead()`'in yanına `KumandaKolu.xRead()` ekledim. Bana
  pin numarası, direnç değeri, menü yolu veya bağlantı tarifi verme. İki
  fonksiyonun aynı nesneden (`KumandaKolu`) farklı eksenler okuduğunu
  düşündüren bir soru sor; cevabı söyleme."

### Yanındaki yetişkine

Bu kart çocuğa değil yanındaki yetişkine yazıldı; AI ve internet gerekmez.
Cevabı söylemeyin, sırayla şunları sorun:

1. Kod yüklenmeden önce çıt çıt anahtar kapalı, tekerlekler havada mıydı?
2. Kolu sağa ittiğinizde araç bir yöne, sola ittiğinizde öteki yöne mi
   dönüyor (yön hangisi olursa olsun, önemli olan tutarlılık)?
3. Kolu bıraktığınızda araç duruyor mu?

## 9. SEN YAP

1. `donusHizi` değerini değiştir (örn. 10 ve 18). Aracın dönüş hızı ve
   kontrolü nasıl değişiyor? 20'yi geçme — bu güvenlik sınırıdır. Çözüm `cozumler/`'de.
2. `sagaEsik`/`solaEsik` değerlerini birlikte değiştir. Kolun ne kadar
   yana itilmesi gerektiği nasıl değişiyor? Çözüm `cozumler/`'de.
3. Zemine bantla bir kare ya da daire çiz. Aracı yalnız kumandayla sürüp
   bandı takip etmeyi dene. Bunun tek bir "doğru" kodu yok; gözlemini ve
   denemeni kendi cümlenle anlat.
