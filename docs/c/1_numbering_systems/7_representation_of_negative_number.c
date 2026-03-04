#include <stdio.h>

int main() {
    signed char pos = 27;
    signed char neg = -27;

    printf("27 binary: %d\n", pos);
    printf("-27 binary (two's complement): %d\n", neg);
    printf("Raw bytes: 0x%X and 0x%X\n", (unsigned char)pos, (unsigned char)neg);
    return 0;
}