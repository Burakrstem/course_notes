#include <stdio.h>

int add(int a, int b) { return a + b; }
int square(int x)     { return x * x; }

int main(void) {
    int sonuc = add(square(3), square(4));
    printf("(3^2 + 4^2) = %d\n", sonuc);
    return 0;
}