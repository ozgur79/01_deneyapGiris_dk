# Malzeme

Eğitim setinin içeriği. Açık uçlu — envanter netleştikçe satır eklenir/güncellenir.
Bir ders, burada olmayan bir malzemeyi gerektiremez.

| parça | adet | not |
|-------|------|-----|
| Deneyap Mini v2 kartı | sette var | |
| Type-C ↔ USB kablo | sette var | |
| Breadboard | sette var | |
| Jumper kablo | sette var | |
| Direnç | sette var | 220 ohm (LED) ve 10K ohm (buton pull-down, dk0050) yeterince var — Özgür teyit etti (2026-09-21) |
| LED | sette var | renk/adet Özgür dolduracak |
| Buton | sette var | Özgür teyit etti (2026-09-18) |
| Deneyap Kumanda Kolu | Oturum 2 kaynaklarında kullanılıyor | |
| Deneyap Çift Kanallı Motor Sürücü | Oturum 3 (dk0080/dk0090/dk0100) | I2C soket, adres 0x16 |
| 6V LEGO uyumlu DC motor | 2 adet, Oturum 3 | |
| 18650 pil + seri bağlı 2'li pil yuvası | Oturum 3 | motor sürücünün beslemesi, kart beslemesi değil |
| 5V powerbank | Oturum 3 (dk0100) | LEGO araçta Deneyap kartın beslemesi; karta Type-C USB kablosuyla bağlanır (Özgür, 2026-09-24) |
| Çıt çıt anahtar | yeterince var (Özgür, 2026-09-24) | 18650 pil hattında, motor sürücü beslemesini açıp kapatır (dk0080-dk0100); pil yuvasının jumper hattına lehimli, jumper uçları motor sürücünün vidalı besleme girişine tornavidayla takılır |
| LEGO gövde parçaları | Oturum 3 (dk0100) | montaj adımları Özgür'den bekleniyor |
| 3D basılı LEGO uyumlu tabla | Oturum 4 (Özgür, 2026-09-24) | Deneyap kart ve breadboard bu tablanın üzerinde durur; tabla LEGO **7x11** frame'e takılır |
| LEGO 5x7 frame | eğitim setinde var (Özgür, 2026-09-24) | Deneyap Kumanda Kolu ve Deneyap Çift Kanallı Motor Sürücü modülleri bu frame'e takılabiliyor |

(liste açık uçlu — dersler ilerledikçe satır eklenir; adet/değer bilgisini Özgür doldurur)
