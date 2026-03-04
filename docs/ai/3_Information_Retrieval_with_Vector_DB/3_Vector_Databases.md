## 🗄️ Vektör Veritabanları ile Çalışmak: Weaviate Örneği

Üretim ölçeğinde bir **RAG sistemi**, genellikle vektörleri **vektör veritabanı**nda depolar ve oradan arar.  

---

# 1️⃣ Vektör Veritabanı Nedir?

- Yüksek boyutlu vektörleri depolamak ve **vektör tabanlı algoritmaları** (örn. ANN, HNSW) çalıştırmak için optimize edilmiş bir veritabanıdır.  
- Relational database’ler, semantic search için yetersiz kalır ve KNN gibi **yavaş algoritmalara** benzer performans gösterir.  
- Vektör veritabanları:  
  - Proximity graph oluşturma  
  - Vektör mesafelerini hızlı hesaplama  
  - Büyük veri setlerinde ölçeklenebilir arama  

**Örnek:** [Weaviate](https://weaviate.io) – Açık kaynaklı, yerel veya cloud ortamında çalışabilir.

---

# 2️⃣ Veri Hazırlığı ve Koleksiyon Oluşturma

1. Veritabanını başlat veya var olan bir instance’a bağlan.  
2. **Koleksiyon oluştur** (örn. `article`)  
   - Başlık ve içerik saklanır  
   - Hangi embedding modeli kullanılacağı belirtilir  
3. **Veri ekle**  
   - `batch.addObject` ile toplu veri ekleme  
   - Hatalar takip edilir, gerekirse düzeltilebilir  

---

# 3️⃣ Arama Tipleri

### 3.1 Vektör Arama
- Query text’i vektöre çevir → koleksiyondaki vektörlerle mesafeyi hesapla → en yakın K sonucu döndür.

### 3.2 Keyword Arama
- Weaviate otomatik **inverted index** oluşturur  
- BM25 veya benzeri algoritma ile top K döküman bulunur

### 3.3 Hybrid Search
- Vektör ve keyword arama **paralel** çalışır  
- `alpha` parametresi ile ağırlık verilir (örn. `alpha=0.25`)  
  - Vector search: %25  
  - Keyword search: %75  
- Sonuçlar **yeniden sıralanır** ve top K döndürülür

---

# 4️⃣ Filtreleme

- Hybrid search sonrası **metadata filtreleri** uygulanabilir  
- Belirli bir property kontrol edilir → eşleşiyorsa döndürülür, değilse atılır

---

# 5️⃣ İşlem Döngüsü

1. Veritabanını yapılandır  
2. Veriyi yükle ve indeksle  
3. Query yaz → hybrid search ve filtreleri uygula  
4. Top K dökümanı al

> Bu adımlar, tüm RAG projelerinde kullanılan temel **vektör veritabanı iş akışını** oluşturur.