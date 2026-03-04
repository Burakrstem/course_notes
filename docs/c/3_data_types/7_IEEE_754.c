#include <stdio.h>

int main() {
    float f = -6.5f;
    unsigned int *p = (unsigned int*)&f;

    printf("float: %f\nbinary: ", f);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (*p >> i) & 1);
        if (i == 31 || i == 23) printf(" ");
    }
    printf("\n");
    return 0;
}