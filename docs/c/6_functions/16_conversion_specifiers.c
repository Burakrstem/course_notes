#include <stdio.h>

int main(void) {
    int i = 255;
    double d = 3.14159;
    char c = 'A';
    const char *s = "Merhaba";

    printf("int: %d, hex: %x, octal: %o\n", i, i, i);
    printf("float: %.2f, scientific: %.3e\n", d, d);
    printf("char: %c, string: %s\n", c, s);
    printf("adres: %p\n", (void*)s);
    return 0;
}