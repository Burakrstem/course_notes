## 🔄 Reranking ile Semantik Aramada En İyisini Almak

Reranking, **ilk retrieval sonrası yapılan bir işlem**dir: Vector database’den dönen belgeler, daha güçlü ama maliyetli modellerle yeniden sıralanır ve böylece **en alakalı belgeler** elde edilir.

---

### 1️⃣ Reranking Nasıl Çalışır?

1. Vector database, prompt’a göre belgeleri veya chunk’ları getirir.  
2. Reranker bu belgeleri **yeniden skorlar ve sıralar**.  
3. Sonuç: Sadece en alakalı belgeler LLM’e iletilir.

> Örnek: Prompt: “What is the capital of Canada?”  
> Vector database’in getirdiği belgeler:  
> - “Toronto is in Canada”  
> - “The capital of France is Paris”  
> - “Canada is the maple syrup capital of the world”  
> → Reranker sayesinde sadece gerçekten uygun belge (Ottawa ile ilgili bilgi) öne çıkar.

---

### 2️⃣ İşlem Adımları

- İlk retrieval genellikle **over-fetch** yapılır: 20–100 belge veya chunk getirilir.  
- Reranker ile bu belgeler **yeniden skorlanır**.  
- Sonuçta sadece 5–10 belge döndürülür, fakat bunlar çok daha alakalı olur.

---

### 3️⃣ Kullanılan Mimariler

- Rerankers genellikle **cross-encoder** mimarisine sahiptir:
  - Cross-encoder, bi-encoder’dan daha iyi sonuç verir ama yavaş ve milyonlarca belge için kullanılamaz.
  - Bi-encoder, aday belgeleri daralttıktan sonra cross-encoder ile reranking yapmak **maliyet/fayda dengesini** sağlar.

- **LLM tabanlı reranking**:
  - Fikri cross-encoder ile benzer.
  - Prompt-belge çiftini doğrudan LLM’e verir, LLM bir **relevance score** üretir.
  - Maliyet olarak cross-encoder ile benzerdir ve yine **önce vector search ile adayları daraltmak gerekir**.

---

### 4️⃣ Avantajlar

- Basit bir ekleme ile çoğu vector database’de uygulanabilir.
- **15–25 belgeyi over-fetch edip rerank yapmak**, minimal gecikme ile ciddi bir **relevance artışı** sağlar.
- RAG sistemlerinde zorunlu değil ama genellikle **performansı büyük ölçüde artırır**.

---

> Özet: Reranking, semantik aramada **hız ve kaliteyi dengeleyen bir yöntemdir**. Önce bi-encoder veya hybrid search ile aday belgeler seçilir, sonra cross-encoder veya LLM ile rerank edilerek en alakalı sonuçlar LLM’e gönderilir.