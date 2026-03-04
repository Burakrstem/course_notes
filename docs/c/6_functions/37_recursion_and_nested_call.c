#include <stdio.h>

// Helper function for nested calls
int square(int n) {
    return n * n;
}

// 17. Recursive Function Definition: Calculates factorial
int factorial(int n) {
    // Base Case (Stops the recursion)
    if (n == 0) {
        printf("  [Base Case] Reached n=0, returning 1.\n");
        return 1;
    }

    // Recursive Step
    printf("  Calling factorial(%d) * %d...\n", n - 1, n);
    // Function calling itself
    return n * factorial(n - 1); 
}


// Value-returning function with a function call inside its return
int calculate_hypotenuse_squared(int a, int b) {
    // 16. Another call inside return: Uses nested calls.
    // square(a) and square(b) are evaluated first.
    return add_numbers(square(a), square(b)); // Assuming add_numbers is available/defined
}

// A function defined earlier (from Intermediate Demo)
int add_numbers(int a, int b) {
    return a + b;
}

int main() {
    printf("--- 1. Nested and Return Calls ---\n");

    int side1 = 3;
    int side2 = 4;

    // 16. Nested call: calculate_hypotenuse_squared is called.
    // Inside it, add_numbers is called, and inside that, square is called twice.
    int h_squared = calculate_hypotenuse_squared(side1, side2);
    printf("Side 1^2 + Side 2^2 (3^2 + 4^2) = %d\n", h_squared); // Output: 25

    printf("\n--- 2. Recursive Function (Factorial) ---\n");
    int number = 4;
    printf("Calculating Factorial of %d:\n", number);

    // 17. Recursive call starts here
    int fact_result = factorial(number); 
    printf("Result of 4! is: %d\n", fact_result); // Output: 24

    return 0;
}