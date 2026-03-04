#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS/EXIT_FAILURE

// A value-returning function that might return a garbage value.
int check_and_exit(int x) {
    if (x < 0) {
        printf("Condition met, exiting early with status code 1.\n");
        // We can use 'return' with a value here, but we are also
        // using the standard library's exit function to terminate the *entire program* immediately.
        exit(EXIT_FAILURE); // Terminates the program entirely, bypassing the return
    }

    // 7. If the end is reached without a return statement, it returns a garbage value.
    // NOTE: Many modern compilers will issue a warning or error if a non-void
    // function reaches the end without a return statement, but the C standard allows it.
}


// A void function demonstrating early exit
void process_data(int data) {
    if (data == 0) {
        printf("Data is zero, cannot process. Exiting function early.\n");
        // 7. return; used to end execution in a void function.
        return; 
    }

    printf("Data %d processed successfully.\n", data);
}

int main() {
    printf("--- 1. Void Function Exit Flow ---\n");
    process_data(10);
    process_data(0); // This call triggers an early return
    process_data(20); // This is executed after the early return

    printf("\n--- 2. main() Return Value ---\n");

    // 8. The return value of main is passed to the operating system.
    // A function call that returns a value (r-value)
    int result = check_and_exit(5);

    // 8. Convention: 0 for success.
    return EXIT_SUCCESS; // which is usually 0

    /*
    If we had called check_and_exit(-1) instead, the program would have
    terminated immediately inside that function with exit(EXIT_FAILURE),
    and the 'return EXIT_SUCCESS' line here would never be reached.
    */
}