#include <stdio.h>

int main(void) {
    int ch;
    printf("Ctrl+Z (Windows) veya Ctrl+D (Linux) ile çıkın:\n");
    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }
    printf("\nEOF algılandı.\n");
    return 0;
}