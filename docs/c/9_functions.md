# Functions

## 1. What is a Function?

In the C language, subprograms are called **functions**.  
Unlike the concept of a function in mathematics, a function is an **independent sub-block of the program.**

A function is written to perform a specific task or produce a value.



## 2. Benefits of Dividing the Program into Functions
1. The code becomes shorter, **the .exe file becomes smaller.**  
2. The code becomes **more readable and easier to maintain**.  
3. **Repetitive operations** are grouped in one place.  
4. **Debugging** becomes easier.  
5. Functions become **reusable**.

Every C program consists of functions and contains at least one function (`main`).


## 3. Function Inputs and Outputs
- **Input:** Values sent to the function → *actual parameter*  
- **Output:** The value returned by the function → *return value*

The purpose of a function:  
1. To perform a task  
2. To calculate and return a value.


## 4. Return Values of Functions
A value is returned at the end of a function using the **return** statement.

### Purposes of use
- To return the calculated result
- To indicate whether an operation was successful
- To convey status information
- Or to return no value (`void`)


## 5. Function Definition

The body of the function is defined as follows:

```c
[return_type] function_name([parameters]) {
    /* code */
}
```

Example:
```c
double func() {
    return 3.14;
}
```
The `func` function takes no parameters and returns a value of type `double`.

---

### The `void` Keyword

```c
void hello() {
    printf(“Hello!”);
}
```
`void` → The function does not produce a return value.

---

### Functions Without a Specified Type

```c
func() { }
```
The C compiler interprets this as `int func()`.  
In C++, this is invalid — the type **must be specified.**

---

## 6. Where Functions Are Defined

A function cannot be defined inside another function.

```c
double foo() {
    int bar() { } // Invalid
}
```

Correct usage:
```c
double foo() { }
int bar() { }
```

---

## 7. `return` Statement

Ends the function's execution and returns a value.

```c
return;
return x * y;
return (a * b - c * d);
```

- If the end is reached without a `return` statement, it **returns a garbage value.**
- `void` functions can use `return;` on its own.
- A function can only return **one value**.

---

## 8. `main` Function

```c
int main() {
    return 0;
}
```

- It is the starting point of the program.  
- The return value of `main` is passed to the operating system.  
  - `0` → success  
  - Non-zero → error

> Although `void main()` is valid, it is **not recommended.**

---

## 9. Function Invocation

Function call operator: `()`

```c
func();
result = calculate();
```

- The code of the called function executes, then control returns to the caller.  
- The return value is an **R-value**.

```c
func() = 5; // Invalid
```

---

## 10. Undefined Functions

A function can be called even if it is declared but not defined.  
There will be no compilation error, but **an error will occur during the linking phase if no definition is found.**

---

## 11. Parameters

These are the **input variables** that functions take.

```c
int add(int a, int b) {
    return a + b;
}
```
When called:
```c
int z = add(x, y);
```
The values of `x` and `y` are **copied** to the parameters `a` and `b`, respectively.

---


## 12. Old Style

```c
double area(x, y)
double x, y;
{
    return x * y;
}
```
> Parameter types are declared later — **no longer used.**

---

## 13. New Style

```c
double area(double x, double y) {
    return x * y;
}
```
> Types are specified in parentheses — **modern C standard**.

---

## 14. Functions Without Parameters

```c
int foo() { }      // or
int foo(void) { }
```
Both indicate that no parameters are taken.

---

## 15. Copying Arguments

Functions take parameters **by value**.

```c
void func(int a) { a++; }

int main() {
    int x = 10;
    func(x);
    printf(“%d”, x); // 10
}
```
 **Demonstrates:** Function parameters are *copies*, the original value remains unchanged.

---

## 16. Function Call Forms

1. **Void function call:**  
   ```c
   func();
   ```
2. **Value-returning function:**  
   ```c
   a = foo();
   ```
3. **Call without using the value:**  
   ```c
   foo();
   ```
4. **Nested call:**  
   ```c
   z = square(add(x, y));
   ```
5. **Another call inside return:**  
   ```c
   return add(square(a), square(b));
   ```

---

## 17. Recursive Functions

A function can **call itself.**

```c
int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}
```

This feature is called **recursion**.

---

## 18. Summary

| Concept | Explanation |
|:--------|:----------|
| Function | Subprogram, independent code block |
| Definition | Writing the function's code |
| Call | Executing the function |
| Parameter | Data sent to the function |
| Return value | Result produced by the function |
| `void` | Function with no return value |
| `main` | Program's starting point |

