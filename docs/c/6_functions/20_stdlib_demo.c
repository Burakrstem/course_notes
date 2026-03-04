#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    double x = 9.0;
    printf("sqrt(%.2f) = %.2f\n", x, sqrt(x));

    char buf[64] = "C";
    const char *s2 = " Programlama";
    strcat(buf, s2); // dikkat: hedef buffer yeterince büyük olmalı
    printf("Birleştirme: %s\n", buf);

    char ch = 'a';
    printf("%c -> %c\n", ch, toupper((unsigned char)ch));
    return 0;
}