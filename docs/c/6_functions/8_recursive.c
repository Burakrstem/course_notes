#include <stdio.h>

int faktoriyel(int n) {
    if (n == 0) return 1;
    return n * faktoriyel(n - 1);
}

int main() {
    printf("5! = %d\n", faktoriyel(5));
    return 0;
}