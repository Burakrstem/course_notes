#include <stdio.h>

void increment_ref(int *x) {
    (*x)++;
    printf("increment_ref() içinde: *x = %d\n", *x);
}

int main(void) {
    int value = 10;
    increment_ref(&value);
    printf("main() içinde: value = %d\n", value);
    return 0;
}
