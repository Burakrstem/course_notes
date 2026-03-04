# ⚙️ Preprocessor Directives (2)

## What is Conditional Compilation?

**Conditional compilation** is the process where the compilation operation is performed based on a condition or some conditions. Certain parts of the written source code are given to the compiler by the preprocessor program, while some parts are not. The source code to be given to the compiler is selected by the preprocessor program.

### Conditional Compilation Preprocessor Directives

The preprocessor directives used for conditional compilation are:

* `#if`, `#else`, `#elif`, `#ifdef`, `#ifndef`, `#endif`

### The `#if` and `#endif` Preprocessor Directives

The argument of the `#if` preprocessor directive must be a **constant expression of an integer type**. If the value of the expression following the `if` word is a non-zero value (true), the section between the `#if` command and the `#elif`, `#else`, or `#endif` commands is given to the compiler. If the `#if` expression is false, i.e., the value of the expression is zero, the section between the `#if` command and the `#else` is not given to the compiler. Compile and run the following program:

    int main()
    {
    #if 1 // True
        printf("this text will appear on the screen\n");
    #endif
    
    #if 0 // False
        printf("this text will not appear on the screen\n");
    #endif
        return 0;
    }

The expression to be used in the `#if` command must be of an integer type. The following can be used in this expression:

* **Integer literals** can be used. The preprocessor program assumes all number literals used are of type signed `long` or unsigned `long`.
* **Character literals** can be used.
* **Arithmetic operators** (`+`, `-`, `*`, `/`, `%`), **comparison operators** (`<`, `<=`, `>`, `>=`, `==`, `!=`), **bitwise operators** (`~`, `&`, `^`, `|`), and **logical operators** (`!`, `&&`, and `||`) can be used. **Short-circuit behavior** applies to the use of the `&&` and `||` operators.
* All replacement operations related to **symbolic constants and macro definitions** are performed before the value of the `#if` expression is calculated.
* All names that are **not symbolic constants or macro names** are assumed to have the value **0**.
* The **`sizeof` operator cannot be included** in the `#if` expression. Literals from enumeration types are **not** treated as the values they represent. If an enumeration constant is used in the `#if` expression, this constant is treated as the value **0**, just like all names that are not macro names.
* Other preprocessor directives can be located in the region between the `#if` command and the `#endif` command. The preprocessor directives located in this region are executed only if the `#if` expression is true.
* Readability is increased if the expression following the `#if` command is repeated in a comment following the `#endif` command associated with this `#if` command. This situation is especially beneficial when `#if` commands are nested. Examine the following example:

    ```c
    #if MAX > 100
    #if MIN < 20
    #define LIMIT 100
    #endif /* MIN < 20 */
    #define UPPER_BOUND 2000
    #endif /* MAX > 100 */
    ```

### The `#else` Preprocessor Directive

An `#if` command can be followed by an **`#else`** command. In this case, if the value of the `#if` expression is a non-zero value, i.e., the expression is true, the source code segment between the `#if` and `#else` commands is given to the compiler. If this expression is false, the part between the `#else` and `#endif` commands is given to the compiler program. Thus, different code segments can be given to the compiler depending on whether an integer constant expression is true or false. Compile and run the following program:

    #include <stdio.h>
    #define MAX 100
    int main()
    {
    #if MAX > 10 // True
        printf("%d\n", MAX); // This part is compiled
    #else
        printf("**********\n");
    #endif /*MAX > 100 */
        return 0;
    }

### The `#elif` Preprocessor Directive

The word `elif` is obtained by combining and abbreviating the words **`else if`**.

Just like the `if` statement in the C language, another `#if` command can be located in the true or false part of an `#if` command. A ladder structure can be created with the `#if` and `#else` commands. The `#elif` command is a command that can be used for this purpose.

The **`#elif`** command is again followed by an integer constant expression. If this integer constant expression has a non-zero value, it is interpreted as true, and the part between the `#elif` command and the next `#elif` or `#endif` command following it is given to the compiler. Compile and run the following example:

    #include <stdio.h>
    #define MAX 60
    int main()
    {
    #if MAX > 10 && MAX <= 20 // False
        printf("(if)%d\n", MAX);
    #elif MAX > 20 && MAX <= 50 // False
        printf("(elif1)%d\n", MAX);
    #elif MAX > 50 && MAX < 100 // True
        printf("(elif2)%d\n", MAX); // This part is compiled
    #else
        printf("(else)%d\n", MAX);
    #endif
        return 0;
    }

