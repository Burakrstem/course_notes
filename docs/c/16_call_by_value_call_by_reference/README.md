# 📘 C Dili — Call by Value ve Call by Reference

---

## 🔹 1. Fonksiyon Çağrı Mimarileri

| Yaklaşım | Açıklama |
|:----------|:-----------|
| **Call by Value** | Argümanın değeri kopyalanır. Fonksiyon bu kopya üzerinde işlem yapar. |
| **Call by Reference** | Argümanın adresi (referansı) fonksiyona gönderilir. Fonksiyon doğrudan değişkenin kendisine erişir. |

---

## 🔹 2. C’de Varsayılan Davranış: *Call by Value*

C dilinde **tüm fonksiyon çağrıları varsayılan olarak `call by value`**’dur.

```c
#include <stdio.h>

void foo(int x) {
    x = 9999;
}

int main(void) {
    int a = 5;
    foo(a);
    printf("a = %d\n", a);
    return 0;
}
```

📘 `foo(a)` çağrısında `x` değişkenine `a`’nın değeri kopyalanır.  
`x` üzerinde yapılan değişiklik `a`’yı etkilemez.

---

## 🔹 3. C’de Call by Reference

C’de doğrudan “referans tipi” yoktur, ancak **pointer** kullanarak aynı etki sağlanır.

```c
#include <stdio.h>

void foo(int *x) {
    *x = 9999;
}

int main(void) {
    int a = 5;
    foo(&a);
    printf("a = %d\n", a);
    return 0;
}
```

📘 `foo(&a)` çağrısında `a`’nın adresi gönderilir.  
Fonksiyon bu adresin gösterdiği değeri değiştirir → doğrudan `a` değişkeni.

---

## 🔹 4. Swap (Değer Takası) Örneği

### 🧩 Call by Value
```c
void swap(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}
```

### 🧩 Call by Reference (Pointer ile)
```c
void iswap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
```

```c
int main(void) {
    int a = 5, b = 43;
    printf("a = %d, b = %d\n", a, b);
    iswap(&a, &b);
    printf("a = %d, b = %d\n", a, b);
}
```

📘 `iswap()` parametre olarak iki adres alır.  
Bu adreslerin gösterdiği değerler yer değiştirir.

---

## 🔹 5. C++’ta Call by Reference

```cpp
void iswap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}
```

📘 `&` referans operatörü doğrudan değişkenin takma adı (alias)’nı oluşturur.  
Bu yapı yalnızca **C++** dilinde desteklenir.

---

## 🔹 6. Özet Karşılaştırma

| Özellik | Call by Value | Call by Reference |
|:----------|:----------------|:------------------|
| Argüman türü | Değer | Adres |
| Bellek etkisi | Kopya oluşur | Aynı adres paylaşılır |
| Değişken etkisi | Orijinal değişmez | Orijinal değişir |
| Performans | Küçük verilerde hızlı | Büyük yapılarda avantajlı |
| C’de doğrudan destek | ✅ | ❌ (pointer ile taklit edilir) |

---

## 🔹 7. Farkı Gösteren Basit Kod

```c
#include <stdio.h>

void byValue(int x) {
    x++;
    printf("byValue: %d\n", x);
}

void byReference(int *x) {
    (*x)++;
    printf("byReference: %d\n", *x);
}

int main(void) {
    int num = 10;
    byValue(num);
    printf("main: %d\n", num);

    byReference(&num);
    printf("main: %d\n", num);
    return 0;
}
```

---

## 🔹 8. C’de Fonksiyon Çağrı Modeli

C derleyicisi çağrı sırasında argümanları **stack**’e kopyalar.  
Pointer gönderildiğinde pointer’ın kopyası gider, ancak o kopya aynı adresi gösterdiği için “referans etkisi” oluşur.

> 💡 Teknik olarak C’de her zaman *call by value* vardır.  
> Pointerlar sayesinde *call by reference* etkisi elde edilir.

---

## 🔹 9. Bellek Görselleştirme

```c
int a = 10;
foo(&a);
```

| Adres | Değer | Açıklama |
|:------|:------|:----------|
| `0x7ffdf4a0` | `10` | `a` değişkeni |
| `0x7ffdf4a8` | `0x7ffdf4a0` | `foo` içindeki `int *x` |

Fonksiyon içinden `*x = 999;` → `a`’nın bellekteki değeri değişir.

---