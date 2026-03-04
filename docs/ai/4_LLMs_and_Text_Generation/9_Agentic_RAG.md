## 🤖 RAG Sistemlerinde Agentik İş Akışları

RAG sisteminiz olgunlaştıkça, performansı artırmanın güçlü yollarından biri **agentik iş akışları** kullanmaktır. Agentik bir iş akışı, **her adımı için ayrı LLM’ler** kullanan bir sistem tasarımıdır.

---

### 1. Agentik Sistem Nedir?

- Geleneksel kullanım: Tek bir LLM → Prompt → Yanıt  
- Agentik kullanım:  
  1. Görevler bir dizi adım ve karar olarak ele alınır  
  2. Her adım için farklı bir LLM çağrılır  
  3. LLM’ler, ek araçlara erişebilir:  
     - Kod yorumlayıcı  
     - Web tarayıcı  
     - Vector database (RAG bağlamında)

---

### 2. Örnek Agentik RAG İş Akışı

1. Kullanıcı bir prompt gönderir  
2. **Router LLM**: Prompt’un retrieval gerektirip gerektirmediğine karar verir (Yes / No)  
3. Eğer retrieval gerekliyse:  
   - **Vector database** üzerinden dokümanlar alınır  
   - **Evaluator LLM**: Retrieve edilen dokümanların yeterli olup olmadığını değerlendirir  
   - Gerekirse ek retrieval yapılır  
4. **Draft LLM**: Augmented prompt ile yanıt oluşturur  
5. **Citation LLM**: Yanıta kaynak ekler

> Her adım için farklı LLM’ler kullanılabilir: küçük ve hızlı LLM’ler basit görevlerde, büyük LLM’ler içerik üretiminde, uzman LLM’ler citation için.

---

### 3. Agentik İş Akışı Türleri

| Tür | Açıklama | Örnek |
|-----|----------|-------|
| **Sequential (Sıralı)** | Yanıt, LLM’ler zinciri boyunca ilerler | Query parser → Query rewriter → Citation generator |
| **Conditional (Koşullu)** | LLM, prompt’un hangi yoldan gitmesi gerektiğine karar verir | Router LLM retrieval gerekliliğini belirler |
| **Iterative (Yinelenen)** | Prompt, sistem içinde bir önceki adıma geri yönlendirilir | Kod üretimi → Draft kontrol → Feedback döngüsü |
| **Parallel (Paralel)** | Orchestrator prompt’u alt görevlere böler, sonuçları synthesizer birleştirir | İki araştırma makalesinin özetlenmesi ve karşılaştırılması |

---

### 4. Dikkat Edilecek Noktalar

- LLM’ler artık **modüler parçalar** olarak görülür  
- Küçük veya sadece belirli görevlerde iyi olan modeller, workflow içinde avantaj sağlar  
- Agentik iş akışları, RAG sisteminizi daha esnek ve yetenekli hale getirir  

> Agentik yaklaşımla, her LLM kendi güçlü yönüne odaklanır ve sistem genelinde daha kaliteli, güvenilir ve ölçeklenebilir yanıtlar üretirsiniz.