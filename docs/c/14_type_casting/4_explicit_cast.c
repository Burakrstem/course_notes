#include <stdio.h>

int main(void) {
    int a = 5, b = 2;
    float result;

    // Without casting: integer division
    result = a / b;
    printf("Without casting: %.2f\n", result);

    // With casting
    result = (float)a / b;
    printf("With casting: %.2f\n", result);

    return 0;
}
