#include <stdio.h>

int main(void) {
    int ch;
    printf("Bir karakter girin (x ile bitir): ");
    do {
        ch = getchar();
        printf("Karakter: %c | ASCII: %d\n", ch, ch);
    } while (ch != 'x');
    return 0;
}