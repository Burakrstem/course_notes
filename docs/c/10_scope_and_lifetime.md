# Scope and Storage Duration

In previous topics, the names, values, and types of objects were discussed. Objects also have three more properties that are very important in terms of the C language: **scope**, **storage duration**, and **linkage**.

---

## Scope

**Scope** is the program region within which an identifier (name) can be recognized. Names declared to the compiler are not known everywhere by the compiler. Each name can only be recognized by the compiler within **"that name's scope."** Scope is a concept directly related to the source code, thus it is associated with compile-time. In the C language, variables declared to the compiler are only accessible in certain parts of the source code. That is, defining a variable does not mean that the variable can be accessed from everywhere in the source file.

C standards categorize scopes into 4 distinct groups:

1.  **File scope:** A name is known throughout the entire source file after its declaration, meaning within all defined functions.
2.  **Block scope:** A name is known only within a block after its declaration.
3.  **Function Scope:** A name is known only within a block after its declaration. This is a special definition covering only `goto` labels. This scope will be addressed in the section on the "goto statement."
4.  **Function Prototype Scope:** A definition covering the recognition of names used within the function parameter list in function declarations. This scope will be addressed in the section on "Function Declarations."

Variables defined within a source file can be divided into two categories, **"local"** and **"global,"** based on their scope:

---

## Local Variables

Variables defined inside blocks or within the parameter lists of functions are called **local variables**. In the C language, you know that definitions of variables inside blocks must be done at the very beginning of the block. Local variables are variables defined within a block; they might be declared within a function's main block or within an inner block.

The scope of local variables is **block scope**. That is, local variables can only be accessed within the block in which they are defined. They cannot be accessed in a block outside the block in which they are defined.

All variables defined in the following program are local, because the variables named $x$, $y$, and $z$ are defined inside blocks. These variables can only be used within the block in which they are defined. Their use outside their defining block is invalid. Statements enclosed in comment lines are invalid. Variables $z$ and $y$ are used outside their scope.

In the example above, since all variables are local, they conform to the block scope rule, but this does not mean that the scopes of all 3 variables are exactly the same. In the example program, variable $x$ has the widest scope, while variable $y$ has a smaller scope, and variable $z$ has the smallest scope.

## Code Example for Block Scope
```c
#include <stdio.h>
int main()
{
    int x = 10;
    printf("x = %d\n", x);
    {
        int y = 20;
        printf("y = %d\n", y);
        x = 30;
        {
            int z = 50;
            y = 60;
            printf("z = %d\n", z);
            printf("x = %d\n", x);
            printf("y = %d\n", y);
        }
        // z = 100; /* Invalid! */
        y = x;
        printf("x = %d\n", x);
        printf("y = %d\n", y);
    }
    // y = 500; /* Invalid! */
    printf("x = %d\n", x);
    return 0;
}
```

## Function Parameters and Block Scope

**Formal parameters** (function parameters) also adhere to the **block scope** rule. These variables are known within the function's main block. The scope of a function parameter variable ends when the main block of the function closes. That is, the scope of a function parameter variable is the function's main block.

    void func (int a, double b)
    {
        /* a and b are known everywhere within this function. */
    }

In the example above, the variables named `a` and `b`, which are the formal parameters of the `func` function, can be used anywhere within the `func` function.

---

## Global Variables

You know that variables can also be defined outside of blocks in the C language. Variables defined outside of blocks are called **global variables**.

The compilation process has a direction: it is top-down within the source code. Whether a variable is local or global, its use before its definition is invalid. **Global variables** are known everywhere from the point they are defined until the end of the source file:
```c
#include <stdio.h>
int g; // Global variable
void func()
{
    g = 10;
}
int main()
{
    g = 20;
    printf("g = %d\n", g);
    func();
    printf("g = %d\n", g);
    /* g = 20 */
    /* g = 10 */
    return 0;
}
```
In the example above, since the variable `g` is defined outside a block—or not defined within any function—it is a global variable. The scope of the variable `g` is **file scope**. That is, the variable `g` can be used within all functions after its definition. In the program above, the global variable `g` is first assigned the value 20. Then, this value is printed to the screen using the `printf` function. After that, the `func` function is called. When `func` is called, the flow of the code passes to the `func` function. The global variable `g` is also known within the `func` function. After the global variable `g` is assigned the value 10 within the `func` function, this value is printed to the screen again using the `printf` function.

---

## Variables with the Same Name

