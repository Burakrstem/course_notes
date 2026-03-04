#include <stdio.h>

int main(void) {
    char c;
    printf("Metin girin ('.' ile bitir):\n");
    while ((c = getchar()) != '.') {
        if (c >= 'a' && c <= 'z')
            c -= 32; // küçük → büyük
        putchar(c);
    }
    printf("\nTamamlandı.\n");
    return 0;
}