### The `defined` Preprocessor Operator

In the section on macros, we first saw the preprocessor stringizing (`#`) and token pasting (`##`) operators. The 3rd and final operator of the preprocessor program is the **`defined` operator**. The `defined` preprocessor operator is followed by an identifier. This identifier can also be enclosed in parentheses:

    defined MAX
    defined (MAX)

If the identifier that is the operand of the `defined` operator is a previously defined symbolic entity, the `defined` operator produces the value **1**. If there is no symbolic constant defined with this identifier, the `defined` operator produces the value **0**.

Examine the following example:

    #include <stdio.h>
    #define MAX 100
    int main()
    {
    #if defined MAX && !defined MIN // MAX is defined, MIN is not defined
        printf("max = %d\n", MAX); // This part is compiled
    #endif
        return 0;
    }

### The `#ifdef` and `#ifndef` Preprocessor Directives

The `#ifdef` and `#ifndef` preprocessor directives can be used wherever the `#if` preprocessor directive is used:

The **`#ifdef`** preprocessor directive is followed by an identifier. If this identifier refers to a previously defined symbolic constant, the part up to the first `#else`, `#elif`, or `#endif` preprocessor command is given to the compiler. If a symbolic constant is not defined with the identifier following the `#ifdef` preprocessor directive, the part up to the first `#else`, `#elif`, or `#endif` command is not given to the compiler. The task performed by this command can also be performed by using the `#if` preprocessor command together with the `defined` operator:

A preprocessor command usage like:

    #ifdef IDENTIFIER

is synonymous with a preprocessor command like:

    #if defined (IDENTIFIER)

The **`#ifndef`** preprocessor directive is also followed by an identifier. If a symbolic constant with this identifier has **not** been previously defined with the `#define` preprocessor directive, the part up to the first `#else`, `#elif`, or `#endif` preprocessor command is given to the compiler.

If a symbolic constant is defined with the identifier following the `#ifndef` preprocessor directive, the part up to the `#else`, `#elif`, or `#endif` commands is not given to the compiler.

A preprocessor command like:

    #ifndef SYSTEM

is synonymous with a preprocessor command like:

    #if !defined (SYSTEM)

Compile and run the following program:

    #include <stdio.h>
    #define ID1
    int main()
    {
    #ifdef ID1 // ID1 is defined
        printf("this text will appear on the screen!\n"); // This part is compiled
    #endif
    
    #ifndef ID1 // ID1 is defined (not NOT defined)
        printf("this text will not appear on the screen!\n");
    #endif
        return 0;
    }

### The `#error` Preprocessor Directive

The **`#error`** preprocessor directive is used in conditional compilation.

When the preprocessor program encounters this directive, it terminates the compilation process in the pre-processing phase. Its usage is as follows:

    #error text

The `error` preprocessor directive is followed by an error message, separated by a space character. When the preprocessor sees the `#error` command, it prints this error message to the screen and terminates the compilation process. How the error text is displayed on the screen can vary depending on the compiler.

    #ifndef __STDC__
    #error This program only compiles in a standard C compiler.
    #endif

In the example above, the `#ifndef` command checks whether the compiler that will perform the compilation is a standard C compiler. If the compiler is not a standard C compiler, the compilation process is terminated in the preprocessor phase. When the compilation process is terminated, the screen prints:

    This program only compiles in a standard C compiler.

    #if UINT_MAX < 65535
    #error unsigned int type is not large enough
    #endif

If the written program is attempted to be compiled for a system where the `int` type is smaller than 2 bytes, the screen prints a message in the form:

    Error directive: unsigned int type is not large enough

and the compilation process is terminated.

### The `#undef` Preprocessor Directive

Redefining a symbolic constant for a second time in a way that is not identical to the first is **undefined behavior**. For example, a definition operation like the following is incorrect:

    #define MAX 100
    #define MAX 200 // Invalid if different