---
## Additional examples
### 1. square
```c
#include <stdio.h>

int kare(int x) {
    return x * x;
}

int main() {
    printf("5’in karesi: %d\n", kare(5));
    return 0;
}

```
### 2.void
```c
#include <stdio.h>

void selamla() {
    printf("Merhaba!\n");
}

int main() {
    selamla();
    return 0;
}

```
### 3. decleration and call
```c
#include <stdio.h>

// Bildirim (prototip)
int topla(int, int);

int main() {
    int s = topla(3, 4);
    printf("Toplam = %d\n", s);
    return 0;
}

// Tanımlama
int topla(int a, int b) {
    return a + b;
}

```
### 4. return exit
```c
#include <stdio.h>

void bolme(int a, int b) {
    if (b == 0) {
        printf("Sıfıra bölme hatası!\n");
        return; // erken çıkış
    }
    printf("Sonuç: %d\n", a / b);
}

int main() {
    bolme(10, 2);
    bolme(5, 0);
    return 0;
}

```
### 5. use funcs as formal parameter
```c
#include <stdio.h>

int topla(int a, int b) { return a + b; }
int kare(int x) { return x * x; }

int main() {
    int sonuc = kare(topla(3, 2));
    printf("Sonuç: %d\n", sonuc); // (3+2)^2 = 25
    return 0;
}

```
### 6. copy parameters
```c
#include <stdio.h>

void arttir(int a) {
    a++;
    printf("İşlev içinde: %d\n", a);
}

int main() {
    int x = 10;
    arttir(x);
    printf("Ana programda: %d\n", x);
    return 0;
}

```
### 7. function chains
```c
#include <stdio.h>

int kare(int x) { return x * x; }
int topla(int a, int b) { return a + b; }

int main() {
    printf("%d\n", kare(topla(3, 4))); // (3+4)^2 = 49
    return 0;
}

```
### 8. recursive
```c
#include <stdio.h>

int faktoriyel(int n) {
    if (n == 0) return 1;
    return n * faktoriyel(n - 1);
}

int main() {
    printf("5! = %d\n", faktoriyel(5));
    return 0;
}

```
### 9. function pointer
```c
#include <stdio.h>
/*
you can use function pointers to select functions at runtime.
this is show the functions can be used like data types
*/

int topla(int a, int b) { 
    return a + b; 
}
int carp(int a, int b) { 
    return a * b; 
}

int (*secim(int islem))(int, int) {
    if (islem == 1) return topla;
    else return carp;
}

int main() {
    int (*f)(int, int);
    f = secim(1);
    printf("Sonuç: %d\n", f(3, 4)); // 7
    return 0;
}

```

------
## Functions 2

## 1. Function Return Values and Call Chains

The return value of a function can be an argument to another function.  
Additionally, a function can be used in another function's `return` statement.

**Example:**  
```c
int add(int a, int b) {
    return a + b;
}

int square(int x) {
    return x * x;
}

int sum_square(int a, int b) {
    return add(square(a), square(b));
}
```

**Explanation:**  
- `sum_square` returns the sum of the squares of two numbers.  
- The return values of the `add` and `square` functions are used **by nesting calls**.  
- This is possible because every function call in C produces an **R-value**.

---

## 2. Standard C Functions (Standard Library Functions)

Standard C functions are predefined functions that every C compiler **must support**.  
The code for these functions comes with the compiler.

### Why Use Standard Functions?
- Increases code portability  
- Creates a common language  
- Reduces code repetition  
- Ensures reliability (previously tested)

### Example Standard Functions
`printf()`, `scanf()`, `getchar()`, `putchar()`, `abs()`, `sqrt()`, `pow()`, `strlen()`, `malloc()`, `free()`, `exit()`

---

## 3. Libraries and Header Files

| Component | Description |
|:---------|:----------|
| **Header file (.h)** | Contains function **declarations**. |
| **Library (.lib / .a)** | Contains function **definitions (compiled code)**. |
| **Linker** | Includes compiled functions into the program. |

**Example Usage:**
```c
#include <stdio.h>  // printf, scanf
#include <math.h>   // sqrt, pow
```

---

## 4. `printf()` Function (Output)

`printf()` → Standard output function that writes data to the screen.

**Example:**
```c
#include <stdio.h>

int main() {
    int x = 25;
    double pi = 3.1415;

    printf(“x = %d\npi = %lf\n”, x, pi);
    return 0;
}
```

**Formatting Characters:**  
| Format | Type | Description |
|:-------|:-----|:----------|
| `%d` | int | Decimal system |
| `%ld` | long | Decimal system |
| `%u` | unsigned int | Decimal |
| `%x`, `%X` | unsigned int | Hexadecimal |
| `%o` | unsigned int | Octal |
| `%f` | float/double | Real number (decimal) |
| `%e` | float/double | Exponential notation |
| `%c` | char | Character |
| `%s` | string | Text |

**Escape Sequences:**
| Sequence | Meaning |
|:------|:--------|
| `\n` | New line |
| `\t` | Tab |
| `\r` | Carriage return |
| `\a` | Bell sound |
| `\"` | Double quote |
| `\\` | Backslash |

---

## 5. The `scanf()` Function (Input)

`scanf()` → Used to get data from the keyboard.  
The formatting characters are the same as `printf`, but it **reads** the data.

