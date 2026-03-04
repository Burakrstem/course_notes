## 🧩 Gelişmiş Chunking Teknikleri

Basit chunking yöntemleri (sabit boyutlu veya karakter tabanlı) bazı riskler taşır: bağlam kaybolabilir. Örneğin:

> “That night she dreamed, as she did often, that she was finally an Olympic champion.”

Yanlış yerde bir split, rüyanın **gelecek başarıyı** mi yoksa **zaten kazanılmış bir madalya**yı mı anlattığını değiştirebilir.  

---

# 1️⃣ Semantic Chunking

- Amaç: **anlam olarak benzer cümleleri aynı chunk’ta toplamak**  
- İşleyiş:  
  1. Belgede cümle cümle ilerler  
  2. Her cümle ve mevcut chunk **vektörleştirilir**  
  3. Vektörler belirli bir eşik değerinin altında ise: **aynı chunk’a eklenir**  
  4. Eşik aşıldığında: chunk kesilir, süreç yeni cümle ile tekrar başlar  

- Sonuç: **değişken boyutlu chunklar**, yazarın düşünce akışını takip eder  
- Kullanışlı:  
  - Kavramsal sapmalar  
  - Fikirlerin birden fazla paragrafta devam etmesi  

**⚠️ Not:** Hesaplama maliyeti yüksek, çünkü her cümle için vektör karşılaştırması gerekir.

---

# 2️⃣ LLM Tabanlı Chunking

- Yöntem: Belgeleri LLM’e verip **anlam bazlı chunk’lar** üretmesini istemek  
- Örnek:  
  - Benzer kavramları aynı chunk’a koy  
  - Yeni konu başladığında yeni chunk oluştur  
- Avantajlar:  
  - Siyah kutu yaklaşımı olsa da yüksek performanslı  
  - LLM maliyetleri düştükçe ekonomik olarak uygun  

---

# 3️⃣ Context-Aware Chunking

- Amaç: Chunk’lara **bağlam ekleyerek** arama doğruluğunu artırmak  
- Örnek:  
  - Blog yazısı sonunda destekçilerin isimleri: tek başına anlamsız olabilir  
  - LLM, chunk’a “Bu liste blog yazısının sonunda yer alıyor” gibi **ek açıklama** ekler  

- Avantajlar:  
  - Vektörleştirme sırasında arama doğruluğunu artırır  
  - Chunk retrieval sonrası LLM’e anlam sağlar  
- Dezavantaj: **yüksek ön işleme maliyeti** (tüm bilgi tabanı LLM ile işlenmeli)  

---

# 4️⃣ Özet ve Strateji

| Yöntem | Avantaj | Dezavantaj |
|--------|---------|------------|
| Sabit boyut / karakter tabanlı | Basit, hızlı, başlangıç için uygun | Bağlam kaybı |
| Semantic chunking | Yüksek doğruluk, bağlam korur | Hesaplama maliyeti yüksek |
| LLM tabanlı | Çok yüksek doğruluk, esnek | Maliyetli, siyah kutu |
| Context-aware | Chunk bağlamını artırır | Ön işleme maliyeti yüksek |

**Tasarım Tavsiyesi:**  
- Önce küçük veri subsetiyle test et  
- Sistem gereksinimlerine ve maliyetlere göre karar ver  
- Fixed-size chunking ile başlamak çoğu prototip için yeterli  
- Semantic ve LLM tabanlı yöntemler, yüksek performans ve bağlam için ikinci adım olarak uygundur  

**🎯 Hedef:** En ileri chunking tekniğini uygulamak değil, verinize uygun ve maliyet-fayda dengesine göre en doğru yöntemi seçmek.