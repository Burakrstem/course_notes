# ⚙️ Macros

Structured programming relies on subprogramming. A problem solution is broken down into easier steps, and functions are defined for these steps. The source code of some of the defined functions may be very short. Consider a function defined as follows:

    int get_max(int a, int b)
    {
        return a > b ? a : b;
    }

The `get_max` function returns the larger of the two numbers sent to it. Now let's ask this question: Should a function with such short source code be defined? Wouldn't it be better to place the function's code directly where the function call is, instead of defining a function?

Suppose the larger of two numbers needs to be found in a code snippet:

Instead of a statement like:

    x = get_max(y, z);

couldn't a statement like:

    x = y > z ? y : z;

be written?

Should a function be defined and the defined function be called, or should the function's code be written directly?

First, let's focus on the arguments supporting function definition:

1.  **Function call often creates code with higher readability**, especially if the function's name is well chosen. Examine the example below:

        a = get_max(ptr->no, per.no);
        a = ptr->no > per.no ? ptr->no : per.no;

    In the first statement, a function named `get_max` is called. In the second line, the expression with the larger value of the two expressions is found without calling a function. Which statement has better readability?

2.  **Function call reduces source code size** in most cases. Especially if the operation related to the function is repeated frequently in the source code, defining a function and calling it in various places reduces the source code size.

3.  **Function call makes modifying the source code easier**: Suppose the larger of two values is found and used in many places within the source code. Later, imagine that a change needs to be made at those points in the source code, and the smaller of the two values needs to be found and used at the same points. If the code were written explicitly instead of a function call, making the change would be much more difficult.

4.  **Function call increases the possibility of debugging.** Debugger programs generally provide better support for function calls than for explicitly written code.

5.  **Function call allows the compiler to perform some checks.** The compiler checks whether the total number of arguments sent to the function is equal to the total number of parameters of the function. Additionally, the compiler checks whether the types of the arguments sent to the function are compatible with the types of the function's relevant parameters.

Now let's look at the advantages that can be obtained when the function's code is written directly instead of making a function call:

A call made to a function has an added cost in terms of processor time and memory usage. Additional machine instructions need to be executed for the execution of the function entry and function exit code. If present, the function's parameters also occupy space in memory when the function is called. In many cases, paying this cost is undesirable, especially for functions whose source code is very short and which are called frequently within the source file.

If the code is written explicitly instead of making a function call, the compiler can perform a more efficient **optimization** based on the location of the code.

## 📝 What is a Macro?

A **macro** is a tool that allows the benefit of some advantages of a function call without defining a function. Since there is no actual function definition, there is no added overhead paid for the function.

Macros are defined with the preprocessor program's **`#define`** directive. A macro definition is a parametric replacement directive given to the preprocessor program.

    #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

* `MAX` is the name of the defined macro. This name must be followed by an "opening parenthesis" character.
* The names declared separated by commas inside the parenthesis following the macro name are called **"macro parameters."**
* The tokens following the space after the closing parenthesis are the **"macro replacement list."**
* In the replacement list, macro parameters can be used as many times and in any order desired.

When the preprocessor program encounters the name `MAX` in the subsequent section of the source code, it accepts the expressions inside the parenthesis as macro arguments. A similar replacement operation is performed where the macro call is located, using the macro arguments in the same way the macro parameters are used in the macro definition's replacement list. Examine the code below:

    #include <stdio.h>
    #define ISEVEN(a)    (!((a) & 1)) // Checks if LSB is 0
    #define MAX(a, b)    ((a) > (b) ? (a) : (b))
    
    int main()
    {
        int x, y;
        printf("enter two numbers :");
        scanf("%d%d", &x, &y);
        
        if (ISEVEN(x)) // Macro call 1
            printf("%d is an even number!\n", x);
        else
            printf("%d is an odd number!\n", x);
            
        printf("%d and %d numbers, the larger is = %d\n", x, y, MAX(x, y)); // Macro call 2
        return 0;
    }

In the `main` function above, two macros named `ISEVEN` and `MAX` are defined. After the preprocessor passes over the macro definition, when it encounters the line:

    if (ISEVEN(x))

