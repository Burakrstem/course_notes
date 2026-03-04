## DIFFERENCES BETWEEN THE C LANGUAGE AND THE C++ LANGUAGE

In this section, we will cover the syntactical (syntax) differences between the ANSI C language (C89 ISO/IEC 9889:1990) and the C++ language (ISO/IEC 14882:1998).

Source codes written in C can also be compiled with a C++ compiler. By changing the settings of a C++ compiler, it can be ensured that the source codes to be written are treated directly as C source files.
Furthermore, almost all compilers understand which language's rules to compile the source code by looking at the extension of the created source file—for example, whether the extension is .c or .cpp.

The basic syntactical structure of the C++ language was formed by making some additions onto the C language's syntax. In this case, the C language can be seen as a syntactical subset of the C++ language. At some points, C and C++ languages also show differences in terms of syntax rules.

The syntactical differences between C and C++ can be handled in two main groups:
1. While C is a language that supports procedural programming techniques, C++ supports multiple programming paradigms (multiparadigm). A significant part of the differences between the two languages relates to the new tools C++ has added to support other programming techniques.
2. The other differences are not directly related to programming techniques. These differences cover the changes and additions made with the aim of making C++ a better C.

A file written in C may need to be ported to C++, and a file written in C++ to C. When a source file written and valid according to ANSI C rules is ported to C++, situations that are invalid according to C++ rules may arise.

Undoubtedly, the reverse is also true. That is, a piece of code that does not contain a syntax error in C++ may be invalid according to the rules of the C language.

In some cases, even if the written code is evaluated as valid according to the rules of both languages, the written code may have different meanings according to the rules of the two languages. In porting a source file from one language to another, incompatibility problems may be encountered due to rule changes.

We will address the fundamental syntactical differences between C and C++ under three separate headings:

Valid in C, Invalid in C++ / Valid in C++, Invalid in C / Rule Differences between C and C++

---

### Valid in C, Invalid in C++

**1. Some words that are not keywords in C are keywords in C++.** The standard ANSI C language (C89) has 32 keywords. These words are also keywords in the C++ language. However, C++ has defined 42 new keywords in addition to these. The following words are keywords in C++ but not in C:

`and`, `and_eq`, `asm`, `bitand`, `bitor`, `bool`, `catch`, `class`, `compl`, `const_cast`, `delete`, `dynamic_cast`, `explicit`, `export`, `false`, `friend`, `inline`, `mutable`, `namespace`, `new`, `not`, `not_eq`, `operator`, `or`, `or_eq`, `private`, `protected`, `public`, `reinterpret_cast`, `static_cast`, `template`, `this`, `throw`, `true`, `try`, `typeid`, `typename`, `using`, `virtual`, `wchar_t`, `xor`, `xor_eq`

In valid C code, any of the words above might have been used as an identifier (name). However, the same code is not valid when compiled in C++:

    void foo()
    {
        int new;
        /***/
    }

Above, a variable of type `int` named `new` is defined. The definition is valid in C, invalid in C++.

**2. In C, if a function that produces a return value does not produce a return value with a `return` statement within its definition, this situation is not evaluated as a syntax error by compilers.** In this case, the called function returns a garbage value. Undoubtedly, this is a programming error.
However, in C++, a return value must be produced by writing a `return` statement within the definition of a function that produces a return value. If a return value is not produced with a `return` statement, the code is invalid.

    int func()
    {
    }

The function definition above is valid in C, invalid in C++.

In C++, a plain `return` statement cannot be used in the definition of functions that produce a return value:

    int func()
    {
        /***/
        return;
    }

The `return` statement in the example above is valid in C but invalid in C++. Doubtless, the way the `return` statement is used above is a programming error. Almost all C compilers report this situation with a logical warning message.

However, the `main` function is excluded from this rule in C++. Even if the `main` function is defined to produce a return value of type `int`, a `return` statement may not be written inside the `main` function. In this case, the compiler automatically treats the source code as if the statement
`return 0;`
were written before the end of the main function's main block. The code is valid.

The following code is valid in both C and C++. There is no situation that would require a logical warning for C++ compilers.

    int main()
    {
    }

**3. In C, if the type information of a function's return value is not written, it is understood that the function returns a value of type `int` (implicit int).** However, in C++, it is mandatory to write the return value type in function declarations and definitions:

    foo(void);

    func(double x)
    {
        /***/
    }

The declaration of the `foo` function above is valid in C, invalid in C++. The definition of the `func` function above is valid in C, invalid in C++.

**4. In C, there are two separate syntax rules for defining a function.** These syntax rules are named old style and new style. Although old style function definition is no longer preferred by programmers, it is still valid according to C language rules. However, according to C++ language standards, old style function definition is not valid:

    int foo(a, b, c)
    int a;
    double b, c;
    {
        /***/
    }

