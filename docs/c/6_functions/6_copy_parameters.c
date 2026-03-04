#include <stdio.h>

void arttir(int a) {
    a++;
    printf("İşlev içinde: %d\n", a);
}

int main() {
    int x = 10;
    arttir(x);
    printf("Ana programda: %d\n", x);
    return 0;
}