# ✍️ Type Name Declarations and the `typedef` Specifier

In the C language, new names can be given to a type already known by the compiler, which can substitute for that type in every respect. This is provided by a declaration statement using the **`typedef`** keyword.

The general form of a `typedef` declaration is as follows:

    typedef <type> <new name>;

Example:

    typedef unsigned int UINT;

After this declaration, the name `UINT` is treated by the compiler as a **new name for the `unsigned int` type**. That is, where the `typedef` declaration is visible in the source code, when the name `UINT` is used, the compiler interprets it as the `unsigned int` type.

    UINT x, y, z;

In the declaration above, the variables $x$, $y$, and $z$ are now defined as being of type `unsigned int`.

After the `typedef` declaration, the name `UINT` can now be used wherever a type-specifying name is required:

    printf("%zu\n", sizeof(UINT));

Creating a new type name with a `typedef` declaration does not prevent the use of the previous name for that type. That is, there is no obstacle to making a declaration like:

    unsigned int result;

after the `typedef` declaration shown in the example above.

Undoubtedly, the same task could also be done with the `#define` preprocessor directive:

    #define UINT unsigned int

However, a `typedef` declaration is processed by the compiler, while names defined with the `#define` preprocessor directive concern the preprocessor program. That is, after the use of the preprocessor directive above, the compiler does not see the name `UINT`. By the time it is the compiler's turn, the tokens `unsigned int` have replaced the name `UINT`.

Easier-to-understand type names can be given to hard-to-perceive type names with `typedef` declarations. The simple rule given below provides convenience for `typedef` declarations:

The `typedef` keyword can precede any type declaration. When the `typedef` keyword precedes a declaration, the names that would have been variable names if `typedef` had not been used become the type names of the relevant type when the `typedef` keyword is added. For example:

    char *pstr;

The declaration above defines $pstr$ as a variable of type `char *`.

    typedef char *pstr;

The statement above is a `typedef` declaration. Now, $pstr$ is treated as a **type name** by the compiler. $pstr$ is a valid type, a synonym for a `char *` address type. That is, after the `typedef` declaration above:

    pstr p;

a definition like this can be made. This definition means the same as:

    char *p;

The benefit obtained with a `typedef` declaration cannot always be achieved with the `#define` preprocessor directive:

When a preprocessor name definition like:

    #define pstr char*

is made, the preprocessor places the tokens `char *` where it sees the name `pstr`. There is no error in writing a declaration like:

    pstr str;

instead of:

    char *str;

When the preprocessor places `char *` in place of `pstr`, the code sent to the compiler becomes:

    char *str

Now suppose a declaration like the following is intended to be made using the `#define` preprocessor directive:

    char *p1, *p2, *p3;

When:

    pstr p1, p2, p3;

is written, the code given to the compiler after the preprocessor performs the replacement operation changes to the following form:

    char *p1, p2, p3;

This definition is **not equivalent** to the intended definition. In the declaration above, only $p1$ is a pointer variable. $p2$ and $p3$ are not pointer variables; they are variables of type `char`.

A new type name declaration can also be made for an array:

    char array_name[20];

The statement above defines a 20-element `char` array named `array_name`.

    typedef char array_name[20];

The statement above is a declaration. With this declaration, `array_name` is now the **type name** for 20-element `char` arrays. After this `typedef` declaration, if a definition like:

    array_name a, b, c;

is made, $a$, $b$, and $c$ are now all 20-element `char` arrays.

More than one type name can be created with a single `typedef` declaration:

    typedef unsigned int WORD, UINT;

After the declaration statement above, both `WORD` and `UINT` are new type names replacing the `unsigned int` type:

    WORD x, y;
    UINT k, l;

The variables $x$, $y$, $k$, and $l$ are now of type `unsigned int`.

The type name declaration for a 10-element `char` pointer array can be made as follows:

    typedef char *PSTRARRAY[10];

After this declaration statement:

    PSTRARRAY s;

has the exact same meaning as:

    char *s[10];

A type name can also be used in the declaration of other type names:

    typedef unsigned int WORD;
    typedef WORD UINT;

The newly created type names are chosen either entirely in uppercase or only their first letter is capitalized for readability.

### Using `typedef` Declarations for Structures

A new type is created with a structure declaration. After this type is first introduced to the compiler, variables related to this type can be defined:

    struct Data {
        int a, b, c;
    };

A new data type is created with the declaration above. The name of this data type in the C language is **`struct Data`**. The name of the type is not `Data`. That is, if an object of this data type is to be defined, `struct Data` must be written as the type name.

> \[In the C++ language, structure tags are also the name of the type. They are accepted by the compiler as the name of this type even when used without the `struct` keyword.]

After the declaration above, if a definition were to be made, for example:

    struct Data d;

