# Data Types

## 1. What is a Type?

An **object's type** determines how that object will be represented in memory and what operations can be performed on it.  
Type is an **essential** feature of an object. An object without a type cannot be discussed.

Based on type information, the compiler determines:
- How much space the data will occupy in memory,
- How the 1s and 0s in memory will be interpreted,
- Which operations can be performed on that data.

---

## 2. Grouping Types

Types in the C language are divided into two main groups:

| Type Group | Description |
|:-----------|:-----------|
| **1. Built-in Types** | Standard types that exist by design in the C language. (e.g., `int`, `float`, `char`) |
| **2. User-defined Types** | Allows the programmer to define new types. (e.g., `struct`, `union`, `enum`) |

> If the predefined types are not sufficient, the programmer can define their own type using structures such as `typedef`, `struct`, `enum`, and `union`.

---

## 3. Integer Types

In the C language, **integer types** represent negative or positive integers.  
There are a total of 8 integer types (including signed and unsigned versions).

### Signed and Unsigned

- **Signed:** Can hold negative and positive values.  
- **Unsigned:** Holds only positive values (and zero).

### Integer Types

| Type | Size (byte) | Value Range | Description |
|:----|:---------------|:------------------|:-----------|
| `signed char` | 1 | -128 → +127 | 1 byte, signed character type |
| `unsigned char` | 1 | 0 → 255 | 1 byte, unsigned character type |
| `char` | 1 | Compiler-dependent | May be signed or unsigned |
| `short int` / `signed short int` | 2 | -32,768 → +32,767 | Short integer |
| `unsigned short int` | 2 | 0 → 65,535 | Unsigned short integer |
| `int` / `signed int` | 2 or 4 | -32,768 → +32,767 (2B) or -2,147,483,648 → +2,147,483,647 (4B) | System-dependent |
| `unsigned int` | 2 or 4 | 0 → 65,535 (2B) or 0 → 4,294,967,295 (4B) | System dependent |
| `long int` / `signed long int` | 4 | -2,147,483,648 → +2,147,483,647 | Long integer |
| `unsigned long int` | 4 | 0 → 4,294,967,295 | Long unsigned integer |
| `long long int` (C99) | 8 | -9,223,372,036,854,775,808 → +9,223,372,036,854,775,807 | Very large integers |
| `unsigned long long int` (C99) | 8 | 0 → 18,446,744,073,709,551,615 | |

> The `char` type must be **1 byte according to the C standard**.

---

## 4. Floating-Point Types

There are 3 basic types for real numbers (floating-point numbers):

| Type | Size (byte) | Precision | Range (approx.) | Description |
|:----|:---------------|:----------|:------------------|:-----------|
| `float` | 4 | 6 digits | 1.17 × 10⁻³⁸ → 3.40 × 10³⁸ | Single precision |
| `double` | 8 | 15 digits | 2.22 × 10⁻³⁰⁸ → 1.17 × 10³⁰⁸ | Double precision |
| `long double` | 8 / 10 / 12 | System-dependent | Not portable | Extended precision |

### IEEE 754 Standard

In the C language, the `float` and `double` types are generally maintained according to the **IEEE 754** standard.

| Component | float (32 bits) | double (64 bits) |
|:----------|:----------------|:-----------------|
| Sign bit | 1 bit | 1 bit |
| Exponent | 8 bits | 11 bits |
| Fraction / Mantissa | 23 bits | 52 bits |

> This provides approximately 6 digits of precision for `float` and 15 digits for `double`.

---

## 5. New Types Introduced with C99

The C99 standard added complex numbers and the bool type.

| Type | Size (byte) | Description |
|:-----|:---------------|:-----------|
| `_Bool` | 1 | Boolean type (`true` or `false`) |
| `float _Complex` | 8 | Complex number (real and imaginary parts) |
| `double _Complex` | 16 | |
| `long double _Complex` | 24 | |
| `float _Imaginary` | 4 | Imaginary part only |
| `double _Imaginary` | 8 | |
| `long double _Imaginary` | 12 | |

---

## 6. ANSI C Portability Rules

According to ANSI C standards, only certain type lengths are **guaranteed**:

- The `char` type must **always be 1 byte**.  
- The `short` ≤ `int` ≤ `long` rule **always applies.**  
- Each type may have a different length depending on the system's processor architecture.

---

## 7. Processor Architecture Examples

### In 16-bit systems

| Type | Size |
|:-----|:------|
| `char` | 1 byte |
| `int` | 2 bytes |
| `short` | 2 bytes |
| `long` | 4 bytes |

### In 32-bit systems

| Type | Size |
|:-----|:------|
| `char` | 1 byte |
| `int` | 4 bytes |
| `short` | 2 bytes |
| `long` | 4 bytes |


## 8. Performance and Usage Recommendations

- **Integers** are **faster** to process than floating-point numbers.  
  This is because floating-point numbers are encoded in memory in a special format.  
- Unnecessary use of `float` or `double` can **slow down** the program.
- If integers are sufficient, **`int`** should be preferred.  
- If a larger range is required, **`long`** or **`long long`** can be used.  
- For real numbers, **`double`** should generally be the default choice.

---

