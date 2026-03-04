#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a; // p stores the address of a

    *p = 25;  // *p is an L-value because it refers to memory location 'a'
    printf("a = %d\n", a);
    return 0;
}