**Example:**
```c
#include <stdio.h>

int main() {
    int x, y;
    printf(“Enter two numbers: ”);
    scanf(“%d%d”, &x, &y);
    printf(“%d + %d = %d\n”, x, y, x + y);
    return 0;
}
```

**Notes:**
- The `&` operator → gives the address of the variable.  
- Spaces, tabs, or Enter keys don't matter; `scanf` treats them as separators.  

---


---

## 6. Functions for Reading Characters from the Keyboard

### `getchar()`
- It is a standard C function.  
- It reads **one character** from the keyboard.  
- The return value is the ASCII code of the character.

```c
#include <stdio.h>

int main() {
    char ch;
    printf(“Enter a character: ”);
    ch = getchar();
    printf(“Character: %c\nASCII: %d\n”, ch, ch);
    return 0;
}
```

---

### `getch()` *(non-standard)*
- Available in most compilers (especially Windows `conio.h`).  
- **No need to press Enter**, the character is not printed on the screen.

```c
#include <conio.h>
#include <stdio.h>

int main() {
    printf(“Press a key...\n”);
    getch();
    printf("Okay, let's continue \n"0);
    return 0;
}
```

---

### `getche()` *(non-standard)*
- Similar to `getch()`, but the character you press **appears on the screen.**

```c
#include <conio.h>
#include <stdio.h>

int main() {
    printf(“Press any key (character will appear): ”);
    getche();
    return 0;
}
```

---

### Comparison Table

| Function | Standard? | Does it require Enter? | Does the character appear? |
|:-------|:--------------|:------------------|:----------------------|
| `getchar()` | ✅ | ✅ | ✅ |
| `getch()` | ❌ | ❌ | ❌ |
| `getche()` | ❌ | ❌ | ✅ |

---

## 7. `%%` Escape Sequence

To print the `%` character itself in `printf`:
```c
printf(“%%25\n”);  // Output: %25
```

---

## 8. Benefits of Using Standard Functions

1. **Portability:** The code works on every system.  
2. **Readability:** The code is simple and understandable.  
3. **Testing:** Standard functions are reliable.  
4. **Time Savings:** Using ready-made functions speeds up the developer.  
5. **Sustainability:** The same function behaves the same way across different compilers.

---

## 9. Conversion Specifiers, Variadic Functions, and String Literals

### `printf()` is a Variadic Function

`printf()` takes a variable number of arguments:

```c
int printf(const char *format, ...);
```

- First parameter: format string (`const char*`)  
- `...` : variable number of arguments  

> Functions such as `printf`, `scanf`, `fprintf`, and `sprintf` are **variadic**.  

---

### String Literals and `‘\0’` (Null Byte Termination)

In C, a character string ends with a **`‘\0’` null byte**:

```c
char str[] = “Hello”;
```
How it is stored in memory:
```
H e l l o \0
```

In the call `printf(“%s”, str);`, `printf` prints the characters one by one  
and terminates the process when it encounters the `‘\0’` character.

---

### Conversion Specifiers

The `%` character in the format string specifies a conversion:

```
%[flags][width][.precision][length]specifier
```

| Specifier | Type | Description |
|:-----------|:-----|:----------|
| `%d`, `%i` | int | Decimal number |
| `%u` | unsigned int | Decimal |
| `%x`, `%X` | unsigned int | Hexadecimal |
| `%f` | double | Decimal |
| `%e`, `%E` | double | Exponential notation |
| `%c` | char | Character |
| `%s` | char* | String (C string) |
| `%p` | void* | Memory address |
| `%%` | — | The `%` character itself |

---

### Flags, Width, and Precision

| Element | Description | Example | Output |
|:--------|:----------|:-------|:-------|
| `-` | left alignment | `%-5d`, 42 | `42   ` |
| `0` | zero-fill | `%05d`, 42 | `00042` |
| `+` | show sign | `%+d`, 42 | `+42` |
| `.precision` | decimal places | `%.2f`, 3.1415 | `3.14` |
| `width` | minimum space | `%8s`, “C” | `“       C”` |

---

### Example: Complete Formatting
```c
#include <stdio.h>
int main() {
    printf(“%-10s %04d %.3f\n”, “C”, 7, 3.14159);
    return 0;
}
```
**Output:**
```
C          0007 3.142
```

---

### `printf` Return Value

`printf()` returns the **number of characters** it prints to the screen:

```c
int n = printf(“Hello!”);
printf(“\nTotal %d characters printed.\n”, n);
```
**Output:**
```
Hello!
Total 6 characters printed.
```

---

### `puts()` and `putchar()`

| Function | Description |
|:-----------|:----------|
| `putchar(c)` | Writes a single character |
| `puts(str)` | Writes a string and appends `\n` to the end |

**Example:**
```c
#include <stdio.h>
int main() {
    putchar(‘A’);
    puts(“ Hello”);
    return 0;
}
```
**Output:**
```
A Hello
```