it should be made in this form. In the C language, writing this definition in the form:

    Data d;

is invalid. However, this situation is valid in the C++ language.

To eliminate the necessity of using the `struct` keyword before the structure name in structure object definitions, programmers create new type names related to the structure types they have declared with a `typedef` declaration.

Creating a new type name related to a structure type can be done in three separate ways.

1.  **First, the structure declaration is made. Then, a separate `typedef` declaration is made for the declared structure type:**

    ```c
    struct tagPerson {
        char name[30];
        int no;
    };
    typedef struct tagPerson Person;
    
    Person per = {"Necati Ergin", 123}; // Definition using the new type name
    ```

    In the example above, a type named `struct tagPerson` is created first, and then the name `Person` is given as a new name to the `struct tagPerson` type with a `typedef` declaration. After the `typedef` declaration, both `struct tagPerson` and `Person` names can be used as type names.

2.  **The `typedef` declaration and the structure declaration can be combined into a single declaration form:**

    ```c
    typedef struct tagPerson {
        char name[30];
        int no;
    } Person; // Person is the typedef name
    
    Person per;
    ```

    Recall the rule given earlier: If the `typedef` keyword were not present at the beginning of this declaration, the name `Person` would be the name of an object of type `struct tagPerson`, right? In the example above, a structure whose name is `struct tagPerson` is declared, and the name `Person` is also given as a new name to this structure with a `typedef` declaration. After the relevant declaration, both `struct tagPerson` and `Person` names can be used as type names.

3.  **A structure declaration without a structure tag can be combined with a `typedef` declaration:**

    ```c
    typedef struct { // No structure tag
        char name[30];
        int no;
    } Person; // Person is the typedef name
    
    Person y;
    ```

    The type created in the example above has only one name. This name is `Person`. When this type is desired to be used, the `struct` keyword can no longer be used.

Instead of finding different names for structure names (structure tags) and the type names to be created with a `typedef` declaration, most programmers establish a relationship between them using a few characters. One of the frequently used patterns is to prefix the structure name with an underscore character to separate it from the type name:

    typedef struct _Employee {
        int no;
        char name[30];
        double fee;
    } Employee;

Undoubtedly, a declaration like the following would also not cause an error:

    typedef struct Employee {
        int no;
        char name[30];
        double fee;
    } Employee;

The old name of the type is not `Employee`, but `struct Employee`. That is, the name `Employee` is given to the `struct Employee` type with a `typedef` declaration. This situation does not create a problem.

In `typedef` declarations related to Windows API programming, a pattern like the following is also used:

    typedef struct tagEmployee {
        int no;
        char name[30];
        double fee;
    } Employee;

The structure name is started with the prefix `tag`, and the prefix `tag` is removed in the chosen `typedef` name.

Instead of giving a name to the structure type itself, a new name can be given to the address type related to that structure. Examine the following example:

    struct {
        int a, b, c;
    } *Hdata; // Hdata is a pointer variable, not a type name!

The declaration above is incorrect; $\text{Hdata}$ is a pointer variable.

If the intention was to define a new type name for the pointer:

    typedef struct {
        int a, b, c;
    } *Hdata; // INVALID: typedef applies to the variable list

    // Correct way to define a pointer type name for an anonymous struct:
    typedef struct {
        int a, b, c;
    } Data_t, *DataPtr_t; 

Assuming the intention was to create a pointer type, the $\text{sizeof}(\text{Hdata})$ expression in Unix/Windows systems would give the size of the pointer (4 or 8), and $\text{sizeof}(\text{*Hdata})$ would give the size of the structure itself (e.g., 12).

### Some `typedef` Declarations Found in Standard Header Files

In the declarations of some standard functions, some predetermined `typedef` names are used instead of directly using a native data type. Since native types can have different lengths from system to system, using a `typedef` name in the interface of some functions instead of native type names provides greater flexibility to the writers of the compiler. For example, the declaration of the standard `malloc` function in the `stdlib.h` header file is as follows:

    void *malloc(size_t ntypes);

You see that the name **`size_t`** is used as a type name in this declaration. The declaration of this type is made in the `stddef.h`, `stdio.h`, and `stdlib.h` header files in most compilers as follows:

    typedef unsigned int size_t; // Or unsigned long int

This type is actually a type whose true nature is left to the writers of the compilers. Compilers give the name `size_t` to one of the unsigned integer types with `typedef` declarations in the relevant header files. According to the standards, the `size_t` type is the type of the value produced by the `sizeof` operator. The `size_t` type is valid in the declarations of many functions in the ANSI standards. For example, the actual declaration of the `strlen` function in the `string.h` header file is made as:

    size_t strlen(const char *);

That is, the parameter variable of the `malloc` function or the return value of the `strlen` function is of type `size_t`. The actual nature of this type is left to the writers of the compilers. However, the `size_t` type is determined as the `typedef` name for the `unsigned int` type in almost all compilers.

