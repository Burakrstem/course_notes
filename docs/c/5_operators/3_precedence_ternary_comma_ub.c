#include <stdio.h>

void advanced_operators_demo() {
    int a = 20, b = 5, c = 2, d;

    printf("--- 1. Precedence and Associativity ---\n");

    // Expression: d = a + b * c;
    // Precedence: * (Level 3) is higher than + (Level 4).
    // Evaluation: d = a + (b * c) -> d = 20 + 10 -> 30
    d = a + b * c;
    printf("a + b * c (20 + 5 * 2) = %d\n", d); // Output: 30

    // Expression: d = (a + b) * c;
    // Parentheses (Level 1) force a higher precedence.
    // Evaluation: d = (20 + 5) * 2 -> d = 25 * 2 -> 50
    d = (a + b) * c;
    printf("(a + b) * c ( (20 + 5) * 2 ) = %d\n", d); // Output: 50

    printf("\n--- 2. Conditional (Ternary) Operator (?:) ---\n");
    // The C-only Ternary Operator: <condition> ? <value_if_true> : <value_if_false>
    // Right Associative (Level 13)

    int max = (a > b) ? a : b; // Condition (a > b) is True, max gets a (20)
    printf("Max of 20 and 5 is: %d\n", max); 

    int abs_val = (b < 0) ? -b : b; // Condition (b < 0) is False, abs_val gets b (5)
    printf("Absolute value of 5 is: %d\n", abs_val);

    printf("\n--- 3. Comma Operator (,) ---\n");
    // Lowest Precedence (Level 15). Guarantees left-to-right evaluation.
    // The value produced by the whole expression is the value of the RIGHT operand.

    int e = 0;
    // (e = 10, e + 5)
    // 1. e = 10 (Side effect: e is now 10)
    // 2. e + 5 -> 10 + 5 -> 15 (Value produced by the expression is 15)
    d = (e = 10, e + 5); 
    printf("Comma Operator (e = 10, e + 5): Result = %d, e value = %d\n", d, e); // Output: 15, 10

    printf("\n--- 4. WARNING: Undefined Behavior ---\n");

    int x = 10;
    // **DANGER!** A variable 'x' is modified by '++' and also appears elsewhere in the expression.
    // C Standard says: "If a side effect on a scalar object is unsequenced relative to either 
    // a second side effect on the same scalar object or a value computation using the value 
    // of the same scalar object, the behavior is undefined."
    // The outcome of the following line is NOT guaranteed and should be AVOIDED.
    // Depending on the compiler/optimization, the result could be 22, 23, or something else.
    int result_ub = ++x + x; 

    printf("++x + x (Initial x=10). The result is: %d (!!! Undefined Behavior !!!)\n", result_ub);
    printf("Final x value: %d\n", x);
}

/*
To compile and run:
gcc advanced_operators.c -o advanced_demo
./advanced_demo
*/