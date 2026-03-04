## Embedding Modelleri Nasıl Eğitilir?

Bir embedding modelinin görevi tanımlaması kolaydır:

- Benzer metinleri birbirine yakın vektörlere yerleştirmek  
- Farklı (anlamsal olarak uzak) metinleri ise daha uzak vektörlere yerleştirmek  

Ancak bir bilgisayarın metnin anlamını nasıl “anladığını” düşünmeye başladığınızda, bu işin ne kadar karmaşık olduğunu fark edersiniz.

Şimdi embedding modellerinin bu etkileyici işi nasıl başardığını inceleyelim.

---

# Pozitif ve Negatif Çiftler (Positive & Negative Pairs)

Embedding modelinin eğitimi, **pozitif ve negatif çiftler** kavramına dayanır.

### ✅ Pozitif Çift

Anlamca benzer iki metin:

- “good morning”
- “hello”

Bu iki ifade uzayda birbirine **yakın** yerleştirilmelidir.

### ❌ Negatif Çift

Anlamca farklı iki metin:

- “good morning”
- “that’s a noisy trombone”

Bu iki ifade uzayda **uzak** yerleştirilmelidir.

Modelin amacı:

- Pozitif çiftleri birbirine yaklaştırmak  
- Negatif çiftleri birbirinden uzaklaştırmak  

---

# 1️⃣ Eğitim Verisinin Oluşturulması

İlk adım:

- Çok büyük miktarda pozitif ve negatif çift toplamak

Gerçek sistemlerde:

- Milyonlarca örnek kullanılır.
- Her kelime veya metin parçası birçok farklı örnek içinde yer alır.
- Böylece çok sayıda kavramla ilişkisi öğrenilir.

---

# 2️⃣ Rastgele Başlangıç

Eğitimin başında:

- Model her metni rastgele bir vektöre eşler.
- Bu vektörlerin anlamla hiçbir ilgisi yoktur.
- Eğer bu aşamada retrieval yapılırsa sonuçlar anlamsız olur.

---

# 3️⃣ Contrastive Training (Karşıtlık Temelli Eğitim)

Model, eğitim verisindeki tüm pozitif ve negatif çiftlere bakar ve şunu sorar:

> Pozitif çiftleri ne kadar yakın yerleştirdim?  
> Negatif çiftleri ne kadar uzak yerleştirdim?

Bu yaklaşım, pozitif ve negatif örnekler arasındaki karşıtlığı kullanarak performansı ölçtüğü için **contrastive training** olarak adlandırılır.

Model:

- Hatalarına göre iç parametrelerini günceller.
- Pozitif çiftleri yaklaştırmaya
- Negatif çiftleri uzaklaştırmaya çalışır.

---

# 4️⃣ İteratif Güncelleme

Bu süreç defalarca tekrar edilir:

1. Metinler yeni parametrelerle tekrar vektörlere dönüştürülür.
2. Performans tekrar ölçülür.
3. Parametreler yeniden güncellenir.

Her turda:

- Bazı vektörler birbirine yaklaşır.
- Bazıları birbirinden uzaklaşır.

---

# Tek Bir Metin Üzerinden Örnek

Anchor (merkez) metin:

> “he could smell the roses”

Pozitif örnek:

> “a field of fragrant flowers”

Negatif örnek:

> “a lion roared majestically”

Başlangıçta hepsi rastgele konumlardadır.

Eğitim sürecinde:

- Anchor, pozitif örneği kendine yaklaştırır.
- Negatif örneği kendinden uzaklaştırır.

Milyonlarca örnek olduğunda:

- Her vektör aynı anda birçok yönde çekilir ve itilir.
- Süreç çok daha karmaşık hale gelir.

---

# Neden Yüksek Boyut?

Bu karmaşıklık nedeniyle:

- Embedding vektörleri yüzlerce hatta binlerce boyut içerir.
- Yüksek boyutlu uzay, nüanslı ilişkileri temsil etmeyi kolaylaştırır.
- Modelin vektörleri itip çekebileceği daha fazla yön olur.

---

# Eğitim Sonrası Ne Olur?

Eğitim tamamlandığında:

- Benzer kavramlar uzayda kümelenir.
- Farklı kavramlar birbirinden uzaklaşır.

Örneğin:

- “lion” ile ilgili kelimeler bir kümede
- “trombone” ile ilgili kelimeler başka bir kümede olabilir.

Önemli nokta:

> Bu kümeler uzayda belirli bir yerde anlam taşımaz.  
> Anlam, sadece benzer kavramların birlikte kümelenmesinden gelir.

---

# Rastgelelik ve Konum

Eğer eğitimi iki kez:

- Farklı rastgele başlangıç değerleriyle yaparsanız,

Aynı kümeler yine oluşur, ancak:

- Uzaydaki konumları farklı olabilir.

Yani önemli olan:

- Mutlak konum değil  
- Göreli konumdur (yakınlık/uzaklık)

---

# Önemli Uyarı: Aynı Modelin Vektörleri Karşılaştırılır

Yalnızca:

> Aynı embedding modeli tarafından üretilen vektörler karşılaştırılmalıdır.

Çünkü her model:

- Farklı veriyle eğitilmiştir.
- Farklı boyut sayısına sahiptir.
- Farklı rastgele başlangıç değerleri kullanır.

Farklı modellerin vektörlerini karşılaştırmak anlamsız sonuçlar üretir.

---

# Pratikte Ne Yaparsınız?

Genellikle:

- Hazır (off-the-shelf) embedding modelleri kullanırsınız.
- Bu modeller kelime, cümle veya belgeleri oldukça başarılı şekilde konumlandırır.
- Mesafe hesaplamalarını da genellikle hazır kütüphaneler yapar.

---

# Temel Çıkarımlar

1. Semantic vektörler soyuttur.
2. Eğitimden önce uzaydaki konumların anlamı yoktur.
3. Eğitimden sonra anlam, kümelenme yapısından doğar.
4. Yalnızca aynı modelin ürettiği vektörler karşılaştırılmalıdır.

Embedding modellerinin nasıl eğitildiğini anlamak, RAG sisteminizde semantic search’ü daha bilinçli kullanmanızı sağlar.

Bir sonraki bölümde bu yoğun (dense) vektörleri retriever içinde nasıl kullanabileceğinizi göreceğiz.