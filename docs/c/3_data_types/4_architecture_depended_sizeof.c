#include <stdio.h>
#include <limits.h>

int main() {
    printf("char: %zu byte, [%d, %d]\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("short: %zu byte, [%d, %d]\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("int: %zu byte, [%d, %d]\n", sizeof(int), INT_MIN, INT_MAX);
    printf("long: %zu byte, [%ld, %ld]\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("long long: %zu byte, [%lld, %lld]\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
    return 0;
}