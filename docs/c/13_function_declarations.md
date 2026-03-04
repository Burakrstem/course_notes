# ✍️ Function Declarations (Prototypes)

The compilation process is performed by the compiler from top to bottom within the source code. During the compilation phase, when the compiler encounters a function call, it must know the **return type** of the called function. A function's return type determines which CPU register the return value will be retrieved from. Obtaining this information at compile time is essential for the program to run correctly.

If the definition of the called function is placed **before** the calling function, the compiler already has information about the return type of the called function before it encounters the function call expression during the compilation process. This is because compilation is performed from top to bottom.

Examine the following example:

    #include <stdio.h>
    double get_val(double x, double y)
    {
        return x * y / (x + y);
    }
    int main()
    {
        double d;
        d = get_val(4.5, 7.3);
        printf("d = %lf\n", d);
        return 0;
    }

In the example above, the `get_val` function is defined before the `main` function that calls it. Before reaching the call expression, the compiler already knows the return type of the `get_val` function.

If the definition of the called function is made **after** the calling function, the compiler cannot know the return type of the called function when it reaches the function call expression. This is a problematic situation:

    #include <stdio.h>
    int main()
    {
        double d;
        // The return type of the function is unknown.
        d = get_val(4.5, 7.3);
        printf("d = %lf\n", d);
        return 0;
    }
    double get_val(double x, double y)
    {
        return x * y / (x + y);
    }

Above, the `get_val` function is called within the `main` function. However, the definition of the `get_val` function is placed later in the source code than the `main` function. When the compiler encounters the call to the `get_val` function during compile time, it does not know the return type of this function.

If a C compiler encounters a function call expression and has not yet obtained information about the function's return type, it **assumes** that the return value of the function in question is of type `int`.

In the example above, the compiler assumes that the return value of the `get_val` function is of type `int` and generates code accordingly. Later, when the compilation flow reaches the function's definition, it sees that the function's return value is of type `double`. Compilers report this contradictory situation, which prevents target code generation, with an error message.

