# 🗃️ Functions with Variable Number of Arguments

Functions that take a variable number of arguments can be defined in C. The declaration of a function that takes a variable number of arguments is as follows:

    [Function return value] function_name(parameter declarations, ...);

The name of the three-dot token "..." in English is **"ellipsis."** For a function to be able to take a variable number of arguments, its last parameter must be declared with the ellipsis token. Such functions can be called with any number of arguments.

Such functions must have at least one parameter of a known type on the left side of the ellipsis.

Declarations of some functions that take a variable number of arguments are shown below:

    int printf(const char *, ...);
    int scanf(const char *, ...);
    double get_mean(int, ...);

The definition of the functions must also be done in the same way. The arguments sent to the function are accessed using some standard macros within the function definitions. These macros are defined in the standard header file named **`stdarg.h`**.

The values of the parameter variables whose type and name are specified in the function that takes a variable number of arguments are accessed by their names, as in other functions. Access to the optional arguments, i.e., each of the arguments whose count is unknown, is achieved by using some standard macros:

Let's first get to know these macros:

### The `va_start` Macro

This macro is used to initialize a variable of type **`va_list`**.

**`va_list`** is a `typedef` name declared in the standard `<stdarg.h>` header file. The pointer that will traverse the optional argument list is of this type. A variable of this type must first be defined. For this pointer to be able to perform the operation of traversing the argument list, this variable must first be initialized with the **`va_start`** macro.

You can think of the `va_start` macro as corresponding to a function like the following:

    void va_start (va_list ap, specific last parameter);

A variable of type `va_list` is sent as the first argument to this macro. The second argument that must be sent to the macro is the value of the function's last parameter variable whose type and name are specified.

    #include <stdarg.h>
    int add_all(int val, …) // 'val' is the specific last parameter
    {
        va_list va; // Declare va_list variable
        va_start(va, val); // Initialize va with va_start
        /***/
    }

The function named `add_all` will return the sum value of the variable number of positive integers sent to it. You see that the first parameter of the function is of type `int`. At least one argument must be sent to this function. The total number of arguments to be used in the function call can be optionally set. However, when the value of the last argument is **$-1$**, it is understood that no more arguments are sent. That is, the last value sent to the function being $-1$ becomes part of the function's interface (convention).

You see that a variable named `va` of type `va_list` is defined inside the function definition. The variable `va` and the function's parameter variable `val` are sent as arguments to the `va_start` macro. You can think that with the execution of the internal code corresponding to this call, the variable `va` is positioned to point to the appropriate argument in the argument list. Thus, the values of the arguments sent to the function can now be obtained.

### The `va_arg` Macro

The **`va_arg`** macro is used to obtain the values of the arguments sent to the function. When this macro is viewed as a function, it can be represented as follows:

    type va_arg (va_list ap, type);

After our `va_list` type variable is initialized with the `va_start` macro, this macro is called to obtain all the optional arguments. The value obtained from this macro is the value of the optional argument. As a result of the macro's operation, the argument list pointer is also positioned to point to the next argument.

With the next call made to this macro, the value of the next optional argument is obtained. The second piece of information to be sent to the macro is the **type** of the argument whose value will be obtained. For example, if the optional argument is of type `int`, then `int` must be passed as the second argument of the macro.

Returning to the `add_all` function:

    int add_all(int val, ...)
    {
        va_list va_p;
        int sum = 0;
        va_start(va_p, val);
        
        while (val != -1) { // Loop until the sentinel value -1 is reached
            sum += val;
            val = va_arg(va_p, int); // Get the next argument, assuming it's an int
        }
        /***/
    }

In the function's definition, a loop is created that runs as long as the variable `val` is not $-1$. In each iteration of the loop, the value of the variable `val` is added to the variable `sum`, and the value of the next optional argument is transferred to the variable `val`:

    val = va_arg(va_p, int);

