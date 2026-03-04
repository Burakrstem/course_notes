# ⚙️ Preprocessor Directives (1)

C compilers consist of two separate modules:

1.  **Preprocessor Module**
2.  **Compilation Module**

The preprocessor has nothing to do with the computer's processor or any other hardware component. The preprocessor is a software program that performs a specific task.

The preprocessor is a preliminary program that performs certain arrangements and changes on the source file. The preprocessor program has an input and an output. The input of the preprocessor is the source file itself. The output of the preprocessor program forms the input of the compilation module. That is, the source program is first processed by the preprocessor. The preprocessor module performs various textual arrangements and changes in the source file. Then, this modified or arranged source file is converted into object code by the compilation module.

In the C programming language, all lines starting with **`#`** are **directives** given to the preprocessor program.

The preprocessor program can perform operations from a predetermined set of commands. Each command is identified by a word following the `#` token. Below is a list of all preprocessor directives:

* `#include`
* `#define`
* `#if`
* `#else`
* `#elif`
* `#ifdef`
* `#ifndef`
* `#endif`
* `#undef`
* `#line`
* `#error`
* `#pragma`

The words above that define the preprocessor directives are **not** C language keywords. By the time it is the compiler's turn, they have been deleted from the source file by the preprocessor. For example, a variable named `include` can be defined if desired, but it can be said that this is not a good idea in terms of readability. The words specifying the preprocessor directives only gain special meaning when they follow the `#` character.

The preprocessor program does not perform any task aimed at generating object code; it performs some textual arrangements within the source code. After performing the directives given to it, it deletes the lines starting with `#` from the source file. The program entering the compilation module no longer contains lines starting with `#`.

For now, you will only see the `#include` and `#define` directives. The remaining preprocessor directives will be covered in detail later.

---

## 📥 The `#include` Preprocessor Directive

The general syntax of the `#include` preprocessor directive is as follows:

    #include <file name>
    // or
    #include "file name"

With the `#include` directive, the content of the file whose name is given is **pasted** into the place where this directive is written. With this directive, the preprocessor reads the specified file from the disk and places it where the directive is written. The job done with this directive can be likened to the **"copy – paste"** operation in text editor programs.

The file name to be included in the source file with the `#include` preprocessor directive can be specified in two separate ways:

1.  **In angle brackets:**
    * `#include <stdio.h>`
    * `#include <time.h>`
2.  **In double quotes:**
    * `#include "general.h"`
    * `#include "genetic.h"`

If the file name is given in angle brackets, the file in question is searched for by the preprocessor only within a **predefined directory**. This predefined directory may vary depending on the compiler used and the system setup. For example:

    \tc\include
    \borland\include
    \c600\include
    // and similarly for UNIX systems:
    /usr/include

Standard header files are included in the source code within angle brackets.

In most systems, when the file name is written within double quotes, the preprocessor first searches for the relevant file in the **current directory**. If it is not found there, it searches in the system-defined directory. For example, let's assume we are working in the directory:

    C:\sample

With the directive `#include "strfunc.h"`, the preprocessor first searches for the file `strfunc.h` in the `C:\sample` directory. If it cannot find it there, it searches in the system-defined directory. Header files created by programmers themselves are usually included in the source code within double quotes, as they are not located in the system's directory.

The file name to be included in the source code with the `#include` preprocessor directive can also include the **file path**:

    #include <sys\stat.h>
    #include "c:\headers\myheader.h"

The `#include` directive can be found anywhere in the source program. However, the best place for files containing various declarations, such as standard header files, is undoubtedly at the **very top of the program**.

The `#include` directive can also be found in a **nested** form. For example, the following method can be used to include a large number of files in the source code:

| `main.c` | `project.h` |
| :--- | :--- |
| `#include "project.h"` | `#include <stdio.h>` |
| `int main()` | `#include <conio.h>` |
| `{ /*...*/ }` | `#include <stdlib.h>` |
| | `#include <time.h>` |

Only the `project.h` file is included in the `main.c` file. After the preprocessor includes this file in the source code, it continues from this file.

### Why are Header Files Used?

Especially large programs are written in separate parts called modules. The purpose of some of these modules is to provide services to other modules. In C and C++ languages, general service codes (**server codes**) are generally written as two separate files. Function definitions and global variable definitions are located in the file with the **`.c`** extension. This file is called the **implementation file**. Declarations concerning the codes that will receive the service (**client codes**) are kept in another file. This file is called the **header file**. A header file is the **interface** of a module. The module establishes its relationship with the outside world through its interface.

