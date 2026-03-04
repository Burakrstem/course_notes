## 📊 RAG Sistemlerinde LLM Performans Ölçümü

RAG sisteminiz çalışırken LLM’inizin performansını anlamak, **sıcaklık ayarı değiştirmek, sistem prompt’unu güncellemek veya yeni bir model denemek** gibi kararları bilinçli alabilmek için kritik öneme sahiptir. Bunun için doğru metrikleri kullanmak gerekir.

---

### 1. LLM’nin Rolünü Tanımlayın

- **Retriever:** Bilgi tabanından ilgili içerikleri bulur  
- **LLM:** Bu içerikleri kullanarak yüksek kaliteli yanıt üretir  
- Eğer sorun retriever kaynaklıysa, LLM’i değiştirmek zaman kaybı olur  
- LLM’nin görevi:
  1. Kullanıcı sorusuna yanıt vermek  
  2. Retrieve edilen bilgileri yanıtına dahil etmek  
  3. Kaynak göstermesi gerekiyorsa bunu yapmak  
  4. Gereksiz bilgilerle dikkatinin dağılmaması

---

### 2. LLM-Spesifik Metrikler

Birçok LLM davranışı **subjektiftir**, bu yüzden **diğer LLM’ler veya insan değerlendirmeleri** ile kalite ölçülür.

#### a) RAGAS Kütüphanesi

RAGAS, LLM’in RAG sisteminde performansını ölçmek için kullanılabilecek open-source bir araçtır.

**Örnek Metrikler:**

1. **Response Relevancy (Yanıtın Alaka Düzeyi)**  
   - Yanıtın kullanıcı sorusuna uygun olup olmadığını ölçer (doğruluk değil)  
   - Süreç:
     1. Yanıt LLM’e verilir, olası kullanıcı soruları üretilir  
     2. Orijinal ve örnek sorular **vektörlere gömülür**  
     3. Kosinüs benzerliği hesaplanır  
     4. Ortalaması alınır → alaka düzeyi ölçüsü

2. **Faithfulness (Sadakat)**  
   - Yanıtın retrieve edilen bilgilerle ne kadar uyumlu olduğunu ölçer  
   - Süreç:
     1. Yanıt içindeki tüm iddialar belirlenir  
     2. Hangi iddiaların retrieve edilen bilgilerle desteklendiği kontrol edilir  
     3. Desteklenen iddiaların yüzdesi → sadakat puanı

3. **Diğer Ölçümler**  
   - Gereksiz bilgilerden etkilenme (sensitivity)  
   - Kaynak gösterme doğruluğu

> Bu metriklerin çoğu LLM çağrıları veya referans doğruları gerektirir. LLM’in rolü karmaşık olduğundan, basit otomatik metrikler yetersiz kalabilir.

---

### 3. Sistem Genelinde Değerlendirme

- Kullanıcı geri bildirimleri (👍 / 👎)  
- A/B testleri ile sistem prompt veya LLM ayar değişikliklerini test etmek  
- Sistem genel performansını ölçerken LLM’e özel değişikliklerin etkisini izlemek

---

### 4. Önerilen Yaklaşım

1. **LLM as a judge veya insan değerlendirmesi** ile subjektif kaliteyi ölçün  
2. **RAGAS veya benzeri metrikler** ile retrieve edilen bilgilerin kullanımını test edin  
3. **Kombinasyon** yaklaşımı: sistem genel performans + LLM özel metrikler → daha güvenilir değerlendirme

> Bu yöntemler, LLM’in RAG sisteminizde ne kadar etkili çalıştığını anlamanıza yardımcı olur ve bilinçli ayarlamalar yapmanızı sağlar.