Other type names, whose actual nature is left to the compiler (i.e., the compiler writers will make `typedef` declarations in the relevant header files) are also defined by the C standards, such as the `size_t` type. Some of these types are:

* **`time_t`**: The type of the return value of the standard `time` function. In the `time.h` header file, the compiler writers give this name to any basic data type with a `typedef` declaration. Although not mandatory, `time_t` is chosen as the `typedef` name for the `long` type in almost all compilers.
* **`clock_t`**: The type of the return value of the standard `clock` function. In the `time.h` header file, the compiler writers give this name to any basic data type with a `typedef` declaration. It is chosen as the `typedef` name for the `long` type in almost all compilers.
* **`ptrdiff_t`**: You know that an integer is obtained by subtracting one address information from another address information. The difference between two addresses is of type `ptrdiff_t`. Indeed, the name of this type comes from the words "pointer difference." This type must be one of the signed integer types. It is chosen as the `typedef` name for the `int` type in almost all compilers.
* **`fpos_t`**: The type of the pointers that are parameter variables of the `fgetpos` and `fsetpos` functions declared in the `stdio.h` header file.
* **`wchar_t`**: The declaration of this type is made in the `stdlib.h` and `stddef.h` header files. It is a type that can represent the largest extended character set in the locale supported by the system. For example, if all values of the extended character set can be expressed in a two-byte area, the `wchar_t` type can be the `typedef` name for the `unsigned short int` type. The name `wchar_t` comes from the words "wide character." Points such as wide characters, wide character literals, and multi-byte characters will be addressed in detail in the section on "Localization."
* **`div_t` and `ldiv_t`**: The declarations of these types are made in the `stdlib.h` header file. `div_t` is the structure type that is the return value of the standard `div` function declared in `stdlib.h`. The `ldiv_t` type is also the structure type that is the return value of the function named `ldiv` declared in the `stdlib.h` header file.

### Scope of Type Names Declared with `typedef`

Scope rules also apply to `typedef` declarations. A `typedef` name defined within a block is not known outside that block.

    void func()
    {
        typedef int WORD;
    }
    void foo()
    {
        WORD x; /* Invalid */ // WORD is not known outside func
    }

The statement `WORD x;` is invalid in the program above. This is because the type `WORD` is a data type known only within the main block of the `func` function. It is not known outside this block.

In the C language, declarations made within a block must be made at the beginning of the blocks. New type name declarations made with `typedef` within a block must also be made at the beginning of the blocks.

However, `typedef` declarations are almost always made at the **global level**. In applications, `typedef` declarations are generally made either at the beginning of the source file or within header files. This is because `typedef` names often belong to the interface of a module that provides services to the outside.

The same `typedef` name cannot be declared as the new name for two different types:

    typedef int WORD;
    /*...*/
    typedef long WORD; /* Invalid! (Redefinition of different type) */

### What is the Purpose of `typedef` Declarations?

`typedef` declarations can be made to **increase readability**. If some types are given names suitable for their purpose of use, the source code is easier to read and understand. For example, the `char` type is generally a type to which character literals are assigned. If the `char` type is to be used only as a one-byte data type, i.e., not used in string operations, a type definition like the following is appropriate:

    typedef char BYTE;
    /*...*/
    BYTE x;

In the C89 standards, the `bool` type is not a native data type. However, the `int` type can be given the name `bool` with a `typedef` declaration:

    typedef int bool;

`typedef` declarations provide **ease of writing**. Many complex type names can be easily written using a `typedef` declaration. The person reading the program encounters a simple name representing a complex type instead of the complex tokens corresponding to the type information. Below, a new name is given to a type related to a function address with a `typedef` declaration, and then an object of this type is defined:

    typedef struct Person *(*Fpper)(struct Person *, int); // Fpper is a function pointer type
    /*...*/
    Fpper fptr;

3. `typedef` declarations are also sometimes used to **increase portability**. With the use of `typedef` declarations, even if the data structures related to the written functions change, the source program does not need to be changed. For example, let the return values of some functions in a library be of type `unsigned int`. Suppose the type of the return values of these functions is changed to the `unsigned long` type in subsequent implementations. If the programmer has used `typedef` declarations in the code related to these functions, they do not need to change the code they wrote previously; they only need to change the `typedef` declarations. For example:

    `typedef unsigned int HANDLE;`
    `/***/`
    `HANDLE hnd;`
    `hnd = GetHandle();`

Here, let the type of the return value of the `GetHandle` function be changed to `unsigned long` in subsequent implementations. Only changing the `typedef` declaration is sufficient:

    `typedef unsigned long HANDLE;`

