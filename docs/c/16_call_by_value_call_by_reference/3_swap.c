#include <stdio.h>

void swap_value(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
}

void swap_reference(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(void) {
    int a = 5, b = 43;

    printf("Başlangıçta: a=%d, b=%d\n", a, b);
    swap_value(a, b);
    printf("Call by value sonrası: a=%d, b=%d\n", a, b);
    swap_reference(&a, &b);
    printf("Call by reference sonrası: a=%d, b=%d\n", a, b);

    return 0;
}