> \[In C++, if the called function is not defined before the calling function, the function's return value is not assumed to be of type `int`. In this case, a function declaration is mandatory. A compile-time error occurs if this declaration is not made.]

Defining the called function above the calling function is not always possible. Dozens of functions can be defined in a large source file. It may be the case that every defined function calls each other. In this case, it becomes very difficult to define the function to be called before the calling function. Furthermore, two functions can call each other in C. This corresponds to a **recursive** call mechanism. In such a function design, defining the called function first is no longer possible.

    double func1()
    {
        /***/
        func2();
        /***/
    }
    double func2()
    {
        /***/
        func1();
        /***/
    }

No matter which of the function definitions above is placed higher, a contradictory situation will still occur.

Moreover, the definitions of the called functions often do not reside in the same source file. In this case, how does the compiler receive information about the called function?

---

## 💡 What is a Function Declaration?

A **function declaration** (or function prototype) is a statement that provides information about a function to the compiler. The compiler generates the code related to the function call based on the information it receives from here. Additionally, the compiler can perform some checks with this information. It prevents possible mistakes by generating error or warning messages as a result of these checks.

### General Form of Function Declarations

The general form of a function declaration is as follows:

    [return_type] <function_name> ([type1], [type2].....);

For example, the declaration for the `get_val` function can be made in the following form:

    double get_val(double, double);

The compiler obtains the following information from such a declaration:

1.  The return value of the `get_val` function is of type `double`. After this information, the compiler no longer assumes the return value to be of type `int` if this function is called; it generates code based on obtaining a `double` return value.
2.  The `get_val` function has two parameters. After this notification, the compiler has the opportunity to check whether this function is called with the correct number of arguments. If it sees that the function is called with the wrong number of arguments, it reports the situation with an error message.
3.  The parameters of the `get_val` function are of type `double`. After this information, the compiler applies automatic type conversion to the arguments if arguments of other types are sent to the function. This topic will be covered in the section named "Automatic Type Conversion."

Example declarations are given below:

    int multiply (int, int);
    double power (double, double);
    void clrscr(void);

Just as in function definitions, if the function's return value is not specified in function declarations, the compiler assumes that the declaration is made for an `int` return value:

    func(double);

is completely equivalent to:

    int func(double);

However, it is better for readability to explicitly write the `int` keyword.

> \[In C++, the return type must be written.]

If the declared function does not produce a return value, the **`void`** keyword must be used:

    void func(double);

Function declarations only provide information to the compiler. This is not a **definition** operation. Therefore, the compiler does not allocate memory for the program's runtime as a result of the declaration.

### Omitting Parameter Types in a Declaration

Before the standardization process of C, the parameter parenthesis was often left empty in function declarations. No information was given about the types and number of the function's parameters in the declaration. The sole purpose of the declaration was to inform about the function's return value type. Therefore, a declaration like:

    double func();

did not mean that the `func` function had no parameters. With the addition made to function declarations during the standardization process, the possibility was given to provide information about the number and types of the function's parameters. However, this raised a problem. If code written according to old rules was compiled according to new rules, and a declaration like `double func();` was interpreted as the function having no parameters, a syntax error would occur if the declared function was called as, for example, `func(5)`. To ensure backward compatibility, a decision was made: If the function has no parameters, the `void` keyword must be written inside the parameter parenthesis in the declaration. Examine the following declarations:

    double foo();
    double func(void);

According to the standards, the compiler concludes from the declaration of the `foo` function that no information has been given about the `foo` function's parameters, and when it encounters a function call, it does not check the number of arguments sent to the function. That is, a function declared this way can be called with the desired number of arguments in compliance with the rules.

From the declaration of the `func` function, the compiler concludes that the `func` function has no parameters, and if it encounters one or more arguments sent to the function when it encounters a function call, it determines this as a compile-time error.

> \[In C++, both declarations are equivalent. That is, there is no difference between leaving the parameter parenthesis empty and writing the `void` keyword in a function declaration.]

### Writing Parameter Names in Declarations

In function declarations, the names of the parameters can also be written after their types. The scopes of the parameter names included in declarations are limited only to the declaration's parameter parenthesis. Standards defined this situation with a separate scope rule. Names used inside the function declaration parenthesis are only known within that parenthesis. These names are not known when exiting this parenthesis. This scope rule is called the **"Function Prototype Scope"** rule.

The parameter names written here are only useful for readability. There is no requirement for these parameter names to be the same as the parameter names used in the function's definition.

Let's rewrite the declarations above by giving names to the parameters:

    float calculate(float a, float b);
    int multiply(int number1, int number2);
    double pow(double base, double exp);

Those who read only the function declarations without seeing the function definitions get an idea of what information these variables expect from function calls based on the parameter names used in the declarations.

### Location of Function Declarations

A function's declaration can be made anywhere in the program. If declarations are made at the **global level**, meaning outside all blocks, they remain valid within the area from where they are declared until the end of the file. The function's declaration must be made before the function in question is called.

However, although rarely encountered in applications, function declarations can also be made at the **local level**. In this case, information is given only to the block where the declaration was made. In other words, a function declaration, like variable definitions, adheres to the scope rule.

Generally, function declarations are made at the top of the program or inside one of the header files defined by the programmer. **Header files** will be discussed in detail later.

### Declarations of Standard C Functions

The declarations of standard C functions are placed inside standard header files. In applications, the programmer does not write the declaration of a standard C function himself; he includes the header file containing this declaration in his source code using the **`#include`** preprocessor command.

---

## 🚫 Not Making a Function Declaration

There is no requirement for the source code of a called function to be in the same source file. When the compiler encounters a function call, it does not search for the source code of the called function. It writes information indicating that the relevant function has been called into the generated object file for the linker. Finding the compiled code of the called function and combining the object files appropriately is the job of the **linker** program.

Suppose the definition of a called function is not in the same source file. What happens if the declaration of the called function is not made? In the C language, this is **not a syntax error**.

> \[In C++, this situation is directly a syntax error. The compiler must see the definition or declaration of a function before the function in question is called.]

In the C language, the compiler produces the object file by assuming the return value of an undeclared function is of type `int`. If the function's return value is not used in the source code, or if the return value of the called function is indeed of type `int`, no problem arises. However, if the function's return value is used and the return value is not of type `int`, a **runtime error** is in question. Compile and run the following example on your compiler:

    #include <stdio.h>
    int main()
    {
        double d;
        d = sqrt(9.); // sqrt is defined in math.h, but math.h is not included.
        printf("d = %lf\n", d);
        return 0;
    }

No error occurs during the compilation of the program above. However, the compiler generates code assuming the return value of the called `sqrt` function is of type `int`. In fact, the return value of the compiled `sqrt` function is of type `double`. During runtime, instead of the `double` value returned by the function, an `int` value is attempted to be pulled as a result of the code produced by the compiler. This is a program runtime error.

Now, compile and run the program again by adding the following declaration before the `main` function:

    double sqrt(double val);

The declarations of standard C functions are in header files with the `.h` extension. By including the relevant header file in the source code with the **`#include`** preprocessor command, the standard C functions are actually declared. Indeed, when the source program, which is the output of the preprocessor program, is given to the compiler, the declaration of the function is found in this included file. Undoubtedly, instead of including the relevant header file in the source code, the declarations of standard C functions can also be made by the programmer. In this case, no error will occur either. In the example above, the declaration of the called `sqrt` function can be added to the source code in two ways:

i. By including the header file containing the function declaration in the source code with a preprocessor command:

    #include <math.h>

ii. The function's declaration can be written directly:

    double sqrt(double val);

However, the preferred method should be to include the header file in the source code. This is because the programmer might write the function's declaration incorrectly.

The reason for including header files in the source code is not only function declarations. Header files also contain other declarations: Macros, symbolic constants, type name declarations, structure declarations, etc.

### Function Declaration and Argument-Parameter Compatibility Check

The main purpose of function declarations, as stated above, is to inform the compiler about the function's return type. However, if the types of the function's parameters are specified in the function declarations (prototype), the compiler compares the number of parameters in the prototype declaration with the number of arguments sent to the function in the function call expression. For example:

If a declaration like:

    float process(float, float);

is written, a compile-time error occurs if the `process` function is called with too few or too many arguments.

    x = process(5.8);               /* Invalid! Call with insufficient argument */
    y = process(4.6, 7.9, 8.0)      /* Invalid! Call with excessive arguments */

### Details Regarding Declaration Syntax

The declarations of functions with the same return type can be written separated by commas, but such a declaration form is generally not preferred by programmers.

    double func1(int), func2(int, int), func3(float);

The declaration above is valid. With such a declaration, the compiler is informed that the return value of all functions `func1`, `func2`, and `func3` is of type `double`.

Function declarations can also be combined with variable definitions. This is also not preferred for readability.

    long func1(int), long func2(void), x, y;

With the declaration statement above, the declarations of `func1` and `func2` are made, while the variables $x$ and $y$ are defined.

Making a function declaration does not necessitate defining or calling that function. Not defining a declared function does not cause an error.

A function's declaration can be made multiple times. This does not cause a compile-time error. However, the declarations made must **not contradict** each other.

Suppose declarations for the same function are made in different places in the source file, in the following forms:

    int func (int, int);
    func (int, int);
    int func(int x, int y);
    func(int number1, int number2);

There is no contradiction in any of the declarations above. Using different names for the function parameters in subsequent declarations does not create a contradiction because the scope of these names is only within the parenthesis where the declaration is made. However, the following different declarations are invalid:

    double func(int x, double y);
    double func(int x, float y);  /* Invalid! Conflict in parameter type */
    long sample(double x);
    sample (double x); /* Invalid! Return type conflict (assumed int vs declared long) */

### Locations of Function Declarations in Multi-File Projects

In C and C++ languages, a project often consists of more than one source file, i.e., modules. In most source files, functions defined in other source files are called. That is, there is often a service-client relationship between source files. A module that will serve other modules is written as two separate files. One of the files is the implementation file, which has the `.c` extension. Declarations regarding the services provided by this file to other modules are placed in another file with the `.h` extension. This file is called a **header file**. Declarations of functions that will serve other modules should be placed inside the header file.

The client source file includes the content of the server module's header file in its own file using the **`#include`** preprocessor command. Thus, the declaration is made. This situation will be revisited in the section on "Preprocessor Commands."