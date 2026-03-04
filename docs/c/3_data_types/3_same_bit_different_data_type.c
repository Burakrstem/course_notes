#include <stdio.h>
/*
01000001 -> 65 -> 'A'
this bit pattern can represent different data types
*/

int main() {
    int i = 65;
    char c = 'A';

    printf("int olarak: %d\n", i);
    printf("char olarak: %c\n", c);
    printf("Bellekte aynı değeri farklı türle yorumlama: %c\n", (char)i);
    return 0;
}