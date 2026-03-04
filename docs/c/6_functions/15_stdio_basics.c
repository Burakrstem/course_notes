#include <stdio.h>

int main(void) {
    int x;
    printf("Bir sayı girin: ");
    if (scanf("%d", &x) == 1) {
        printf("Girdiğiniz sayı: %d\n", x);
    } else {
        printf("Geçersiz giriş!\n");
    }
    return 0;
}