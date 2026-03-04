#include <stdio.h>

int main() {
    double a = 1.23e3;   // 1.23 × 10^3 = 1230
    double b = 1.23e-3;  // 1.23 × 10^-3 = 0.00123
    printf("a = %f\nb = %f\n", a, b);
    return 0;
}