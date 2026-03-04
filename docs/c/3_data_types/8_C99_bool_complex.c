#include <stdio.h>
#include <stdbool.h>
#include <complex.h>

int main() {
    bool flag = true;
    double complex z = 2.0 + 3.0 * I;

    printf("bool örneği: %d\n", flag);
    printf("complex örneği: %.1f + %.1fi\n", creal(z), cimag(z));
    return 0;
}