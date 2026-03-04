## 🔑 Retriever Modülünün Ana Çıkarımları

Bu modül boyunca **retriever’lar** ve onların kullandığı bilgi erişim prensiplerini öğrendik. İşte özet:

---

# 1️⃣ Retriever Arama Teknikleri

Retriever’lar genellikle **üçlü hibrit yaklaşım** kullanır:

1. **Keyword Search (Anahtar Kelime Arama)**  
   - Dokümanları, prompt’ta geçen anahtar kelimelerin sıklığına göre sıralar.  
   - Güçlü yönü: Dokümanlar prompt’taki **exact keywords**’i içerir.

2. **Semantic Search (Anlamsal Arama)**  
   - Dokümanları prompt ile **benzer anlamda** olmasına göre sıralar.  
   - Kullanılan teknoloji: **Embedding modelleri**  
     - Metni vektörlere dönüştürür.  
     - Benzer anlamlı metinler vektör uzayında birbirine yakın konumlanır.  
   - Güçlü yönü: Daha esnek ve anlam temelli eşleştirme sağlar.

3. **Metadata Filtering (Meta Veri Filtreleme)**  
   - Dokümanları, meta verilerindeki katı kriterlere göre eler.  
   - Amaç: Sonuçların kullanıcı için gerçekten **ilgili** olmasını sağlamak.

---

# 2️⃣ Hybrid Search (Hibrit Arama)

Hibrit sistem adımları:

1. **Prompt alınır**
2. **Keyword ve semantic search** yapılır
3. **Meta veri filtresi** uygulanır
4. **İki liste birleştirilir** ve tek bir sıralı liste oluşturulur
5. **Top-K dokümanlar** kullanıcıya döndürülür

**Avantaj:**  
- Her tekniğin güçlü yönlerinden faydalanır:  
  - Keyword → kesin eşleşme  
  - Semantic → anlam temelli eşleşme  
  - Metadata → gereksiz dokümanları eler

---

# 3️⃣ Retriever Performans Metrikleri

Hybrid sistemde performans ölçümü için:

- **Precision** → Dönen sonuçların doğruluğu  
- **Recall** → Kaç ilgili dokümanın bulunduğu  
- **MAP (Mean Average Precision)** → Sıralama kalitesi  
- **MRR (Mean Reciprocal Rank)** → İlk ilgili dokümanın konumu

💡 Bu metrikler:  
- Ayarladığınız **hyperparameter’ların etkisini** ölçmenize yardımcı olur  
- Sistemi **tuning ve optimize etmek** için yol gösterir

---

# ✅ Özet

- Retriever’lar bilgi tabanını etkili bir şekilde taramak için **keyword, semantic ve metadata** yöntemlerini birleştirir.  
- Hybrid search, her yöntemin avantajlarını kullanır ve top-K dokümanları döndürür.  
- Performansı ölçmek için precision, recall, MAP ve MRR gibi metrikler kullanılır.  
- Artık RAG sistemlerindeki retriever kavramlarının temellerini biliyorsunuz.

🎯 Sonraki modülde: Bu kavramların **üretim ölçeğinde retriever’larda** nasıl uygulandığını göreceğiz.