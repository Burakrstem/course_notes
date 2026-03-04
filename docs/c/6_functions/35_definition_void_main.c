#include <stdio.h>

// 1. VOID Function Definition (No return value, no parameters)
// Purpose: To perform a specific task (printing)
void print_separator() {
    printf("\n--------------------------\n");
    // A void function can optionally use 'return;' to exit early.
}

// 2. Value-Returning Function Definition (Returns an int, takes no parameters)
// Purpose: To calculate and return a value.
int get_current_year() {
    // Returns the calculated result (2025 in this example)
    return 2025; 
}

// 8. The main function - the program's starting point
int main() {

    // 9. Function Invocation (Void function call)
    print_separator();
    printf("C Functions: Basic Demo\n");
    print_separator();

    // 9. Function Invocation (Value-returning function, result used immediately)
    printf("The current year is: %d\n", get_current_year());

    // 9. Function Invocation (Value-returning function, result assigned to a variable)
    int year = get_current_year();
    printf("Year stored in variable 'year': %d\n", year);

    // 8. The return value of main is passed to the OS (0 means success)
    return 0; 
}