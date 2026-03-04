#include <stdio.h>

int check_function(const char* name) {
    printf("-> Evaluating function: %s\n", name);
    return 0; // Always returns 0 (False)
}

void intermediate_operators_demo() {
    int val1 = 10, val2 = 20;

    printf("--- 1. Relational Operators (Produce 1 or 0) ---\n");
    // Relational Operators: <, >, <=, >=, ==, !=

    // val1 < val2 (10 < 20) is True, so it produces 1.
    printf("10 < 20: %d\n", val1 < val2); 

    // val1 == val2 (10 == 20) is False, so it produces 0.
    printf("10 == 20: %d\n", val1 == val2); 

    printf("\n--- 2. Logical Operators (!, &&, ||) ---\n");

    // Logical NOT: !
    // ! (10 < 20) -> ! (1) -> 0
    printf("! (10 < 20): %d\n", !(val1 < val2)); 

    // Logical AND: &&
    // (10 < 20) && (10 != 20) -> 1 && 1 -> 1
    printf("(10 < 20) && (10 != 20): %d\n", (val1 < val2) && (val1 != val2)); 

    printf("\n--- 3. Short Circuit Behavior (&&) ---\n");
    int x = 5;

    // Condition: (x is 0/False) && (Call function)
    // The left side (x != 5) is 0 (False).
    // The right operand is NOT evaluated. The function is NOT called.
    if ((x != 5) && check_function("RightOperand_AND")) {
        // This block is skipped
    } else {
        printf("&& Short Circuit: Left side was False (0), RightOperand_AND was NOT called.\n");
    }

    printf("\n--- 4. Short Circuit Behavior (||) ---\n");

    // Condition: (x is non-zero/True) || (Call function)
    // The left side (x == 5) is 1 (True).
    // The right operand is NOT evaluated. The function is NOT called.
    if ((x == 5) || check_function("RightOperand_OR")) {
        printf("|| Short Circuit: Left side was True (1), RightOperand_OR was NOT called.\n");
    }
}

/*
To compile and run:
gcc intermediate_operators.c -o intermediate_demo
./intermediate_demo
*/