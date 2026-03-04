#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    int i;
    double t;

    start = clock();
    for (i = 0; i < 100000000; ++i) { int x = i * 2; }
    end = clock();
    t = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("int işlemleri: %.3f saniye\n", t);

    start = clock();
    for (i = 0; i < 100000000; ++i) { double x = i * 2.0; }
    end = clock();
    t = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("double işlemleri: %.3f saniye\n", t);
    return 0;
}