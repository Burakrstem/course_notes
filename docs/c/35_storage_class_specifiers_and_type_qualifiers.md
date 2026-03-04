# 🏷️ Storage Class Specifiers and Type Qualifiers

**Storage class specifiers** are keywords used during declarations that provide information to compilers about the properties of objects.

The specifiers used in C are:

* `auto`, `register`, `static`, `extern`, and `typedef`.

**Type qualifiers** provide information about whether the values inside the objects can be modified.

The type qualifiers are:

* `const`, `volatile`.

Storage class specifiers and type qualifiers are C keywords.

## 📝 Declaration with Storage Class Specifiers

The order of arrangement of the storage class specifier, type qualifier, or type-expressing keywords can be any:

    auto const unsigned long int a;
    const auto unsigned long int a;
    unsigned long int auto const a;
    int const long auto unsigned a;

All the declarations above are valid. However, writing the storage class specifier word earlier is recommended for readability.

If a declaration is used without type information (specifier or qualifier), the default type of **`int`** is assumed for the declaration.

    register int a;

is equivalent to the declaration:

    register a;

However, such a declaration is not recommended for readability.

### The `auto` Specifier

The `auto` specifier is a storage class specifier that can only be used for **local variables**. Using the `auto` specifier in the declaration of global variables or function parameters is invalid.

This keyword indicates that the object will disappear after its scope ends, and the memory space it occupies will no longer be valid. Local variables have **automatic storage duration**. That is, they are created when the code for the block in which they are defined begins execution, and they are destroyed after the execution of the block ends. The `auto` specifier is used to emphasize this situation. A local variable is treated as `auto` by default unless another storage class specifier is used. Thus, the use of the `auto` storage class specifier is redundant:

    {
        auto int a; // 'auto' is redundant
        float b;    // 'b' is implicitly auto float
    }

The `auto` storage class specifier is not used with global variables or parameter variables. For example:

    auto int g; /* Invalid! */
    function(auto int x) /* Invalid! */
    {
        /***/
    }

The `auto` keyword was conceived to maintain compatibility in some microprocessors. It has no meaningful use in modern systems.

### The `register` Specifier

The `register` specifier is a keyword that communicates the request to the compiler that the variable should be stored **"in CPU registers rather than in memory."** Storing variables directly in registers instead of memory speeds up the program's execution.

What is a **register**? Registers are buffer memory regions located inside the **CPU (Central Processing Unit)**. The unit that performs arithmetic and logical operations inside the CPU is related to registers and memory. In general, both operands of the arithmetic and logical operations performed by the CPU cannot be memory-related. For example, suppose two variables in memory named `number1` and `number2` are to be added, and the resulting value is to be written to another memory region named `number3`. This corresponds to the C operation:

    number3 = number1 + number2;

The CPU can perform this operation only in 3 steps:

1.  **Step 1**: `number1` is first fetched from memory into one of the CPU registers.
    `MOV reg, number1`
2.  **Step 2**: The register and `number2` are added.
    `ADD reg, number2`
3.  **Step 3**: The sum is written to the memory area specified by `number3`.
    `MOV number3, reg`

Writing to memory and reading from memory are slower operations than writing to and reading from registers. This is because a machine cycle is required for memory access.

The `register` specifier only transmits a **request** to the compiler. That is, there is no guarantee that a variable declared with the `register` specifier will be stored in a register. Compilers may not comply with such a request. CPU registers are limited in number, regardless of the system in question. For this reason, even if more than a few variables are defined with the `register` specifier, they may not be stored in registers. C compilers generally do not give error or warning messages for variables they cannot store in registers. That is, when compilers encounter variables with more `register` specifiers than the number of available registers, they disregard the `register` specifiers related to those variables.

`register` specifiers can only be used with **local variables or parameter variables**. They cannot be used with global variables. Examples:

    register int g; /* Invalid! (Global) */
    int func (register int y) /* Valid (Parameter) */
    {
        register int x; /* Valid (Local) */
    }

The maximum number of variables that can be stored in registers depends on the computer hardware and compilers. Additionally, types whose length is greater than the integer (`int`) type generally cannot be stored in registers. In these situations, error or warning messages should not be expected from the compilers.

