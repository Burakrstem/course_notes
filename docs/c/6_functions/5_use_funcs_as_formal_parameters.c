#include <stdio.h>

int topla(int a, int b) { return a + b; }
int kare(int x) { return x * x; }

int main() {
    int sonuc = kare(topla(3, 2));
    printf("Sonuç: %d\n", sonuc); // (3+2)^2 = 25
    return 0;
}