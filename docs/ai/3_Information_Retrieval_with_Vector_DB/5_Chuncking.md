## 📄 Belge Parçalama (Chunking) ile Arama Kalitesini Artırmak

Vektör tabanlı bir retriever için **chunking**, uzun belgeleri küçük parçalara bölme işlemidir. Amaç üç katmanlıdır:

1. **Embedding model sınırları** – Modellerin tek seferde işleyebileceği metin miktarı sınırlıdır.  
2. **Arama doğruluğunu artırmak** – Daha küçük, anlam açısından odaklanmış parçalar daha iyi eşleşme sağlar.  
3. **LLM context penceresini verimli kullanmak** – Gereksiz uzun metinler gönderilmez.

---

# 1️⃣ Neden Chunking?

Örnek: 1.000 kitaplık bir bilgi tabanınız var.  
- Tek vektörle kitap vektörleştirilirse:  
  - Tüm kitabın anlamı **ortalama** vektörle temsil edilir  
  - Belirli konular veya bölümler kaybolur  
  - LLM’e tüm kitap gönderildiğinde context window hızla dolar  

**Çözüm:** Sayfa, paragraf veya cümle seviyesinde parçalamak  
- 1.000 kitap → 1 milyon paragraf  
- Vektör veritabanları milyonlarca vektörü kolayca saklayabilir ve arayabilir

---

# 2️⃣ Chunk Boyutu Seçimi

- **Çok büyük:** (örn. bölüm seviyesi)  
  - Yine anlamı iyi yakalamaz, LLM context dolabilir  
- **Çok küçük:** (örn. kelime seviyesi)  
  - Bağlam kaybolur → arama doğruluğu düşer  
- **Orta yol:**  
  - Genellikle paragraf veya belirli karakter sayısı ile sabit chunk boyutu seçilir

---

# 3️⃣ Sabit Boyutlu Chunking

- Örnek: 250 karakter/chunk  
  - Chunk 1: 1–250  
  - Chunk 2: 251–500  
  - Chunk 3: 501–750  

### 🔹 Overlap (Çakışma) ile Geliştirme
- Örneğin %10 overlap:  
  - Chunk 1: 1–250  
  - Chunk 2: 226–475  
  - Chunk 3: 451–700  
- Avantaj: Kelimeler bağlamlarını kaybetmez, arama doğruluğu artar  
- Dezavantaj: Veritabanında **fazladan vektör** oluşur  

---

# 4️⃣ Dinamik Chunking: Recursive Character Splitting

- Belirli karakterlere göre bölme (örn. `\n` → paragraf)  
- Avantajlar:  
  - Belge yapısına uygun  
  - İlgili kavramlar bir chunk içinde kalır  
- Farklı belge türleri için özelleştirilmiş stratejiler:  
  - HTML: paragraf veya başlık tag’ları  
  - Kod: fonksiyon tanımları  
  - Düz metin: newline karakterleri  

---

# 5️⃣ Metadata ile Chunking

- Chunklar, kaynağın metadata bilgisini miras almalı  
- Gerekiyorsa **konum bilgisi** gibi ek metadata eklenebilir

---

# 6️⃣ Pratik Öneriler

- Başlangıç için:  
  - 500 karakter/chunk  
  - 50–100 karakter overlap  
- Daha karmaşık stratejiler gerektiğinde **dış kütüphaneler** veya recursive splitting kullanılabilir  

**Fayda:**  
- Arama doğruluğu artar  
- LLM context penceresi verimli kullanılır  