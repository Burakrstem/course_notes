# Creating a C Program

## 1. Creating the Source File

C programs are written as **text-based source files**.  
These files are usually created using a **text editor**.

- Files are written according to the syntax rules of the C language.  
- Traditionally, C source files have the extension **`.c`**.

For example:
```
main.c
mathutils.c
```

> The source file contains only plain text; it cannot be run before compilation.

---

## 2. Compilation Stage

Programs that translate a program written in one programming language into another language are called **translators**.  
In the C language, the translator that does this job is called a **compiler**.

### Compilation Process

- The compiler takes the source file.  
- It checks whether it complies with the syntax rules.  
- If successful, it produces an **object file**.  
- If unsuccessful, it gives an error or warning message.

### Compile Time

The stage during which the compiler processes the source file is called **compile time**.  
During this stage, the following types of messages may be generated:

| Type | Description | Result |
|:----|:----------|:--------|
| **Error message** | Syntax or language rule violation | Compilation fails, object file is not created |
| **Warning message** | Potential logical error | Compilation may complete, object file is produced |

> According to C standards, compilers report not only syntax errors but also potential **logical errors** as warnings.

---
## 3. Object Files

Files produced during the compilation phase are files that have been **translated into machine language** but cannot yet be run independently.

| Operating System | Extension | Example |
|:----------------|:--------|:--------|
| UNIX / Linux | `.o` | `main.o` |
| Windows / DOS | `.obj` | `main.obj` |

Object files are usually combined during the **linking** phase.

---

## 4. Linker Program

The **linker** combines one or more compiled object files to create an **executable file**.

### Result Files

| Operating System | Extension | Example |
|:----------------|:--------|:--------|
| UNIX / Linux | (usually no extension) | `program` |
| Windows | `.exe` | `program.exe` |

> 🔹 The linker also incorporates external libraries (such as `stdio.h`, `math.h`) into the program.

---

## 5. Compiler Programs

Compilers are generally designed to be run from the **command line**.  
This allows them to be easily called by other tools or IDEs.

| Platform | Compiler | Executable File |
|:----------|:------------|:----------------|
| Microsoft Windows | MSVC | `cl.exe` |
| UNIX / Linux | GNU C Compiler | `gcc` or `clang` |

### Example Compilers

- **GCC (GNU Compiler Collection)** → popular, open source.  
- **Clang** → a modern and fast alternative.  
- **MSVC** → Microsoft Visual C/C++ compiler.

---

## 6. IDE (Integrated Development Environment)

An **IDE** is not a compiler.  
It is a **development environment** that runs the compiler in the background and facilitates software development.

| IDE | Compiler Used |
|:----|:---------------------|
| Dev-C++ | GCC |
| Code::Blocks | GCC or Clang |
| Visual Studio | MSVC |
| MinGW | GCC (for Windows) |

> An IDE can automatically perform compilation and linking operations and present error messages to the user in an easy-to-understand manner.

---

## 7. Preprocessor

In C and C++, it is a program that runs **before** the compilation stage.  
At this stage, **text-based operations** are performed on the source code (e.g., `#include`, `#define`).

Before passing to the compiler, the preprocessor:
- Processes macros (`#define`),
- Performs file inclusions (`#include`),
- Evaluates conditional compilation directives (`#ifdef`, `#ifndef`).

> The preprocessor is a separate program, but most modern compilers (e.g., GCC) call it automatically.

---

## 8. General Summary of the Process

The C program development process goes through the following steps:

```
Source Code (.c)
      ↓
  [Preprocessor]
      ↓
  [Compiler]
      ↓
  Object File (.obj / .o)
      ↓
  [Linker]
      ↓
Executable Program (.exe / program)
```

## 9. Example codes
### main.c mathutils.c mathutils.h

```c
// mathutils.h

#ifndef MATHUTILS_H
#define MATHUTILS_H

// Function declaration with external linkage
// Declares that a function named 'calculate_distance' is defined elsewhere.
double calculate_distance(int x1, int y1, int x2, int y2);

#endif // MATHUTILS_H
```
```c
// mathutils.c
// This module provides the mathematical implementation.

#include "mathutils.h"
#include <math.h> // Required for sqrt() and pow() function definitions

// Definition of the function declared in mathutils.h
double calculate_distance(int x1, int y1, int x2, int y2) {
    // Uses the standard C math library functions
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    // pow(base, exponent) and sqrt() are external library functions (libm.a on Unix/Linux)
    return sqrt(pow(dx, 2) + pow(dy, 2));
}
```

```c
// main.c

#include <stdio.h>
#include "mathutils.h" // Includes the function prototype

int main() {
    int p1_x = 10, p1_y = 20;
    int p2_x = 40, p2_y = 60;
    double dist;

    // Call the function defined in mathutils.c
    dist = calculate_distance(p1_x, p1_y, p2_x, p2_y);

    printf("Distance between (%d,%d) and (%d,%d) is: %.2lf\n",
           p1_x, p1_y, p2_x, p2_y, dist);
           
    return 0;
}
```
### 9.1.Object files
```bash
gcc -c main.c      # ->main.o
gcc -c mathutils.c # ->mathutils.o
```

### 9.2.Linkage
```bash
gcc main.o mathutils.o -o program
```

### 9.3.Run
```bash
./program
```

### Generate object files + link + run
```bash
gcc main.c mathutils.c -o program
./program
```

## Glossary of Terms

| Term | English | Description |
|:------|:-------------|:----------|
| Source file | Source file | Text file written by the programmer |
| Compiler | Compiler | Converts source code to machine code |
| Object file | Object file | Compiled but not yet executable code |
| Linker | Linker | Combines object files |
| Preprocessor | Preprocessor | Performs text processing before compilation |
| IDE | Integrated Development Environment | Development environment |

---

