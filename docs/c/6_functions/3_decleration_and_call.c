#include <stdio.h>

// Bildirim (prototip)
int topla(int, int);

int main() {
    int s = topla(3, 4);
    printf("Toplam = %d\n", s);
    return 0;
}

// Tanımlama
int topla(int a, int b) {
    return a + b;
}