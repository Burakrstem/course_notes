# Constants
---

## 1. What is a Constant?

Data is either stored within **objects** or written directly as **constants**.  
Constants are fixed values written directly by the programmer.

Example:
```c
x = y + z;    // y and z are variables
d = x + 10;   // 10 is a constant
```

The value of constants is known at **compile time**.  
This means the compiler places this value directly into the code.

---

## 2. Types of Constants

Just as every object in C has a type, constants also have a type.  
The compiler determines the type of the constant based on its syntax.

### Types
- Integer constants  
- Character constants  
- Floating constants

---

## 3. Integer Constants

Integer constants can be one of the following types:
- `signed int`
- `unsigned int`
- `signed long`
- `unsigned long`

### Notation

| Number System | Notation | Example |
|:--------------|:--------------|:------|
| Decimal | `123` | `456`, `7890` |
| Octal | `0...` (starts with zero) | `0710`, `016` |
| Hexadecimal | `0x...` or `0X...` | `0x1C8`, `0XFF` |

> In hexadecimal, digits greater than 9 are represented by the letters **A–F** or **a–f**.

---

### Suffixes Used in Integer Constants

| Suffix | Meaning | Example |
|:------|:--------|:-------|
| `u` / `U` | Unsigned integer | `123U` |
| `l` / `L` | Long integer (`long`) | `456L` |
| `ul` / `UL` | Long unsigned integer (`unsigned long`) | `789UL` |

> To avoid visual confusion, it is recommended to use `L` instead of `l`.

---

### Type Determination Rules

| Notation | Type Order |
|:--------------|:---------------|
| `bb...b` | `signed int`, `signed long`, `unsigned long` |
| `0xbb...b` or `0bb...b` | `signed int`, `unsigned int`, `signed long`, `unsigned long` |
| `bb...bU` | `unsigned int`, `unsigned long` |
| `bb...bL` | `signed long`, `unsigned long` |
| `bb...bUL` | `unsigned long` |

> The compiler selects the first type that can fit the value without overflowing from top to bottom.

---

### Examples (for 2-byte int, 4-byte long systems)

| Notation | Type |
|:------|:----|
| `456` | `signed int` |
| `59654` | `signed long` |
| `0x1C8` | `signed int` |
| `987U` | `unsigned int` |
| `0XBCE1C53C` | `unsigned long` |
| `062000L` | `signed long` |
| `890765UL` | `unsigned long` |

---

## 4. Character Constants

They are written within single quotes `‘ ’`.

**Examples:**
```c
‘a’
'J'
‘8’
':'
‘Ç’
```

A character constant is actually an **integer** representing the ASCII code number of that character.

```c
char ch = ‘a’;  // ASCII 97
ch = ‘a’ + 3;   // 100 → 'd'
```

---

### Escape Sequence Characters

| Constant | Meaning |
|:-----------|:--------|
| `‘\\0’` | Null character |
| `‘\\a’` | Bell sound |
| `‘\\b’` | Backspace |
| `‘\\t’` | Tab |
| `‘\\n’` | Newline |
| `‘\\v’` | Vertical tab |
| `‘\\f’` | Form feed |
| `‘\\r’` | Carriage return |
| `‘\\’'` | Single quote |
| `‘\\\"’` | Double quote |
| `‘\\\\’` | Backslash |

---

### Hexadecimal and Octal Representations

**Hexadecimal:**
```c
‘\\x41’   // ‘A’
'\\xff'   // 255
```

**Octal:**
```c
‘\\012’   // ASCII 10 (newline)
‘\\07’    // ASCII 7 (bell)
```

The same character can be expressed in different formats:
```c
‘\\x7’   // hex
‘\\07’   // octal
‘\\a’    // escape — recommended format
```

> The recommended format is **predefined escape sequences** such as `‘\\a’` because they are readable and portable.

---

### Character Encoding Information

- The most common character set is **ASCII** (7-bit).  
- Some systems use **EBCDIC** or **Unicode** (UTF-16, UTF-32).  
- Unicode is designed to cover all languages.

---

## 5. Floating Constants

Floating constants can be of type `float`, `double`, or `long double`.

### float
```c
1.31F
10.F
-2.456f
```

### double
```c
-24.5
```

### long double
```c
1.34L
10.2L
```

---

### Scientific Notation

Real numbers can be written in exponential form using `e` or `E`.

```c
2.3e+04f   // 2.3 × 10^4
1.74e-6F   // 1.74 × 10^-6
8.e+9f     // 8 × 10^9
```

Equivalent examples:
```c
1.34E-2f == 0.0134
-1.2E+2F == 120.0
```

---

## 6. Character Constant Type

In C, character constants are actually of type `int`.  
They behave like `char` in operations, but are treated as `int` in type conversions.

---
## 7. Summary
| Type | Notation Example | Type Information |
|:-----|:---------------|:------------|
| Integer | `125800` | `signed long` |
| Integer (hex) | `0xBCE1C53C` | `unsigned long` |
| Character | `‘A’`, `‘\\n’`, `‘\\x41’` | `int` |
| Real number | `-24.5`, `1.34L`, `2.3e+04f` | `float`, `double`, `long double` |
---

