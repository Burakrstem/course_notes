#include <stdio.h>
/*
you can use function pointers to select functions at runtime.
this is show the functions can be used like data types
*/

int topla(int a, int b) { 
    return a + b; 
}
int carp(int a, int b) { 
    return a * b; 
}

int (*secim(int islem))(int, int) {
    if (islem == 1) return topla;
    else return carp;
}

int main() {
    int (*f)(int, int);
    f = secim(1);
    printf("Sonuç: %d\n", f(3, 4)); // 7
    return 0;
}