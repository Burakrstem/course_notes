#include <stdio.h>

void printFloatBits(float f) {
    unsigned int bits = *(unsigned int *)&f;
    printf("Float: %.2f\nBits : ", f);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
}

int main() {
    float x = 6.5f;
    float y = -6.5f;
    printFloatBits(x);
    printFloatBits(y);
    return 0;
}