No problem arises if a symbolic constant is defined for a second time in a way that is identical to the first. If a symbolic constant is desired to be defined for a second time, the old definition must be removed first. This operation is performed with the **`#undef`** preprocessor directive.

The name of the symbolic constant or macro whose validity is to be removed must be written next to the `#undef` preprocessor directive:

    #undef MAX
    #define MAX 20

With the preprocessor directives above, the definition of the `MAX` symbolic constant is removed first, and then the `MAX` symbolic constant is defined as 20. Even if the symbolic constant desired to be undefined has not been defined before, this situation does not cause a problem. In the example above, if the `MAX` symbolic constant had not been defined before, this would not cause an error.

### Predefined Symbolic Constants

5 symbolic constants are assumed to be predefined in the standard C language. Although these symbolic constants are not defined with the `#define` preprocessor directive in any header file, they undergo a replacement operation before the source code is processed by the compiler. These symbolic constants are mostly used in code written for debugging purposes:

* **`__LINE__`** predefined symbolic constant
    This symbolic constant is replaced with an integer literal indicating the line number of the source code where it is used.
* **`__FILE__`** predefined symbolic constant
    This symbolic constant is replaced with a string literal indicating the name of the source file in which it is used.
* **`__DATE__`** predefined symbolic constant
    This symbolic constant is replaced with a string literal indicating the compilation date. The format of the string containing the date information is as follows: `Mmm dd yyyy` (Month, day, year).
* **`__TIME__`** predefined symbolic constant
    This symbolic constant is replaced with a string literal indicating the compilation time. The format of the string containing the time information is as follows: `hh:mm:ss` (hour, minute, second).
* **`__STDC__`** predefined symbolic constant
    This symbolic constant is assumed to be defined if the compiler is a standard C compiler. If the compiler is not a standard C compiler, this symbolic constant is assumed to be undefined.

Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        printf("source file name : %s\n", __FILE__);
        printf("compilation date = %s\n", __DATE__);
        printf("compilation time = %s\n", __TIME__);
        printf("line number = %d\n", __LINE__);
    #ifdef __STDC__
        printf("standard C compiler\n");
    #else
        printf("not a standard C compiler\n");
    #endif
        return 0;
    }

> \[The **`__cplusplus`** predefined symbolic constant is also assumed to be defined in C++ compilers.]

### The `#line` Preprocessor Directive

This preprocessor directive can be used to change the line number and file name that the compiler maintains for the source code. This command can take two arguments. The first argument the command can take is the line number as an integer. The optional second argument the command can take is the string literal indicating the file name.

This preprocessor directive can be used by programs that generate source code. The `#line` command might seem meaningless to you. Why would the error message the compiler provides indicate line 25, for example, instead of line 20? Why would the compiler write the name of another file in the error message instead of the name of the source file it is compiling?

The `#line` command is used more by programs that output C source code than by programmers. Compile and run the following program:

    #include <stdio.h>
    int main()
    {
        printf("line %d of file %s\n", __LINE__, __FILE__);
    #line 100 "test_file.c" // Change line number to 100 and file name to "test_file.c"
        printf("line %d of file %s\n", __LINE__, __FILE__); // Output: line 101 of file test_file.c
        return 0;
    }

### Including a Header File More Than Once in the Source File

Projects often consist of different source files and header files. Client codes include the header files of the server codes. You know that including a header file is done with the `#include` preprocessor directive. Suppose two separate header files are included in a coding file:

    /*** file1.c *****/
    #include "header1.h"
    #include "header2.h"

Including other header files inside header files is frequently encountered. For example, suppose a header file named `header3.h` is included in both header files named `header1.h` and `header2.h`:

    /*** header1.h *****/
    #include "header3.h"

    /*** header2.h *****/
    #include "header3.h"

In this case, the header file named `header3.h` is included twice in the source file named `file1.c`. This situation is called **"multiple inclusion"** in English. So, is there a drawback to this situation?

Header files contain declarations. If a header file is included twice, the declarations inside this header file are made twice. Repeating some declarations identically does not cause a problem. For example, a function declaration can be repeated, provided it does not conflict with a previous declaration. The same situation applies to `extern` declarations and `typedef` declarations. However, repeating a type declaration made by the programmer is invalid, even if the declarations are identical:

    struct A {
    /****/
    };
    struct A {
    /****/
    };

