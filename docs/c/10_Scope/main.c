#include "header.h"
#include <stdio.h>

int main(void) {
    printf("=== Variable Scope Demonstration ===\n\n");

    printf("[main.c] Initial global_count = %d\n", get_global_count());
    increase_global();
    increase_global();
    printf("[main.c] global_count after increments = %d\n\n", get_global_count());

    printf("Local variable test (each call resets value):\n");
    local_variable_demo();
    local_variable_demo();
    local_variable_demo();
    printf("\n");

    printf("Static local variable test (value persists):\n");
    static_local_demo();
    static_local_demo();
    static_local_demo();
    printf("\n");

    int global_count = 999; // shadows global variable
    printf("[main.c] Local shadowed global_count = %d\n", global_count);
    printf("[main.c] Real global_count (via getter) = %d\n\n", get_global_count());

    printf("=== End of Demo ===\n");
    return 0;
}