---

### Memory Safety

`printf(“%d”, 3.14);` → ❌ **Undefined behavior (UB)**  
Because `%d` expects an integer, while `3.14` is a double type.  

Compilers usually warn about such errors with the `-Wall` option.

---

## 10. Summary Table

| Concept | Description |
|:--------|:----------|
| Variadic function | `printf` takes a variable number of arguments |
| String literal | A constant string enclosed in double quotes, ending with `‘\0’` |
| Conversion specifier | `%d`, `%f`, `%s`, `%p`, etc. |
| `printf` return value | Number of characters written |
| Memory safety | Format and argument types must match |

---
## Additional examples
### 1. return 
```c
#include <stdio.h>

// Temel örnek: return değeri döndüren/döndürmeyen fonksiyonlar

int square(int x) {
    return x * x; // değer döndürür
}

void greet(void) {
    printf("Merhaba!\n"); // hiçbir şey döndürmez
}

int main(void) {
    greet();
    printf("5'in karesi: %d\n", square(5));
    return 0;
}

```
### 2. definition call
```c
#include <stdio.h>

// Bildirim (prototip)
int topla(int, int);

int main(void) {
    int sonuc = topla(3, 4);
    printf("Toplam = %d\n", sonuc);
    return 0;
}

// Tanımlama
int topla(int a, int b) {
    return a + b;
}

```
### 3. parameters
```c
#include <stdio.h>

// Parametre aktarımı (by value): kopya üzerinden çalışır

void arttir(int a) {
    a++;
    printf("İşlev içinde: %d\n", a);
}

int main(void) {
    int x = 10;
    arttir(x);
    printf("Ana programda: %d\n", x); // x değişmez
    return 0;
}

```
### 4. nested calls
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int square(int x)     { return x * x; }

int main(void) {
    int sonuc = add(square(3), square(4));
    printf("(3^2 + 4^2) = %d\n", sonuc);
    return 0;
}

```
### 5. recursion
```c
#include <stdio.h>

// Klasik: faktöriyel (özyineleme)

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main(void) {
    printf("5! = %d\n", factorial(5));
    return 0;
}

```
### 6. stdio_basics
```c
#include <stdio.h>

int main(void) {
    int x;
    printf("Bir sayı girin: ");
    if (scanf("%d", &x) == 1) {
        printf("Girdiğiniz sayı: %d\n", x);
    } else {
        printf("Geçersiz giriş!\n");
    }
    return 0;
}

```
### 7. conversion specifiers
```c
#include <stdio.h>

int main(void) {
    int i = 255;
    double d = 3.14159;
    char c = 'A';
    const char *s = "Merhaba";

    printf("int: %d, hex: %x, octal: %o\n", i, i, i);
    printf("float: %.2f, scientific: %.3e\n", d, d);
    printf("char: %c, string: %s\n", c, s);
    printf("adres: %p\n", (void*)s);
    return 0;
}

```
### 8. variadic
```c
#include <stdio.h>
#include <stdarg.h>

// Çok basit bir mini printf: sadece %d destekli
void mini_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) == 'd') {
            int val = va_arg(args, int);
            printf("%d", val);
            fmt += 2;
        } else {
            putchar(*fmt++);
        }
    }
    va_end(args);
}

int main(void) {
    mini_print("Sonuc: %d + %d = %d\n", 2, 3, 5);
    return 0;
}

```
### 9. strings
```c
#include <stdio.h>

int main(void) {
    char str[] = "C dili"; // '\0' ile sonlanır
    printf("Yazı: %s\n", str);

    int i = 0;
    while (str[i] != '\0') {
        printf("%c ", str[i]);
        i++;
    }
    printf("\nUzunluk: %d\n", i);
    return 0;
}

```
### 10. escape sequences
```c
#include <stdio.h>

int main(void) {
    printf("Yeni satir\\nve tab\\törneği\n");
    printf("Ters bölü: \\\\ ve tırnak: \\\" \n");
    printf("Sekizlik: \\101 (A), Onaltılık: \\x41 (A)\n");
    return 0;
}

```
### 11. stdlib_demo
```c
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    double x = 9.0;
    printf("sqrt(%.2f) = %.2f\n", x, sqrt(x));

    char buf[64] = "C";
    const char *s2 = " Programlama";
    strcat(buf, s2); // dikkat: hedef buffer yeterince büyük olmalı
    printf("Birleştirme: %s\n", buf);

    char ch = 'a';
    printf("%c -> %c\n", ch, toupper((unsigned char)ch));
    return 0;
}

```
### 12. printf
```c
#include <stdio.h>

int main(void) {
    printf("%10s\n", "C");      // sağa yasla
    printf("%-10s\n", "C");     // sola yasla
    printf("%04d\n", 7);        // sıfırla doldur
    printf("%+d\n", 42);        // işaret göster
    printf("%.3f\n", 3.14159);  // ondalık basamak
    printf("%#x\n", 255);       // alternatif biçim -> 0xff
    return 0;
}

