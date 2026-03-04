## BM25 (Best Matching 25)

TF-IDF klasik bir anahtar kelime arama algoritması olmaya devam etse de, günümüzde çoğu retriever’da kullanılan algoritma **Best Matching 25**, kısaca **BM25**’tir.

Bu isim, geliştiricileri tarafından önerilen puanlama fonksiyonları serisinin 25. varyantı olmasından gelir.

BM25, TF-IDF üzerine bazı önemli iyileştirmeler getirir. Şimdi bunların nasıl çalıştığını inceleyelim.

---

## BM25 Nasıl Çalışır?

BM25 formülü, belirli bir belge için tek bir anahtar kelimeye ait **alakalı (relevance) skorunu** hesaplar.

- Tüm anahtar kelimeler için bu skorlar toplanır.
- Ortaya çıkan toplam skor, belgenin sıralanmasında kullanılır.

Temel yapı TF-IDF’e oldukça benzerdir, ancak birkaç kritik geliştirme içerir.

---

## 1️⃣ Term Frequency Saturation (Terim Frekansı Doygunluğu)

TF-IDF’te bir kelime belgede ne kadar çok geçerse, skor o kadar artar.

Ancak BM25 şunu dikkate alır:

> Bir belgede “pizza” kelimesinin 20 kez geçmesi, 10 kez geçmesine göre iki kat daha alakalı olduğu anlamına gelmez.

Bu nedenle:

- Anahtar kelime tekrarlandıkça sağlanan ek katkı giderek azalır.
- Buna **term frequency saturation** denir.

Yani tekrar eden kelimeler için azalan getiriler uygulanır.

---

## 2️⃣ Document Length Normalization (Belge Uzunluğu Normalizasyonu)

TF-IDF’te uzun belgeler cezalandırılır, ancak bu ceza bazen fazla agresif olabilir.

BM25’te:

- Uzun belgeler hâlâ cezalandırılır.
- Ancak bu ceza da **azalan oranlıdır**.

Sonuç:

- Uzun belgeler, eğer anahtar kelimeleri yeterince yüksek frekansta içeriyorsa yine yüksek skor alabilir.
- Belge uzunluğuna göre yapılan bu ayarlamaya **document length normalization** denir.

---

## 3️⃣ Ayarlanabilir Hiperparametreler

BM25, TF-IDF’ten farklı olarak iki ayarlanabilir hiperparametre içerir.

Bu hiperparametreler:

- Terim frekansı doygunluğunun ne kadar hızlı gerçekleşeceğini
- Belge uzunluğu cezasının ne kadar güçlü uygulanacağını

kontrol eder.

Üretim ortamındaki (production) bir retriever’da bu hiperparametreler:

- Bilgi tabanındaki veri yapısına göre ayarlanır
- En iyi performansı verecek puanlama sistemine ulaşmak için optimize edilir

---

## Neden BM25?

Üretim sistemlerinde standart anahtar kelime arama algoritması genellikle **BM25**’tir.

Çünkü:

- TF-IDF’ten genellikle daha iyi performans gösterir
- Hesaplama maliyeti benzerdir
- Hiperparametre ayarlanabilirliği sayesinde daha esnektir

---

# Anahtar Kelime Aramasının Genel Özeti

Ana fikir şudur:

> Belgeler, prompt’taki anahtar kelimeleri ne sıklıkta içerdiğine göre eşleştirilir.

Bu süreçte:

- Hem prompt hem belgeler sparse vektörlere dönüştürülür.
- Bu vektörler, sistem sözlüğündeki her kelimenin metinde kaç kez geçtiğini sayar.
- TF-IDF veya BM25, bu vektörleri işleyerek belgeleri puanlar ve sıralar.

Bu yöntemler şu faktörleri dikkate alır:

- Kelimenin nadirliği (IDF)
- Belgede kaç kez geçtiği (TF)
- Belge uzunluğu

---

## Anahtar Kelime Aramasının Güçlü Yönleri

### ✅ 1. Basitlik

- Anlaşılması ve uygulanması görece kolaydır.
- Pratikte oldukça iyi çalışır.
- Çoğu zaman güçlü bir temel (baseline) performans sunar.

### ✅ 2. Kesin Kelime Eşleşmesi

Getirilen belgelerin, kullanıcının prompt’undaki anahtar kelimeleri **gerçekten içerdiğini garanti eder**.

Bu özellikle şu durumlarda çok önemlidir:

- Teknik terminoloji kullanıldığında
- Ürün adları birebir yazıldığında
- Spesifik kavramlar arandığında

---

## Zayıf Yönü

Anahtar kelime aramasının temel zayıflığı şudur:

> Sorgudaki kelimelerin belgede birebir geçmesine bağlıdır.

Eğer kullanıcı:

- Belgeyle aynı anlama gelen
- Ancak farklı kelimeler kullanan

bir prompt yazarsa, anahtar kelime araması bu eşleşmeyi yakalayamaz.

Bu sorunu çözmek için şimdi **anlamsal aramaya (semantic search)** geçeceğiz.