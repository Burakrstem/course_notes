## Anlamsal Arama (Semantic Search)

Şimdi dikkatimizi **anlamsal aramaya (semantic search)** çevirelim.

Anlamsal arama, belgeleri prompt ile **ortak anlamlarına göre** eşleştirebilir ve anahtar kelime aramasının kaçırdığı nüansları yakalayabilir.

Örneğin:

- Anahtar kelime araması **happy** ve **glad** kelimelerini eşleştiremez (eş anlamlı olmalarına rağmen).
- Ayrıca **Python (programlama dili)** ile **python (yılan)** kelimelerini yanlış şekilde eşleştirebilir.

Anlamsal aramanın arkasındaki teknoloji oldukça etkileyicidir. Şimdi nasıl çalıştığını inceleyelim.

---

# Yüksek Seviyede Çalışma Mantığı

Yüzeyde bakıldığında anlamsal arama, anahtar kelime aramasına benzer:

1. Her belge bir vektöre dönüştürülür.
2. Prompt da bir vektöre dönüştürülür.
3. Bu vektörler karşılaştırılır.
4. En yakın olan belgeler en alakalı kabul edilir.

Ancak temel fark şudur:

> Vektörlerin nasıl oluşturulduğu.

---

# Embedding Model Nedir?

Anahtar kelime aramasında kelimelerin frekansını sayarsınız.

Anlamsal aramada ise belge veya prompt, **embedding modeli** adı verilen özel bir matematiksel modelden geçirilerek vektöre dönüştürülür.

Embedding modeli:

- Kelimeleri uzaydaki bir konuma eşler.
- Bu konum bir vektörle temsil edilir.

Örneğin:

- “pizza” → (3, 1)
- “bear” → (5, 2)

İki boyutlu uzayda bunları x-y düzleminde noktalar olarak düşünebilirsiniz.

---

# Anlamsal Yakınlık = Uzaydaki Yakınlık

Embedding modelinin “sihirli” tarafı şudur:

> Anlamsal olarak benzer kelimeler uzayda birbirine yakın konumlara yerleştirilir.

Örneğin:

- “food” ve “cuisine” → birbirine yakın
- “trombone” ve “cat” → birbirinden uzak

Benzer anlam → yakın konum  
Farklı anlam → uzak konum

Bu eksenlerin basit bir yorumu yoktur.  
“Yemek ekseni” veya “hayvan ekseni” gibi açık bir anlam taşımazlar.

Sadece çok boyutlu bir uzayda kümelenmiş noktalar olarak düşünmelisiniz.

---

# Yüksek Boyutlu Uzay

2 boyut yetersizdir.

3 boyutlu vektörler düşünelim:

- Daha fazla kavramsal küme oluşabilir.
- Daha nüanslı ilişkiler yakalanabilir.

Gerçek embedding modellerinde:

- Vektörler yüzlerce hatta binlerce boyut içerir.
- Bu yüksek boyutlu uzayı görselleştirmek imkânsızdır.
- Ancak matematiksel prensipler aynıdır.

---

# Cümle ve Belge Embedding’leri

Embedding modelleri sadece kelimeler için değil:

- Kelimeler
- Cümleler
- Tüm belgeler

için de vardır.

Her durumda model:

> Girdiyi alır ve onu uzaydaki tek bir noktayı temsil eden bir vektöre dönüştürür.

Örneğin:

1. He spoke softly in class.  
2. He whispered quietly during class.  
3. Her daughter brightened the gloomy day.

İlk iki cümlenin vektörleri birbirine yakın olur.  
Üçüncü cümle ise diğerlerinden uzak konumlanır.

---

# Benzerlik Nasıl Ölçülür?

Vektörler arasındaki mesafeyi ölçerek metinler arasındaki benzerliği hesaplayabiliriz.

Bunun birkaç yöntemi vardır:

---

## 1️⃣ Euclidean Distance (Öklid Mesafesi)

Geometride öğrendiğiniz düz çizgi mesafesidir.

- İki nokta arasındaki en kısa mesafeyi ölçer.
- Pisagor teoreminin çok boyutlu genellemesidir.

Ancak yüksek boyutlu uzayda çoğu nokta birbirinden oldukça uzaktır.

---

## 2️⃣ Cosine Similarity (Kosinüs Benzerliği)

En yaygın kullanılan ölçümdür.

- Vektörlerin yönünü karşılaştırır.
- Mutlak uzaklıktan ziyade yön benzerliğine bakar.

Örneğin:

- (10, 10) ve (100, 100)  
  → Fiziksel olarak uzak olabilirler  
  → Ama aynı yöndedirler  

Kosinüs benzerliği:

- 1 → Aynı yön
- -1 → Tam zıt yön

---

## 3️⃣ Dot Product (Skaler Çarpım)

Bir vektörün diğerine izdüşüm uzunluğunu ölçer.

- Benzer yön ve uzunluk → yüksek değer
- 90 derece açı → 0
- Zıt yön → negatif

---

## Pratik Bilgi

Matematik detaylarını uygulamak zorunda değilsiniz.  
Ancak şunu bilmek önemlidir:

- Dot product ve cosine similarity için **yüksek değer = yüksek benzerlik**
- Cosine similarity → -1 ile 1 arasında
- Dot product → -∞ ile +∞ arasında olabilir

---

# Semantic Search Nasıl Çalışır?

1. Tüm belgeler embedding modeliyle vektör uzayına projekte edilir.
2. Benzer anlamlı belgeler birbirine yakın konumlanır.
3. Prompt da embedding modelinden geçirilir.
4. Prompt vektörü ile her belge vektörü arasındaki mesafe hesaplanır.
5. En kısa mesafeye sahip belgeler en alakalı kabul edilir.
6. Belgeler mesafeye göre sıralanır ve en yakın olanlar döndürülür.

Sonuç:

> Prompt ile anlamca en benzer belgeler bulunmuş olur.

---

# Özet

Anlamsal arama şu varsayıma dayanır:

- Benzer kavramlar uzayda birbirine yakın konumlanır.
- Vektörler arasındaki mesafe, anlam benzerliğini temsil eder.

Embedding modeli düzgün çalıştığı sürece sistem oldukça etkilidir.

Embedding modellerinin nasıl eğitildiğini ve benzer kavramları nasıl doğru şekilde yaklaştırdığını daha iyi anlamak, anlamsal arama konusundaki kavrayışınızı derinleştirir.

Bir sonraki bölümde embedding modellerinin nasıl eğitildiğini daha detaylı inceleyeceğiz.