## Additional codes
### 1. precision and speed test
This code demonstrates the difference in precision between float and double and measures how much faster integer arithmetic is compared to floating-point arithmetic in a simple loop.
```c
#include <stdio.h>
#include <time.h> // For performance measurement (clock_t)
#include <limits.h> // For loop limits

// Test parameters
#define ITERATIONS 100000000
#define CLOCK_UNIT CLOCKS_PER_SEC // Defined in <time.h>

void analyze_float_precision() {
    float f = 123456789.0f; 
    double d = 123456789.0;
    
    printf("--- 1. Precision Test ---\n");
    // float has around 6-7 digits of precision. The last digits are lost.
    printf("Float (low precision): %.2f\n", f); 
    // Double retains higher precision.
    printf("Double (high precision): %.2f\n", d); 
    printf("\n");
}

void analyze_performance_difference() {
    clock_t start, end;
    double time_used;
    long i;
    
    printf("--- 2. Performance Test (Iteration Count: %d) ---\n", ITERATIONS);

    // Integer Arithmetic Test (Fast)
    long int_sum = 0;
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        int_sum += (i & 0x0F); // Simple bitwise operation to ensure constant work
    }
    end = clock();
    time_used = ((double)(end - start)) / CLOCK_UNIT;
    printf("Integer Time (int_sum): %.4f seconds\n", time_used);


    // Floating-Point Arithmetic Test (Slower)
    double float_sum = 0.0;
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        float_sum += (i * 1.0) / 10.0; // Floating point division and addition
    }
    end = clock();
    time_used = ((double)(end - start)) / CLOCK_UNIT;
    printf("Float Time (float_sum): %.4f seconds\n", time_used);
    
    // Note: The integer operations are expected to be significantly faster due to the CPU architecture.
}

int main() {
    analyze_float_precision();
    analyze_performance_difference();
    return 0;
}
```

### 2. Defining a Portable Structure
This code shows that the types in C are not portable (like the size of int) and, therefore, how we construct structures with known sizes using typedef and sizeof. This is critically important, especially in Data Structures and network programming.
```c
#include <stdio.h>
#include <stdint.h> // For fixed-width integer types (e.g., int32_t, uint16_t)

// Define a type whose size is strictly guaranteed for portability
// This is crucial for Data Structures that rely on fixed sizes (like network packets or file storage).
typedef struct {
    // We use types from stdint.h to ensure fixed sizes regardless of the system architecture.
    uint16_t id;    // Guaranteed 2 bytes (short)
    int32_t count;  // Guaranteed 4 bytes (int/long)
    double price;   // Standard 8 bytes
} ProductData;


int main() {
    ProductData item;
    
    printf("--- Portable Type Analysis ---\n");
    
    // 1. Check fixed sizes guaranteed by stdint.h
    printf("Size of uint16_t (ID): %zu bytes\n", sizeof(uint16_t)); 
    printf("Size of int32_t (Count): %zu bytes\n", sizeof(int32_t));
    
    // 2. Check the size of the structure itself (may include padding/alignment)
    printf("Size of ProductData Structure: %zu bytes\n", sizeof(ProductData));
    
    // 3. Robustly calculate array size using sizeof (as taught in the previous section)
    int my_array[] = {10, 20, 30, 40, 50};
    size_t array_length = sizeof(my_array) / sizeof(my_array[0]);
    printf("Calculated Array Length (Robust): %zu\n", array_length);
    
    // Note: Using int32_t instead of plain int ensures the structure layout is consistent 
    // across 16-bit, 32-bit, and 64-bit systems, which is vital for DSA and I/O.

    return 0;
}
```

### 3. same bit in different data type
```c
#include <stdio.h>
/*
01000001 -> 65 -> 'A'
this bit pattern can represent different data types
*/

int main() {
    int i = 65;
    char c = 'A';

    printf("int olarak: %d\n", i);
    printf("char olarak: %c\n", c);
    printf("Bellekte aynı değeri farklı türle yorumlama: %c\n", (char)i);
    return 0;
}

```

### 4. for your computer sizeof
```c
#include <stdio.h>
#include <limits.h>

int main() {
    printf("char: %zu byte, [%d, %d]\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("short: %zu byte, [%d, %d]\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("int: %zu byte, [%d, %d]\n", sizeof(int), INT_MIN, INT_MAX);
    printf("long: %zu byte, [%ld, %ld]\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("long long: %zu byte, [%lld, %lld]\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
    return 0;
}

```

### 5. signed unsigned
```c
#include <stdio.h>

int main() {
    signed char a = -1;
    unsigned char b = -1;

    printf("signed char a = %d\n", a);
    printf("unsigned char b = %u\n", b);
    return 0;
}

```

### 6. float and double
```c
#include <stdio.h>

int main() {
    float f = 1.0 / 3.0;
    double d = 1.0 / 3.0;

    printf("float = %.10f\n", f);
    printf("double = %.20lf\n", d);
    return 0;
}

```

### 7. IEEE 754
```c
#include <stdio.h>

int main() {
    float f = -6.5f;
    unsigned int *p = (unsigned int*)&f;

    printf("float: %f\nbinary: ", f);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (*p >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
    return 0;
}

```

### 8. C99 bool complex
```c
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>

int main() {
    bool flag = true;
    double complex z = 2.0 + 3.0 * I;

    printf("bool örneği: %d\n", flag);
    printf("complex örneği: %.1f + %.1fi\n", creal(z), cimag(z));
    return 0;
}

```

### 9. data types and performance
```c
#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    int i;
    double t;

    start = clock();
    for (i = 0; i < 100000000; ++i) { int x = i * 2; }
    end = clock();
    t = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("int işlemleri: %.3f saniye\n", t);

    start = clock();
    for (i = 0; i < 100000000; ++i) { double x = i * 2.0; }
    end = clock();
    t = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("double işlemleri: %.3f saniye\n", t);
    return 0;
}

```
