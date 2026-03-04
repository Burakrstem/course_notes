#include "header.h"
#include <stdio.h>

// Global variable definition
int global_count = 0;

void increase_global(void) {
    global_count++;
    printf("[utils.c] global_count incremented to: %d\n", global_count);
}

void local_variable_demo(void) {
    int local_var = 0;
    local_var++;
    printf("[utils.c] local_var (local scope) = %d\n", local_var);
}

void static_local_demo(void) {
    static int static_var = 0;
    static_var++;
    printf("[utils.c] static_var (static local) = %d\n", static_var);
}

int get_global_count(void) {
    return global_count;
}