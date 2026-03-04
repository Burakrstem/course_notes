## 🧠 Gelişmiş Semantik Arama Mimarileri

Bugüne kadar gördüğünüz semantik arama teknikleri **vanilla (temel) mimariyi** kullanır: Her belge ve sorgu tek bir vektöre dönüştürülür ve benzerliklerine göre arama yapılır. Bu, iyi sonuçlar verir ancak daha sofistike mimarilerle **daha yüksek kaliteli retrieval** mümkündür.  

İki popüler mimari: **Cross-Encoder** ve **ColBERT**.

---

# 1️⃣ Bi-Encoder (Temel Mimari)

- Her belge ve sorgu ayrı ayrı embed edilir.
- Ardından **Approximate Nearest Neighbors (ANN)** algoritmasıyla vektör yakınlığına göre belgeler bulunur.
- Avantaj:
  - Belgeler önceden embed edilebilir → hızlı arama.
- Dezavantaj:
  - Belge-sorgu etkileşimlerini derinlemesine yakalayamaz.

---

# 2️⃣ Cross-Encoder

- Belgeleri ve sorguyu **birleştirip tek bir modelden geçirir**.
- Model, prompt ve belgenin **derin bağlam etkileşimlerini** anlayabilir.
- Çıkış: 0-1 arası bir **relevancy score** (uygunluk skoru).  

**Örnek Akış:**
1. Prompt: “Great places to eat in New York”  
2. Her belge ile prompt birleştirilir.  
3. Model her belge için 0-1 skorunu üretir.  

- Avantaj:
  - Çok yüksek doğruluk, **arama kalitesi bi-encoder’dan üstündür**.
- Dezavantaj:
  - Ölçeklenemez.  
  - Milyonlarca belge varsa her prompt için tüm belgeler üzerinden çalıştırmak gerekir → aşırı maliyetli.

---

# 3️⃣ ColBERT (Contextualized Late Interaction over BERT)

- Amaç: Bi-encoder hızını **cross-encoder kalitesiyle** birleştirmek.
- İşleyiş:
  - Her belge için **her token ayrı vektör** olarak embed edilir.
  - Prompt geldiğinde aynı şekilde token bazında embed edilir.
  - Skorlama: Her prompt tokenı, belgede en benzer token ile eşleşir → en yüksek skorlar toplanır → **max sim score**.  

- Avantajlar:
  - Bi-encoder gibi önceden embed edilmiş belgelerle çalışır → hızlı.
  - Prompt-belge etkileşimlerini daha iyi yakalar → yüksek doğruluk.
- Dezavantajlar:
  - Çok sayıda vektör saklamanız gerekir (token başına bir vektör).  
    - Örnek: 2.000 token’lı belge → 2.000 vektör.  
  - Bi-encoder tek vektörle yetinir.  

---

# 4️⃣ Özet Karşılaştırma

| Mimarisi      | Hız           | Arama Kalitesi      | Vektör Saklama Maliyeti |
|---------------|---------------|-------------------|------------------------|
| Bi-Encoder    | Çok hızlı     | Orta              | Düşük                  |
| Cross-Encoder | Çok yavaş     | Çok yüksek        | Yüksek (sorgu başına) |
| ColBERT       | Orta-yüksek   | Yüksek (~cross)   | Çok yüksek             |

- Bi-encoder: **varsayılan ve pratik** çözüm.  
- Cross-encoder: **altın standart** kalite → varsayılan olarak kullanılamaz.  
- ColBERT: Bi-encoder hızı ile cross-encoder kalitesini dengeleyebilir → özellikle **hukuk ve tıp** gibi yüksek hassasiyet gereken alanlarda ideal.  

> Sonraki adım: Cross-encoder’ların üretim sistemlerinde nasıl entegre edildiğini inceleyeceğiz.