In the example above, when the declaration of the structure named `struct A` is made for the second time, the compiler program provides an error message. Let's give an example from the standard library: You know that a structure named `struct tm` is declared in the standard header file `time.h`. If the content of the `time.h` header file is emptied into a coding file twice, an error occurs during the compilation of the coding file. This is because the `struct tm` structure is declared twice.

Eliminating such errors during the project development process leads to extra time loss. A precaution can be taken in this regard with preprocessor conditional compilation directives. Header files in C and C++ languages are mostly prepared in the following form:

    //header1.h
    #ifndef _HEADER1_H_ // Check if the guard is NOT defined
    #define _HEADER1_H_ // Define the guard
    // Entire content of the header file is here
    #endif // End of conditional block

When this header file is included for the first time by a source file, the symbolic constant `_HEADER1_H_` has not been defined yet, so the part up to the `#endif` preprocessor directive is given to the compiler. However, if this header file is desired to be included one more time, since the symbolic constant `_HEADER1_H_` has already been defined, the part up to the `#endif` preprocessor directive is no longer given to the source code.

### Where Are Preprocessor Directives Related to Conditional Compilation Used?

1.  **Conditional compilation directives are frequently used for debugging purposes.**
    Some codes are added to the program for debugging purposes while the program is being written. However, the code for bug searching is not desired to be present in the final version of the program. This is because the added overhead these codes bring during the program's runtime is undesirable. Specific code segments within the program are compiled only in the debug version:

    ```c
    #if DEBUG
    /***/ // Debug code only
    #endif
    ```

2.  **Some programs may be desired to run on more than one operating system.** Specific parts of the source code are selected by the preprocessor program according to the operating system and given to the compiler:

    ```c
    #if defined(WINDOWS)
    /***/
    #elif defined (DOS)
    /***/
    #elif defined(OS2)
    /***/
    #endif
    ```

3.  **Sometimes, the same program is compiled with different compilers.**

    ```c
    #ifdef __STDC__
    /***/
    #else
    /***/
    #endif
    ```

An example of a program snippet related to the use of preprocessor directives for conditional compilation is given below:

    #if DLEVEL > 5
    #define SIGNAL 1
    #if STACKUSE == 1
    #define STACK 200
    #else
    #define STACK 50
    #endif
    #else // DLEVEL <= 5
    #define SIGNAL 0
    #if STACKUSE == 0
    #define STACK 200
    #else
    #define STACK 50
    #endif
    #endif
    
    #if DLEVEL == 0
    #define STACK 0
    #elif DLEVEL == 1
    #define STACK 100
    #elif DLEVEL > 5
    display(debugptr); // Only compiled if DLEVEL > 5
    #else
    #define STACK 200
    #endif

In the first `#if` block in the example above, there are two separate `#if #else` structures. Depending on whether the value of the `DLEVEL` symbolic constant is greater than 5 or not, the true part or the false part is processed by the preprocessor.

In the second `#if` block, which also contains the `#elif` preprocessor directive, one of 4 options is processed depending on the value of the `DLEVEL` symbolic constant. The `STACK` symbolic constant is defined as 0, 100, or 200, depending on the value of the `DLEVEL` symbolic constant. If the value of the `DLEVEL` symbolic constant is greater than 5, the statement:

    display(debugptr);

is given to the compiler. In this case, the `STACK` symbolic constant is not defined here.

## The `assert` Macro

**`assert`** is a macro used by the programmer to detect possible bugs during the program development process. It is defined in the standard C header file `assert.h`. The `assert` macro is used by providing an expression as an argument to the macro. For example:

    assert(p != NULL);

The expression inside the parenthesis specifies a condition that is assumed to be true or should be true. If the numerical value of the expression given to the `assert` macro is a non-zero value, i.e., the tested proposition is true, the `assert` macro does nothing. However, if the value of the macro expression is zero, i.e., the proposition related to the expression is logically false, the `assert` macro calls the standard **`abort()`** function and terminates the program.

