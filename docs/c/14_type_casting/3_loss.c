#include <stdio.h>

int main(void) {
    double pi = 3.14159;
    int i = pi; // implicit conversion (precision lost)

    printf("pi as int = %d\n", i);

    float large = 1e20;  // 100000000000000000000
    int small = (int)large;  // overflow, undefined result
    printf("large as int = %d\n", small);

    return 0;
}
