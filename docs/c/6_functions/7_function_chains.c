#include <stdio.h>

int kare(int x) { return x * x; }
int topla(int a, int b) { return a + b; }

int main() {
    printf("%d\n", kare(topla(3, 4))); // (3+4)^2 = 49
    return 0;
}