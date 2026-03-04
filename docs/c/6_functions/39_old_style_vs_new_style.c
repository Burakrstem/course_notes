#include <stdio.h>

// 14. Function without Parameters (Implicit 'void') - Deprecated
// In C, an empty parenthesis means "takes an unspecified number of arguments."
// The compiler does NOT check the number of arguments passed in the function call.
int old_style_no_param() {
    return 1;
}

// 14. Function without Parameters (Explicit 'void') - New Style
// This is the correct, modern way to state a function takes NO arguments.
// The compiler WILL issue an error if arguments are passed.
int new_style_no_param(void) {
    return 2;
}

// 12. Old Style Parameter Declaration (Pre-ANSI C)
// Parameter types are listed after the function header. This is obsolete.
int old_style_params(x, y)
int x; 
int y; // The compiler can still compile this but throws a warning.
{
    printf("  [Old Style] Parameters: %d and %d\n", x, y);
    return x - y;
}


int main() {
    printf("--- 1. New Style vs. Old Style Parameters ---\n");

    // 13. New Style Call: Types declared in the parentheses.
    printf("New Style Subtraction (10 - 5): %d\n", old_style_params(10, 5));

    printf("\n--- 2. Parameter Constraints: () vs. (void) ---\n");

    // Using () (unspecified)
    printf("old_style_no_param() returned: %d\n", old_style_no_param());

    // DANGER: We can call the '()' function with arguments, and the compiler
    // may not complain, leading to Unspecified Behavior! (Value is ignored/garbage)
    printf("old_style_no_param(100, 200) returned: %d\n", old_style_no_param(100, 200));

    // Using (void)
    printf("new_style_no_param(void) returned: %d\n", new_style_no_param());

    // ERROR: If you uncomment the line below, the compiler will catch it,
    // as the (void) parameter list explicitly states no arguments are allowed.
    // printf("new_style_no_param(100) returned: %d\n", new_style_no_param(100));

    return 0;
}