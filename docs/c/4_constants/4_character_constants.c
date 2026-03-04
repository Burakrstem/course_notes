#include <stdio.h>

int main() {
    char ch1 = 'A';
    char ch2 = 65; // aynı şey
    printf("%c %d\n", ch1, ch1);
    printf("%c %d\n", ch2, ch2);
    return 0;
}