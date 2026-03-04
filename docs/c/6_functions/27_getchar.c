#include <stdio.h>

int main(void) {
    int ch;
    printf(“Enter a character: ”);
    ch = getchar();
    printf(“The character you entered: ”);
    putchar(ch);
    putchar(‘\n’);
    return 0;
}