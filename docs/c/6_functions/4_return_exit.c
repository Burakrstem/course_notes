#include <stdio.h>

void bolme(int a, int b) {
    if (b == 0) {
        printf("Sıfıra bölme hatası!\n");
        return; // erken çıkış
    }
    printf("Sonuç: %d\n", a / b);
}

int main() {
    bolme(10, 2);
    bolme(5, 0);
    return 0;
}