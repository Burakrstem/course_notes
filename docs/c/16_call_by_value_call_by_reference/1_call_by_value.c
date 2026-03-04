#include <stdio.h>

void foo(int x) {
    x = 9999; // sadece kopya değişir
    printf("foo içi: x = %d\n", x);
}

int main(void) {
    int a = 5;
    foo(a);
    printf("main içi: a = %d\n", a);
    return 0;
}
