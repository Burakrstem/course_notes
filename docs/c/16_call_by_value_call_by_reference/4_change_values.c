#include <stdio.h>

void change_both(int *x, int *y) {
    *x += 10;
    *y *= 2;
}

int main(void) {
    int a = 3, b = 7;
    change_both(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