```
### 13. char_io
```c
#include <stdio.h>

int main(void) {
    int ch; // getchar() int döndürür (EOF-end of file- ayırtı için)
    printf("Bir karakter girin: ");
    ch = getchar();
    if (ch != EOF) {
        printf("Girdiğiniz karakter: ");
        putchar(ch);
        putchar('\n');
    }
    puts("----Program bitti.----");
    return 0;
}

```
### 14. undefined behaviour
```c
#include <stdio.h>

int main(void) {
    // UYARI: Aşağıdaki satır tanımsız davranıştır (UB).
    // %d tamsayı beklerken double gönderilirse sonuç belirsizdir.
    printf("%d\n", 3.14);

    // Doğrusu:
    printf("%f\n", 3.14);

    return 0;
}

```

---

## Functions 3
## 1. Purpose of Character Input/Output Functions

In the C language, **character-based** input/output operations are used to **read a single character from the keyboard** or **write a single character to the screen**.  
These functions are simpler and faster than formatted input/output (`printf`, `scanf`) operations.

---

## 2. The `putchar()` Function

```c
int putchar(int ch);
```

- A standard C function.  
- Writes the character in its parameter to **the location of the cursor on the screen.**  
- Return value: the **ASCII code value of the written character.**  
- Its definition is in the `stdio.h` header file.

### Example

```c
#include <stdio.h>

int main(void) {
    char ch;
    ch = getchar();   // read a character from the keyboard
    putchar(ch);      // write the character to the screen
    return 0;
}
```

> The same operation could also be performed with the line `printf(“%c”, ch);`.

---

## 3. The `putch()` Function

```c
int putch(int ch);
```

- It is a **non-standard** function (under `conio.h`).  
- Difference from `putchar`: It writes the `'
'` character only as **LF (ASCII 10)**.

### Example

```c
#include <conio.h>
int main(void) {
    putch(‘A’);
    putch(‘\n’);
    putch(‘B’);
    return 0;
}
```

> `A` and `B` appear on the screen in the same column, one below the other.

---

## 4. The `puts()` Function

```c
int puts(const char *str);
```

- It performs the same function as `printf(“%s\n”, str);` but **automatically adds `\n`.**
- It writes up to the `\0` character.

### Example

```c
#include <stdio.h>

int main(void) {
    puts(“Hello World”);
    return 0;
}
```

---

## 5. `getchar()` Function

```c
int getchar(void);
```

- Reads **one character** from the keyboard.  
- Reading is completed when the **Enter** key is pressed.
- Return value: the ASCII value of the character (`int`).

### Example

```c
#include <stdio.h>

int main(void) {
    int ch;
    printf(“Enter a character: ”);
    ch = getchar();
    printf(“The character you entered: ”);
    putchar(ch);
    putchar(‘\n’);
    return 0;
}
```

---

## 6. `getch()` and `getche()` Functions

| Function | Description | Standard? | Does it require Enter? | Is the character visible? |
|:------------|:------|:---------------|:------------------|:----------------------|
| `getch()` | Reads the character, does not print it to the screen | ❌ | ❌ | ❌ |
| `getche()` | Reads the character, also prints it to the screen | ❌ | ❌ | ✅ |

### `getch()` Example

```c
#include <conio.h>
#include <stdio.h>

int main(void) {
    printf(“Press a key...\n”);
    getch();
    printf(“Okay, let's continue!\n”);
    return 0;
}
```

### `getche()` Example

```c
#include <conio.h>
#include <stdio.h>

int main(void) {
    printf(“Press a key (character will appear on screen): ”);
    getche();
    printf(“\nReading completed.\n”);
    return 0;
}
```

> Both functions are located in the **`conio.h`** library and are **not portable.**

---

## 7. `gets()` Function (SHOULD NOT BE USED)

```c
char *gets(char *str);
```

- Reads a line of text from the user.  
- Takes all characters until the `Enter` key is pressed.  
- Not secure (buffer overflow risk).

### Safe Alternative

```c
fgets(str, sizeof(str), stdin);
```

### Safe Usage

```c
#include <stdio.h>

int main(void) {
    char name[20];
    printf(“Enter your name: ”);
    fgets(name, sizeof(name), stdin);
    printf(“Hello %s”, name);
    return 0;
}
```

---

## 8. Function Comparison Table

| Function | Task | Standard | Return | Line Ending | Note |
|:------------|:------|:-----------|:--------------|:-------------|:------|
| `putchar` | Writes 1 character | ✅ | ASCII code | Manual | Basic output |
| `putch` | Writes 1 character | ❌ | ASCII code | LF (only) | `conio.h` |
| `puts` | Writes string | ✅ | int | Automatic `\n` | Fast |
| `getchar` | Reads 1 character | ✅ | ASCII code | Enter required | basic input |
| `getch` | Reads 1 character | ❌ | ASCII code | Enter not required | invisible on screen |
| `getche` | Reads 1 character | ❌ | ASCII code | Enter not required | visible on screen |
| `gets` | Reads string | ❌ (removed in C11) | pointer | line end not included | security risk |