More than one variable with the same name can be defined in the C language. The general rule is this: **If the scopes of two variables are the same, these variables cannot have the same name.** Having the same name will cause a compile-time error. What does it mean for two variables to have the same scope? If the scopes of two variables end with the same closing curly brace (`}`), then these variables have the same scope.
```c
{
    float a;
    int b;
    double a; // Invalid
    {
        int c;
        /*...*/
    }
}
/* Invalid because both 'a' variables have the same scope. */
```

More than one variable with the same name, but with **different scopes**, can be defined. For the compilers, the fact that these variables have the same name is no longer important. They are stored in different places in memory. Consider the following example:

```c
#include <stdio.h>
int main()
{
    int x = 100;
    printf("%d\n", x);
    {
        int x = 200; // A different x
        printf("%d\n", x);
        {
            int x = 300; // A third x
            printf("%d\n", x);
        }
    }
    return 0;
}
```
There is no error in the program snippet above because the scopes of all three $x$ variables are different from each other. So, when the name $x$ is used in the inner blocks in the example above, which $x$ variable does the compiler associate it with?

If a point in the source code is within the scope of multiple variables with the same name, which of these variables is accessed at that point?

When the compiler encounters the use of a name, it tries to find which software entity this name belongs to. This process is called **"name lookup."** Name lookup is performed from the **narrowest scope** to the **widest scope**. That is, the compiler first searches for the name in its own block. If the name is not defined within this block, it is then searched for in the enclosing blocks. If the name cannot be found in the enclosing blocks, it is then searched for in the global name space.

A name with a narrower scope **masks** or prevents the visibility of the same name in a wider scope. Consider the following program:
```c
void func1()
{
    int k;
    /***/
}
void func2()
{
    int k;
    /***/
}
void func3()
{
    int k;
    /***/
}
```

There is no error in the code snippet above. Although a variable named `k` is defined in all three functions, their scopes are completely different from each other.

Can a local variable have the same name as a global variable? Since the scopes of the two variables are not the same, this does not cause an error.

At a point where both a global variable and a local variable with the same name are accessible, the one accessed will be the **local variable**. This is because if there are multiple variables with the same name in the same scope, the one with the narrowest scope in that area is accessible. Examine the following code:

```c
#include <stdio.h>
int g = 20; /* g global variable */

void func()
{
    /* global g variable is assigned. */
    g = 100;
    /* the value of the global g variable is printed. */
    printf("global g = %d\n", g);
}

int main()
{
    int g; /* g local variable */
    /* local g variable is assigned */
    g = 200;
    /* local g is printed. */
    printf("local g = %d\n", g);
    func();
    /* local g is printed. */
    printf("local g = %d\n", g);
}
return 0; // Note: 'return 0;' should be inside 'main' block.
```

Since functions themselves are defined outside all blocks, they are also global entities. Indeed, functions can be called from anywhere in the source code. Since there cannot be more than one variable with the same name belonging to the same scope, there also cannot be more than one function with the same name.

> \[However, in C++, it is possible to define multiple functions with the same name but different parametric structures (function overloading).]

A declared name may not be accessible everywhere within its scope. This is because a name might be masked by the same name in a narrower scope. For this reason, in addition to "scope," one can also talk about the term **"visibility."**

> \[In C++, if a global name is masked by a local name, access to the global name is possible with an operator called the **scope resolution operator** (`::`).]

---

## Storage Duration of Objects

**Storage duration** (lifespan) is a term used to describe the period during the program's runtime in which objects occupy memory space. Not all variables defined within a source code are created simultaneously when the program starts running. Entities used in programs can be divided into three groups based on their storage duration:

1.  Static duration entities
2.  Automatic duration entities
3.  Dynamic duration entities

### i. Static Duration Entities

**Static duration entities** (static storage class) take their place in memory when the program starts running and persist until the program finishes executing; that is, they occupy memory. Static duration entities are typically written into the object code (`.obj`). In the C language, there are three distinct groups of static duration entities:

* **Global variables**
* **String literals** (text within double quotes)
* **Static local variables**

You will see string literals and static local variables later.

**Global variables** are static duration entities. That is, global variables are variables that live throughout the program's execution, meaning they occupy memory throughout the program's execution.

### ii. Automatic Duration Entities

**Automatic duration objects** are objects that are created at a certain time during the program's execution, remain active for a certain period, and then cease to exist—that is, their lifespan ends. The lifespan of such objects is shorter than the program's total runtime.

**Local variables** have automatic duration. They are created when the execution of the block in which they are defined starts during program runtime, and they are destroyed when the execution of the block ends, meaning their lifespan terminates.

    void func(int a, int b)
    {
        int result;
        /***/
    }

