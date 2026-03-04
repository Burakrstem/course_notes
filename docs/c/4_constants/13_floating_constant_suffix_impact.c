#include <stdio.h>

int main() {
    // 1. Unsuffixed constant: Type is double (8 bytes)
    printf("Size of 3.14 (Default): %zu bytes\n", sizeof(3.14)); 

    // 2. 'F' suffix: Type is float (4 bytes)
    printf("Size of 3.14F (Float): %zu bytes\n", sizeof(3.14F)); 

    // 3. 'L' suffix: Type is long double (8/10/12+ bytes)
    printf("Size of 3.14L (Long Double): %zu bytes\n", sizeof(3.14L)); 

    return 0;
}