it understands that the name `ISEVEN` belongs to the previously defined macro and that the token $x$ is used as the macro argument. When the preprocessor program performs the relevant replacement operation, this line is transformed into the following form:

    if ((!((x) & 1)))

Similarly, the line:

    printf("%d and %d numbers, the larger is = %d\n", x, y, MAX(x, y));

is transformed by the preprocessor expanding the macro named `MAX` into:

    printf("%d and %d numbers, the larger is = %d\n", x, y, ((x) > (y) ? (x) : (y)));

## 🛡️ Writing Safe Macros

Examine the following macro:

    #define Square(x) x * x

Suppose this macro is used in the source code as follows:

    void func()
    {
        int a = 10;
        int b;
        b = Square(a + 5); // Macro call
        /***/
    }

If `Square` were a function, the value of the argument expression $a + 5$ would be calculated first. Since the value of the argument expression is 15, the called function would return the value 225. However, the preprocessor program performs a replacement operation as follows:

    b = a + 5 * a + 5;

Since the multiplication operator has higher precedence than the addition operator, the value assigned to the variable $b$ here would be 65, right? To solve this kind of precedence problem, macro parameters must be enclosed in parentheses in the expansion list:

    #define Square(x) (x) * (x)

This time, the same expression is expanded by the preprocessor as follows:

    b = (a + 5) * (a + 5);

The value assigned to the variable $b$ becomes 225. However, now consider that the macro is used as follows:

    b = 100 / Square(a);

If `Square` were a function, the value 1 would be assigned to the variable $b$, right? However, the macro above is expanded by the preprocessor as:

    b = 100 / (a) * (a);

Here, the value assigned to the variable $b$ becomes 100.

To solve this kind of precedence problem, the macro expansion list must be enclosed in outer parentheses.

    #define Square(x) ((x) * (x))

This time, the same expression is expanded by the preprocessor as follows:

    b = 100 / ((a) * (a));

This time, the value assigned to the variable $b$ becomes 1.

Enclosing the macro expansion list in outer parentheses and enclosing each macro parameter in parentheses within the expansion list is still **not enough to make macros reliable**. Indeed, the biggest problem with macros is the reliability problem. Examine the following code:

    #include <stdio.h>
    #define Square(x) ((x) * (x))
    
    int func(int val); // Assume func is defined elsewhere
    
    int main()
    {
        int x = 10;
        int y = Square(x++); // Macro call 1
        int z = Square(func(y)); // Macro call 2
        /*********/
        return 0;
    }

In the statement `y = Square(x++);`, if `Square` were a function, this function would be called with the value 10. Due to the side effect of the postfix `++` operator, the value of the object $x$ would become 11. However, when the macro is expanded by the preprocessor, the code the compiler sees is:

    y = ((x++) * (x++));

This situation is **"undefined behavior"** because the macro causes the argument expression with a side effect to be evaluated multiple times.

The preprocessor expands the statement `z = Square(func(y));` as follows:

    z = ((func(y)) * (func(y)));

The compiled code causes the `func` function to be called **twice**. However, if `Square` were a function, the return value produced by the called `func` function would be sent as an argument to the `Square` function only once.

## 🌟 Example Macros

Examples of some useful macro definitions are given below. Examine the examples:

    #define GETRANDOM(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min)) // Random number in [min, max]
        
    #define ISLEAP(y) \
        (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0) // Checks for leap year
        
    #define SWAPINT(x, y) ((x) ^= (y) ^= (x) ^= (y)) // Swaps two integers
    
    #define XOR(x, y) \
        ((!(x)) ^ (!(y))) // Logical XOR operation

The macro named `GETRANDOM` defined above results in a random integer being generated between the values `min` and `max`.

When the `ISLEAP` macro is expanded by the preprocessor, the value 1 is produced if the argument expression is a leap year, and the value 0 otherwise. In this case, the macro is used like a testing function.

The `SWAPINT` macro expands into an expression that swaps the values of the integer variables that are its arguments.

