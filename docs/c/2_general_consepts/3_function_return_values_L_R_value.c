#include <stdio.h>

// Returns an R-value (a copy of the static value)
int func1() {
    static int x = 5;
    return x;  
}

// Returns a pointer (an L-value address)
int* func2() {
    static int y = 10;
    return &y; // Returns the persistent address of 'y'
}

int main() {
    // func1() = 20; ❌ Error: func1 returns an R-value (a temporary value)

    // *func2() is an L-value because it dereferences a persistent address (the address of static int y)
    *func2() = 30;   // ✅ Valid: Modifies the static variable 'y'

    printf("Value pointed to by func2(): %d\n", *func2()); // Output: 30
    return 0;
}