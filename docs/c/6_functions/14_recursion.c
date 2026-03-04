#include <stdio.h>

// Klasik: faktöriyel (özyineleme)

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int main(void) {
    printf("5! = %d\n", factorial(5));
    return 0;
}