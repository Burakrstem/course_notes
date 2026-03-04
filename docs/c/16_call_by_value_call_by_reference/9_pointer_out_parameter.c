#include <stdio.h>

void calc_stats(int a, int b, int *sum, int *diff) {
    *sum = a + b;
    *diff = a - b;
}

int main(void) {
    int x = 10, y = 4, toplam, fark;
    calc_stats(x, y, &toplam, &fark);
    printf("Toplam=%d, Fark=%d\n", toplam, fark);
    return 0;
}