Consequently, the `register` specifier should only be used for a few variables in very special and short code snippets where speed is critical. Most modern compilers perform optimization on the code optionally, storing some variables in registers. This situation often makes the use of the `register` keyword unnecessary.

### The `static` Specifier

The `static` specifier can only be used in the declaration of **local or global variables**. This specifier cannot be used in the declaration of parameter variables.

Using the `static` keyword in the declaration of global and local variables has different meanings.

#### Using the `static` Keyword in the Declaration of Local Variables

Local variables or local arrays defined with the `static` storage class specifier remain in memory throughout the program's execution. In other words, the `static` keyword promotes the lifespan of local variables from automatic storage duration to **static storage duration**. Static local variables are created when the program starts running, just like global variables, and are held in memory until the program finishes executing.

Static local variables are used after they are initialized by the programmer. The initialization operation is performed by the compiler at **compile time**, not during the program's execution. The compiler generates machine code that will lead to memory allocation. The space in memory for the static local variable is allocated during the program's loading. Space is not actually allocated in memory at compile time. Machine code to perform the memory allocation is generated. Static local variables are loaded into memory along with their initial values.

Compile and run the following program:

    #include<stdio.h>
    void func1()
    {
        int x = 5; // Automatic storage duration. Initialized every call.
        printf("x = %d\n", x);
        x++;
    }
    void func2()
    {
        static int y = 5; // Static storage duration. Initialized only once.
        printf("y = %d\n", y);
        y++;
    }
    int main()
    {
        int k;
        printf("func1 is called 5 times!\n");
        for (k = 0; k < 5; ++k)
            func1();
        printf("\nfunc2 is called 5 times!\n");
        for (k = 0; k < 5; ++k)
            func2();
        return 0;
    }

Every time the `func1` function defined in the program above is called, the variable $x$ is created, and when the function's execution ends, the variable $x$ is deallocated from memory. Although the value of the variable $x$ is incremented by 1 before the function ends, this has no effect on the next call. In the next call to the `func1` function, the variable $x$ is initialized with the value 5 again.

The situation is different for the `func2` function. The local variable named $y$ inside the `func2` function belongs to the block scope but has **static storage duration**. The statement initializing the variable $y$ is a part of the code produced by the compiler. The variable $y$ is initialized with the value 5 at the beginning of the program and retains its place in memory until the end of the program. The same variable $y$, whose memory location does not change, is used no matter how many times the function is called. In this case, since the value of the variable $y$ is incremented by 1 at the end of the function's main block, the value of the variable $y$ becomes 6 in the next call. The screen output for the program is given below.

    func1 is called 5 times!
    x = 5
    x = 5
    x = 5
    x = 5
    x = 5
    
    func2 is called 5 times!
    y = 5
    y = 6
    y = 7
    y = 8
    y = 9

#### Main Themes Regarding the Use of Static Local Objects

The main themes related to the use of static local objects utilize the fact that these objects have static storage duration. Global variables can also be used in these themes. However, global variables, while having static storage duration, belong to the **file scope**. Static local variables, on the other hand, belong to the **block scope**. To avoid the disadvantages arising from global variables having file scope, the need for objects with static storage duration in functions is met with static local variables in many situations.

#### Functions Returning with Addresses of Static Local Objects

You know that functions that return an address value should not return the addresses of local variables. This is because local variables have automatic storage duration and are deallocated from memory when the function ends. However, since local variables defined with the `static` keyword retain their place in memory until the program terminates, there is no problem with a function returning the address of a **static local variable**:

    #include <stdio.h>
    char *get_name()
    {
        static char entry[100]; // Static local array
        printf("enter a name: ");
        gets(entry);
        return entry; // Returns address of a static array
    }

However, returning with the address of a static local array is different from returning with the address of a dynamic array (an array whose space is obtained with the `malloc` function). The function returns the **same address** every time it is called. Examine the following `main` function:

    #include <stdio.h>
    int main()
    {
        char *p[10];
        int k;
        for (k = 0; k < 10; ++k)
            p[k] = get_name(); // All p[k] point to the SAME static array
        /*...*/
        for (k = 0; k < 10; ++k)
            printf("name = (%s)\n", p[k]); // All print the LAST entered name
        return 0;
    }

