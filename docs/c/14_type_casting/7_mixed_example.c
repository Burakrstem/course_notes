#include <stdio.h>

int main(void) {
    int x = 7;
    double y = 2.0;
    double z;

    // implicit + explicit casting mix
    z = (int)(x / y * 3.5);
    printf("z = %.2f\n", z);

    return 0;
}
