#include <stdio.h>

void set_to_100(int **ptr) {
    **ptr = 100;
}

int main(void) {
    int value = 42;
    int *p = &value;
    int **pp = &p;

    set_to_100(pp);
    printf("value = %d\n", value);
    return 0;
}
