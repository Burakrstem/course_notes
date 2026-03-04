### Valid in C++, Invalid in C

**1. According to C89 standards, all local declarations must be made at the beginning of blocks.** That is, an executable statement cannot be present before a declaration made within a block. [According to C99 standards, declarations can be made anywhere within a local block.] The reason for such a design in C was to allow the programmer to easily find the location of a declaration.
However, in C++, declarations and definitions can be made anywhere within a block:

    void foo()
    {
        int y;
        y = 10;
        int x;
        /***/
    }

The definition of the variable `x` above is invalid in C, but valid in C++.

In C++, the ability to make a declaration or definition within a block close to where it is first used is considered a factor that enhances the source code's readability. However, the main important reason relates to variables of user-defined types. In C++, such objects, in many cases, begin to use external resources as soon as they are defined. If these variables had to be defined at the very beginning of the block, they would have to use resources unnecessarily until their first use.

The source code range where a name can be recognized by the compiler is called its **scope**. In C, local variables adhere to block scope. That is, they are known anywhere from the beginning to the end of the block in which they are declared. In C++, since declarations do not have to be made at the beginning of blocks, the scope rule must be changed as follows: In C++, the scope of local variables is the source code region from the point they are declared to the end of the relevant block. In C++, as in C, multiple variables with the same name cannot be declared within a block.

**2. In C++, `bool` is a fundamental data type.**
In C, `bool` is not a predefined data type. (The `bool` type was added to the C language with the C99 standards.)

    void foo()
    {
        bool flag;
        /***/
    }

The code above is valid in C++, invalid in C.

In C, when such a requirement is felt, some tools can be used.
`#define BOOL` /* with a preprocessor command */
`typedef int BOOL` /* with a typedef declaration */
`enum BOOL {TRUE, FALSE}` /* as an enumeration type */

However, in C++, `bool` is the name of a fundamental type, and `bool` is a keyword. The words `true` and `false`, which represent values of this type, have also been added to C++'s set of keywords.
In C++, an object of type `bool` can take the values `true` and `false`.
If a value of another type is assigned to an object of type `bool`, these values are automatically converted to `true` or `false` before assignment. That is, there is an automatic type conversion from other fundamental types to the `bool` type. A non-zero value assigned to a `bool` object is converted to `true`, and a 0 value is converted to `false`. An address value can also be assigned to a `bool` object. The `NULL` address is converted to `false` before assignment, while other address values are converted to `true`.

A value of type `bool` can also be assigned to other fundamental types. In this case, the `true` value is converted to the `int` value 1, and the `false` value to the `int` value 0 before assignment.
In C, comparison and logical operators produce `int` values of 1 or 0. However, in C++, these operators produce `bool` values of `true` or `false`.

**3. In C++, `const` variables initialized with a constant expression can be used where constant expressions are required.**
In C, `const` variables are not considered constant expressions. Expressions containing `const` variables are not treated as constant expressions. However, in C++, `const` variables initialized with constant expressions can be used as "constant expressions."

    void foo()
    {
        const int size = 10;
        int a[size];
        /***/
    }

The code above is valid in C++, invalid in C.

The most important difference between C and C++ in `const` object definition is that in C++, the variable defined with the `const` keyword is treated like a symbolic constant. That is, in C++, the `const` keyword is like the version of the `#define` operation performed by the compilation module. The C++ compiler, seeing a `const` variable being used, processes the initial value given to it as a constant instead of the `const` variable.

**4. In C++, structure, union, and enumeration tags are also accepted as type names.**

    struct Complex {
        /*....*/
    };

    enum POS {OFF, ON};

    Complex func(Complex, Complex);
    POS position;

In the example above, the declaration of the `func` function and the definition of the `position` variable are valid in C++, invalid in C.
In C, the names of these declared types are `struct Complex` and `enum Pos`. If it is desired to express the type information without using the `struct` and `enum` words, a `typedef` declaration must be made in C.

**5. In C++, there is the possibility of using comment lines starting with the `//` atom.** This comment line format is not valid in C.
In C, source code regions between the `/*` and `*/` atoms are treated as comment lines by C compilers and are not put into the compilation process.

`x = func(); /* x is assigned the return value of the func function */`

The length of the region between the `/*` and `*/` atoms can be longer than one line.

    x = func();
    /* The return value of the func function is assigned to the x variable. But in real
    programs, comment lines should only be used when necessary;
    unnecessary use of comment lines makes programs
    harder to read */

