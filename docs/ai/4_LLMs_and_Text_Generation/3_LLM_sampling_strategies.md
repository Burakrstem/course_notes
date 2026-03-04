## 🎲 LLM’lerde Rastgelelik ve Kontrolü

LLM’ler (Large Language Models), her token’ı üretirken **olasılığa dayalı rastgele seçim** yapar.  
Bu rastgeleliği anlamak ve kontrol etmek, LLM davranışını optimize etmenin temelidir.

---

### 1. Greedy Decoding (Aç Gözlü Kod Çözme)

- LLM, her zaman **en yüksek olasılıklı tokenı seçer**.  
- Avantaj: Deterministik, aynı prompt her zaman aynı yanıtı üretir.  
- Dezavantaj: Tahmin edilebilir, tekrar eden veya monoton metinler üretebilir.  
- Kullanım: Kod tamamlama veya sistem testi gibi durumlarda mantıklı.

---

### 2. Temperature (Sıcaklık) Parametresi

- Temperature, **olasılık dağılımının şekli**ni değiştirir.  
- 1.0 = normal dağılım  
- <1.0 = daha keskin dağılım, olasılıkları yoğunlaştırır → deterministik davranış  
- 0.0 = greedy decoding  
- >1.0 = dağılımı düzleştirir → daha fazla çeşitlilik ve yaratıcılık

> Not: Yüksek sıcaklık çok fazla rastgelelik getirebilir, anlamsız tokenlar seçilebilir.

---

### 3. Top-k Sampling

- LLM’yi, **en olası k token ile sınırlamak**.  
- Örnek: top-k = 5 → sadece ilk 5 token arasından seçim yapılır.  

### 4. Top-p (Nucleus) Sampling

- LLM, **kümülatif olasılığı p’yi aşmayan tokenlardan** seçim yapar.  
- Örnek: top-p = 0.85 → toplam olasılık %85’e ulaşana kadar tokenlar seçilebilir.  
- Daha dinamik: Dağılım keskinse seçim az, dağılım düzse daha geniş token havuzundan seçim yapılır.

---

### 5. Repetition Penalty (Tekrar Cezası)

- Daha önce kullanılan kelimelerin olasılıklarını düşürür.  
- Metni daha doğal ve çeşitli hale getirir.

### 6. Logit Biasing

- Belirli tokenların seçilme olasılığını **artırır veya azaltır**.  
- Örnek: Küfürleri engellemek veya belirli sınıfları öne çıkarmak.

---

### 7. Örnek Parametre Kombinasyonu

- Temperature: 0.8  
- Top-p: 0.9  
- Repetition penalty: 1.2  

Bu ayarlar, LLM’nin seçimini biraz daha **temkinli** yapar, aşırı uç tokenlardan kaçınır ve tekrar eden tokenleri hafifçe cezalandırır.

---

### 🔑 Özet

- LLM rastgele seçim yapar, ama **kontrol edilebilir**.  
- Düşük temperature + düşük top-p → kesin ve güvenilir yanıtlar (faktual veya kod).  
- Yüksek temperature + yüksek top-p → yaratıcı ve keşif odaklı metinler.  
- Repetition penalties ve logit biasing ile daha ince ayar yapılabilir.  

> LLM’in rastgele seçimlerini anlamak ve parametreleri projenize göre ayarlamak, performansı artırmanın anahtarıdır.