## Code examples
### 1. basics
```c
#include <stdio.h>

int main() {
    printf("Onluk: %d\n", 42);
    printf("Sekizlik: %d\n", 052);   // 0 ile başlarsa sekizlik → 5*8 + 2 = 42
    printf("Onaltilik: %d\n", 0x2A); // 0x ile başlarsa onaltılık → 2*16 + 10 = 42
    return 0;
}

```
### 2. suffix
```c
#include <stdio.h>

int main() {
    printf("int: %zu byte\n", sizeof(10));
    printf("long: %zu byte\n", sizeof(10L));
    printf("unsigned long: %zu byte\n", sizeof(10UL));
    printf("long long: %zu byte\n", sizeof(10LL));
    return 0;
}

```

### 3.signed unsigned
```c
#include <stdio.h>

int main() {
    signed int a = -1;
    unsigned int b = -1;
    printf("signed a = %d\n", a);
    printf("unsigned b = %u\n", b);
    return 0;
}

```

### 4. character constants
```c
#include <stdio.h>

int main() {
    char ch1 = 'A';
    char ch2 = 65; // aynı şey
    printf("%c %d\n", ch1, ch1);
    printf("%c %d\n", ch2, ch2);
    return 0;
}

```

### 5. escape sequences
```c
#include <stdio.h>

int main() {
    printf("Satır1\nSatır2\n");     // \n yeni satır
    printf("Sekme\tArası\n");       // \t sekme
    printf("Ters Bölü: \\\n");      // \\ bir ters bölü
    printf("Tırnak: \"Merhaba\"\n");
    return 0;
}
```

### 6. character in numeric process
```c
#include <stdio.h>

int main() {
    char a = 'a';
    char b = a + 3;
    printf("'%c' + 3 = '%c'\n", a, b);
    printf("ASCII kodları: %d + 3 = %d\n", a, b);
    return 0;
}
```

### 7. octal and hex character constants
```c
#include <stdio.h>

int main() {
    char x = '\x41';  // 0x41 = 65
    char y = '\101';  // 0101 = 65
    printf("x=%c (%d), y=%c (%d)\n", x, x, y, y);
    return 0;
}
```
### 8. reel number constants
```c
#include <stdio.h>

int main() {
    float f = 1.23F;
    double d = 1.23;
    long double ld = 1.23L;
    printf("float: %.10f\n", f);
    printf("double: %.10lf\n", d);
    printf("long double: %.10Lf\n", ld);
    return 0;
}
```

### 9. scientific notation
```c
#include <stdio.h>

int main() {
    double a = 1.23e3;   // 1.23 × 10^3 = 1230
    double b = 1.23e-3;  // 1.23 × 10^-3 = 0.00123
    printf("a = %f\nb = %f\n", a, b);
    return 0;
}

```

### 10. type conversion
```c
#include <stdio.h>
#include <float.h>

int main() {
    printf("10 -> int: %zu byte\n", sizeof(10));
    printf("10L -> long: %zu byte\n", sizeof(10L));
    printf("10.0 -> double: %zu byte\n", sizeof(10.0));
    printf("10.0f -> float: %zu byte\n", sizeof(10.0f));

    double a = 1e39;  // float sınırını aşar
    float b = 1e39f;  // taşma (overflow)
    printf("a(double) = %e\n", a);
    printf("b(float)  = %e\n", b);
    return 0;
}
```


### 11. Constant Type Determination
```c
#include <stdio.h>
#include <limits.h> // For INT_MAX

int main() {
    // 1. Un-suffixed decimal constant (32-bit system)
    int a = 2000000000;  // Type: signed int
    
    // 2. Suffix 'L' forces the constant type to signed long
    long b = 3000000000L; // Type: signed long (needed as 3B > 2B int max)
    
    // 3. Suffix 'U' forces the constant type to unsigned int
    unsigned int c = 500U; // Type: unsigned int

    printf("Value of b (long): %ld\n", b);
    
    // Example of overflow (assuming 32-bit int)
    // The constant 3000000000 is too large for signed int, so its type defaults to signed long (if it fits).
    // If it didn't fit long, it would become unsigned long.
    
    return 0;
}
```

### 12. Character Arithmetic(integer promotion)
```c
#include <stdio.h>

int main() {
    // 'A' is an integer constant (ASCII 65)
    char start_char = 'A'; 
    int offset = 3; 

    // The character constant 'A' is promoted to an int (65) for the addition.
    // The result (68) is then assigned back to the char variable.
    char result = start_char + offset; // 65 + 3 = 68 ('D')

    printf("Character constant 'A' value: %d\n", 'A');
    printf("Result of 'A' + 3: %c\n", result);
    
    return 0;
}
```

## 13. Floating Constant Suffix Impact
```c
#include <stdio.h>

int main() {
    // 1. Unsuffixed constant: Type is double (8 bytes)
    printf("Size of 3.14 (Default): %zu bytes\n", sizeof(3.14)); 
    
    // 2. 'F' suffix: Type is float (4 bytes)
    printf("Size of 3.14F (Float): %zu bytes\n", sizeof(3.14F)); 
    
    // 3. 'L' suffix: Type is long double (8/10/12+ bytes)
    printf("Size of 3.14L (Long Double): %zu bytes\n", sizeof(3.14L)); 

    return 0;
}
```