A macro does not have to have parameters. Examine the `randomize` macro defined below:

    #define randomize() \
        srand((unsigned int)time(NULL)) // Initializes the random number generator

## # The Preprocessor Stringizing Operator (`#`)

The `#` token in the expansion list of a macro definition is an operator of the preprocessor program. The `#` operator is a **unary prefix** operator. The operand of this operator must be one of the macro parameters. This operator cannot be used in parameterless macros.

When the preprocessor expands the macro, it encloses the macro argument corresponding to the macro parameter in **double quotes**:

Examine the code below:

    #include <stdio.h>
    #define printint(x) printf(#x " = %d\n", x) // #x is stringized argument
    
    int main()
    {
        int a = 10;
        int b = 20;
        printint(a);        // Macro call 1
        printint(a + b);    // Macro call 2
        return 0;
    }

In the example above, the macro parameter $x$ is made the operand of the stringizing operator in the expansion list of the `printint` macro. The preprocessor program transforms the code of the `main` function into the following form:

    int main()
    {
        int a = 10;
        int b = 20;
        printf("a" " = %d\n", a); // Expansion of printint(a)
        printf("a + b" " = %d\n", a + b); // Expansion of printint(a + b)
        return 0;
    }

Recall that strings separated by whitespace characters are automatically combined into a single string by the compiler. When the program is compiled and run, the screen output is as follows:

    a = 10
    a + b = 30

