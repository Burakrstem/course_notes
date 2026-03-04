#include <stdio.h>

void basic_operators_demo() {
    int a = 10;
    int b = 3;
    int result;

    printf("--- 1. Basic Arithmetic (Binary Infix) ---\n");
    // Binary Infix Operators: +, -, *, /, %
    printf("Addition: 10 + 3 = %d\n", a + b);     // Produces 13
    printf("Division (Integer): 10 / 3 = %d\n", a / b); // Produces 3 (integer division)
    printf("Modulus (Remainder): 10 %% 3 = %d\n", a % b); // Produces 1 (Constraint: requires integer types)

    // Unary Prefix Operator: - (Sign Minus)
    printf("Unary Minus: -10 = %d\n", -a); // Produces -10

    printf("\n--- 2. Unary Inc/Dec Operators (Side Effects) ---\n");

    int x = 5;
    printf("Initial x: %d\n", x); // x is 5

    // Prefix Increment: ++x
    // Action: 1. Changes x (side effect) 2. Value produced is the NEW value
    result = ++x; 
    printf("Prefix ++x: Value produced = %d, x after operation = %d\n", result, x); // Output: 6, 6

    x = 5; // Reset x

    // Postfix Increment: x++
    // Action: 1. Value produced is the OLD value 2. Changes x (side effect)
    result = x++;
    printf("Postfix x++: Value produced = %d, x after operation = %d\n", result, x); // Output: 5, 6

    // Note: If used in isolation (e.g., x++;), prefix and postfix are functionally identical.
}

/*
To compile and run:
gcc basic_operators.c -o basic_demo
./basic_demo
*/