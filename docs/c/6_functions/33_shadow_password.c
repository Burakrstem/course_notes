#include <conio.h>
#include <stdio.h>

int main(void) {
    char pass[20];
    int i = 0;
    char ch;

    printf("Şifre girin: ");
    while (i < 19 && (ch = getch()) != '\r') { // '\r' = Enter
        pass[i++] = ch;
        putch('*'); // maskelenmiş yazdırma
    }
    pass[i] = '\0';
    printf("\nGirdiğiniz şifre: %s\n", pass);
    return 0;
}