---

##  Input/Output Application

```c
#include <stdio.h>

int main(void) {
    char ch;
    printf(“Enter a character (end with x): ”);
    do {
        ch = getchar();
        putchar(ch);
    } while (ch != ‘x’);
    return 0;
}
```
Characters are printed to the screen as-is until the user enters `x`.

---

## 10. Result

- `putchar` → standard, for printing characters
- `putch` → non-standard, for DOS/Windows systems  
- `puts` → prints a string, adds `\n`  
- `getchar` → standard, reads a character  
- `getch` / `getche` → not portable  
- `gets` → **should not be used**, use `fgets` instead

---

## Additional examples
### 1. putchar
```c
#include <stdio.h>

int main(void) {
    char ch;
    printf("Bir karakter girin: ");
    ch = getchar();   // klavyeden tek karakter oku
    printf("Ekrana yazılıyor: ");
    putchar(ch);      // karakteri yaz
    putchar('\n');    // satır sonu
    return 0;
}

```

### 2. puts printf
```c
#include <stdio.h>

int main(void) {
    char ch;
    printf("Bir karakter girin: ");
    ch = getchar();   // klavyeden tek karakter oku
    printf("Ekrana yazılıyor: ");
    putchar(ch);      // karakteri yaz
    putchar('\n');    // satır sonu
    return 0;
}

```
### 3. getchar
```c
#include <stdio.h>

int main(void) {
    char ch;
    printf("Bir şeyler yazın (x ile çıkış):\n");
    do {
        ch = getchar();
        putchar(ch);
    } while (ch != 'x');
    return 0;
}

```
### 4. getch and getche
```c
#include <conio.h>
#include <stdio.h>

int main(void) {
    printf("Bir tuşa basın (getch): ");
    getch(); // Enter gerekmez
    printf("\ngetche test (karakter görünür): ");
    getche(); // karakter görünür
    printf("\nTamamlandı.\n");
    return 0;
}

```
### 5. putch 
```c
#include <conio.h>

int main(void) {
    putch('A');
    putch('\n');
    putch('B');
    return 0;
}

```
### 6. gets and gfets
```c
#include <stdio.h>

int main(void) {
    char ad1[20], ad2[20];

    printf("Adınızı (gets ile) girin: ");
    gets(ad1);  // ⚠️ TEHLİKELİ — boyut kontrolü yok!

    printf("Adınızı (fgets ile) girin: ");
    fgets(ad2, sizeof(ad2), stdin);

    printf("\ngets sonucu : %s\n", ad1);
    printf("fgets sonucu: %s\n", ad2);

    return 0;
}

```
### 7. fgets
```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char isim[30];
    printf("Adınızı girin: ");
    fgets(isim, sizeof(isim), stdin);
    isim[strcspn(isim, "\n")] = '\0'; // \n karakterini sil
    printf("Merhaba %s!\n", isim);
    return 0;
}

```
### 8. EOF_end of file
```c
#include <stdio.h>

int main(void) {
    int ch;
    printf("Ctrl+Z (Windows) veya Ctrl+D (Linux) ile çıkın:\n");
    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }
    printf("\nEOF algılandı.\n");
    return 0;
}

```
### 9. getchar ascii
```c
#include <stdio.h>

int main(void) {
    int ch;
    printf("Bir karakter girin (x ile bitir): ");
    do {
        ch = getchar();
        printf("Karakter: %c | ASCII: %d\n", ch, ch);
    } while (ch != 'x');
    return 0;
}

```
### 10. shadow password
```c
#include <conio.h>
#include <stdio.h>

int main(void) {
    char pass[20];
    int i = 0;
    char ch;

    printf("Şifre girin: ");
    while (i < 19 && (ch = getch()) != '\r') { // '\r' = Enter
        pass[i++] = ch;
        putch('*'); // maskelenmiş yazdırma
    }
    pass[i] = '\0';
    printf("\nGirdiğiniz şifre: %s\n", pass);
    return 0;
}

```
### 11. write and read
```c
#include <stdio.h>

int main(void) {
    char c;
    printf("Metin girin ('.' ile bitir):\n");
    while ((c = getchar()) != '.') {
        if (c >= 'a' && c <= 'z')
            c -= 32; // küçük → büyük
        putchar(c);
    }
    printf("\nTamamlandı.\n");
    return 0;
}

```