In the `main` function above, the programmer defines a 10-element pointer array. The addresses that are the return values obtained from the calls to the `get_name` function are assigned to each element of the pointer array. However, the `get_name` function returns the address of the **same static local array** each time. The name entry made by the user is overwritten on the previous entry each time. At the end of the `main` function, all elements of the pointer array point to the same string, right?

Some standard C functions also return the addresses of static local arrays. For example, the `ctime` and `asctime` functions, whose declarations are made in the `time.h` header file, return with the starting address of a string held in a static array.

#### Performance Improvement Achieved by Using Static Local Arrays

Arrays can also be defined with the `static` keyword.

    void func()
    {
        static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        /*…*/
    }

In the example above, since the `alphabet` array is defined with the `static` keyword inside the `func` function, after it is initialized once, it retains these values every time it is called and maintains its existence until the end of the program. If the `static` keyword had not been used, this array would be recreated with every call made to the `func` function, and the initial value assignments made to the array's elements would be performed again each time. This would cause an extra machine time to be spent for every call made to the function.

#### Functions Establishing a Logical Connection with Their Previous Calls

Some functions perform their tasks by establishing a logical connection with their previous calls. For example, let $\text{LIMIT}$ be a positive integer. Suppose we want to define a function that generates random numbers in the range $0 – \text{LIMIT}$. Let the function not generate a number it has generated before again. The function can store the information of whether a number has been generated before in a **static local flag array**. Compile and run the following program:

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <time.h>
    #define LIMIT 20
    
    int isprime(int val) { /* implementation assumed */ return 1; } 
    // Assuming isprime and other helpers exist
    
    int urand()
    {
        static char flags[LIMIT] = {0}; // Static local array, initialized to 0 once
        int ret_val;
        
        // Check if all numbers have been generated (memchr finds the first non-zero byte's address)
        if (!memchr(flags, 0, sizeof(flags)))
            return -1; // All numbers generated
        
        while (flags[ret_val = rand() % LIMIT])
            ; // Loop until an ungenerated number is found
            
        flags[ret_val]++; // Mark the found number as generated
        return ret_val;
    }
    
    int main()
    {
        int k;
        srand(time(0));
        for (k = 0; k < LIMIT; ++k)
            printf("%d ", urand());
        printf("\n");
        printf("%d\n", urand()); // Should return -1
        return 0;
    }

The elements of the static local array named `flags` inside the `urand` function are initialized with the value 0. Each element of the array is used as a flag indicating whether the relevant value has been generated before. For example, when the function is called, whether the value 12 has been generated before is understood from the value of the 12-indexed element of the `flags` array. If the value of this element is 0, it means the value 12 has not been generated; if it is 1, it means the value 12 has been generated.

The function first checks with the standard `memchr` function whether the value 0 is present in the array. If the value of none of the elements of the array is 0, it means all values have been generated. The function communicates information about this situation by returning the value -1.

If there is at least one value of 0 in the flag array, random values are continuously generated within a loop. The generated value is assigned to a variable named `ret_val`. The loop continues to run as long as the value of the `ret_val`-indexed element of the flag array is 1. To exit the loop, a value that has not been generated before must be generated. After the loop is exited, the value of the variable `ret_val` is the value to be returned. However, before this value is returned, the value of the `ret_val`-indexed element of the flag array is set to 1. This prevents this value from being generated again in the next call.

#### Comparison of Static Local Variables and Global Variables

Static local variables exhibit the same characteristics as global variables in terms of **storage duration**. That is, they are created when the program starts running, and their lifespan ends when the program finishes executing. However, they differ in terms of **scope**. Global variables adhere to the **file scope**, while static local variables adhere to the **block scope**. The fact that static local variables have block scope facilitates **data hiding** and increases **reusability** of the code. This is because functions dependent on global variables cannot be easily transferred from one project to another.

## 🤝 Module Concept and Linkage Property of Objects

A project can consist of more than one source file that can be compiled independently. Each source file of the project that can be compiled independently is called a **"module."** After the source files forming the project are compiled independently, they are all combined together by the **linker** to form a single executable file.

