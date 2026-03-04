## 🔍 Üretim RAG Sistemlerinde Sorgu İşleme (Query Parsing)

Üretim RAG sistemlerinde, **kullanıcı tarafından girilen sorgular çoğunlukla doğrudan kullanılmaya hazır değildir**. İnsan yazımı sorgular genellikle konuşma dilinde, uzun veya belirsizdir. Sorgu işleme, bu sorguları retriever’a göndermeden önce optimize etmeye yardımcı olur.

---

# 1️⃣ Temel Sorgu Yeniden Yazma

- **Amaç:** Kullanıcı sorgularını temizleyip daha doğru sonuçlar alınmasını sağlamak  
- **Yöntem:** Bir LLM kullanarak sorguyu yeniden yazmak ve aşağıdaki yönergeleri uygulamak:  
  - Belirsiz ifadeleri netleştirmek  
  - Alanınıza özel terimler kullanmak (ör. tıbbi terimler)  
  - Eşanlamlılar ekleyerek eşleşme olasılığını artırmak  
  - Gereksiz bilgileri çıkarmak  

**Örnek:**

**Kullanıcı Sorgusu:**  
> “Köpeğimle yürüyüşe çıktım… Üç gün sonra omzum hâlâ uyuşuyor ve parmaklarım karıncalanıyor. Ne oluyor?”  

**Yeniden Yazılmış Sorgu:**  
> “Omuzda ani kuvvetli çekme sonucu oluşan kalıcı omuz ve parmak uyuşması. Potansiyel nedenler veya teşhisler nelerdir, örneğin nöropati veya sinir sıkışması?”  

- **Fayda:** Sorguyu basitleştirir ve odaklanmasını sağlar, retrieval doğruluğunu artırır.  
- **Maliyet:** Her sorgu için ek bir LLM çağrısı gerektirir.

---

# 2️⃣ Adlandırılmış Varlık Tanıma (NER)

- **Amaç:** Sorguda önemli bilgi kategorilerini tanımak (ör. kişi, tarih, yer, ürün).  
- **Yöntem:** Bir NER modeli (ör. **Gliner**) kullanarak varlıkları etiketlemek.  
- **Kullanım:**  
  - **Vector search**’i bilgilendirmek  
  - **Metadata filtreleme** yapmak  

**Örnek:** Metin verildiğinde model, kişi, tarih, yer vb. etiketleriyle sorguyu işaretler ve retrieval için kullanır.

- **Fayda:** Sorguyu daha yapılandırılmış hale getirerek retrieval doğruluğunu artırır.  
- **Dezavantaj:** Sorgu başına hafif gecikme ekler.

---

# 3️⃣ Hipotetik Belge Gömme (HIDE)

- **Amaç:** Retriever’ın, **ideal arama sonucunu** anlamasına yardımcı olmak.  
- **Yöntem:**  
  1. LLM, mükemmel cevabı temsil eden **hipotetik bir belge** üretir.  
  2. Bu belge vektöre dönüştürülür (embedding).  
  3. Arama, bu vektör kullanılarak yapılır.  

- **Örnek:**  
  - Kullanıcı sorgusu: Omuz ve el uyuşması → LLM detaylı tıbbi metin oluşturur → retriever, bu vektörü kullanarak arama yapar.

- **Fayda:** Sorgu ile bilgi tabanı belgeleri daha uyumlu hale gelir (“elma ile armut” karşılaştırmasını azaltır).  
- **Maliyet:** Ek LLM çağrısı, biraz daha yüksek gecikme.

---

# 4️⃣ Pratik Öneriler

| Teknik | Fayda | Maliyet / Dikkat Edilecek Nokta |
|--------|-------|--------------------------------|
| Temel sorgu yeniden yazma | En gerekli, retrieval’ı güçlendirir | Düşük-orta (her sorgu için LLM çağrısı) |
| Adlandırılmış Varlık Tanıma | Yapılandırılmış anlayış ekler | Hafif gecikme, kurulum karmaşıklığı |
| HIDE | Yüksek retrieval doğruluğu, sorguyu ideal belgeyle hizalar | Yüksek gecikme ve hesaplama maliyeti |

**Anahtar Noktalar:**

- Temel sorgu yeniden yazma genellikle yeterli ve **kesinlikle önerilir**.  
- NER veya HIDE gibi ileri teknikler ek fayda sağlayabilir ama **kademeli olarak test edilmelidir**.  
- Her zaman **retrieval kalitesi ve hesaplama maliyeti** arasındaki dengeyi ölçün.  
- Deneysel sonuçlara göre hangi gelişmiş tekniklerin uygulanacağına karar verin.