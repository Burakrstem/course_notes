## ASSIGNING DEFAULT VALUES TO PARAMETER VARIABLES

In C, if a function has a certain number of parameter variables, that many arguments must be passed to the function. In C++, however, a function can be called with fewer arguments than its number of parameter variables. One or more of a function's parameter variables can take a **default argument**. This means: if a value is not passed to the function's parameter variable through the function call, a predetermined value is automatically passed.

It is specified that a parameter variable will receive a predetermined value in the function's declaration or definition, with an expression written after an equals (=) operator following the parameter variable. Examine the following example:

    #include <iostream>

    void foo(int x = 10, int y = 20);

    void foo(int x, int y)
    {
        std::cout <<"x = " << x << '\t' << "y = " << y << std::endl;
    }

    int main()
    {
        foo(); // x = 10  y = 20
        foo(100); // x = 100 y = 20
        foo(100, 200); // x = 100 y = 200
        return 0;
    }

Default arguments are used in the declaration of the `foo` function. In the first call made within the `main` function, no arguments are sent to the `foo` function. In this case, the default values of 10 and 20 are passed to the parameter variables `x` and `y`. In the second call made within the `main` function, only the value 100 is sent to the `foo` function. In this case, while the value 100 is copied to the first parameter variable, the default value of 20 is copied to the second parameter variable. In the third call to the `foo` function, the values 100 and 200 are sent to the function. In this case, none of the parameter variables receive a default value. As seen, default values are the values that are not sent to the function when the function is called.

Default values can be used if arguments are sent to the parameter variables on the left, and the function is called without writing the other arguments on the right. However, the reverse is not valid. The following call form is invalid in any case:

    foo(, 10);

If a default value has been set for a parameter variable, all parameter variables located to the right of this parameter variable must also have default values:

    void func(int x = 10, int y); // Invalid!
    void foo(int x, int y = 20); // Valid

The required arguments must be sent via the call expression for all parameter variables that do not have a default value.

A pointer, which is a function's parameter variable, can also take a default value. Examine the following example:

    #include <iostream>

    void put_message(const char *p = "Success!")
    {
        std::cout << p;
    }

    int main()
    {
        put_message("Failed!");
        put_message();
        return 0;
    }

In the program above, the string "Success!" is passed as the default argument for the parameter variable `p`, which is a pointer in the `put_message` function. In the first call made within the `main` function, the string "Failed!" is passed as an argument to the function, while in the second call, no argument is sent to the function. The text "Success!" is printed to the screen with the second call made.

The expression specified as a default argument does not have to be a constant expression. Expressions containing variables can also be used as default arguments. In expressions used as default arguments, global variables that have been previously declared can be used, as can function calls.

    int func1();
    int func2(int);
    int func3(double = 3.14);
    int g = 10;
    int func4(int a = func1(), int b = func2(g), int c = func3());

All function declarations made above are valid. All three parameters of the `func4` function take default arguments. If a value is not assigned to the first parameter, `a`, with the function call expression, the return value of the `func1` function is assigned. If a value is not passed to the second parameter variable, `b`, the return value of the `func2` function is assigned. In the meantime, the value of the global variable `g` is passed to the called `func2` function. When a value is not passed to the last parameter variable, the return value of the `func3` function is assigned to this parameter variable, and the `func3` function to be called, since no argument is sent to it, takes the default value of 3.14.

The evaluation of expressions related to default arguments occurs at the point where the function is called. That is, if the `func4` function is not called, the `func1`, `func2`, and `func3` functions are not called either.

The value specified as a default argument must be written only once. It is invalid to rewrite the default argument in a second declaration in the same source file.
Examine the following example:

    ///////
    // file1.h
    int func(int a, int b, int c = 0);
    ///////

    ///////
    // file2.h
    #include “file1.h"
    int func(int a, int b, int c = 0);
    // Invalid
    ///////

However, in a declaration made a second time, a default value can be declared for a parameter variable that did not previously have a default argument specified. Of course, in this case, default values must have been previously specified for all parameter variables remaining to the right. If the `file2.h` file were as follows, a compile-time error would not occur:

    ///////
    // file2.h
    ///////////////////////////
    #include "file1.h"
    int func(int a, int b = 1, int c);
    int func(int a = 2, int b, int c);

