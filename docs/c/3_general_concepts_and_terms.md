# General Concepts and Terms

## 1. Tokens and Their Types

The smallest meaningful parts of a source file written in a programming language are called **tokens**.  
Before a C program is compiled, it is **broken down into tokens (tokenizing / lexical analysis)**.

Tokens are divided into 6 basic groups:

### 1.1 Keywords

These are words with **predefined** special meanings in the C language. These words cannot be used for any other purpose (e.g., as variable names).

#### C89 Standard Keywords (32 in total)

```c
auto break case char const continue default do double else enum extern 
float for goto if int long register return short signed sizeof static 
struct switch typedef union unsigned void volatile while
```

**Note:**  
- The C language is **case-sensitive**.  
- Therefore, `register` is a keyword, but `REGISTER` or `Register` can be used.

---

### 1.2 Identifiers

These are the names given to variables, functions, macros, or constants.  
The validity of identifiers is defined by specific rules (for example, they must start with a letter and cannot contain spaces).

```c
int counter;
float average;
char name[20];
```

---

### 1.3 Operators

These are symbols that perform predefined operations.  
For example, `+`, `-`, `*`, `/`, `>=`, `<=` are operators.  
There are **45 operators** in the C language.

> Some operators consist of two characters and do not contain spaces:  
> `++`, `--`, `<=`, `>=`, `==`, `!=`

For example, exponentiation (`^`) is not an operator in C; instead, the **pow()** function is used.

```c
#include <math.h>
int main() {
    double result = pow(2, 3); // 2 to the power of 3
}
```

---


### 1.4 Constants

These are atoms whose values do not change throughout the program.

```c
int a = 10;       // 10 is an integer constant
float pi = 3.14;  // 3.14 is a real number constant
char c = ‘A’;     // Character constant
```

---

### 1.5 Strings

These are fixed character sequences enclosed in double quotes.  
A string is treated as **a single atom** in a program.

```c
printf(“Hello World!”);
```

> `“STRINGS ARE ALSO ATOMS”` is a string.

---

### 1.6 Delimiters and Punctuation Marks

Used to separate atoms from each other.  
Examples:  
```
( ) , ; { } [ ] < > # " '
```

Translated with DeepL.com (free version)

---


## 2. Breaking Down a C Program into Its Building Blocks

Example program:

```c
#include <stdio.h>

int main() {
    int number, k;
    int total = 0;

    printf(“Please enter a number\n”);
    scanf(“%d”, &number);

    for (k = 1; k <= number; ++k)
        total += k;

    printf(“Total = %d\n”, total);
    return 0;
}
```

### The atoms of this program:

| Type | Examples |
|:----|:-----------|
| Keywords | include, int, for, return |
| Names | main, number, total, printf, scanf |
| Operators | =, <=, ++, += |
| Constants | 0, 1 |
| Strings | “please enter a number\n”, “%d”, “total = %d\n” |
| Delimiters | <, >, (, ), {, }, ;, , |

---


## 3. Object

These are areas that occupy space in memory and whose contents can be accessed.  
For an expression to be considered an object, it must have a **physical address in memory**.

```c
int a = 10;
int b = 20;
int result = a + b;
```

- `a`, `b`, `result` → are objects.  
- `10`, `20` → are constants (not objects).

### Properties of Objects

| Property | Description |
|:--------|:----------|
| **Name** | The name given by the programmer. |
| **Value** | The information stored in memory by the object. |
| **Type** | The length and interpretation format of the object in memory. |

Each type occupies a different amount of space in memory.  
For example, `int` is 4 bytes, `char` is 1 byte, `double` is 8 bytes.

> Every **variable is an object**, but not every object is a variable (e.g., pointers).

---


## 4. Data Types

### 4.1 Built-in Types

There are 11 built-in types in the C language. Examples:  
`int`, `float`, `double`, `char`, `void`, `short`, `long`, `signed`, `unsigned`, `enum`, `struct`

### 4.2 User-Defined Types

Programmers can define their own types using `struct`, `union`, or `enum`.

```c
typedef struct {
    char name[20];
    int age;
} Person;
```

> There is no `bool` type in C89. Logical values are typically represented using `int` (`0` = false, `1` = true).

---


## 5. Scope

The **program area** where a name can be recognized by the compiler.

```c
int x = 10; // global scope

void func() {
    int y = 20; // local scope
    printf(“%d %d”, x, y);
}
```

---

## 6. Storage Duration

The time interval during which an object **exists while the program is running.**

| Type | Description |
|:----|:----------|
| **Automatic (auto)** | Defined within a function, disappears when the function ends. |
| **Static (static)** | Remains in memory for the duration of the program. |
| **Dynamic (malloc/free)** | Managed by the programmer. |

```c
void f() {
    static int count = 0;
    count++;
    printf(“%d\n”, count);
}
```

---

## 7. Linkage

The ability of an object to be recognized in other modules of the program.

```c
// file1.c
int globalVar = 42;

// file2.c
extern int globalVar;
printf(“%d”, globalVar);
```

> The `extern` keyword indicates that the variable is defined in another file.

---


## 8. Expression

It is a combination of variables, operators, and constants.

```c
a + b / 2
c * 2
d = h + 34
```

Every expression **produces a value.**

---