A local variable named `result` is defined within the main block of the `func` function above. The `result` variable is created when the `func` function's code is entered during program execution. When the program flow exits the `func` function, the lifespan of the `result` variable ends.

There is also a difference between static duration variables and automatic duration variables in terms of **initialization**. Global variables, which have static duration, can be initialized just like local variables.

A local variable that has not been initialized or assigned a value contains a **garbage value**. This value is the value formed by the 1s and 0s currently present in the memory location allocated for that variable.

It is guaranteed that static duration variables that are not initialized will be initialized to a value of **0**. Global variables that are not initialized or assigned a value always contain the value **0**. That is, these variables are initialized to 0 with the help of code generated by the compiler.

Compile and run the following program:

    #include <stdio.h>
    int g;
    int main()
    {
        int y;
        printf("g = %d\n", g);
        printf("y = %d\n", y);
        return 0; // Note: 'return 0;' should be inside 'main' block.
    }

Using a local variable without initializing it or assigning a value to it is a programming error. Almost all compilers issue a logical warning message in such cases.

> \[There is no such strict requirement in C++.]

Global variables can only be initialized with **constant expressions**. Variables or function call expressions cannot be used in the expression (initializer) used to initialize global variables. The expression must consist only of constants.

> \[Initializing global variables with non-constant expressions is valid in C++. Most modern C compilers also tend to consider the code valid when global variables are initialized with non-constant expressions. For portability, we advise against this practice.]

However, there is no such restriction on initializing local variables.

    #include <stdio.h>
    int func(void);
    int x = 5;
    // int y = x + 5; /* Invalid */
    // int z = func(); /* Invalid */

    int main()
    {
        // Assume 'b' is accessible, or defined elsewhere for this example to work.
        // int a = b; 
        // int k = b - 2;
        int m = func();
        /***/
    }
    // In the program above, the definitions of variables a, k, m within the main function are valid (assuming b and func() are defined/accessible).

### iii. Dynamic Duration Entities

Objects whose memory locations are allocated using dynamic memory functions have **dynamic duration**. You will see objects created with dynamic memory functions later.

---

## Comparison of Global and Local Variables

When a variable is needed in a program, using a global or local variable may bring some advantages or disadvantages. However, some drawbacks of global variables can be discussed in general. Unless there is a special situation, **local variables should be preferred over global variables**, and global variables should only be used when necessary. Global variables can cause the following disadvantages:

1.  Since global variables have static duration, they remain in memory until the end of the program. This leads to less efficient use of memory.
2.  Since global variables are shared by all functions, source files that use global variables heavily are harder to read.
3.  In a source file that frequently uses global variables, the cost of bug hunting is higher. If there is a bug related to a global variable, all functions must be searched to find this bug. The ability of all functions to access global variables also creates the risk that a function might accidentally modify a global variable.
4.  Modifying a source file that uses global variables also requires more effort. Different parts of the source code become tightly coupled through the use of global variables. In this case, making a change in one place in the source code may require making changes in other places as well.
5.  Most programmers want to use global variables as little as possible. This is because functions that use global variables cannot be easily reused in other projects. The same global variables must be defined in the projects where they are used. Therefore, the reusability of functions written based on global variables decreases.
6.  Global variables pollute the global namespace. This point will be revisited when the concept of **"linkage"** is discussed later.

---

## Objects Holding Function Return Values

Functions convey their return values to the calling functions with the help of a **temporary object**. Examine the following program:

    #include <stdio.h>
    int add(int x, int y)
    {
        return x + y;
    }
    int main()
    {
        int a, b, sum;
        printf("Enter two numbers: ");
        scanf("%d%d", &a, &b);
        sum = add(a, b);
        printf("sum = %d\n", sum);
        return 0;
    }

The return type of a function actually means the type of the temporary object that will carry the function's return value. You can see the `add` function defined above is called from within the `main` function. When the program flow reaches the `return` statement within the `add` function, a temporary object is created. This temporary object is initialized with the `return` expression. That is, the `return` expression is actually the expression that initializes the temporary object created. A call to a function that produces a return value represents the temporary object holding that function's return value. So, how long is the lifespan of this temporary object? This object is created by the `return` statement and is destroyed when the evaluation of the expression containing the function call ends. Thus, after the execution of the statement:

    sum = add(a, b);

within the `main` function in the example, the lifespan of the temporary object also ends.

---
Would you like to move on to the next topic, **Linkage**, or review the comparison of global and local variables?