### 12. Definition, `void` and `main`
```c
#include <stdio.h>

// 1. VOID Function Definition (No return value, no parameters)
// Purpose: To perform a specific task (printing)
void print_separator() {
    printf("\n--------------------------\n");
    // A void function can optionally use 'return;' to exit early.
}

// 2. Value-Returning Function Definition (Returns an int, takes no parameters)
// Purpose: To calculate and return a value.
int get_current_year() {
    // Returns the calculated result (2025 in this example)
    return 2025; 
}

// 8. The main function - the program's starting point
int main() {
    
    // 9. Function Invocation (Void function call)
    print_separator();
    printf("C Functions: Basic Demo\n");
    print_separator();

    // 9. Function Invocation (Value-returning function, result used immediately)
    printf("The current year is: %d\n", get_current_year());
    
    // 9. Function Invocation (Value-returning function, result assigned to a variable)
    int year = get_current_year();
    printf("Year stored in variable 'year': %d\n", year);

    // 8. The return value of main is passed to the OS (0 means success)
    return 0; 
}
```

### 13. Parameters and Pass by-value
Please remember in pass by-value the arguments are copied, the original variable remains unchanged

```c
#include <stdio.h>

// 11. New Style Function Definition with Parameters
// Takes two int parameters (copies) and returns their sum (int)
int add_numbers(int a, int b) {
    // 7. Returns the calculated result.
    return a + b;
}

// 15. Demonstrating Copying Arguments (Pass-by-Value)
// The parameter 'val' is a copy of the argument passed in.
void try_to_change(int val) {
    printf("  Inside function: Original value is %d\n", val);
    val = 999; // Only changes the local copy 'val'
    printf("  Inside function: Value changed to %d (local copy)\n", val);
    return; // 7. Void function using 'return;'
}

int main() {
    int x = 10;
    int y = 20;

    printf("--- 1. Using Parameters ---\n");
    
    // 9. Function Invocation: x and y are the actual parameters.
    // Their values (10 and 20) are copied to parameters a and b.
    int sum_result = add_numbers(x, y); 
    printf("Sum of %d and %d is: %d\n", x, y, sum_result); // Output: 30

    printf("\n--- 2. Pass-by-Value (Copying Arguments) ---\n");

    int original_value = 50;
    printf("Before call: Original variable value is %d\n", original_value);

    // 15. Call the function, passing a copy of 50.
    try_to_change(original_value); 

    // The function's change to 'val' did not affect 'original_value'.
    printf("After call: Original variable value remains %d\n", original_value); // Output: 50
    
    return 0;
}

```

### 14. Recursion and Nested Calls
recursion (a function calling itself) and nested function calls (using one function's return value as another's input).
```c
#include <stdio.h>

// Helper function for nested calls
int square(int n) {
    return n * n;
}

// 17. Recursive Function Definition: Calculates factorial
int factorial(int n) {
    // Base Case (Stops the recursion)
    if (n == 0) {
        printf("  [Base Case] Reached n=0, returning 1.\n");
        return 1;
    }
    
    // Recursive Step
    printf("  Calling factorial(%d) * %d...\n", n - 1, n);
    // Function calling itself
    return n * factorial(n - 1); 
}


// Value-returning function with a function call inside its return
int calculate_hypotenuse_squared(int a, int b) {
    // 16. Another call inside return: Uses nested calls.
    // square(a) and square(b) are evaluated first.
    return add_numbers(square(a), square(b)); // Assuming add_numbers is available/defined
}

// A function defined earlier (from Intermediate Demo)
int add_numbers(int a, int b) {
    return a + b;
}

int main() {
    printf("--- 1. Nested and Return Calls ---\n");
    
    int side1 = 3;
    int side2 = 4;

    // 16. Nested call: calculate_hypotenuse_squared is called.
    // Inside it, add_numbers is called, and inside that, square is called twice.
    int h_squared = calculate_hypotenuse_squared(side1, side2);
    printf("Side 1^2 + Side 2^2 (3^2 + 4^2) = %d\n", h_squared); // Output: 25

    printf("\n--- 2. Recursive Function (Factorial) ---\n");
    int number = 4;
    printf("Calculating Factorial of %d:\n", number);

    // 17. Recursive call starts here
    int fact_result = factorial(number); 
    printf("Result of 4! is: %d\n", fact_result); // Output: 24

    return 0;
}
```

