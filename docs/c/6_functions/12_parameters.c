#include <stdio.h>

// Parametre aktarımı (by value): kopya üzerinden çalışır

void arttir(int a) {
    a++;
    printf("İşlev içinde: %d\n", a);
}

int main(void) {
    int x = 10;
    arttir(x);
    printf("Ana programda: %d\n", x); // x değişmez
    return 0;
}