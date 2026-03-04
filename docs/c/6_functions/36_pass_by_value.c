#include <stdio.h>

// 11. New Style Function Definition with Parameters
// Takes two int parameters (copies) and returns their sum (int)
int add_numbers(int a, int b) {
    // 7. Returns the calculated result.
    return a + b;
}

// 15. Demonstrating Copying Arguments (Pass-by-Value)
// The parameter 'val' is a copy of the argument passed in.
void try_to_change(int val) {
    printf("  Inside function: Original value is %d\n", val);
    val = 999; // Only changes the local copy 'val'
    printf("  Inside function: Value changed to %d (local copy)\n", val);
    return; // 7. Void function using 'return;'
}

int main() {
    int x = 10;
    int y = 20;

    printf("--- 1. Using Parameters ---\n");

    // 9. Function Invocation: x and y are the actual parameters.
    // Their values (10 and 20) are copied to parameters a and b.
    int sum_result = add_numbers(x, y); 
    printf("Sum of %d and %d is: %d\n", x, y, sum_result); // Output: 30

    printf("\n--- 2. Pass-by-Value (Copying Arguments) ---\n");

    int original_value = 50;
    printf("Before call: Original variable value is %d\n", original_value);

    // 15. Call the function, passing a copy of 50.
    try_to_change(original_value); 

    // The function's change to 'val' did not affect 'original_value'.
    printf("After call: Original variable value remains %d\n", original_value); // Output: 50

    return 0;
}