### 15. Prototypes, Linking, and Return Constraints
declarations (prototypes), the linker phase, and what happens when a function's return value is ignored or misused.
```c
#include <stdio.h>

// 1. Function Prototype (Declaration)
// This tells the compiler the function exists, its signature, and its return type.
// It allows us to define the function later or in a separate file.
int calculate_something(int x, int y); 

// 5. Function Without a Specified Type (Old C/Pre-ANSI C)
// The compiler automatically assumes 'int' return type. (Not recommended).
// 10. This is defined *before* the call, so no prototype is strictly needed.
no_type_func() {
    printf("-> (Warning) Function without a specified type. Assumed 'int'.\n");
    return 100;
}

// 3. Main function demonstrating function calls
int main() {
    int a = 10, b = 5;

    printf("--- 1. Using and Not Using Return Values ---\n");
    
    // 16. Value-returning function, result assigned. (Normal use)
    int result = calculate_something(a, b);
    printf("Result used (10 * 5) = %d\n", result);

    // 16. Call without using the value. (Can sometimes trigger a warning)
    calculate_something(a, b);
    printf("Result not used. (Compiler might issue 'code has no effect!')\n");

    // 9. Function Invocation: func() = 5 is Invalid (R-value constraint)
    // The value produced by a function call is an R-value, it cannot be assigned to.
    // Error: L-value required as left operand of assignment.
    // (If you uncomment the line below, it will cause a compile error.)
    // calculate_something(a, b) = 100; 
    
    // Call function with implicit 'int' return type
    printf("no_type_func returned: %d\n", no_type_func());

    return 0;
}

// 5. Function Definition (Must be defined somewhere for the linker)
int calculate_something(int x, int y) {
    return x * y;
}

// 10. Undefined Function Example
// If we had a prototype for 'void linker_error();' but no definition anywhere,
// the compiler would be happy, but the *linker* would fail.
```

### 16. Old Style vs. New Style and `int foo()` vs. `int foo(void)`
Old Style vs. New Style and int foo() vs. int foo(void)
```c
#include <stdio.h>

// 14. Function without Parameters (Implicit 'void') - Deprecated
// In C, an empty parenthesis means "takes an unspecified number of arguments."
// The compiler does NOT check the number of arguments passed in the function call.
int old_style_no_param() {
    return 1;
}

// 14. Function without Parameters (Explicit 'void') - New Style
// This is the correct, modern way to state a function takes NO arguments.
// The compiler WILL issue an error if arguments are passed.
int new_style_no_param(void) {
    return 2;
}

// 12. Old Style Parameter Declaration (Pre-ANSI C)
// Parameter types are listed after the function header. This is obsolete.
int old_style_params(x, y)
int x; 
int y; // The compiler can still compile this but throws a warning.
{
    printf("  [Old Style] Parameters: %d and %d\n", x, y);
    return x - y;
}


int main() {
    printf("--- 1. New Style vs. Old Style Parameters ---\n");
    
    // 13. New Style Call: Types declared in the parentheses.
    printf("New Style Subtraction (10 - 5): %d\n", old_style_params(10, 5));
    
    printf("\n--- 2. Parameter Constraints: () vs. (void) ---\n");
    
    // Using () (unspecified)
    printf("old_style_no_param() returned: %d\n", old_style_no_param());
    
    // DANGER: We can call the '()' function with arguments, and the compiler
    // may not complain, leading to Unspecified Behavior! (Value is ignored/garbage)
    printf("old_style_no_param(100, 200) returned: %d\n", old_style_no_param(100, 200));

    // Using (void)
    printf("new_style_no_param(void) returned: %d\n", new_style_no_param());

    // ERROR: If you uncomment the line below, the compiler will catch it,
    // as the (void) parameter list explicitly states no arguments are allowed.
    // printf("new_style_no_param(100) returned: %d\n", new_style_no_param(100));
    
    return 0;
}
```

### 17. Return flow and exit
function exit points, including using `return` in a `void` function, and the difference between the actual return value and the OS return value.
```c
#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS/EXIT_FAILURE

// A value-returning function that might return a garbage value.
int check_and_exit(int x) {
    if (x < 0) {
        printf("Condition met, exiting early with status code 1.\n");
        // We can use 'return' with a value here, but we are also
        // using the standard library's exit function to terminate the *entire program* immediately.
        exit(EXIT_FAILURE); // Terminates the program entirely, bypassing the return
    }
    
    // 7. If the end is reached without a return statement, it returns a garbage value.
    // NOTE: Many modern compilers will issue a warning or error if a non-void
    // function reaches the end without a return statement, but the C standard allows it.
}


// A void function demonstrating early exit
void process_data(int data) {
    if (data == 0) {
        printf("Data is zero, cannot process. Exiting function early.\n");
        // 7. return; used to end execution in a void function.
        return; 
    }
    
    printf("Data %d processed successfully.\n", data);
}

int main() {
    printf("--- 1. Void Function Exit Flow ---\n");
    process_data(10);
    process_data(0); // This call triggers an early return
    process_data(20); // This is executed after the early return
    
    printf("\n--- 2. main() Return Value ---\n");
    
    // 8. The return value of main is passed to the operating system.
    // A function call that returns a value (r-value)
    int result = check_and_exit(5);
    
    // 8. Convention: 0 for success.
    return EXIT_SUCCESS; // which is usually 0
    
    /*
    If we had called check_and_exit(-1) instead, the program would have
    terminated immediately inside that function with exit(EXIT_FAILURE),
    and the 'return EXIT_SUCCESS' line here would never be reached.
    */
}

```