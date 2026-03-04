## 📊 RAG Sistemi İçin Özel Veri Setleri (Custom Datasets)

Üretim RAG sisteminizde **geçmiş performansı anlamak ve sistem değişikliklerini test etmek** için custom dataset’ler oluşturabilirsiniz.  

---

### 🔹 Custom Dataset Nedir?

- Daha önce sisteminize gönderilmiş promptların bir koleksiyonudur  
- Her prompt için sistemin nasıl çalıştığına dair **ek bilgiler** de eklenebilir:  
  - Retriever tarafından döndürülen dokümanlar  
  - Re-ranker sonrası sıralama  
  - Query rewriter çıktıları  
  - Router LLM’lerin çıktıları (agentic workflow için)  
  - Kullanıcı ID’si, zaman damgaları vb.

---

### 🔹 Hangi Verileri Saklamalı?

1. **Temel veriler (end-to-end değerlendirme için)**  
   - Kullanıcı tarafından gönderilen prompt  
   - Üretilen nihai cevap  

2. **Bileşen düzeyi veriler (component-level evaluation)**  
   - Retriever giriş ve çıkışları  
   - Re-ranker girdileri ve çıktıları  
   - Query rewriter çıktıları  
   - Router veya evaluator LLM çıktıları  

Bu sayede sistemin her bileşenini ayrı ayrı analiz edebilir ve performansı farklı boyutlarda inceleyebilirsiniz.

---

### 🔹 Örnek Kullanım Senaryosu

- **Durum:** Customer service chatbot  
- **Gözlem:** İade (refund) soruları iyi yanıtlanıyor, ürün gecikmesi (product delays) soruları kötü performans gösteriyor  
- **Analiz:** Retriever ilgili dokümanları bulamıyor → Bilgi tabanını genişletmek gerekebilir  
- **Sonuç:** Sorun kaynağı tespit edilip hızlıca çözülüyor  

---

### 🔹 Gerçek Hayattan Örnek

- Sistem: RAG + text, image ve code üretimi (Mermaid.js ile diagram)  
- Problem: Router LLM, “draw a diagram” sorusunu yanlışlıkla text-to-image modeline gönderiyor  
- Çözüm: Router LLM prompt’u güncellendi, doğru model seçildi  
- Sonuç: Customer complaints hızlıca çözüldü  

---

### 🔹 Visualizasyon ve Analiz

- Çok sayıda veri topladığınızda **görselleştirme** ile yüksek seviyeli trendleri gözlemleyin  
- Örnekler:  
  - Prompts clustering → Ürün lansmanı, troubleshooting gibi konu başlıklarını belirleme  
  - Eval pipeline’ı sadece belirli prompt türlerine uygulama → Sistem performansını konu bazında değerlendirme  

---

💡 **İpucu:** Custom dataset’ler, RAG sisteminizi **gerçek kullanıcı taleplerine göre optimize etmek** ve her bileşeni ayrı ayrı geliştirmek için en etkili araçtır.