In C++, although this type of comment line is completely valid, a second comment line format has been added:
In C++, the part from the point where the `//` atom is located to the end of the line is not put into the compilation process. It can be said that this commenting format is particularly useful for short explanations. (C++ adopted this comment line from the BCPL language.)

However, the `//` comment line cannot continue on the next line. If the explanation or comment is longer than one line, the `//` atom must be placed at the beginning of each line again.

In C, failure to close a comment line can lead to hard-to-find errors:

    int a, b;
    a = 10;/* a object was assigned the value 10.
    b = 20;/* b object was not assigned the value 20! */

In the example above, because the first comment line was not closed, the `b = 20;` assignment is not put into the compilation process.
Since the C++ style comment line is created with a single atom, there is no possibility of making the mistake above:

    void foo()
    {
        int a, b;
        a = 10;
        b = 20;
        // a object was assigned the value 10.
        // b object was assigned the value 20.
        /***/
    }

The code above is valid in C++, invalid in C.
However, most C compilers allow the use of `//` comment lines. `//` comment lines were also added to the C language with the C99 standards.

**6. In C++, there is no requirement to use a constant expression when initializing variables with static storage duration.**
In C, it is mandatory to initialize variables with static storage duration with constant expressions.

    int foo();
    int x = 5;
    int y = x;

    void func()
    {
        static int z = foo();
        /***/
    }

In the example above, the global variable `y` and the static local variable `z` are initialized with expressions that are not constant expressions. These statements are valid in C++, but invalid in C.

**7. In C++, variables can be defined in the first part of the `for` loop statement's parenthesis, and within the parenthesis of `if`, `while`, and `switch` statements.**
In C, local variables can only be defined at the beginning of blocks and inside function parameter parentheses. In C++, the ability to define variables in the first part of `for` loops, within the parentheses of `while` loops, and within the parenthesis of the `if` statement has been introduced.

    #include <cstdio>
    int main()
    {
        for (int i = 0; i < 100; ++i)
            printf("%d\n", i);
        return 0;
    }

The `for` statement above is valid in C++, invalid in C.

The object defined in the first part of the `for` loop statement's parenthesis can be of any type. Here, by using the comma operator, more than one object of the same type can also be defined.

Before the 1998 ISO standards, declarations were not allowed inside `if`, `while`, and `switch` parentheses. However, with the standards, these situations were also made possible. Let us remind you that old compilers may not allow variable definition inside the parentheses of these statements. Because this situation was added to the C++ language with the 1998 standards.

So, what is the scope of the variable defined in the first part of the `for` parenthesis? In the program above, where can the `i` variable defined in the first part of the `for` loop be used?
The rule regarding the scope of such variables was changed with the standards. Before the C++ standards—Some compilers still compile according to this rule—the rule regarding scope was as follows:
A variable defined inside the `for` parenthesis is known until the end of the block in which the `for` loop is, i.e., until the closing curly brace.

However, the 1998 standards limited the scope of variables defined inside the `for` parenthesis to the loop body. That is, the following code snippet, while valid according to the previous rules, is invalid according to the C++ standards.

    #include <cstdio>
    int main()
    {
        for (int i = 0; i < 100; ++i)
            printf("%d\n", i);
        printf("i = %d\n", i);
        //Invalid
        return 0;
    }

This change regarding the scope of the loop variable can be the source of dangerous bugs.

    #include <cstdio>
    int i = 0;
    int main()
    {
        for (int i = 0; i < 100; ++i)
            printf("%d\n", i);
        
        i = 100;
        // assignment is made to the global variable i.
        //...
    }

In the program above, with the assignment statement `i = 100;`, which `i` variable is being assigned to? According to old compilers, the assignment is made to the `i` variable defined inside the `for` statement parenthesis. Because the variable with the same name in the narrow scope masks the variable with the same name in the wide scope! However, according to the rules of the standard ISO C++ language, only the global variable `i` can be accessed, so the assignment is made to the global variable `i`.

Does defining variables inside the parentheses of other control statements provide any benefit in practice? The main theme is assigning the return value produced by a function call to the variable defined inside the parenthesis and using this variable only in the body of the control statement:

    if (int x = get_value()) {
        //...
    }