### Benefits of Dividing Large Projects into Modules

If all modules are combined into a single source code, the entire project must be recompiled for even the smallest change. However, in projects divided into modules, compiling only the module where the change was made is sufficient. This is because the other modules have already been compiled and only undergo processing during the linking phase. Another advantage of writing programs in the form of modules emerges during teamwork. In this case, the independent parts (modules) of the projects can be prepared by different people. Furthermore, modules, like functions, are reusable structures. A module can be used in more than one project.

### The Concept of Linkage

Can a name defined in one of the source files forming the project be accessed in another source file forming the project? Since these source files ultimately form a single executable file, it is perfectly natural that in some cases, an object defined in one module is desired to be accessed in another module.

The property that indicates whether a variable defined in one module can be used in another module is called the object's **linkage property**. The linkage property is different from scope. Scope is a concept concerning the compiler, i.e., related to **compile time**. If an object is used outside its scope, a compile-time error occurs. However, linkage is a concept concerning the linker program, i.e., related to **link time**. If an object is used in a module where it has no linkage, a link-time error occurs.

According to C standards, objects are divided into 3 main groups in terms of their linkage properties.

1.  **Objects with external linkage**
    If, after an object is defined, this object can be accessed both everywhere within its own module and in other modules, it is said that the "object has external linkage."
2.  **Objects with internal linkage**
    If, after an object is defined, this object can be accessed everywhere within its own module, but cannot be accessed in other modules forming the project, it is said that the "object has internal linkage."
3.  **Objects with no linkage**
    Objects that are known only within a specific block in their own module.

Function parameter variables and local objects defined within a function are **unlinked objects**. It is not possible to access these objects in other modules forming the project.

Global variables normally have **external linkage**. That is, a global variable can be accessed in another module. So, how can a global variable defined in one source file belonging to the project be used in another source file?

### The `extern` Specifier

The `extern` specifier is used to make a **declaration**. Declaring a variable with the `extern` specifier tells the compiler that the object is defined in another module.

Let a project consist of two source files named `mod1.c` and `mod2.c`:

| MOD1.C | MOD2.C |
| :--- | :--- |
| `int a;` | `int func2()` |
| `float func1()` | `{ ...` |
| `{ ...` | `a = 300; /* ERROR */` |
| `a = 100;` | `}` |
| `...` | |

The variable $a$ defined in the `mod1.c` file is a global variable and has external linkage, so it can normally be used in other source files in the project. The variable $a$ can also be accessed in the `mod2.c` file. However, in the example above, where the two modules are compiled separately, a problematic situation arises. This is because the compiler cannot know that the variable $a$ is globally defined in the `mod1.c` source file during the compilation of the `mod2.c` file. The compiler, which cannot find information about the variable $a$ while compiling the `mod2.c` source file, flags this situation as an error. In the C language, a variable can only be used if it has been declared beforehand, right? The **`extern` specifier** is used to inform the compiler that the relevant global variable is defined in another module, not within its own module.

The problem in question is eliminated if the variable $a$ is declared with the `extern` keyword in the `mod2.c` module.

| MOD2.C |
| :--- |
| `extern int a;` /* extern declaration specifies that variable a is defined in another module */ |
| `int func2()` |
| `{` |
| `a = 300;` |
| `/***/` |
| `}` |

The compiler that sees the `extern` declaration assumes that the variable is defined in another module belonging to the project, thus eliminating the error state. However, since the compiler cannot determine the location in memory of a variable declared with the `extern` keyword while generating machine code, it leaves this task to the linker program, which will examine all modules. Thus, the operation of finding the module where the variable is defined and linking it with those declared as `extern` is performed by the **linker program**. That is, the programmer notifies the compiler, and the compiler notifies the linker with the `extern` specifier.

The compiler that sees the `extern` specifier does not allocate space in memory. An `extern` declaration is a declaration, not a definition.

In fact, the use of the `extern` specifier is in question not only for variables but also for functions. C compilers automatically treat functions that are called but not defined within their own module—such as standard C functions—as `extern`. For this reason, there is no need to explicitly write the `extern` specifier in function declarations. It is assumed to be written by the compiler.

