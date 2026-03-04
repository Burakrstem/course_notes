#include <stdio.h>

int main() {
    printf("int: %zu byte\n", sizeof(10));
    printf("long: %zu byte\n", sizeof(10L));
    printf("unsigned long: %zu byte\n", sizeof(10UL));
    printf("long long: %zu byte\n", sizeof(10LL));
    return 0;
}