The `abort` function terminates the program when called, just like the standard `exit()` function. However, the `abort` function does not perform some cleanup operations that the `exit` function does. The `abort` function prints the message "Abnormal program termination" to the `stdout` stream when it terminates the program. Before calling the `abort` function when the `assert` macro fails, it prints the tested expression and information about which file and line the `assert` operation occurred on to the screen:

    #include <stdio.h>
    #include <assert.h>
    int main()
    {
        int x, y;
        printf("enter two numbers : ");
        scanf("%d%d", &x, &y);
        assert(y != 0); // Fails if y is 0
        printf("%d / %d = %d\n", x, y, x / y);
        return 0;
    }

Examine the program above. If the value entered into the variable $y$ from the keyboard is $0$, since the expression given to the `assert` macro is false, the program is terminated by calling the `abort` function. Run the program and examine the text printed to the screen when the program is terminated.

`assert` is a macro defined in the `assert.h` file, similar to the following:

    #ifndef NDEBUG // If NDEBUG is NOT defined (Debug version)
    #define assert(exp) if(!(exp)){fprintf(stderr,"Assertion failed: %s,file %s, line %d\n",\
                                  #exp, __FILE__, __LINE__);abort();}
    #else // If NDEBUG IS defined (Release version)
    #define assert(exp)
    #endif

This macro does the following: If the programmer has not defined the symbolic constant **`NDEBUG`** in the source code area above the location where the content of the `assert.h` file is emptied, control codes are placed instead of all `assert` macros. As seen, if the numerical value of the expression is zero, the program is terminated with the `abort` function. If the programmer has defined the symbolic constant `NDEBUG` before the inclusion of the `assert.h` file, all `assert` macros are removed from the source code. To remove all `assert` macros from the source code, the command:

    #define NDEBUG

must be placed at the top of the program's source code.

### Why is the `assert` Macro Used?

The `assert` macro is a macro added to the source code by the programmer to catch potential errors during the program's development phase. The programmer places `assert` macros for situations that might occur when encountering a bug while writing their code. If the program is terminated by the `assert` macro during testing in the development process, the programmer understands that an undesirable situation has occurred and suspects that this situation is due to a bug. The bug may undoubtedly not be exactly where the `assert` macro is located. Errors made elsewhere might have caused the bug. This situation is seized by the `assert` macro as a clue. When caught by the `assert` macro, the programmer should examine their code according to the flow and try to determine the source of the bug. The checks performed with the `assert` macro are checks that are unnecessary for a correctly functioning program. The version of the program where `assert` macros place control codes (i.e., where the `NDEBUG` symbolic constant is not defined) is called the **"debug version."** The debug version is the version where the source code is inflated with `assert` macros. If the programmer is sure that there are no bugs in their code, they compile the program one last time by defining the `NDEBUG` symbolic constant before delivering the program. This is called the **"release version"** of the program. Large programs should be created in the debug version, and the release version should be obtained in the final stage.

### Where Are `assert` Macros Used?

`assert` macros should not be used in the commercial versions of the program or in situations where the check needs to remain in the code. For example, the return values of the `malloc` and `fopen` functions should be checked in both the debug version and the release version of the program. `assert` macros can be used in the following situations:

* The situation where function parameters take abnormal values that should not occur can be controlled with the `assert` macro. Especially the case where pointer parameters become the `NULL` address immediately at the entry of the main block can be controlled, as it is a frequent situation for pointers to become `NULL` due to bugs.

For example, the `assert` macro can be used as follows in the definition of a function that performs a sorting operation:

    void sort_array(int *pArray, size_t size)
    {
        int i, k, temp;
        /*…*/
        assert(pArray != NULL); // Check if pointer is NULL
        /*…*/
    }

If a situation that should absolutely not happen according to the program's design occurs in the program, the `assert` macro should be used in situations where a bug is suspected.

`assert` expressions should not be kept very long. This is because the cause may not be understood if the `assert` expression fails in this case. For example:

    assert(row1 < 25 && col1 < 80 && row2 < 25 && col2 < 80);

Instead of the above, using the following code is more meaningful:

    assert(row1 < 25 && col1 < 80);
    assert(row2 < 25 && col2 < 80);