## ✍️ RAG Sisteminde Prompt Mühendisliği

LLM’inizden en iyi performansı almak için **yüksek kaliteli bir prompt** yazmanız gerekir.  
**Prompt engineering**, bu süreci optimize etmek için kullanılan bir dizi tekniktir.

---

### 1. Prompt Formatı

En yaygın format: **OpenAI Messages Format**  
- Promptlar **JSON mesaj dizisi** olarak yapılandırılır.  
- Her mesajda iki ana alan vardır:  
  - `content`: mesajın metni  
  - `role`: `system`, `user`, veya `assistant`

| Rol | Açıklama |
|-----|----------|
| **System** | LLM’in genel davranışını yönlendirir (yüksek seviyeli talimatlar). |
| **User** | Kullanıcının gönderdiği prompt. |
| **Assistant** | LLM’in önceki yanıtları. |

> Çok turlu (multi-turn) bir sohbette LLM, geçmişi hatırlamaz; her yeni kullanıcı mesajı ile tüm sohbet JSON formatında LLM’e gönderilir.

---

### 2. Sistem Promptu

- LLM’in **yüksek seviyeli talimatlarını** verir.  
- Örnek kullanım:  
  - Belirli bir tonda yanıt verme  
  - Adım adım akıl yürütme  
  - Sadece güvenli ve doğru bilgiler sağlama  
  - Markdown kullanımı  
  - Belirli bir kişilik veya tutum kazandırma  

- RAG uygulamalarında:  
  - Yanıtları yalnızca **retriever’dan alınan dokümanlara** dayandır  
  - **Kaynak gösterme**  
  - Dokümanların **ilgili olup olmadığını değerlendirme**

> Sistem promptu, her LLM çağrısında eklenir ve **stil ile kaliteyi büyük ölçüde etkiler**.

---

### 3. Prompt Şablonları (Templates)

- **Amaç:** Kompleks promptları düzenli ve test edilebilir hale getirmek.  
- Yapısı genellikle:  
  1. **Sistem promptu**: yüksek seviyeli talimatlar  
  2. **Önceki sohbet mesajları** (multi-turn için)  
  3. **Retriever’dan alınan top N doküman**  
  4. **En güncel kullanıcı promptu**

- Şablon kullanmanın avantajları:  
  - Farklı prompt yapılarını denemek kolaydır  
  - Bileşenleri değiştirdiğinizde LLM’in tepkisini gözlemleyebilirsiniz

---

### 4. Özet

1. **Sistem promptu** → LLM’in genel davranışını yönlendirir  
2. **Mesaj geçmişi** → Multi-turn diyalog desteği  
3. **Retrived context** → LLM’in yanıtını doğru ve güncel bilgiye dayandırır  
4. **Kullanıcı promptu** → LLM’in yanıtlaması gereken en son soru  

> Bir RAG sisteminde iyi bir prompt tasarımı, **LLM performansını ve yanıt kalitesini doğrudan artırır**.