**8. In C++, it is not mandatory to give an initial value with a constant expression to variables with static storage duration.** (Note: This point appears to be a repetition/rephrasing of point 6.)
In C, if variables with static storage duration, i.e., global variables and local variables defined with the `static` keyword, are given an initial value, the initializing expression (initializer) must be a constant expression. That is, the initializing expression cannot contain a previously defined variable. The reason for this in C is that objects with static storage duration are written into the object code with their initial values. For this to be possible, the given initial values must be determined at compile time. To be ascertainable at compile time, the expression must be a constant expression. However, in C++, objects with static storage duration can be initialized with any type of expression. Even if these variables are not given an initial value, they are written into the object code with a value of 0. They receive their initial values during the program's runtime and before the `main` function.

**9. In C++, two-character alternative token (digraph) atoms have been defined.** The compiler and preprocessor program assume that their equivalent characters are present wherever they see these character pairs:
`<:` [
`:>` ]
`<%` {
`%>` }
`%:` #

These character pairs are not valid in C:

    %:include <stdio.h>

    void copy(char dest<::>, const char source<::>, size_t nbytes)
    <%
        while (nbytes--)
            *dest++ = *source++;
    %>

(Note: The `<::>` in the original text appears to be a typo, it should be `<: :>`. The translation uses `<: :>` which corresponds to `[ ]`.)

    %:include <stdio.h> /* Equivalent to #include <stdio.h> */

    void copy(char dest<: :>, const char source<: :>, size_t nbytes) /* <: :> is [ ] */
    <% /* <% is { */
        while (nbytes--)
            *dest++ = *source++;
    %> /* %> is } */

The program above is valid in C++, invalid in C.

**10. In C++, the expression formed with the prefix `++` operator is an l-value.** In C, such expressions are not l-values. (Note: The text says 'prefix' (`++x`) but the heading says 'suffix' (`x++`). The code example uses `++x`. The translation will follow the code.)

    #include <stdio.h>
    int main()
    {
        int x = 5;
        ++x = 10;
        printf("x = %d\n", x);
        return 0;
    }

The assignment `++x = 10;` made in the program above is valid in C++, not valid in C.

**11. In C++, an expression formed with the conditional operator is an l-value if the second and/or third terms of the conditional operator are objects.** In C, an expression written with the conditional operator is never an l-value:

    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>

    int main()
    {
        int x, y;
        x = y = 0;
        srand((unsigned int)time(0));
        (rand() % 2 ? x : y) = 1;
        printf("x = %d\n", x);
        printf("y = %d\n", y);
        return 0;
    }

The statement `(rand() % 2 ? x : y) = 1;` made in the program above is valid in C++, invalid in C.

**12. In C++, an expression formed with the comma operator corresponds to the object if the right term of the comma operator is an object.** In C, an expression written with the comma operator is never an l-value:

    #include <stdio.h>
    int main()
    {
        int x = 10;
        int y;
        (x, y) = 30;
        printf("x = %d\n", x);
        printf("y = %d\n", y);
        return 0;
    }

The statement `(x, y) = 30;` written in the program above is valid in C++, but invalid in C.

**13. In C++, the identical repetition of a `typedef` declaration is valid.** In C, writing a `typedef` declaration a second time is a syntax error.

    typedef double dollar;
    typedef double dollar;

The declarations above are valid in C++, invalid in C.

**14. In C++, there is a functional form of the type-casting operator.** Such use of the operator is not valid in C.

    void foo()
    {
        double d = 4.5;
        int x;
        x = int (d);
        /***/
    }

In the example above, the value of the `double` type variable `d` is converted to `int` type using the functional form of the type-casting operator before assignment.
The code above is valid in C++, but not valid in C.

**15. In C++, in a function that does not produce a return value, the `return` keyword in the `return` statement can be followed by an expression of type `void`.** In C, in such functions, the `return` keyword cannot be followed by an expression:

    void foo();

    void func()
    {
        /***/
        return foo();
    }

The `return` statement used in the example above is valid in C++, invalid in C.

**16. In C++, it is not mandatory to give a name to a parameter variable in a function definition:**

    void func(int)
    {
        /***/
    }

The definition of the `func` function in the example above is valid in C++, invalid in C. Doubtless, when such a function definition is made, it is not possible to use the unnamed parameter within the function. The reason for defining such functions in C++ is related to the facility called "function overloading."

**17. In C++, there is no requirement to use constant expressions when initializing arrays, structure, or union objects.** However, in C, only constant expressions can be used as initializer expressions in these situations.

    void func(int x)
    {
        int a[3] = {x, x + 1, x + 2};
        /***/
    }

The definition of the array `a` in the example above is valid in C++, invalid in C.