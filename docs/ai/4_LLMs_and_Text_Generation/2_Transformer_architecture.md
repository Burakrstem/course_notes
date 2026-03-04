## 🔍 LLM’ler ve Transformer Mimarisi

Retriever, RAG sisteminizin kritik bir parçasıdır, ancak **LLM** (Large Language Model) sistemi gerçekten yöneten zekâdır.  
Retriever bilgiyi toplar; LLM ise bu bilgiyi kullanarak kaliteli yanıt üretir.  

---

### LLM İçinde Neler Oluyor?

1. **Tokenizasyon:**  
   - Prompt, küçük birimler olan **tokenlara** ayrılır.  
   - Her token’a bir **ilk tahmin vektörü** atanır.

2. **Pozisyon Bilgisi:**  
   - Her token’ın prompt içindeki **konumu** bir vektörle gösterilir.

3. **Attention Mekanizması:**  
   - Her token, diğer tokenlara **hangi oranla dikkat edeceğine** karar verir.  
   - Örnek: “The brown dog sat next to the red fox” cümlesinde `dog`, büyük ihtimalle `brown` ve `sat` tokenlarına daha fazla dikkat eder.  
   - Her LLM birden fazla **attention head** kullanır; her head farklı ilişki türlerine odaklanır.

4. **Feedforward Katmanı:**  
   - Token vektörleri, attention bilgisiyle birlikte güncellenir.  
   - Yeni vektörler, tokenların anlamını bağlam içinde daha doğru temsil eder.

5. **Katman Tekrarı:**  
   - Bu süreç 8–64 kez tekrarlanabilir.  
   - Token anlamı her tekrar ile daha da inceltilir.

6. **Üretim (Generation):**  
   - LLM, olası sonraki tokenları **olasılık dağılımı** olarak hesaplar.  
   - Seçilen token prompt’un sonuna eklenir.  
   - Her yeni token eklenmesiyle süreç tekrarlanır.

---

### RAG Sistemi Bağlamında Önemli Noktalar

- **LLM neden RAG ile iyi çalışır?**  
  - Attention mekanizması ve feedforward katmanları, retriever’dan gelen bilgiyi **derinlemesine anlamayı** sağlar.

- **LLM rastgeledir:**  
  - Aynı bilgiyi verdiğinizde, model bazen farklı yanıtlar üretebilir.  
  - Bu nedenle yanıtların retriever bilgilerinden **temellendiğini doğrulamak** gerekir.

- **Hesaplama maliyeti yüksektir:**  
  - Her token, diğer tüm tokenları inceler; uzun prompt ve completions maliyeti artırır.  
  - RAG sistemlerinin en büyük maliyeti, bu güçlü ama pahalı transformer modellerinden gelir.

---

Bir sonraki adımda, LLM davranışını RAG sisteminizde nasıl daha iyi kontrol edebileceğinizi göreceğiz.