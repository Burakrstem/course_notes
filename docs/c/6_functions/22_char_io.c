#include <stdio.h>

int main(void) {
    int ch; // getchar() int döndürür (EOF-end of file- ayırtı için)
    printf("Bir karakter girin: ");
    ch = getchar();
    if (ch != EOF) {
        printf("Girdiğiniz karakter: ");
        putchar(ch);
        putchar('\n');
    }
    puts("----Program bitti.----");
    return 0;
}