For example, suppose the function $x1$ located in the `mod2.c` module is called within the function $y1$:

| MOD1.C | MOD2.C |
| :--- | :--- |
| `int a;` | `extern int a;` |
| `float x1()` | `extern float x1(void);` |
| `{ a = 100; ... }` | `int y1()` |
| | `{ float f;` |
| | `f = x1();` |
| | `a = 300;` |
| | `... }` |

Examine the prototype statement written for the function $x1$ in the `mod2.c` module:

    extern float x1(void);

In this example, the `extern` keyword is used in the declaration of the function $x1$ because it is defined in another module. However, the compiler would assume `extern` even if the `extern` specifier were not added.

If a global variable is declared as `extern` in all modules without being defined in any module, all modules can be compiled without errors. The error arises during the linking phase, in the form of the linker not finding the object declared as `extern` in any module.

The `extern` specifier has an **"unintended" use** when only a single module is in question. In the example below, the global variable $x$ inside the `main` function causes an error because it is used before its definition.

    int main()
    {
        /***/
        x = 100; // Used before definition
        /***/
    }
    int x; // Global variable
    int func()
    {
        x = 200;
        /***/
    }

When the code above is compiled, an error message is encountered indicating that the declaration of the variable $x$ inside the `main` function was not found. In this case, if a global variable is used before its definition, an `extern` declaration must be made beforehand to avoid an error.

    extern int x; // Declaration
    int main()
    {
        /*…*/
        x = 100;
        /*…*/
    }
    int x; // Definition
    int func()
    {
        x = 200;
        /***/
    }

Instead of using the `extern` declaration in this manner, defining the global variable at the very beginning of the program is a better technique.

#### Using the `static` Keyword with Global Variables

If the `static` specifier is used with a global variable, it gives this variable **internal linkage**. That is, a global variable defined with the `static` keyword has internal linkage. Such a variable is not used in other modules forming the project with an `extern` declaration; it can only be used within its own module.

Note that the `static` definition for global variables only affects **linkage**, not storage duration (it remains static storage duration).

Let's also think about this question: Why would we want to use a global variable with internal linkage? What benefits can limiting a global variable to its own module provide?

##### Name Pollution

The names of two entities with external linkage cannot be the same within the files forming a project. If two global entities share the same name, an error occurs during the linking phase. This is a dangerous situation, especially when large projects are in question. This is because in most large projects, many programmers write code, and files written by other companies are also used in the project. In this case, the same names cannot be given to global entities in different source files. If the same names are chosen, an error occurs at link time.

##### Global Variables Whose Modification by Other Modules is Undesirable

If a global variable concerns only one module and does not concern the modules that this module serves, it can be accidentally modified by other modules during the program's runtime. It can also lead to name conflicts with global variables in other modules, causing **name pollution**. The natural thing to do is for such a global variable to have **internal linkage**. Such global variables should be defined with the **`static` keyword**.

### Creating Modules

A module is a unit consisting of codes that will provide some services to the outside. In the C language, two separate files are conventionally created for a module. One of these files is the **header file** of the module. A header file is the **interface** of a module. The interface of a module contains declarations that provide the information the compiler needs to know during the compilation of the files that will use that module. Modules establish their relationship with the outside world through their interfaces. Declarations concerning the outside for a module are conventionally collected in text files whose extension is chosen as **".h"**. The extension "h" comes from the first letter of the word "header."

A source file that uses a module includes the header file of that module with the **`#include`** preprocessor directive. Thus, the compiler sees all declarations.

The definitions related to that module are located in a separate file with the **`.c`** extension. These definitions are the definitions of global variables and the definitions of functions. Technically, this file is called the **"implementation file."** If a programmer working on the project changes the code of the module, i.e., the source file, without changing the module's interface, the programmers using this module in the project do not need to make a change in their own code. Thus, if the interfaces related to the modules are first determined, and source files are written dependent on these interfaces, even if there is a change in the source file, no change is required in the modules that call the functions in this source file.

### Using the `static` Keyword in Function Declarations or Definitions

