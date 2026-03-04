## Anahtar Kelime Araması (Keyword Search)

Arama tekniklerini incelemeye anahtar kelime aramasıyla başlayalım.

Bu teknik, onlarca yıldır veritabanları ve arama motorlarında retrieval işlemini desteklemektedir. Basitliği ve etkililiği sayesinde modern RAG sistemlerinde de temel bir bileşen olmaya devam etmektedir.

Şimdi nasıl çalıştığına ve retriever pipeline’ına hangi güçlü yönleri kazandırdığına bakalım.

---

## Temel Mantık

Anahtar kelime araması, belgeleri prompt ile **ortak kelimeler içerip içermediklerine** göre getirir.

Temel fikir şudur:

> Prompt’taki kelimelerin çoğunu içeren belgeler, büyük olasılıkla daha alakalıdır.

---

## Bag of Words Yaklaşımı

Hem prompt hem de her belge bir **kelime torbası (bag of words)** olarak ele alınır.

Bu yaklaşımda:

- Kelime sırası tamamen göz ardı edilir.
- Sadece hangi kelimelerin bulunduğu ve kaç kez geçtiği önemlidir.

Örneğin:

> "making pizza without a pizza oven"

Bu metin:
- `pizza` kelimesini 2 kez,
- `making`, `without`, `a`, `oven` kelimelerini 1’er kez içerir.

Bu kelime sayıları bir **vektör** içinde saklanır.

---

## Sparse (Seyrek) Vektörler

- Vektörde, sistem sözlüğündeki her kelime için bir konum bulunur.
- Bu sözlük on binlerce kelime içerebilir.
- Her konum, ilgili kelimenin metinde kaç kez geçtiğini gösterir.
- Çoğu konum 0 olduğu için bu vektörlere **sparse (seyrek) vektör** denir.

---

## Term-Document Matrix (Terim-Belge Matrisi)

Bilgi tabanındaki her belge için bir sparse vektör oluşturulur.

Bu vektörler bir araya getirilerek bir tablo oluşturulur:

- Her sütun bir belgeyi temsil eder.
- Her satır bir kelimeyi temsil eder.

Bu yapıya **term-document matrix** denir.

Aynı yapı bazen **inverted index (ters indeks)** olarak da adlandırılır çünkü:

- Normalde bir belgeden hangi kelimeleri içerdiğini düşünürüz.
- Burada ise bir kelimeden hangi belgelerde geçtiğini buluruz.

Bu ters indeks, arama yapılmadan önce bir kez oluşturulabilir.

---

## Skorlama ve Sıralama

Prompt geldiğinde:

1. Prompt için de bir sparse vektör oluşturulur.
2. Her belge prompt’a göre puanlanır.

### Basit Skorlama

En basit yöntem:

- Prompt’taki her kelime bir **anahtar kelime (keyword)** olarak kabul edilir.
- Bir belge, bir anahtar kelimeyi içeriyorsa 1 puan alır.

Örneğin:

Prompt 5 anahtar kelime içeriyorsa, maksimum puan 5 olur.

Toplam puanlara göre belgeler sıralanır ve en yüksek puanlı belgeler getirilir.

---

## Geliştirme 1: Kelime Sıklığını Dikkate Alma

Basit yöntem bir kelimenin belgede birden fazla kez geçmesini dikkate almaz.

Çözüm:

- Belge, bir anahtar kelimeyi kaç kez içeriyorsa o kadar puan alır.

Ancak bu yeni bir sorun yaratır:

> Uzun belgeler, sadece uzun oldukları için daha fazla kelime içerebilir.

---

## Geliştirme 2: Normalizasyon

Bu sorunu çözmek için:

Belge puanı, belgedeki toplam kelime sayısına bölünür.

Bu sayede:

- Anahtar kelimelerin belge içindeki oranı önem kazanır.
- Sadece uzun olduğu için avantajlı olan belgeler dengelenir.

---

## IDF (Inverse Document Frequency)

Bir başka sorun:

Tüm kelimeler eşit ağırlıkta puanlanır.

Ancak:

- "the", "a" gibi yaygın kelimeler
- "pizza", "oven" gibi nadir kelimeler

aynı derecede bilgilendirici değildir.

Bu sorunu çözmek için **Inverse Document Frequency (IDF)** kullanılır.

### IDF Nasıl Hesaplanır?

Her kelime için:

1. Kaç belgede geçtiği sayılır.
2. Toplam belge sayısına bölünür.

Örneğin:

- 100 belgeden 5’inde geçen "pizza" → 5/100 = 0.05
- 100 belgenin tamamında geçen "the" → 100/100 = 1

Sonra kesir ters çevrilir:

- Pizza → 20
- The → 1

Genellikle aşırı büyümeyi engellemek için log(IDF) kullanılır.

Sonuç:

> Nadir kelimeler daha yüksek ağırlık alır.

---

## TF-IDF Matrisi

IDF değerleri hesaplandıktan sonra:

- Ters indeksteki her satır,
- İlgili kelimenin IDF değeriyle çarpılır.

Ortaya çıkan matris:

> **TF-IDF (Term Frequency - Inverse Document Frequency) matrisi**

---

## TF-IDF ile Skorlama

Skorlama süreci aynıdır:

- Prompt’taki her anahtar kelime için
- O kelimenin satırındaki TF-IDF değerleri belgelerin puanına eklenir.

Sonuç:

- Anahtar kelimeleri sık kullanan belgeler yüksek puan alır.
- Özellikle nadir kelimeleri içeren belgeler daha yüksek puanlanır.

Örneğin:

- "pizza" veya "oven" içeren belgeler
- "a" veya "without" içeren belgelere göre daha yüksek skor alır.

---

## Modern Sistemler: BM25

TF-IDF, anahtar kelime aramasının temel yaklaşımıdır.

Ancak modern sistemler genellikle bunun geliştirilmiş bir versiyonu olan:

> **BM25**

algoritmasını kullanır.

Bir sonraki bölümde BM25’in nasıl çalıştığını inceleyeceğiz ve ardından anahtar kelime aramasının güçlü yönlerini ve RAG sisteminiz içindeki yerini değerlendireceğiz.