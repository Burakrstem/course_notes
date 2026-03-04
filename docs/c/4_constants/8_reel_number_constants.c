#include <stdio.h>

int main() {
    float f = 1.23F;
    double d = 1.23;
    long double ld = 1.23L;
    printf("float: %.10f\n", f);
    printf("double: %.10lf\n", d);
    printf("long double: %.10Lf\n", ld);
    return 0;
}