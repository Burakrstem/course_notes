# Declaration and Definition

## 1. Declaration

A **declaration statement** provides information to the compiler at compile time.  
This information relates to the type, name, and existence of the variable or function.

**Example:**
```c
extern int count;
void printCount();
```
It informs the compiler that “there is an integer variable named `count` and a function named `printCount()`.”  
However, it does not allocate memory.

---

## 2. Definition

**Definition** causes the compiler to allocate memory.  
Unlike declaration, definition creates a real object.

**Example:**
```c
int count = 5; // Definition
```
This statement allocates memory for the `count` variable.  
Every definition is a declaration; however, not every declaration is a definition.

| Operation | What the Compiler Does |
|:------|:---------------------|
| Declaration | Receives information, does not allocate space |
| Declaration | Receives information and allocates space in memory |

---

## 3. Variable Declaration

In C, a variable must be **declared** before it is used.  
The compiler allocates the appropriate amount of memory for the variable, knowing its type and name.

**General Syntax:**
```c
<type-specifying words> <variable name>;
```

**Examples:**
```c
int total;
unsigned long counter;
float average;
```

The semicolon (`;`) terminates the statement.  
In C, `;` is the “period” of the expression.

---

## 4. Type-Specifying Keywords

Keywords that can be used:
```
signed, unsigned, char, short, int, long, float, double
```
All keywords are written in **lowercase**. The C language is **case-sensitive**.

### 🔸 Equivalent Type Declarations

| Type | Equivalent Notations |
|:----|:----------------|
| Signed character | `signed char`, `char` |
| Unsigned character | `unsigned char` |
| Signed short integer | `short`, `signed short`, `short int` |
| Unsigned short integer | `unsigned short`, `unsigned short int` |
| Signed integer | `int`, `signed int`, `signed` |
| Unsigned integer | `unsigned`, `unsigned int` |
| Long integer | `long`, `long int`, `signed long int` |
| Unsigned long integer | `unsigned long`, `unsigned long int` |
| Floating point numbers | `float`, `double`, `long double` |

---

## 5. Naming Rules (Identifiers)

### Valid characters:
- `a-z`, `A-Z`
- `0-9`
- `_` (underscore)

### Invalid characters:
Spaces, Turkish characters (`ç, ğ, ü, ö, ş, ı` etc.), `+`, `-`, `/`, `*`, `&`, `$` etc.

### Rules:
- Names **cannot start with a number.**
- They can start with the `_` character.
- **Keywords** cannot be used as names.
- Case sensitivity matters (`var`, `Var`, `VAR` are different).
- At least **31 characters** are guaranteed to be considered.

### Long and Meaningful Names
Names should express the purpose of the variable:
```c
int tax_rate;
int number_of_students;
```
`_` or CamelCase is often used instead of spaces:
```c
int total_price;
int TotalPrice;
```

---

## 6. Declaration Examples

```c
int x;
unsigned long int var;
double MFCS;
unsigned _result;
signed short total;
```

Multiple variables of the same type:
```c
unsigned char ch1, ch2, ch3, ch4;
float fl1, fl2;
int tax_rate, tax_base;
```

Defining different types on the same line is invalid:
```c
long x, int y; // Error
```

### Keyword Order
```c
signed long int x;
long signed int x;
int long signed x;
```
All are valid, but `signed long int` is more readable.

---

## 7. Locations of Declarations in Source Code

Variable declarations can be made in 3 places:

| Location | Description |
|:----|:----------|
| Inside a block | Local variable |
| Outside blocks | Global variable |
| In the function parameter list | Parameter declaration |

### Rule
Declarations must be **at the beginning of the block**.

```c
{
    int x, y;     // Valid
    x = 5;
    float f;      // Invalid (there is an expression before it)
}
```

But in a nested block:
```c
{
    int a;
    { float b; }  // Valid
}
```

---

## 8. Null Statement

A standalone `;` is an executable **null statement.**
In this case, any subsequent declaration becomes invalid.

```c
{
    int x;;
    int y; // Invalid
}
```

An empty block `{ }` is also considered an executable statement.

---

## 9. Initialization

When defining a variable, **an initial value can be assigned.**  
This is not an assignment, but **a declaration.**

```c
int a = 20;
int b = 10, c = 30;
```

Incorrect example:
```c
void func() {
    int a;
    a = 20;
    int b; // Invalid (there is an expression before it)
}
```
Correct example:
```c
void func() {
    int a = 20;
    int b; // Valid
}
```

---

## 10. Declaration and Definition in Multi-File Programs

### header.h
```c
extern int count;
void printCount();
```
`extern` tells the compiler that “this variable will be defined in another file.”

### main.c
```c
#include “header.h”
int count = 5;

int main() {
    printCount();
}
```

### util.c
```c
#include “header.h”
#include <stdio.h>

void printCount() {
    printf(“%d\n”, count);
}
```

`header.h` contains the declaration, `main.c` performs the definition, and `util.c` uses the declared `count`.

---

## 11. Compilation & Linking

Compilation:
```bash
gcc -c main.c   → main.o
gcc -c util.c   → util.o
```
Linking:
```bash
gcc main.o util.o -o program
```
Running:
```bash
./program
```
**Output:**
```
5
```

---

## 12. Summary

| Concept | Definition | Allocates Memory? | Example |
|:--------|:------|:------------------------|:-------|
| **Declaration** | Provides information to the compiler | No | `extern int x;` |
| **Definition** | Creates an object | Yes | `int x = 5;` |

---