The function definition above is valid in C, invalid in C++.

**5. In C, function declaration is not mandatory.** When a C compiler encounters a call to an undeclared function, it generates code assuming the function produces an `int` return value. However, in C++, function declaration is mandatory:

    int main()
    {
        foo();
    }

The call to the `foo` function in the example above is valid in C, invalid in C++.
However, calling a function without declaration, although valid in C, is not considered correct.

**6. In C, leaving the inside of the function parameter parenthesis empty in a function declaration and writing the `void` keyword inside the parameter parenthesis carry different meanings:**

    int func();

    void foo()
    {
        func(5);
    }

In the example above, nothing is written inside the parameter parenthesis in the declaration for the `func` function. In C, the meaning of this declaration is: No information has been given to the compiler about the parameter variables of the declared `func` function. That is, in the call to the `func` function, the compiler does not check whether the number of arguments sent to the function is the same as the number of parameter variables of the function. A special meaning has been attributed to this declaration for backward compatibility. If this declaration in C were made in the form
`int func(void);`
the compiler would have been explicitly informed that the `func` function has no parameter variables.

However, in C++, both declarations have the same meaning:
`int func();`
`int foo(void)` (Note: This line in the text seems to be a typo, it should likely be `int func(void)`)

In C++, there is no difference between leaving the inside of the parameter parenthesis empty in a function declaration and writing the `void` keyword inside the parenthesis. In both cases, the information is given that the function has no parameter variables.

**7. In C, the address of the `main` function can be taken. The `main` function can call itself.** However, this situation is not allowed in C++.
In C++, the `main` function cannot call itself. The address of the `main` function cannot be taken.

**8. In C, specifiers (`auto`, `register`, `static`, `extern`, `const`, `volatile`) can be used directly with the variable name in variable definitions without a type-specifying keyword.** In this case, the compiler assumes the defined variable is of type `int`. However, using specifiers this way is not valid in C++.

    void foo()
    {
        const i = 0;
    }

The code above is valid in C, invalid in C++.

**9. In C, it is completely valid to define a `const` variable without giving it an initial value.** Undoubtedly, for an object with automatic storage duration, this situation is a programming error. In C++, it is mandatory to give initial values to `const` variables:

    void foo()
    {
        const int x;
        char *const ptr;
        /***/
    }

The definitions above are valid in C, invalid in C++.

In C++, it is also mandatory to give initial values to `const` variables with static storage duration:

    const int x;
    void foo(){}

The definition of the `x` variable in the example above is valid in C, invalid in C++. However, the following
definition is valid in both languages:

    const int *ptr;

Here, the `ptr` variable itself is not `const`. The location pointed to by the `ptr` variable is treated as `const`.

**10. In C, it is valid to assign an address of type `void` to a pointer variable that is not of type `void` without a type-casting operation.** Some C compilers may give a logical warning message in this situation. But this situation is not evaluated as a syntax error. However, this situation is a syntax error in C++. In C++, `void` type addresses cannot be assigned to a pointer of another type without using a type-casting operator:

    #include <stdlib.h>

    void foo()
    {
        int *ptr;
        ptr = malloc(sizeof(int));
        /***/
    }

The assignment to the `ptr` variable in the example above is valid in C, invalid in C++.

**11. In C, it is wrong to assign a value other than address information to a pointer variable or to assign an address of a different type to a pointer variable.** Most C compilers report this situation with a logical warning message. In C, there is an automatic type conversion between fundamental types and address types.
In C++, the situation of assigning an expression that is not an address value to a pointer variable or assigning an address to a pointer variable of a different type is directly a syntax error.

    void foo()
    {
        int x = 10;
        double *dp;
        int *ip;
        dp = &x;
        ip = 20;
        /***/
    }

The assignments to the `dp` and `ip` pointer variables in the code snippet above are not valid in C++.

**12. In C, it is wrong to assign the address of a `const` variable to a pointer whose pointed-to location is not `const`.** Most C compilers tend to give only a logical warning message in such a case. In C++, it is invalid to assign the address of a `const` variable to a pointer whose pointed-to location is not `const` without type casting.
In C++, the addresses of `const` objects are considered to be of a separate address type. Such addresses can only be assigned to pointer variables whose pointed-to location is `const`:

    void foo()
    {
        const int x = 20;
        volatile int y = 50;
        int *ptr;
        ptr = &x;
        ptr = &y
    }

The assignments to the `ptr` pointer in the code snippet above are not valid in C++. Similarly, in C++, the value of a pointer whose pointed-to location is `const` cannot be assigned to a pointer whose pointed-to location is not `const`:

    void func(const char *ptr)
    {
        char *temp = ptr;
        /***/
    }

