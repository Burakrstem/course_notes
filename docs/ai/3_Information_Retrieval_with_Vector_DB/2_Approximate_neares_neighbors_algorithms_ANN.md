## ⚡ Vektör Aramayı Ölçeklendirmek: KNN ve ANN

Keyword ve semantic search temel olmasına rağmen, **büyük veri ölçeğinde** bazı problemler ortaya çıkar.  

---

# 1️⃣ K-Nearest Neighbors (KNN)

- Her doküman ve prompt için embedding vektörü oluşturulur.  
- Prompt ile her doküman arasındaki **vektör mesafesi** hesaplanır.  
- Dokümanlar bu mesafelere göre sıralanır ve **k en yakın komşu** döndürülür.  

**Problem:**  
- Hesaplama sayısı **doğrusal olarak artar** (linear scaling).  
- 1 milyar dokümanda 1 milyar mesafe hesaplamak gerekir → **çok yavaş**.

---

# 2️⃣ Approximate Nearest Neighbors (ANN)

- KNN’in yerine kullanılan **yaklaşık çözüm algoritmaları**.  
- **Avantaj:** Çok daha hızlı, büyük veri setlerinde kullanılabilir.  
- **Dezavantaj:** Mutlak en yakın dokümanı garanti etmez, ama çok yakın olanları bulur.  

---

# 3️⃣ Navigable Small World (NSW) Algoritması

- **Proximity graph** oluşturur:  
  - Her doküman bir node  
  - Her node, en yakın birkaç komşusuna bağlanır → ağ benzeri yapı  
- Arama:  
  1. Rastgele bir node ile başlanır (candidate vector)  
  2. Komşular incelenir, prompt’a en yakın olan yeni candidate olur  
  3. Hiçbir komşu daha yakın değilse durulur ve candidate döndürülür  

**Hız:** Çok hızlı çünkü her adımda yalnızca birkaç komşu kontrol edilir.

---

# 4️⃣ Hierarchical Navigable Small World (HNSW)

- **Katmanlı proximity graph** kullanır:  
  - Üst katmanda az sayıda node → büyük adımlarla yaklaşık bölgeye geçiş  
  - Alt katmanda tüm dokümanlar → en iyi aday bulunur  
- **Avantaj:**  
  - Arama işlemi **logaritmik zamanlı**  
  - Milyarlarca vektör için hızlı vektör arama mümkün  
- **Katmanlar:**  
  1. Layer 3: 10 node  
  2. Layer 2: 100 node  
  3. Layer 1: 1000 node (tüm veritabanı)  

---

# 5️⃣ Özet ve Pratik Notlar

1. ANN algoritmaları **KNN’den çok daha hızlıdır**.  
2. En yakın sonuçları bulma garantisi yok, ama genellikle çok yakın dokümanlar bulunur.  
3. **Proximity graph** önceden oluşturulabilir, böylece arama sırasında zaman kazanılır.  

> HNSW ve benzeri algoritmalar sayesinde **vector search**, milyarlarca dokümanda bile üretim ölçeğinde mümkün hale gelir.