Functions are also global entities. Some functions in a module are defined to provide services to the outside. These functions must be declared in the module's interface, i.e., the header file. However, functions that are used for the module's own internal workings and do not provide direct service to the outside are declared and defined with the **`static` keyword** in the implementation file. In this case, the `static` keyword is written before the function's return type:

    static int func(int); // Internal linkage for the function

---

## 🛡️ Type Qualifiers

There are two type qualifiers in C: **`const`** and **`volatile`**.

> \[A new type qualifier, the **`restrict`** keyword, was added with the C99 standards.]

### The `const` Specifier

The **`const`** specifier indicates that the content of the object cannot be modified after it is initialized. The `const` specifier can be used with local, global variables, and function parameter variables. Assigning to an object defined with the `const` keyword using the assignment operator is invalid:

    const double PI = 3.14159265; /* Valid. Initialization. */
    int main()
    {
        const int i = 10;
        i = 100; /* Invalid */
        return 0;
    }

If a local variable is to be defined with the `const` specifier, it must be initialized; otherwise, using the `const` specifier loses its meaning. Examine the following example:

    void func ()
    {
        const int a; /* Meaningless: 'a' gets garbage value, then cannot be changed */
        /*…*/
    }

In this example, since $a$ is a local variable, it has a garbage value. Since the variable's value can no longer be changed, such a definition has no meaning.

What is the purpose of using the `const` specifier? Depending on where it is used, the `const` specifier can provide the following benefits:

1.  **Increases program readability.** In this way, it helps the person reading the code. Readers of the program receive the information that the object's value will not be changed when they see the `const` keyword.
2.  **Prevents accidental modification of the object's value.** In this way, it helps the person writing the code. If the value of a `const` object is modified via assignment, a compile-time error occurs. Thus, the accidental modification of the value of an object that should not be changed via assignment is also prevented.
3.  **Objects defined with the `const` keyword can be stored in read-only memory by the compiler.** Since the compiler knows that the `const` object's value will not be changed, it can apply additional **optimization** operations for expressions using these objects. The `const` keyword helps the compiler in this way.

#### Comparison of `const` Objects and Symbolic Constants

Since `const` objects are used like literals whose value will not change, symbolic constants created with the `#define` preprocessor directive can often be used in their place. However, there are some differences between `const` objects and symbolic constants. These differences play a role when a choice is to be made between the two:

1.  **Symbolic constants are not objects.** Therefore, they do not occupy space in memory during the program's runtime. Since they are not objects, their scope, storage duration, and linkage properties cannot be referred to. The compiler sees the tokens placed by the preprocessor instead of symbolic constants when the compilation phase is reached.
2.  **Compilers provide better "debugging" support for `const` objects.**
3.  **Compilers provide better support for marking the location of an error** when a compile-time error occurs for `const` objects.
4.  An array can be defined with the `const` keyword. In this case, an assignment cannot be made to any element of the array accessed with the square bracket operator. It is not easily possible to achieve such a situation with the preprocessor `#define` directive:

    ```c
    void foo()
    {
        const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
        alphabet[2] = 'X'; /* INVALID */ // Cannot modify const array element
    }
    ```

5.  `const` objects in C have **external linkage**. A `const` object can be used in other modules by declaring it with `extern`.
6.  `const` objects in C **cannot be used as constant expressions**. Examine the following example:

    ```c
    #define SIZE 100
    int main()
    {
        const int size = 100; // 'size' is NOT a constant expression in C
        int legal_array[SIZE]; // Valid: SIZE is a symbolic constant
        int illegal_array[size]; /* INVALID: 'size' is not a constant expression in C */
        /***/
        return 0;
    }
    ```

#### Using the `const` Keyword in Pointer Definitions:

The `const` keyword is frequently used in the definitions of pointer objects. There are three separate ways the `const` keyword can be used with pointers. The characteristic of the defined pointer changes in each used form.