If a string literal is provided as a macro argument, the double quote (`"`) characters at the beginning and end of the string, and the backslash (`\`) and double quote (`"`) characters inside the string, are automatically preceded by a backslash character in the macro expansion. Examine the code below:

    #include <stdio.h>
    #define print(x) printf(#x "\n")
    
    int main()
    {
        print(The text will appear on the screen); // Macro call 1
        print("The text will appear on the screen in double quotes"\n); // Macro call 2
        print("\""\n); // Macro call 3
        return 0;
    }

When the program is compiled and run, the screen output is as follows:

    The text will appear on the screen
    "The text will appear on the screen in double quotes"
    "\""

## 🔗 The Preprocessor Token Pasting Operator (`##`)

The second operator of the preprocessor program is the **token pasting operator (`##`)**. The token pasting operator is binary infix. It can be used in macros with or without parameters. It is not mandatory for its operands to be one of the macro parameters. The preprocessor combines the operands of the token pasting operator, making a single token from its operands. Examine the following example:

    #include <stdio.h>
    #define paste(x, y) x##y
    
    int main()
    {
        int paste(a, 1); // Macro call 1
        a1 = 10;
        printf("a1 = %d\n", a1);
        return 0;
    }

In the example above, the macro arguments $a$ and 1 are combined by the preprocessor expanding the macro named `paste`, resulting in the token `a1`.

## 🤝 A Macro and a Function Sharing the Same Name

In some libraries, certain functions are defined with the same name as both a macro and a function. The purpose of this is to allow the programmer to optionally choose between macro usage and function call. Let both a macro named `square` and a function named `square` be declared:

    int square(int);
    #define square(a) ((a) * (a))

Suppose there is a statement like the following in the source code:

    x = square(y);

Undoubtedly, the macro is used in such a statement. This is because the preprocessor processes the program code before the compiler program. By the time it is the compiler's turn, the preprocessor has already completed the replacement operation for the relevant macro. However, two methods can be used to choose the function call instead of the macro:

1.  **The macro definition can be removed using the `#undef` preprocessor directive:**

    ```c
    #undef square
    x = square(y); // Now calls the function square
    ```

    When the preprocessor program encounters the `#undef` directive, it removes the macro definition, and when it sees the name `square` in the subsequent lines, it does not perform a replacement operation.

2.  **The name `square` can be enclosed in parentheses to disable the macro:**

    `x = (square)(y);`

    In this case, since the first token following the name `square` is not the opening parenthesis `(`, the preprocessor program does not perform a replacement operation. However, there is no situation that prevents the function call. You know that a function name specifies an address. The name `square`, which will be converted to a function address, is enclosed in parentheses in the expression above.

3.  **A function can be called using a function pointer:**

    ```c
    int square(int);
    void func()
    {
        int (*fp)(int) = &square;
        int result = fp(5); // Calls the function via pointer
    }
    ```

Compilers can also define functions related to the standard library as macros. For example, most compilers define the character testing functions declared in the `ctype.h` header file as macros as well.

### Differences Between Macros and Functions

1.  **Macros often result in the generation of code that runs faster than the function performing the same task.** This is indeed the goal when macros are used.
2.  **Macros often increase the size of the source code** because they are expanded by the preprocessor everywhere they are used. In most cases where the source code size increases, the size of the executable file also increases. However, no matter how many times a function is called, the definition of that function is located in the source code only once.
3.  **Undesirable situations can arise as a result of macro expansion if macro parameters are used more than once in the macro expansion.** If the expression used as a macro argument has a side effect, this side effect occurs more than once. However, no such risk exists when functions are in question.
4.  The address of a function can be stored in function pointers, and some operations can be performed. However, a macro does **not** have an address.
5.  When a macro is in question, the preprocessor program can check the compatibility of the number of arguments given to the macro with the number of macro parameters. However, the preprocessor program **cannot check the type compatibility** of the macro arguments and macro parameters; macros are type-independent. However, since functions are written related to types, they are subject to type checks by the compiler. The compiler can generate an error or warning message if the types of the arguments sent to the function and the function parameters are incompatible.

### Macro Expansions Continuing on the Next Line

The writing of a macro expansion list does not have to end on the line where the macro is defined. The writing of the macro expansion list can continue on the next line. For this, the backslash character `\` is used before moving to the next line.

### Creating a Function Template with Macros

A function template can be prepared using macros. The example below prepares a function template that finds the largest element of an array:

    #include <stdio.h>
    #define generic_max(T) \
        T getmax_##T(const T *ptr, size_t size) {\
            int k; T max = *ptr; for (k = 1; k < size; ++k)\
            if (ptr[k] > max) max = ptr[k]; return max;}
    
    generic_max(int)    // Expands to getmax_int function definition
    generic_max(double) // Expands to getmax_double function definition
    
    int main()
    {
        int a[10] = {1, 4, 5, 7, 8, 9, 10, 2, 3, 6};
        double b[10] = {1.2, 3.5, 7.8, 2.4, 4.4, .7, 3.2, 4.8, 2.9, 1.};
        printf("largest element of array a = %d\n", getmax_int(a, 10));
        printf("largest element of array b = %lf\n", getmax_double(b, 10));
        return 0;
    }

You see that the name $T$ is used as the macro parameter in the definition of the macro named `generic_max`. This name is used as type information. Different function names are obtained as a result of the macro expansion with the preprocessor token pasting operator.

### Using the Macro Name in Macro Expansion

A macro name or a symbolic constant can be included in the replacement list. This situation is called a **"self-referential macro"** in English. If the macro's own name is included in the expansion list, the preprocessor does not perform a recursive replacement operation.

Examine the following example:

    #define max (4 + max)

Suppose the name `max` is the name of another variable used in the program.

    x = max;

When the preprocessor program passes over the statement above, it transforms this statement into the form:

    x = 4 + max;

And then it no longer subjects the name `max` to a replacement operation again.

### The Standard `offsetof` Macro

This macro is defined in the `stddef.h` header file. The macro has two parameters. The first parameter is the name of a structure type, and the second parameter is a member of the structure. The value of the constant expression resulting from the macro expansion is the **offset value** indicating the position of a structure member within the structure object. This value is $0$ for the first member of the structure.

Examine the following example:

    #include <stdio.h>
    #include <stddef.h>
    struct Date {
        int day, mon, year;
    };
    int main()
    {
        printf("%zu\n", offsetof(struct Date, day)); // Output: 0
        printf("%zu\n", offsetof(struct Date, mon)); // Offset of 'mon' in the structure
        printf("%zu\n", offsetof(struct Date, year)); // Offset of 'year' in the structure
        return 0;
    }

The `offsetof` macro is defined in most compilers as follows:

    #define offsetof(type, member) \
        ((size_t)&((type *)0)->member)