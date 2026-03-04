#include <stdio.h>
#include <float.h>

int main() {
    printf("10 -> int: %zu byte\n", sizeof(10));
    printf("10L -> long: %zu byte\n", sizeof(10L));
    printf("10.0 -> double: %zu byte\n", sizeof(10.0));
    printf("10.0f -> float: %zu byte\n", sizeof(10.0f));

    double a = 1e39;  // float sınırını aşar
    float b = 1e39f;  // taşma (overflow)
    printf("a(double) = %e\n", a);
    printf("b(float)  = %e\n", b);
    return 0;
}