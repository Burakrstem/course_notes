#include <stdio.h>
#include <limits.h>

int main() {
    int max_val = INT_MAX; 

    // The compiler is not required to follow a specific rule in the case of signed int overflow.
    // On most systems, it wraps to the value -2147483648 (INT_MIN).
    int result = max_val + 1; 

    printf("INT_MAX + 1 = %d\n", result); 

    return 0;
}