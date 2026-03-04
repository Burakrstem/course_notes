#include <stdio.h>

void swap_pointers(int **p1, int **p2) {
    int *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main(void) {
    int a = 1, b = 2;
    int *ptr1 = &a, *ptr2 = &b;

    printf("Önce: *ptr1=%d, *ptr2=%d\n", *ptr1, *ptr2);
    swap_pointers(&ptr1, &ptr2);
    printf("Sonra: *ptr1=%d, *ptr2=%d\n", *ptr1, *ptr2);

    return 0;
}
