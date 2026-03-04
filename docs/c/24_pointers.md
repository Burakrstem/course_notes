# Pointers

In the code written in the first section, the **values** of objects were used. For example, the values of variables were sent to functions as arguments. Functions returned the values of objects. With **"pointers,"** the **addresses** of objects will now be focused on, in addition to the values of the objects.

The address of an object is information that indicates the **location** of that object in memory.

Indeed, much code written in the C language uses information that is the address of objects. To achieve certain software goals, the addresses of objects are stored in variables, sent to functions, and obtained as return values from functions via function calls.

Since every object occupies space in memory, it has a specific address. The addresses of objects are collectively determined by the compiler and the operating system that loads the program on most systems. The addresses of objects cannot be known definitely before the program is loaded and cannot be determined by the programmer beforehand. The programmer can only learn the addresses of objects during the program's **runtime**. For example:

    char ch;

A compiler that encounters a definition like this allocates 1 byte of space in memory for the variable `ch`. The specific byte address that the compiler will allocate for the variable `ch` cannot be known beforehand. This can only be learned during the program's runtime. Suppose the variable `ch` is a local variable in the example above. The `ch` variable is created when the code of the block in which it is defined begins execution, and its lifespan ends when the execution of the block's code finishes.

The figure below is drawn assuming the variable `ch` is at address `1A02`:

    | 1A00 | 1A01 | ch | 1A03 | 1A04 |
    | ---- | ---- |----| ---- | ---- |
    
If the defined object is longer than 1 byte, then how is the address of the object determined?

    int b;

The addresses of objects longer than 1 byte are specified by the addresses of their **first byte**. In the example above, the address of the variable $b$ is `1C02`. Since it is already known that the variable $b$ is of type `int`, it is clear that its other part will be at address `1C03` (assuming an `int` type object occupies 2 bytes on the relevant system).

Similarly, if the memory layout of the `long` type variable $y$ is assumed to be as follows, its address can be said to be `1F02`:

Let an `int` type variable be defined:

    int x;

For the address of such an object to be used programmatically, this information must be expressed, stored in memory, and interpreted in some way.

The information that is the address of the variable $x$ must also have a **type**. Such a type information is **derived** from the object's own type and is denoted in C in the following form:

    (int *)

The type of information that can be the address of a `double` type object is also denoted as:

    (double *)

Let $x$ be an object of type $T$. The type of information that is the address of the object $x$ is accepted to be the **$(T *)$ type**.

## Pointer Objects

To achieve certain software goals, the addresses of objects also need to be stored in variables. Just as an integer value is stored in a variable of an integer type, an address information is stored in a variable whose type is an address information type.

    int x;

The type of the object $x$ defined above is the `int` type. Since the information that is the address of such an object is of the **(int \*)** type, this information should naturally be stored in a variable of the **int \*** type.

### Declarations of Pointer Variables

    int *ptr;

A variable named `ptr` is defined above. The `ptr` variable is a variable that can hold the information which is the address of an `int` type object. The value of the `ptr` variable is the information that is the address of an `int` type object. Information that can be the address of an `int` type object must be assigned to the `ptr` variable.

Similarly, to store the information that is the address of a `double` type object:

    double *dp;

a variable like this can be defined.

**Pointer variables** are objects used to store address information and perform operations related to addresses. The values of pointer variables are addresses.

The general form of pointer variable declarations is as follows:

    <type> *<pointer name>;

* `<type>` is the type of the pointer (the address inside it). It can be any type such as `char`, `int`, `float`, etc.
* The `*` token here is part of the type information.

Example pointer declarations are given below:

    float *f;
    char *ps;
    int *dizi;
    unsigned long *Pdword;

Pointer declarations are distinguished from declarations for other types by the `*` token.

In the declaration:

    char s;

$s$ is a variable of type `char`, while in the declaration:

    char *ps;

$ps$ is a pointer of type `char`, i.e., an object whose type is `char *`. The address of a `char` type object must be assigned to this variable. The following information can be deduced from such a declaration:

$ps$ is an object, i.e., it occupies a place in memory. The 1s and 0s in the space allocated in memory for the object $ps$ are interpreted as the numerical value of the address of a `char` type object.

The `*` in the definition is **not** an operator. It merely denotes that the object is a pointer, as a syntax rule.

Pointer declarations can be made alongside normal declarations. For example:

    int *p, a;

Here, $p$ is a pointer variable of type `int *`, but $a$ is a normal variable of type `int`.

If more than one pointer of the same type is to be declared, the declaration of each pointer variable must be made with the `*` token, separated by the comma token.

    char *p1, *p2;

In the declaration above, $p1$ and $p2$ are pointer variables of type `char *`.

    double *p1, *p2, d, a[20];

In the declaration above, $p1$ and $p2$ are pointer variables of type `double *`, $d$ is a variable of type `double`, and $a$ is an array of 20 elements of type `double`.

### Sizes of Pointer Variables

