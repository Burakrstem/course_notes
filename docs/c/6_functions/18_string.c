#include <stdio.h>

int main(void) {
    char str[] = "C dili"; // '\0' ile sonlanır
    printf("Yazı: %s\n", str);

    int i = 0;
    while (str[i] != '\0') {
        printf("%c ", str[i]);
        i++;
    }
    printf("\nUzunluk: %d\n", i);
    return 0;
}