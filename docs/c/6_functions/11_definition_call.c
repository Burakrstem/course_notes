#include <stdio.h>

// Bildirim (prototip)
int topla(int, int);

int main(void) {
    int sonuc = topla(3, 4);
    printf("Toplam = %d\n", sonuc);
    return 0;
}

// Tanımlama
int topla(int a, int b) {
    return a + b;
}