1.  **Using the `const` keyword before the `*` token:**
    Such pointers are called **pointers to const objects**. The object pointed to by such a pointer cannot be modified by making an assignment to the object obtained by dereferencing the pointer. However, an assignment can be made to the pointer itself. That is, the pointer can be made to point to another object. Examine the following example:

    ```c
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        double d1 = 2.5, d2 = 3.5;
        char str[] = "Necati";
        int x = 20;
        
        const int *iptr = a;      // Pointer to const int
        double const *dptr = &d1; // Pointer to const double
        const char *cptr = str;   // Pointer to const char
        
        /*
        *iptr = 100;    // Invalid! Cannot modify the object pointed to.
        *dptr = 1.23;   // Invalid!
        cptr[1] = 'x';  // Invalid!
        */
        
        iptr = &x;      // Valid: Pointer itself can be changed.
        dptr = &d2;     // Valid:
        cptr = "Selami"; // Valid:
        return 0;
    }
    ```

    The assignments: `*iptr = 100;`, `*dptr = 1.23;`, `cptr[1] = 'x';` made for the pointers to const objects defined in the `main` function above cause a compile-time error. However, you see that the assignments made to the pointers themselves: `iptr = &x;`, `dptr = &d2;`, `cptr = "Selami";` are entirely compliant with the rules.

    This is the most common form of using the `const` keyword with pointers, and this form is especially used with pointer parameters of functions:

    ```c
    void func(const char *str)
    {
        /***/
    }
    ```

    The pointer $str$, which is the parameter variable of the function named `func` above, receives its value through the function call. The argument in the function call expression is copied to the pointer $s$ (should be $str$) upon the function call. However, an assignment cannot be made to the object `*str` or the object `str[x]` inside the function. That is, the object at the location pointed to by the pointer $str$ (the object whose address was sent to the function) cannot be modified. The use of the `const` keyword in the example above is primarily related to **readability**. A C programmer reading the code above understands that the function `func` will only utilize the value of the object whose address was received from outside, i.e., it will not change the value of this object. Conventionally, the non-use of the `const` keyword in the definition of pointer parameters is accepted as a communication:

    ```c
    void func(char *s) // Pointer NOT to const
    {
        /***/
    }
    ```

    A C programmer reading the code above understands that the function `func` will modify the object whose address was sent to it (although there is no syntactic obligation). The person reading the code thinks: If the function `func` were not going to modify the object whose address was sent, the pointer $s$ would be defined with the `const` keyword.

2.  **Using the `const` keyword after the `*` token:**
    Pointers defined in this way are called **const pointers**. The address given to these pointers as an initial value cannot be modified via assignment. That is, the pointer points to the same object throughout its lifespan. However, it is possible to modify the object the pointer points to by dereferencing the pointer. In this usage form of the `const` keyword, the pointer must be initialized when it is defined; otherwise, the use of the `const` keyword loses its meaning. Examine the following example:

    ```c
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        double d1 = 2.5, d2 = 3.5;
        char str[] = "Necati";
        int x = 20;
        
        int *const iptr = a;        // Const pointer to int
        double *const dptr = &d1;   // Const pointer to double
        char *const cptr = str;     // Const pointer to char
        
        *iptr = 100;     // Valid: Can modify object pointed to.
        *dptr = 1.23;    // Valid:
        cptr[1] = 'x';   // Valid:
        
        /*
        iptr = &x;       // Invalid! Cannot change the pointer itself.
        dptr = &d2;      // Invalid!
        cptr = "Selami"; // Invalid!
        */
        return 0;
    }
    ```

3.  **Using the `const` keyword both before and after the `*` token:**
    In this case, a pointer that is both a **const pointer** and a **pointer to a const object** is defined. Assignment cannot be made to the pointer itself or to the object obtained by dereferencing the pointer. Using the `const` word in this manner is seen more often in the definition of parameter variables, although it is a rare occurrence in applications. Examine the following example:

    ```c
    int main()
    {
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        double d1 = 2.5, d2 = 3.5;
        char str[] = "Necati";
        int x = 20;
        
        const int *const iptr = a;        // Const pointer to const int
        const double *const dptr = &d1;   // Const pointer to const double
        const char *const cptr = str;     // Const pointer to const char
        
        /*
        *iptr = 100;     // Invalid! (Pointer to const)
        *dptr = 1.23;    // Invalid!
        cptr[1] = 'x';   // Invalid!
        
        iptr = &x;       // Invalid! (Const pointer)
        dptr = &d2;      // Invalid!
        cptr = "Selami"; // Invalid!
        */
        return 0;
    }
    ```