A compiler that encounters the definition of a pointer object allocates space in memory for that pointer variable, just as it does for other definitions. The size of the space that compilers allocate for pointers is hardware-dependent and can vary from system to system. In 32-bit systems (e.g., UNIX and Windows systems after 3.1), pointer variables are **4 bytes** long. In compilers running on the 8086 architecture and under DOS, pointer variables can be 2 bytes or 4 bytes. In DOS, 2-byte pointers are called **near pointers**, and 4-byte pointers are called **far pointers**.

The sizes of pointers are **independent of their type**.

Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        char *cp, ch;
        int *ip, i;
        double *dp, d;
        printf("sizeof(ch) = %u\n", sizeof(ch));
        printf("sizeof(i) = %u\n", sizeof(i));
        printf("sizeof(d) = %u\n", sizeof(d));
        printf("sizeof(cp) = %u\n", sizeof(cp));
        printf("sizeof(ip) = %u\n", sizeof(ip));
        printf("sizeof(dp) = %u\n", sizeof(dp));
        printf("sizeof(char *) = %u\n", sizeof(char *));
        printf("sizeof(int *) = %u\n", sizeof(int *));
        printf("sizeof(double *) = %u\n", sizeof(double *));
        return 0;
    }

In the program above, you see that objects of type `char`, `int`, `double` as well as objects of type `char *`, `int *`, and `double *` are defined. Then, the `sizeof` values of these objects are printed to the screen with the `printf` function. Regardless of the `sizeof` value of an object of type $T$, the `sizeof` value of an object of type $T*$ is always the same, right? When the program above is compiled and run for the UNIX operating system, the screen output is as follows:

    sizeof(ch) = 1
    sizeof(i) = 4
    sizeof(d) = 8
    sizeof(cp) = 4
    sizeof(ip) = 4
    sizeof(dp) = 4
    sizeof(char *) = 4
    sizeof(int *) = 4
    sizeof(double *) = 4

### Expressions That are Address Information

Some expressions are of the **address type**. That is, the value of these expressions is an address. An expression whose type is an address, i.e., an address value, must be assigned to a pointer variable.

A variable defined as:

    int *ptr;

is a variable that will store the information that is the address of an `int` type variable. How can such address information be assigned to the `ptr` variable?

### Address Literals

`1200` is an integer literal of type `int`. Such a literal can be assigned to an `int` type object, for example:

    int x = 1200;

An integer literal can be converted to address information through type conversion:

    (int *)1200

The type of the expression above is the **(int \*) type**. Such an expression is information that can be the address of an `int` type object. The `int` type literal `1200` has been converted to a type that can be the address of an `int` type object using the type cast operator. The hexadecimal number system is conventionally used when writing address literals:

    (double *)0x1AC4

The expression above is information that can be the address of a `double` type object. You see that the hexadecimal number system is used in writing the integer part of the address information.

### Type Compatibility with Pointers

An address information of the **same type** must be placed in a pointer variable. For example:

    int *p;
    p = 100;

Here, a value that is not an address is assigned to the pointer variable $p$. Such an assignment is considered incorrect. Almost all compilers report this situation with a logical warning message. This situation will be discussed in detail later.

> \[Such an assignment is invalid in the C++ language.]

    int *p;
    p = (char *) 0x1FC0;

Here, address information of type `char *` is assigned to the pointer $p$ of type `int *`. This incorrect situation is also flagged by most compilers with a logical warning message.

> \[C++ compilers also reject object file generation in such an assignment situation by giving a syntax error message.]

    int *p;
    p = (int *) 0x1FC4; /* a valid and appropriate assignment */

When address information is assigned to a pointer, the numerical component of the address is placed inside the pointer.

    int *p;
    p = (int *) 0x1FC4;

Here, the numerical value `0x1FC4` is placed in the location in memory where the pointer variable $p$ is stored.

Since pointer variables carry address information, assigning the value of another pointer variable of the same type to a pointer is also perfectly appropriate.

    int *p, *q;
    p = (int *) 0x1AA0;
    q = p;

With the assignment above, the value of the pointer $p$ is assigned to the pointer $q$. That is, after this assignment statement, the address `(int *) 0x1AA0` is also contained within the pointer $q$.

When a definition like:

    int k;

is made, the variable $k$ is of type `int`. The value inside it is interpreted as an `int` type value.

An expression consisting of a single literal, such as:

    20

is also of type `int`, because 20 is an `int` type literal. In other words, the type of the expression $k$ and the expression 20 are the same. The type of both expressions is the `int` type. However, the expression $k$ is an Lvalue (denoting an object), while the expression 20 is a non-Lvalue expression, i.e., an Rvalue.

Similarly, the type of an expression consisting of an address literal, such as:

    (int *) 0x1A00

is also an address of type `int`, i.e., an expression of type **(int \*)**. However, this expression is also not an Lvalue.

As seen, pointer variables are objects of a specific address type. That is, they are variables whose values are addresses.