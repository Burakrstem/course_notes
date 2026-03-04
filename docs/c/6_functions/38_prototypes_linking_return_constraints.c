#include <stdio.h>

// 1. Function Prototype (Declaration)
// This tells the compiler the function exists, its signature, and its return type.
// It allows us to define the function later or in a separate file.
int calculate_something(int x, int y); 

// 5. Function Without a Specified Type (Old C/Pre-ANSI C)
// The compiler automatically assumes 'int' return type. (Not recommended).
// 10. This is defined *before* the call, so no prototype is strictly needed.
no_type_func() {
    printf("-> (Warning) Function without a specified type. Assumed 'int'.\n");
    return 100;
}

// 3. Main function demonstrating function calls
int main() {
    int a = 10, b = 5;

    printf("--- 1. Using and Not Using Return Values ---\n");

    // 16. Value-returning function, result assigned. (Normal use)
    int result = calculate_something(a, b);
    printf("Result used (10 * 5) = %d\n", result);

    // 16. Call without using the value. (Can sometimes trigger a warning)
    calculate_something(a, b);
    printf("Result not used. (Compiler might issue 'code has no effect!')\n");

    // 9. Function Invocation: func() = 5 is Invalid (R-value constraint)
    // The value produced by a function call is an R-value, it cannot be assigned to.
    // Error: L-value required as left operand of assignment.
    // (If you uncomment the line below, it will cause a compile error.)
    // calculate_something(a, b) = 100; 

    // Call function with implicit 'int' return type
    printf("no_type_func returned: %d\n", no_type_func());

    return 0;
}

// 5. Function Definition (Must be defined somewhere for the linker)
int calculate_something(int x, int y) {
    return x * y;
}

// 10. Undefined Function Example
// If we had a prototype for 'void linker_error();' but no definition anywhere,
// the compiler would be happy, but the *linker* would fail.