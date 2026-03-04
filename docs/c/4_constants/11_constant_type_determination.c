#include <stdio.h>
#include <limits.h> // For INT_MAX

int main() {
    // 1. Un-suffixed decimal constant (32-bit system)
    int a = 2000000000;  // Type: signed int

    // 2. Suffix 'L' forces the constant type to signed long
    long b = 3000000000L; // Type: signed long (needed as 3B > 2B int max)

    // 3. Suffix 'U' forces the constant type to unsigned int
    unsigned int c = 500U; // Type: unsigned int

    printf("Value of b (long): %ld\n", b);

    // Example of overflow (assuming 32-bit int)
    // The constant 3000000000 is too large for signed int, so its type defaults to signed long (if it fits).
    // If it didn't fit long, it would become unsigned long.

    return 0;
}