The assignment to the `temp` pointer in the code snippet above is not valid in C++.

**13. In C, the address of a `const` or `volatile` object can be assigned to a pointer of type `void`.** In C++, the address of an object defined with the `const` or `volatile` keyword cannot be assigned to a `void` pointer without type casting.
Addresses of any type can be assigned to `void` pointers. However, in C++, the address of an object defined with the `const` or `volatile` keyword cannot be assigned to a `void` pointer without type casting.

    void foo()
    {
        void *vptr1, *vptr2;
        const int x = 10;
        volatile int v = 20;
        vptr1 = &x;
        vptr2 = &v;
        /***/
    }

The code above is valid in C. However, the assignments to the `vptr1` and `vptr2` variables are not valid in C++.

**14. In C, types defined by the programmer can be declared in the place where the return value is written or where the parameter variables are declared in function definitions or declarations.** Such declarations are not valid in C++.

    struct A{int a1, int a2;} foo();

The declaration above is valid in C. The return value of the `foo` function is of the declared `struct A` type. However, this declaration is invalid in C++.

    void func(struct B{int b1, int b2;} x);

The declaration above is also valid in C. The parameter variable of the `func` function is of the `struct B` type declared inside the parameter parenthesis. This declaration is invalid in C++.

**15. In C, it is valid to assign a value from a fundamental type to a variable of an enumeration type.** In C++, only an "enumeration constant" related to the enumeration type in question can be assigned to an object of an enumeration type.

    enum Position {ON, OFF, HOLD};

    void foo()
    {
        enum Position pos = 1;
        /***/
    }

The assignment to the `pos` variable is valid in C, but invalid in C++.

**16. In C, a global variable can be declared more than once without the `extern` keyword.** In C++, a variable can be declared only once within a source file without using the `extern` keyword.

    int x;
    int x;

    void foo()
    {
    }

The code above is valid in C, but invalid in C++.

**17. In C, the tag-name (tag) used for a user-defined type can be the same as a `typedef` name used in the same scope.** This situation is not a syntax error.

    struct Word {
        char hb, lb;
    };
    typedef int Word;

The code snippet above is valid in C, invalid in C++.

**18. In C, a nested structure declaration is directly visible in its enclosing scope.** In C++, nested declared types cannot be used directly:

    struct Outer {
        struct Inner {
            /***/
        }
        /***/
    }

    struct Inner i;

In the example above, the declaration of the `struct Inner` type is done within the declaration of the `struct Outer` type. The definition of the variable `i` of type `struct Inner` is valid in C. Because at this point of definition, the `struct Inner` type is known.
However, the code above is invalid in C++. In C++, the `struct Inner` type cannot be used directly, but as `Outer::Inner`.

**19. In C, when initializing a `char` type array with a string literal, the number of characters in the string literal can be equal to the specified size of the defined array.** In this case, there is no null-terminator character at the end of the text placed in the array.
In C++, such an initialization operation is invalid.

    void foo()
    {
        char message[4] = "hata";
        /***/
    }

The code snippet above is valid in C, invalid in C++.

**20. In C++, when string literals are put into an operation, they are converted to an address of type `const char`, not type `char`.**
In C, when the compiler sees a string literal in the source code, it first allocates a safe place in memory for this string. Then it places the starting address of the allocated place (block) in memory instead of the string. In C, trying to modify a string literal via pointers, although a programming error, does not constitute a syntax error.
However, in C++, string literals are treated as an address of type `const char` when put into an operation. But, to prevent a large number of previously written C++ codes from becoming invalid, the assignment of string literals, which are addresses of type `const char`, to non-const `char` type pointers was allowed by the 1998 Standards. However, this situation has been declared "deprecated".
In this case, according to the 1998 C++ standards, the following code is valid:

    char *p = "Necati Ergin";

Here, the assignment of a `const` address to the `p` pointer, whose pointed-to location is not `const`, is valid. But most C++ compilers give a logical warning message in this situation.
However, if string literals are used in any expression where a non-const `char` type (`char *`) address is needed, this is invalid in C++.

    void foo()
    {
        char *p = "Necati Ergin" + 1;
        char *str = x > 1 ? "Books" : "Book";
        *"selam" = 'k';
    }

The statements above are valid in C, invalid in C++.
In new codes to be written, string literals should now be seen as an address of type `const char` and should only be assigned to pointer variables for reading purposes, i.e., variables of type `const char *`.

**21. In C, the `goto` and `switch` control statements, which provide a jump within a scope, can provide a jump to after a code region where a definition statement is located.** This situation is banned in C++.