#include <stdio.h>

// Temel örnek: return değeri döndüren/döndürmeyen fonksiyonlar

int square(int x) {
    return x * x; // değer döndürür
}

void greet(void) {
    printf("Merhaba!\n"); // hiçbir şey döndürmez
}

int main(void) {
    greet();
    printf("5'in karesi: %d\n", square(5));
    return 0;
}