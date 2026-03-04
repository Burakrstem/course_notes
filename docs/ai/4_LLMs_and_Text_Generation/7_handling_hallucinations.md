## 🛑 LLM Hallusinasyonları ve RAG Sistemlerinde Azaltma Yöntemleri

LLM’ler ile çalışırken **hallusinasyonlar** kaçınılmazdır ve iyi tasarlanmış bir RAG sistemi bile bazen yanlış bilgi üretebilir. Bu nedenle, **hallusinasyonları tespit etmek, azaltmak ve doğru kaynaklarla cevap vermeyi sağlamak** kritik öneme sahiptir.

---

### 1. Hallusinasyon Nedenleri

- LLM’ler **olası metin dizilerini** üretmek üzere tasarlanmıştır, doğru/yanlış ayrımı yapmazlar  
- Hallusinasyonlar genellikle **mantıklı görünür**, bu yüzden tespitleri zor olabilir  
- Zamanla kullanıcı güvenini sarsabilir

**Örnek:**
- Kullanıcı: “Öğrenci indirimi var mı?”  
- RAG retrieve: sadece yaşlılar ve yeni müşteriler için %10 indirim bilgisi  
- LLM yanıtı: “Evet, öğrenci indirimi %10 mevcut” → yanlış bilgi (hallusinasyon)

---

### 2. Hallusinasyon Tespit Yöntemleri

#### a) Self-Consistency (Kendi Kendine Tutarlılık)
- Aynı prompt için birden fazla yanıt üretmek  
- Yanıtlar arasındaki **faktüel tutarsızlıkları** kontrol etmek  
- Dezavantaj: maliyetli ve güvenilir değil

#### b) Bilgi Tabanına Dayanma (RAG)
- En güvenilir yaklaşım: LLM yanıtlarını **retrieve edilen belgelerle** desteklemek  
- Sistem prompt’unda:
  > “LLM yalnızca retrieve edilen bilgiler doğrultusunda gerçek iddialarda bulunabilir.”  
- İsteğe bağlı olarak **kaynak gösterme** eklemek:
  - Her cümlenin veya paragrafın sonunda kaynak ekletmek  
  - Kaynaklar kullanıcı tarafından doğrulanabilir

---

### 3. Kaynak Doğrulama Sistemleri

#### a) ContextCite
- Yanıtı cümle bazında işler ve her cümleyi **retrieve edilen belgelerle eşleştirir**  
- Cümle kaynağı yoksa `no source` etiketi ekler  
- Kullanım:
  - Son yanıt için kaynak gösterme  
  - RAG sisteminizin ne kadar doğru belgelere dayandığını ölçme

#### b) ALCE Benchmark
- LLM’lerin **kaynakları ne kadar doğru kullandığını** ölçer  
- Sağlanan metinler ve sorular ile RAG sisteminizin yanıtlarını test eder  
- Ölçülen metrikler:
  1. Akıcılık (fluency)  
  2. Doğruluk (correctness)  
  3. Kaynak kalitesi (citation quality)

---

### 4. En İyi Uygulamalar

1. **RAG kullanın:** Hallusinasyonları azaltmanın en etkili yöntemi  
2. **Sistem promptunu optimize edin:**  
   - Yanıtların retrieve edilen bilgilere dayandırılmasını sağlayın  
   - Kaynak göstermeyi zorunlu kılın  
3. **Hallusinasyon benchmark’ları ile test edin:**  
   - Yanıtların güvenilir ve kaynaklı olduğundan emin olun

> Bu adımlar, hallusinasyonları önemli ölçüde azaltır ve sisteminizin kullanıcıya güvenilir yanıtlar sunmasını sağlar