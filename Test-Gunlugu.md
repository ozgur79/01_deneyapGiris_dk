| ders | tarih | derlendi mi | kartta çalıştı mı | sorun | çözüm |
|------|-------|--------------|---------------------|-------|-------|
| dk0010 | 2026-09-11 | evet | evet | — | Özgür kartta test etti. |
| dk0020 | 2026-09-11 | evet | evet | — | Özgür kartta test etti. |
| dk0030 | 2026-09-11 | evet | evet | — | Özgür kartta test etti |
| dk0040 | 2026-09-18 | evet | evet | — | Özgür kartta test etti. |
| dk0050 | 2026-09-21 | evet | evet | — | Özgür kartta test etti. |
| dk0060 | 2026-09-23 | evet (kullanıcı bildirimi) | evet (kullanıcı bildirimi) | — | Kullanıcı testin geçtiğini bildirdi; yerel ortamda kütüphane eksik olduğundan ayrıca derlenmedi. |
| dk0070 | 2026-09-23 | evet (kullanıcı bildirimi) | evet (kullanıcı bildirimi) | — | Kullanıcı testin geçtiğini bildirdi; yerel ortamda kütüphane eksik olduğundan ayrıca derlenmedi. |
| dk0080 | 2026-09-24 | evet (Özgür) | evet (Özgür) | — | Özgür LEGO araçta test etti; motor yönleri (MOTOR2 ters, karşılıklı montaj), hiz=15 ve 500 ms adımlar güncellenerek onaylandı. ders.md ve yorumlar Ortak tarafından buna göre güncellendi. |
| dk0090_kumandaIleriGeri | 2026-09-24 | evet | kod çalışıyor (Özgür) | ileri/geri geçişler çok sert; çocuk aracın yanındayken risk | Hız %20'ye düşürüldü (maxHiz=70→20, map hedefi 0-100→0-maxHiz). Yeniden test gerekiyor. **%20 ile yeniden test edildi, onaylandı (Özgür, 2026-09-24).** |
| dk0100_kumandaSagaSola | 2026-09-24 | evet | kod çalışıyor (Özgür) | sağa/sola dönüşler çok sert; çocuk aracın yanındayken risk | Hız %20'ye düşürüldü (maxHiz=70→20, donusHizi=50→20). Yeniden test gerekiyor. Ders adı/klasörü Oturum 4'te `dk0100_legoArac`'tan `dk0100_kumandaSagaSola`'ya (4.3) dönüştürüldü; eski SEN YAP dönüş kodu artık ana koddur. **%20 ile yeniden test edildi, onaylandı (Özgür, 2026-09-24).** |
| dk0110_dortgenUcgen | 2026-09-24 | evet (Özgür) | evet (Özgür) — onaylandı | — | Eskiden `dk0120_dortgenUcgen` idi; Özgür onayladıktan sonra dörtgen/üçgen dersi öne, daire+S rota dersi arkaya alınacak şekilde numaralar yer değiştirdi (5.1). `sureDon90` kalibrasyonu yapılmadan köşeler 90° olmaz; hiçbir hız %20'yi geçmez. |
| dk0120_daireVeSRota | 2026-09-24 | ders kartı onaylandı (Özgür, 2026-09-24); kod yok, Özgür'ün kararı | — | — | dk0120 hiç kod içermiyor: `.ino` dosyası ve `cozumler/dk0120_daireVeSRota` kaldırıldı. Klasörde yalnız ders.md var — bir görev kartı (hedef, kavram ipucu, dk0080/dk0100/dk0110'a göndermeler, %20 hız kuralı, karşılıklı montaj yön kuralı, kalibrasyon döngüsü, AI Yoldaşı/yetişkin kartı). Gerekçe (Özgür): "öğrenci kendi kanatlarıyla uçup görevi tamamlasın." |
