#include <stdio.h>

void trace(int *x) {
    printf("Değer: %d, Adres: %p\n", *x, (void*)x);
}

int main(void) {
    int num = 50;
    trace(&num);
    return 0;
}
