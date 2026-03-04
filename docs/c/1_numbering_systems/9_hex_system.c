#include <stdio.h>

int main() {
    int x = 0x2ADF;  // hexadecimal literal
    printf("Hex: 0x%X, Decimal: %d, Binary: ", x, x);

    for (int i = 15; i >= 0; i--)
        printf("%d", (x >> i) & 1);
    return 0;
}