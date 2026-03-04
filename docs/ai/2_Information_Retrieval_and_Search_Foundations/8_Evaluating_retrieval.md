## Retriever Değerlendirme: Gerçekten İyi Çalışıyor mu?

Retriever’ınız çalışıyor olabilir.  
Ama asıl soru şu:

> Gerçekten doğru dokümanları mı buluyor?

Latency, throughput veya resource usage önemli olsa da, en kritik metrik:

# 🎯 Arama Kalitesi (Search Quality)

---

# 📌 Değerlendirme İçin Gerekli 3 Şey

Bir retriever’ı ölçmek için genellikle şunlara ihtiyacınız vardır:

1. **Prompt**  
2. **Retriever’ın döndürdüğü sıralı doküman listesi**
3. **Ground truth listesi**  
   (Bilgi tabanındaki gerçekten ilgili dokümanların listesi)

Retriever’ı “notlandırmak” için doğru cevapları bilmeniz gerekir.

---

# 🔢 En Temel Metrikler: Precision ve Recall

## 🎯 Precision

> Döndürülen dokümanların ne kadarı gerçekten ilgili?

Formül:
Precision = (Retrieved Relevant Docs) / (Total Retrieved Docs)



Precision yüksekse:
- Sonuçlar güvenilirdir.
- Az sayıda alakasız doküman vardır.

---

## 🔍 Recall

> Gerçekten ilgili olan dokümanların ne kadarını yakaladık?

Formül:

Recall = (Retrieved Relevant Docs) / (Total Relevant Docs in KB)


Recall yüksekse:
- Sistem kapsamlıdır.
- Önemli dokümanları kaçırmaz.

---

# 📘 Örnek Senaryo

Bilgi tabanında:

- 10 ilgili doküman var (elle işaretlenmiş)

### İlk Deneme

Retriever:
- 12 doküman döndürüyor
- 8’i ilgili

Precision = 8 / 12 = %66  
Recall = 8 / 10 = %80  

---

### İkinci Deneme (ayar değiştirildi)

Retriever:
- 15 doküman döndürüyor
- 9’u ilgili

Precision = 9 / 15 = %60  
Recall = 9 / 10 = %90  

📌 Yorum:

- Biraz precision kaybettik
- Recall arttı

Bu genellikle bir **trade-off**’tur.

---

# 📊 Top-K Kavramı

Metrikler genellikle:

> Top-K dokümanlar üzerinden hesaplanır.

Örneğin:

- Precision@5
- Recall@10
- Precision@1

Bu, farklı katılık seviyelerinde ölçüm yapmanızı sağlar.

---

# 📈 Mean Average Precision (MAP@K)

MAP, sıralama kalitesini ölçer.

## Average Precision (AP@K) Nasıl Hesaplanır?

1. İlk K dokümana bakılır.
2. Her sırada Precision@K hesaplanır.
3. Sadece ilgili doküman olan satırlardaki precision değerleri toplanır.
4. Bu toplam, ilgili doküman sayısına bölünür.

MAP ise:

> Birden fazla prompt için hesaplanan AP değerlerinin ortalamasıdır.

### MAP neyi ödüllendirir?

- İlgili dokümanları üst sıralara koymayı.
- Üst sıralara giren alakasız dokümanlar MAP’i düşürür.

Yüksek MAP:

- İlgili sonuçlar yukarıda demektir.

---

# 🥇 Reciprocal Rank ve MRR

## Reciprocal Rank (RR)

> İlk ilgili doküman kaçıncı sırada?

Formül:
RR = 1 / (Rank of First Relevant Document)



Örnek:

- İlk ilgili doküman 2. sıradaysa → 1/2 = 0.5
- 4. sıradaysa → 1/4 = 0.25

Ne kadar yukarıdaysa, o kadar iyi.

---

## Mean Reciprocal Rank (MRR)

Birden fazla prompt için RR değerlerinin ortalamasıdır.

MRR şunu ölçer:

> Ortalama olarak ilk ilgili sonucu ne kadar hızlı buluyorum?

Özellikle şu durumlarda önemlidir:

- Kullanıcı sadece ilk birkaç sonuca bakıyorsa
- Chatbot veya RAG sisteminde ilk dönen doküman kritikse

---

# 📌 Hangi Metrik Ne İçin?

| Metrik | Ne Ölçer? |
|--------|-----------|
| Recall@K | İlgili dokümanları bulma yeteneği |
| Precision@K | Alakasız doküman oranı |
| MAP@K | Sıralama kalitesi |
| MRR | İlk ilgili sonucun konumu |

---

# ⚙️ Hybrid Sistemleri Optimize Etme

Bu metrikleri kullanarak şunları test edebilirsiniz:

- Semantic vs Keyword ağırlıkları (beta)
- RRF K parametresi
- Top-K değeri
- Metadata filtreleri

Örneğin:

> Semantic ağırlığını artırınca Recall artıyor mu?  
> Precision düşüyor mu?  
> MAP yükseliyor mu?

Bu metrikler sistem tuning için pusula görevi görür.

---

# ⚠️ En Büyük Zorluk: Ground Truth

Tüm bu metrikler şuna bağlıdır:

- Elle hazırlanmış ilgili doküman listeleri

Bu:

- Zaman alıcıdır
- Manuel çalışmadır

Ancak sağladığı fayda büyük:

- Geliştirme sürecinde ölçüm yapabilirsiniz
- Production’da performansı izleyebilirsiniz

---

# 🎯 Özet

İyi bir retriever:

- İlgili dokümanları bulmalı (Recall)
- Alakasız dokümanları minimize etmeli (Precision)
- İlgili dokümanları üst sıralara koymalı (MAP)
- İlk ilgili sonucu mümkün olduğunca erken göstermeli (MRR)

Artık tipik bir RAG sistemindeki retriever’ın tüm temel kavramlarını biliyorsunuz.

Bir sonraki adım:  
Bu modülün ana çıkarımlarını özetlemek.
