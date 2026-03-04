### Rule Differences Between C and C++

**1. In C, an enumeration type is no different from `signed int` from the compiler's perspective.** Therefore, the value of an object of an enumeration type can be `<= INT_MAX` and `>= INT_MIN`. In C, assuming `BLUE` is an enumeration constant, the expression
`sizeof(int) == sizeof(BLUE)`
is always true.

However, in C++, the compiler is free to choose the integer type it will use for the enumeration type. Any of the types `signed int`, `unsigned int`, `signed long`, or `unsigned long` can be selected for the enumeration type. On many systems, this means a larger enumeration constant can be defined in C++ compared to C.

When a C++ compiler sees an enumeration type declaration, it looks at the values of the enumeration constants used in the declaration. If all values are within the range of the `int` type, `int` is chosen as the enumeration type. If the value(s) of the enumeration constants cannot be held in a `signed int`, the suitability of `unsigned int`, `signed long`, and `unsigned long` types is tested, in order.

In the case of the example above, the expression `sizeof(int) == sizeof(BLUE)` is not necessarily true.

**2. In C++, character literals are assumed to be of type `char`.** Character literal expressions are of type `char`. In C++,
`sizeof('A') == sizeof(char) == 1`
is guaranteed.

In C, character literals are assumed to be of type `int`, and character literal expressions are of type `int`. In C,
`sizeof('A') == sizeof(int)`
is true, while in C++, the expression
`sizeof('A') == sizeof(char)`
is true.

**3. In C, global objects defined with the `const` keyword have external linkage by default.** However, in C++, global `const` objects have **internal linkage**. They cannot be accessed from other modules (translation units) of the program via an `extern` declaration. In other words, in C++, global `const` objects are treated as if they were defined with the `static` keyword, even if they are not.

In C++, if a global `const` object is desired to have external linkage, it must be defined (or declared) with the `extern` keyword:

    const int size = 10;
    extern const int value = 20;

    // 'size' has internal linkage in C++.
    // 'value' has external linkage in C++.

In the example above, the `size` variable has internal linkage, while the `value` variable has external linkage.

**4. In C, a structure's tag name (structure tag) does not join the regular identifier scope it belongs to.** A structure's tag name never masks an identifier with the same name in a wider scope. However, in C++, the tag name for user-defined types (like structs) *does* join the scope where it is declared.

    int a[100];
    void foo()
    {
        struct a { int i; };
        int n;
        printf("sizeof(a) = %d\n", sizeof(a));
    }

In the example above, the `a` used in the `sizeof(a)` expression refers to the **global array** in C, whereas in C++, it refers to the **structure named `a`** declared inside the `foo` function.