User codes that will benefit from the provided services do not see the service-providing codes themselves, only their interface. Client codes are written dependent on the interfaces of the server codes. Thus, the server codes themselves and their interfaces are clearly separated from each other.

What are the benefits of separating the definitions of the server codes from their interfaces?

User codes, i.e., client codes, are written dependent on the function interfaces, not their definitions. The following benefits can be obtained from this:

1.  Those who write the server codes can make changes to the definition codes, provided they stick to the same interface. In this case, no changes are required in the client codes.
2.  The programmer writing the user codes performs easier abstraction because they do not have to know the implementation details of the server codes.
3.  The project development time is shortened if more than one programmer works on the same project.

---

## 📝 The `#define` Preprocessor Directive

The function of the `#define` preprocessor directive can be likened to the **"find - replace"** feature in text editor programs. This directive is used to replace a text in the source code with another text.

The preprocessor obtains the first non-space sequence of characters after skipping the spaces following the `define` word. Let's call this sequence **STR1**. Then, the entire sequence of characters until the end of the line is obtained. Let's call this **STR2**. The preprocessor places the text **STR2** instead of the text **STR1** in the source code:

    #define SIZE 100

With the preprocessor directive, the preprocessor replaces every `SIZE` token it sees in the source code with the token `100`. The `SIZE` token is no longer present in the source program entering the compilation module.

The `#define` preprocessor directive is most often used to replace a name with a numerical value. A name replaced by a numerical value is called a **"symbolic constant."** Symbolic constants are not objects. In the source code entering the compilation module, symbolic constants are replaced by numerical expressions.

Names defined with the `#define` preprocessor directive are also called **"simple macros."**

Symbolic constants are conventionally named with **uppercase letters**. This allows the reader of the code to distinguish between variables and symbolic constants. As is known, predominantly lowercase letters are used for variable naming in the C language.

A symbolic constant can be used in the definition of another symbolic constant. For example:

    #define MAX 100
    #define MIN (MAX - 50)

The replacement operation is performed if **STR1** is found as a **token** in the source code:

    #define SIZE 100

Assume that the source code contains statements such as:

    size = MAX_SIZE;
    printf("SIZE = %d\n", size);

The preprocessor does not make any changes to these statements.

In the expression `size = MAX_SIZE`, `SIZE` is not a separate token; the token is `MAX_SIZE`. Since the replacement is case-sensitive, the name `size` in the source code is also not the token to be replaced.

In the expression `printf("SIZE = %d\n", max_size)`, the token is the string literal. That is, `SIZE` inside the string literal is not a separate token on its own.

The `#define` preprocessor directive cannot be used to perform a replacement operation for literals and operators. The following `#define` preprocessor directives are invalid:

    #define + -
    #define 100 200

Symbolic constants must be named according to the C language's variable naming rules:

    #define BÜYÜK 10 // Invalid in standard C/English environment

The preprocessor program also executes the preprocessor directives inside the file included in the source code with the `#include` directive. In this case, when a file containing symbolic constant definitions is included in the source code with the `#include` directive, these symbolic constants become valid as if they were defined within the source code.

Strings can also be used in the `#define` preprocessor directive:

    #define ERROR_MESSAGE "FILE CANNOT BE OPENED \n"
    /***/
    printf(HATA_MESAJI);
    /***/

If the string to be used in the symbolic constant definition is long, it can be placed on multiple lines to facilitate code readability. In this case, the `\` token must be placed at the end of all lines except the last one.

For readability, all symbolic constant definitions should be written consecutively one below the other. The chosen symbolic constant names should give the person reading the code an idea of their purpose.

Defining a symbolic constant does not necessitate the existence of information that can be replaced in the source code. Not using a defined symbolic constant in the source code does not lead to any errors.

### Symbolic Constants Make Code More Readable

Symbolic constants increase the readability and comprehensibility of the written code. Giving names to some literals can provide more information about the purpose for which these literals are used. Let's look at the example below:

    #define PERSONNEL_COUNT 750

    void foo()
    {
        /***/
        if (x == PERSONNEL_SAYISI) // PERSONNEL_SAYISI is PERSONEL_SAYISI in Turkish text
        /***/
    }

If the literal value 750 had been used directly instead of the `PERSONNEL_COUNT` symbolic constant in the source code, it would be much more difficult for the reader of the code to deduce what this literal means, wouldn't it?

### Naming Types with Symbolic Constants

The `#define` preprocessor directive can also be used to give names to C's native data types:

    #define BYTE char
    #define BOOL int
    
    BYTE foo(BYTE b);
    BOOL isprime(int val);

