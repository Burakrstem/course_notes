#include <stdio.h>

int main(void) {
    char c1 = 100;
    char c2 = 30;
    int sum = c1 + c2;  // chars are promoted to int

    printf("Sum (as int) = %d\n", sum);

    return 0;
}