## 9. Left-Hand Side Value (L-Value expression)

These are expressions that represent an object in memory.  
They can be found **on the left side of an assignment.**

```c
int a, b;
a = 17;     // ‘a’ is an l-value
b = a + 2;  // ‘b’ is an l-value, (a + 2) is an r-value
```

> `a + b = 25;` → invalid because `(a + b)` does not refer to an object.

---

## 10. Right-Hand Side Value (R-Value expression)

These are expressions that do not refer to an object, but only produce a **value**.  
They can be placed on the right side of an assignment.

```c
int a = 10;
int b = a + 5; // (a + 5) is an r-value
```

---

## 11. Constant Expressions

These are expressions consisting only of **constants**.  
They can be evaluated by the compiler during the compilation phase.

```c
#define SIZE 10
int arr[SIZE + 5]; // the compiler can calculate this
```

Examples:
```
10
3.5
10 + 20
```

---

## 12. Statement

In C, it means **a complete command** and ends with `;`.

```c
result = number1 * number2;
```

Some statements only provide information:  
- **Declaration statements** → provide information to the compiler.  
- **Executable statements** → perform an operation.

```c
int x;            // declaration
x = 5;            // executable statement
printf(“%d”, x);  // executable statement
```

---


## Additional Codes
### 1. Basic L-value and R-value Assignment
```c
#include <stdio.h>

int main() {
    int x = 10;
    int y = 5;

    // L-value: x (persistent memory location)
    // R-value: y + 2 (temporary value calculated on the fly)
    x = y + 2; 

    printf("x = %d, y = %d\n", x, y);
    return 0;
}
```

### 2. Modifying Memory via Pointer Dereference (L-value)
```c
#include <stdio.h>
/*
If you can take the address of an expression using '&', it is an **L-value**.
*/
int main() {
    int x = 10;
    // &x is valid because x is an L-value
    printf("Address of x: %p\n", (void*)&x); 

    // printf("%p", &(x + 1)); // ❌ Error: (x + 1) is an R-value (temporary result)
    return 0;
}
```
```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a; // p stores the address of a

    *p = 25;  // *p is an L-value because it refers to memory location 'a'
    printf("a = %d\n", a);
    return 0;
}
```

### 3. Function Return Values as L-values or R-values
```c
#include <stdio.h>

// Returns an R-value (a copy of the static value)
int func1() {
    static int x = 5;
    return x;  
}

// Returns a pointer (an L-value address)
int* func2() {
    static int y = 10;
    return &y; // Returns the persistent address of 'y'
}

int main() {
    // func1() = 20; ❌ Error: func1 returns an R-value (a temporary value)
    
    // *func2() is an L-value because it dereferences a persistent address (the address of static int y)
    *func2() = 30;   // ✅ Valid: Modifies the static variable 'y'
    
    printf("Value pointed to by func2(): %d\n", *func2()); // Output: 30
    return 0;
}
```

### 4. counter
```c
// counter_module.c

#include <stdio.h>

// Global 'count' variable with internal linkage (only visible in this file)
// Static Storage Duration guaranteed.
static int private_counter = 0; 

// Function with external linkage (visible to other files via header)
// Increments the internal static counter
void increment_counter(void) {
    private_counter++;
}

// Function with external linkage
// Returns the internal counter's value (R-value)
int get_counter_value(void) {
    return private_counter;
}

// Advanced: Returns a pointer to a static local L-value
// The L-value itself (the static variable) has persistent storage duration.
int* get_static_local_lvalue(void) {
    // Static local variable: Block scope, but Static Storage Duration
    static int persistent_config = 99; 
    return &persistent_config; // Returns the address of the L-value
}
```
```c
// counter_module.h

#ifndef COUNTER_MODULE_H
#define COUNTER_MODULE_H

// Declarations (External Linkage assumed by default for functions)
void increment_counter(void);
int get_counter_value(void);

// Declaration for the advanced L-value return function
int* get_static_local_lvalue(void); 

// Note: The variable 'private_counter' itself is NOT declared here, 
// ensuring internal linkage and data hiding.

#endif // COUNTER_MODULE_H
```

```c
// main.c

#include <stdio.h>
#include "counter_module.h" // Includes function prototypes

int main() {
    printf("--- Module Access and Linkage Test ---\n");

    // 1. Storage Duration & Scope Test
    
    // Call the function to increment the hidden counter
    increment_counter();
    increment_counter();
    
    // Access the value using the public getter function
    printf("Counter value after 2 increments: %d\n", get_counter_value()); // Output: 2

    // 2. L-value Manipulation Test (Advanced)
    
    // Get the address of the static local L-value from the module
    int *config_ptr = get_static_local_lvalue(); 
    
    // *config_ptr is an L-value expression; its address is persistent.
    // We can directly modify the value stored at that persistent memory location.
    *config_ptr = 500; 
    
    printf("Static local variable modified to: %d\n", *config_ptr); // Output: 500

    // 3. Linkage Failure Attempt (Illustrative Note)
    
    /* // int check_counter = private_counter; 
    // ❌ ERROR: private_counter has internal linkage and is NOT accessible here.
    // The extern keyword would not work unless the variable was defined globally 
    // without 'static' in counter_module.c.
    */
    
    return 0;
}
```