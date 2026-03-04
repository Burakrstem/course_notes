## Hybrid Search: Arama Tekniklerini Birleştirmek

Retriever içinde kullanılan farklı arama ve filtreleme tekniklerini inceledik.  
Şimdi bu tekniklerin güçlü yönlerinden aynı anda yararlanmak için nasıl **birlikte** kullanıldıklarına bakalım.

Bu yaklaşımın adı: **Hybrid Search**.

---

# 🔎 1. Tekniklerin Kısa Özeti

## 🧩 Metadata Filtering

- Doküman metadata’sında saklanan katı kriterlere dayanır.
- Evet/Hayır (strict) filtreleme yapar.
- Hızlıdır.
- Uygulaması kolaydır.
- Yorumlanması nettir.

Ancak tek başına güçlü bir arama mekanizması değildir.

---

## 🔤 Keyword Search

- Prompt ile aynı anahtar kelimeleri içeren dokümanları bulur.
- Genellikle **BM25** gibi algoritmalar kullanılır.
- Hızlıdır.
- Teknik terimler, ürün isimleri ve özel kavramlarda çok başarılıdır.
- Exact match (tam eşleşme) sağlar.

Zayıf yönü:
- Anlam benzerliğini yakalayamaz.
- Farklı kelimelerle ifade edilmiş aynı fikri bulamaz.

---

## 🧠 Semantic Search

- Anlama dayalı eşleşme yapar.
- Prompt ve dokümanlar embedding modeli ile vektöre dönüştürülür.
- En yakın vektörler en benzer anlamı temsil eder.
- Cosine similarity gibi ölçümler kullanılır.

Avantajı:
- Anlamsal esneklik sağlar.
- Eş anlamlıları ve bağlamsal benzerliği yakalar.

Dezavantajı:
- Daha yavaştır.
- Daha fazla hesaplama gücü gerektirir.

---

# 🚀 Hybrid Search Pipeline Nasıl Çalışır?

Tipik akış şu şekildedir:

### 1️⃣ Prompt Alınır

Retriever bir kullanıcı prompt’u alır.

---

### 2️⃣ İki Ayrı Arama Yapılır

Aynı prompt ile:

- Bir keyword search yapılır.
- Bir semantic search yapılır.

Sonuç:

- Keyword ranking listesi (örneğin 50 doküman)
- Semantic ranking listesi (örneğin 50 doküman)

Bazı dokümanlar iki listede de olabilir, fakat sıralamaları farklı olabilir.

---

### 3️⃣ Metadata Filtering

Her iki liste de metadata filtresinden geçirilir.

Örneğin:

- Belirli departmana ait olmayan dokümanlar çıkarılabilir.
- Tarih aralığı dışında kalanlar silinebilir.

Örnek:

- Keyword listesi → 35 doküman
- Semantic listesi → 30 doküman

---

### 4️⃣ Reciprocal Rank Fusion (RRF)

Artık iki sıralı listeyi tek bir liste haline getirmemiz gerekir.

En yaygın yöntem:

## **Reciprocal Rank Fusion (RRF)**

RRF şu mantıkla çalışır:

Her doküman, her listedeki sırasına göre puan alır.

Formül (basitleştirilmiş haliyle):

Skor = 1 / (rank + K)


---

### 📌 K Parametresi

K bir hiperparametredir.

#### Eğer K = 0 ise:

- 1. sıradaki doküman → 1 puan
- 2. sıradaki doküman → 0.5 puan
- 10. sıradaki doküman → 0.1 puan

Bu durumda üst sıralar çok baskın olur.

#### Eğer K = 50 ise:

- 1. sıradaki → 1/50
- 10. sıradaki → 1/60

Fark çok daha dengeli olur.

K arttıkça:
- Üst sıranın avantajı azalır.
- Liste daha dengeli birleşir.

---

### 📌 RRF Ne Yapmaz?

RRF yalnızca **rank bilgisine** bakar.

- Gerçek skor değerleri dikkate alınmaz.
- 1. ile 2. arasındaki skor farkı önemli değildir.
- Sadece sıralama pozisyonu önemlidir.

---

# ⚖️ Beta Parametresi (Ağırlıklandırma)

Hybrid search içinde genellikle ikinci bir hiperparametre bulunur:

## **Beta (β)**

Bu parametre:

- Semantic search’e ne kadar ağırlık verileceğini belirler.

Örnek:

- β = 0.8 → %80 semantic, %20 keyword
- 70/30 → Genellikle iyi bir başlangıç noktasıdır.

---

## Ne Zaman Hangisi Daha Ağır Olmalı?

### 📌 Exact kelimeler çok önemliyse:

- Keyword search daha yüksek ağırlık almalı.

Örneğin:
- Ürün kodları
- Teknik terimler
- Yasal metinler

---

### 📌 Anlam daha önemliyse:

- Semantic search daha yüksek ağırlık almalı.

Örneğin:
- Soru-cevap sistemleri
- Destek chatbot’ları
- Serbest metin aramaları

---

# 🎯 Son Adım: Top-K Sonuç Döndürme

Hybrid ranking tamamlandıktan sonra:

- En üstteki K doküman döndürülür.
- Bu genellikle “top-K” olarak adlandırılır.

Retriever artık sonuç vermeye hazırdır.

---

# 🏆 Hybrid Search Neden Güçlü?

Çünkü:

- 🔤 Keyword search → Exact match sağlar
- 🧠 Semantic search → Anlam benzerliği sağlar
- 🧩 Metadata filtering → Katı filtreleme sağlar

Her yöntemin güçlü yönü korunur.

---

# 🔧 Tuning Alanları

Hybrid sistem oldukça esnektir. Şunları ayarlayabilirsiniz:

- BM25 parametreleri
- Metadata filtreleri
- K değeri (RRF)
- Beta ağırlıkları
- Top-K değeri

Performans, bilgi tabanınızın yapısına ve uygulamanızın ihtiyacına göre optimize edilir.

---

# Sonraki Adım: Retriever Değerlendirme

Hybrid sistem hazır olabilir, ancak önemli soru şudur:

> Retriever gerçekten iyi çalışıyor mu?

Bunu anlamak için performans ölçüm metriklerini bilmemiz gerekir.

Bir sonraki adım: Retriever’ların nasıl değerlendirildiğini öğrenmek.