The declaration of a pointer to a pointer with the `const` keyword creates different possibilities:

* `const char **ptr;`
    Assignment cannot be made to the object pointed to by the pointer pointed to by `ptr`. The object `**ptr` is `const`. Assignments can be made to the objects `ptr` and `*ptr`. (**pointer to pointer to const object**)
* `char *const *ptr;`
    Assignment cannot be made to the pointer pointed to by `ptr`. The object `*ptr` is `const`. Assignments can be made to the objects `ptr` and `**ptr`.
* `char ** const ptr;`
    Assignment cannot be made to `ptr`. The object `ptr` is `const`. Assignments can be made to the objects `**ptr` and `*ptr`.
* `const char *const *ptr;`
    Only the object `ptr` can be assigned to.
* `char *const * const ptr;`
    Only the object `**ptr` can be assigned to.
* `const char ** const ptr;`
    Only the object `*ptr` can be assigned to.

#### A Function's Return Value Being a `const` Address

The return value of a function that returns an address can be a `const` address:

    const char *get_name(void);

The return value of the function named `get_name` declared above is a `const` address. So, what does this mean? You know that the return type of a function is actually the type of the temporary object that will hold the return value. The type of the temporary object that will hold the return value of the `get_name` function is the **`const char *` type**. That is, the temporary object is a pointer whose pointed-to object is `const`. Since the function call denotes the function's return value, i.e., the value of the temporary object, assignment cannot be made to the object reached when a call to such a function is the operand of the indirection operator or the square bracket operator. Examine the following example:

    char *get_name();
    const char *get_fname();
    int main()
    {
        *get_name() = 'a';     // Valid: get_name returns char*
        get_name()[2] = 'x';   // Valid:
        
        *get_fname() = 'a';    // Invalid! get_fname returns const char*
        get_fname()[2] = 'x';  // Invalid!
        
        return 0;
    }

In the `main` function above, the value 'a' is assigned to the object at the address returned by the called `get_name()` function. Similarly, the object two steps after the object at the address returned by the function is reached with the expression `get_name()[2]`, and the value 'x' is assigned to this object. The assignments are valid. However, similar assignments are invalid and cause a compile-time error for the `get_fname` function, whose return value is of type `const char *`.

### The `volatile` Specifier

Compilers can temporarily store objects in registers for optimization purposes. This kind of temporary residence in registers can be done by compilers even if the `register` specifier is not used. For example:

    int square (int a)
    {
        int b;
        b = a * a;
        return b;
    }

In the function above, $b$ is a temporary variable; therefore, there is no functional difference if the compiler stores the variable $b$ temporarily in one of its registers instead of storing it somewhere in memory. In applications of this kind, the compiler temporarily storing variables in registers speeds up operations. Examine the following code:

    int a;
    int b;
    /***/
    a = b;
    if (a == b) {
        /***/
    }

In this example, the variable $b$ is naturally fetched into one of the registers for transfer to the variable $a$ in the first step. However, the compiler may use the $b$ in the register instead of the $b$ in memory to perform the comparison $a == b$ in the expression inside the `if` parenthesis. In both examples we provided, the compiler wanted to make the program run faster without changing its function through certain optimization operations. However, in some applications, the compiler behaving in this way can cause errors. In the second example:

    a = b;
    if (a == b) {
        /***/
    }

If a hardware interrupt (such as $8h$) changes $b$, this situation may not be noticed by the `if` statement. In such situations, temporarily storing variables in registers for optimization purposes can lead to undesirable results. **`volatile`** is a type qualifier that means, "Do not let variables remain in registers for optimization; use them from their actual locations in memory!" In this sense, we can think of the `volatile` specifier as having the opposite meaning to the `register` specifier. In the example above, a problem such as the one described can be prevented by declaring the variable $b$ as `volatile`.

    int a;
    volatile int b;

`volatile` is a specifier that can be used in very specialized applications. The `volatile` specifier, which can be used with local, parameter, or global variables, can only be important in very specialized applications. Be aware that the unconscious use of this specifier can negatively affect performance.