Suppose variables to be used for counting, whose values can range between 0 and 50000, are desired to be used in a C program. The `long int` type can be chosen for this purpose because the `long int` type can hold values up to $2,147,483,647$ in Windows or Unix systems. However, using the `int` type instead of the `long int` type can be preferred for faster arithmetic operations. Additionally, variables of type `int` may occupy less space in memory on some systems.

Instead of using the `int` type, a new type name can be created for this purpose:

    typedef int COUNTER;
    COUNTER a, b, c;

If the source code is compiled on a system where the `int` type is 16 bits long, the `typedef` declaration can be changed:

    typedef long COUNTER;

It should not be thought that all problems related to portability are solved with this technique. For example, a variable of type `COUNTER` might have been used as the type of the argument expression in calls to `printf` or `scanf` functions:

    #include <stdio.h>
    typedef int COUNTER;
    int main()
    {
        COUNTER a, b, c;
        /***/
        scanf("%d%d%d", &a, &b. &c);
        /***/
        printf("%d %d %d", a, b, c);
        /***/
        return 0;
    }

In the statements above, the variables $a$, $b$, and $c$ are defined as being of type `COUNTER`, i.e., of type `int`. The format specifier `%d` is also chosen for these variables in the calls to the `printf` and `scanf` functions. However, if the `COUNTER` type is changed to the `long` type, the format specifiers used to print variables of this type in the `printf` and `scanf` functions must also be changed to **`%ld`** instead of `%d`.

### Naming Address Types with `typedef`

There is a point to be noted when giving new names to pointer types with a `typedef` declaration. As covered in the section on type qualifiers, when a definition like the following is made in the C language:

    const int *ptr;

$ptr$ is a pointer to a `const` location. That is, the object at the location pointed to by the variable $ptr$ cannot be changed:

    *ptr = 10; // Invalid assignment

However, if the definition is made in the form:

    int *const ptr;

$ptr$ is a pointer that is itself `const`. The value of the object pointed to by the pointer $ptr$ can be changed, but the address inside the pointer $ptr$ cannot be changed, i.e., an assignment like:

    ptr = (int *) 0x1F00; // Invalid assignment

is invalid.

After a declaration like:

    typedef int *IPTR;

when a definition like:

    const IPTR p;

is made, the value of the pointer $p$ cannot be changed, but the value of the object at the location pointed to by the pointer $p$ can be changed. That is, an assignment can be made to the object `*p`. In other words, the statement:

    const IPTR ptr;

is equivalent to the statement:

    int *const ptr;

### `typedef` Names Defined in `windows.h`

`typedef` declarations are frequently used in writing C or C++ programs that will run under the Windows operating system. The `windows.h` header file contains new names given to most basic data types with `typedef` declarations. The `windows.h` header file must be included in the source code for Windows API programming. This file contains declarations of API functions, various structure declarations, `typedef` names, and important symbolic constants.

#### `typedef` Names Defined in `windows.h`

* `typedef int BOOL;`
    Two symbolic constants related to this type are also defined.
    `#define FALSE 0`
    `#define TRUE 1`
    The `BOOL` type is used especially in the return values of functions. This means that the function returns a non-zero value if successful and a zero value if unsuccessful. Success checking should not be done by comparing with the value 1.

* The following `typedef` names symbolize unsigned 1-byte, 2-byte, and 4-byte integers.
    `typedef unsigned char BYTE;`
    `typedef unsigned short WORD;`
    `typedef unsigned long int DWORD;`
    `typedef unsigned int UINT;`

* `typedef` names related to pointers start with the letter **P**. **LP** is used as a prefix to specify far pointers. The concepts of near and far pointers existed in Win16 systems. At that time, pointers prefixed with P represented near pointers, and pointers prefixed with LP represented far pointers. However, the concepts of near and far pointers do not exist in Win32 systems. In this case, there is no difference between pointers prefixed with P and pointers prefixed with LP. However, `typedef` names prefixed with LP are still used due to the habit from Win16. For compatibility with Win16 programs, the words `near` and `far` are eliminated in `windows.h` as follows:
    `#define far`
    `#define near`
    `typedef char near *PSTR;`
    `typedef char far *LPSTR;`
    `PSTR` and `LPSTR` mean exactly the same thing in Win32 systems and specify the `char *` type.
    `typedef char *PSTR;`
    `typedef char *LPSTR;`

* `const` in pointers is indicated by the C suffix after P or LP. For example:
    `typedef const char *PCSTR;`
    `typedef const char *LPCSTR;`

* All native types in C also have their uppercase normal, address, and `const` address forms.
    `typedef long LONG;`
    `typedef int INT;`
    `typedef char CHAR;`

* Many `typedef` names starting with H, used as handles, exist in Windows programming. All of these `typedef` names are of type `void *`. For example:
    `typedef void *HWND;`
    `typedef void *HICON;`