You know that the `char` type is actually a 1-byte integer type. The use of the name `char` often gives the impression that a task related to text or characters is being performed. However, functions that perform general operations on memory blocks also often use the `char` type. In this case, a name like `BYTE` can be used to give more idea about the operation being performed. You recall that the `BOOL` type does not exist in C (historically). The `int` type is used as a logical data type instead of the `bool` data type in C. However, the name `BOOL` can be used with the `#define` preprocessor directive to increase program readability.

We will later address the **`typedef`** keyword and the definition of new type names as an alternative to this usage.

### Functions Returning with Symbolic Constants

Another usage aimed at increasing readability is for the return values of functions. You know that the return values of some functions answer a question, and the return values of some functions give an idea about the success of an operation. Such functions can be better in terms of readability if they use symbolic constants instead of return value expressions:

    return VALID;
    return INVALID;
    return TRUE;
    return FALSE;
    return FAILED;

and so on.

### Calling Functions with Symbolic Constants

Symbolic constants are also sent to some functions by the calling code snippet.

Some symbolic constants are also defined for this purpose in C's standard header files. For example, in the `stdlib.h` header file, there are definitions in the form:

    #define EXIT_FAILURE 1
    #define EXIT_SUCCESS 0

That is, if the `stdlib.h` header file is included in the source code, the `EXIT_FAILURE` symbolic constant can be used instead of 1, and the `EXIT_SUCCESS` symbolic constant can be used instead of 0. These symbolic constants are used in calls to the standard `exit` function:

    exit(EXIT_FAILURE);

In the `stdio.h` header file, three symbolic constants are defined for the purpose of being sent as arguments to the standard `fseek` function:

    #define SEEK_SET 0
    #define SEEK_CUR 1
    #define SEEK_END 2

### Flag Variables Taking Their Values with Symbolic Constants

In C programs, flag variables also often take their values with symbolic constants:

    pos_flag = ON;
    validity_flag = INVALID;

The `case` expressions in the `switch` control statement are also often formed with symbolic constants. We will examine this topic in the `switch` control statement section.

### Modifying the Program via Symbolic Constants

In situations where a literal is used in many places within the program, a replacement operation for this literal can be done from a single location. Thus, the program in question can be written dependent on a symbolic constant, and then recompiled and run for different parametric values by changing the symbolic constant. For example, let's assume we are writing a game program based on the user guessing a number with a specific number of guesses. Let the player have 10 guesses. In this case, the value 10 is used in many places in the source code, right? Suppose it is later desired to increase the player's number of guesses to 20 in the game program. The literals 10, which represent the player's number of guesses, must be changed to 20 in the source code. Performing this replacement operation individually by the programmer is both difficult and error-prone. Not every literal 10 used in the source code may represent the player's guess limit. However, if a symbolic constant is defined instead of the value representing the player's limit:

    #define NO_OF_GUESS 10

and the program is written using this symbolic constant, the values 10 throughout the entire program can be easily converted to the value 20 by making a change in this symbolic constant definition.

### Symbolic Constants Used Instead of Floating-Point Literals

The use of symbolic constants prevents possible inconsistencies and typographical errors, especially when using floating-point literals.

For example, let's assume that the number $\pi$ is frequently used in a program that performs mathematical calculations. The symbolic constant:

    #define PI 3.14159

can be used instead of the number $\pi$. If the number $\pi$ is written as a literal each time, the same value may not be written each time. For example, while the literal $3.14159$ is written in one place in the source code, a value like $3.15159$ might be accidentally written at another point in the source code. The compiler program has no mechanism to issue a logical warning message for such inconsistencies. The use of symbolic constants eliminates such errors.

Most compilers also define many mathematical constants in the `math.h` header file.

### Symbolic Constants Defined for Portability Purposes

Some symbolic constants are defined both to provide portability and to create a common interface. Standard symbolic constants carrying the boundary values of the integer types used on the system are defined in the `limits.h` standard header file:

| Symbolic Constant | Smallest/Largest Possible Value | Meaning |
| :--- | :--- | :--- |
| `CHAR_BIT` | 8 | Number of bits in the `char` type |
| `SCHAR_MIN` | -127 | Smallest value of `signed char` type |
| `SCHAR_MAX` | 127 | Largest value of `signed char` type |
| `UCHAR_MAX` | 255 | Largest value of `unsigned char` type |
| `SHRT_MIN` | -32,767 | Smallest value of `signed short int` type |
| `SHRT_MAX` | 32,767 | Largest value of `signed short int` type |
| `USHRT_MAX` | 65,535 | Largest value of `unsigned short` type |
| `INT_MIN` | -32,767 (varies) | Smallest value of `signed int` type |
| `INT_MAX` | 32,767 (varies) | Largest value of `signed int` type |
| `UINT_MAX` | 65,535 (varies) | Largest value of `unsigned int` type |
| `LONG_MIN` | -2,147,483,648 | Smallest value of `signed long int` type |
| `LONG_MAX` | 2,147,483,647 | Largest value of `signed long int` type |
| `ULONG_MAX` | 4,294,967,295 | Largest value of `unsigned long int` type |
| `LLONG_MIN` | -9,233,372,036,854,775,808 | Smallest value of `signed long long int` type (C99) |
| `LLONG_MAX` | 9,233,372,036,854,775,807 | Largest value of `signed long long int` type (C99) |
| `ULLONG_MAX` | 18,446,744,073,709,551,615 | Largest value of `unsigned long long int` type (C99) |
| `CHAR_MIN` | `SCHAR_MIN` or 0 | Smallest value of `char` type. If system's `char` is signed, value is `SCHAR_MIN`. If unsigned, value is 0. |
| `CHAR_MAX` | `SCHAR_MAX` or `UCHAR_MAX` | Largest value of `char` type. If system's `char` is signed, value is `SCHAR_MAX`. If unsigned, value is `UCHAR_MAX`. |
| `MB_LEN_MAX` | 1 | Maximum number of bytes a multi-byte character can have. (In locales where this type is supported) |

### Locations of Symbolic Constant Definitions

The `#define` directive can be used anywhere in the source code. However, it is effective in the region from where it is defined until the end of the source code. The preprocessor program does not have a concept of scope directly. A symbolic constant defined at the beginning of a block is effective not only within that block but everywhere from where it is defined until the end of the source code.

Symbolic constants are sometimes defined inside the header file and sometimes inside the source file.

### Common Mistakes in Using Symbolic Constants

A typical mistake is using the equals sign (`=`) unnecessarily in the symbolic constant definition:

    #define N = 100

In this case, the preprocessor pastes the text:

    = 100

where it sees `N`. For example, let's assume a definition like:

    int a[N];

is made. The preprocessor converts this definition to:

    int a[= 100];

which is invalid.

Another typical mistake is accidentally terminating the `#define` preprocessor directive line with a semicolon (`;`):

    #define N 100;

In this case, the preprocessor places:

    100;

where it sees `N`. The definition:

    int a[N];

becomes:

    int a[100;];

This definition is invalid. In such errors, the compiler usually issues as many error messages as the symbolic constant is used.

Care must be taken when defining symbolic constants. It must be remembered that the preprocessor module does not perform any arithmetic operations, but only a textual replacement:

    #define MAX 10 + 20
    int main()
    {
        int result;
        result = MAX * 2;
        printf("%d\n", result);
        return 0;
    }

In the example above, the value 50 is assigned to the variable `result`, not 60. However, if the preprocessor directive had been written as:

    #define MAX (10 + 20)

the value 60 would have been assigned to the variable `result`.

### Simple Macros for Standard C Operators

Since some character sets, such as ISO 646, in which the source text is written do not have the characters `&`, `|`, and `^`, problems arise in writing some C operators.

In the `iso646` header file, which was later added to the language by an addition to the C89 standards, simple macros that are converted to some standard C operators are defined. Below is a list of these macros:

| Macro | Replacement |
| :--- | :--- |
| `#define and` | `&&` |
| `#define and_eq` | `&=` |
| `#define bitand` | `&` |
| `#define bitor` | `|` |
| `#define compl` | `~` |
| `#define not` | `!` |
| `#define not_eq` | `!=` |
| `#define or` | `||` |
| `#define or_eq` | `|=` |
| `#define xor` | `^` |
| `#define xor_eq` | `^=` |