The values specified as default arguments must be written only once. These values are part of the function's interface. It is natural for default arguments to be specified in the function declaration. It is invalid for the default argument value to be present in both the function declaration and the function definition:

    void func(int x = 10, int y = 20);

    void func(int x = 10, int y = 20) // Invalid.
    {
    }

As you will recall, the names of parameter variables do not have to be written in function declarations. It is not mandatory to write a name for a parameter variable that will take a default value. Both of the following declarations are valid:

    void func(int a = 10, int b = 20);
    void func(int = 10, int = 20);

However, if the parameter variable that will take a default value is a pointer, and the pointer, which is the parameter variable, is not given a name in the function declaration, one must be careful:

    void func(char *= "Ahmet");
    // Invalid!

Here, the compiler treats the `*=` characters as a single token and evaluates it as the compound assignment operator (Maximum Munch rule). The declaration is invalid. In this case, these two characters related to the default argument should not be written adjacently:

    void func(char * = "Ahmet");

Just as pointer parameter variables can take default arguments, reference parameter variables can also take default values:

    #include <iostream>
    
    int g = 20;
    void func(int &r = g);
    
    int main()
    {
        int y = 30;
        func();
        func(y);
        return 0;
    }
    
    void func(int &r)
    {
        std::cout << r << std::endl;
    }

### Why Are Default Arguments Used?

Some functions have a large number of parameter variables. Especially when such functions are in question, and if the same values are mostly sent to a certain part of these parameter variables in the call to the function, the use of default arguments provides great ease of writing. Reducing the number of arguments sent to the function both reduces the programmer's workload and increases the code's readability.

Care must be taken when specifying default arguments for parameter variables. If a function is mostly called with the same argument values, a parameter variable that takes a default argument can be used. Let's give an example:

Although not standard, most C compilers have a function named `itoa` in the `stdlib` library. The function converts a given integer value into a string in a given number system and writes it to an array whose address it takes:

    char *itoa(int, char *, int);

* The function's first parameter is the value to be converted to a string.
* The function's 2nd parameter is the address where the string will be placed.
* The function's 3rd parameter is the number system in which the conversion will be done.
* The function's return value is the address where the string is placed.

Since the `itoa` function is mostly used to convert an integer into a string in the decimal number system, the value 10 is mostly passed to the function's third parameter. Now let's write a function named `itoa_d` that does the same job but takes a default argument:

    #include <iostream>
    #include <cstdlib>
    
    char *itoa_d(int n, char *str, int base = 10)
    {
        return itoa(n, str, base);
    }
    
    int main()
    {
        char s[100];
        itoa_d(123, s);
        std::cout << s;
        return 0;
    }

You see that the parameter variable named `base` of the written `itoa_d` function takes the value 10 as a default argument. If the function is called with two arguments, the value 10 is passed to the third parameter, the `base` parameter variable. You see that the function calls the `itoa` function within itself. The `itoa` function, in this case, is wrapped by the `itoa_d` function, which takes a default argument.

Default arguments should not be used with the idea, "If it's not going to take any value, it might as well take this value." Such uses mislead the person examining the source code.

Sometimes the default value given to a parameter variable has no special meaning. This default value is only used to determine whether the function was called with the default argument. The real default values can be obtained within the function and with a series of operations. Examine the following example:

    #include <cstdio>
    
    #define DEFAULT_CALL (-1)
    
    void write_file(const void *ptr, unsigned nbytes, FILE *fp, long offset = DEFAULT_CALL)
    {
        if (offset != DEFAULT_CALL)
            fseek(fp, offset, SEEK_SET);
    
        fwrite(ptr, 1, nbytes, fp);
    }
    
    int main()
    {
        double d = 10.2;
        FILE *f;
        /*...*/
        write_file(&d, sizeof(double), f);
        /*...*/
        return 0;
    }

Let's examine the definition of the `write_file` function: The function writes `nbytes` bytes starting from the address passed to its first parameter to a file. If an offset value is passed to the function's last parameter, `offset`, the function positions the file position pointer to this offset value and starts the writing operation from this position. If a value is not passed to the function's last parameter, the writing operation is done starting from the position pointed to by the file position pointer.