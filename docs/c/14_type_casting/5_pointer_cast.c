#include <stdio.h>

int main(void) {
    int a = 12345;
    void *vp = &a;  // generic pointer
    int *ip = (int *)vp;  // explicit cast back to int pointer

    printf("Value through pointer: %d\n", *ip);

    return 0;
}