The first time the `va_arg` macro is used, the first optional argument is obtained; the second time it is used, the second optional argument is obtained, and so on. If the arguments after a certain argument are not desired to be obtained, `va_arg` calls do not have to be made until the end. If an attempt is made to obtain a larger number of arguments than the number of arguments sent with the function call, i.e., if the `va_arg` macro is attempted to be called more times than necessary, **garbage values** are obtained.

### The `va_end` Macro

The **`va_end`** macro is called when the argument list pointer's task is finished.

    void va_end (va_list ap)

This macro performs the final operations related to the variable of type `va_list`.

    int add_all(int val, ...)
    {
        va_list va_p;
        int sum = 0;
        va_start(va_p, val);
        
        while (val != -1) {
            sum += val;
            val = va_arg(va_p, int);
        }
        va_end(va_p); // Cleanup
        return sum;
    }

In most systems, nothing is done in response to the `va_end` macro. That is, even if this macro is not called in applications, there is no change in the operation performed. This is always true in the GNU compiler. However, calling this macro is the correct technique for readability, safety, and portability.

If desired, more than one argument list pointer can be used. In this case, each of the argument pointers must be initialized separately with the `va_start` macro. The arguments sent to the function can be obtained with any of the pointers.

### Calls to Functions Taking a Variable Number of Arguments

Calls to functions that take a variable number of arguments are evaluated in a special way by the compiler. Arguments of types smaller than `int` are automatically **promoted to `int`**. Arguments of type `float` are promoted to **`double`**:

    #include <stdio.h>
    int add_all(int val, ...);
    int main()
    {
        short sh = 5;
        printf("sum1 = %d\n", add_all(23, 12, 30, 14, -1)); // -1 is the sentinel
        // 'A' is promoted to int, 'sh' (short) is promoted to int
        printf("sum2 = %d\n", add_all('A', 10, sh, 20, 30, 40, -1)); 
        return 0;
    }

Now a function is defined that will concatenate the strings whose addresses are sent to it and can be called with a variable number of arguments:

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #define BUFFER_SIZE 1000
    
    // Note: The sentinel is NULL, which must be passed as the last argument
    char *con_strings(const char *ptr, ...) 
    {
        va_list ap;
        char *pd;
        char buffer[BUFFER_SIZE] = {'\0'};
        
        va_start (ap, ptr);
        
        // ptr is the first known argument. Loop while ptr is not NULL.
        while (ptr) { 
            strcat(buffer, ptr);
            // Get the next optional argument, which is expected to be a const char *
            ptr = va_arg(ap, const char *); 
        }
        
        // Allocate dynamic memory for the concatenated string
        pd = (char *)malloc(strlen(buffer) + 1); 
        
        if (pd == NULL) {
            printf("insufficient memory!\n");
            exit(EXIT_FAILURE);
        }
        
        va_end(ap);
        return strcpy(pd, buffer);
    }
    
    int main ()
    {
        // NULL is passed as the sentinel argument
        char *pstr = con_strings("C ", "ve ", "Sistem ", "Programcilari ",
                                 "Dernegi", NULL); 
        puts(pstr);
        free(pstr); // Free the dynamic block
        return 0;
    }

Examine the definition of the `con_strings` function: The variable `ap` of type `va_list` is initialized with the `va_start` macro:

    va_start (ap, ptr);

You see that a `while` loop is created that runs as long as the value of the parameter variable `ptr` is not the `NULL` address. In each iteration of the loop, the value of each of the arguments sent to the function is obtained with the `va_arg` macro, and this value is assigned to the pointer `ptr`. The string pointed to by the pointer `ptr` is first appended to the end of the string in the local `buffer` array with the standard `strcat` function. The last argument sent with the function call must be the `NULL` address. When the value of the pointer `ptr` is the `NULL` address, the string in the `buffer` array is copied to a dynamic memory block. After the `va_end` macro is called inside the function, the function returns with the address of the dynamic block.