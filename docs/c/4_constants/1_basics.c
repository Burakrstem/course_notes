#include <stdio.h>

int main() {
    printf("Onluk: %d\n", 42);
    printf("Sekizlik: %d\n", 052);   // 0 ile başlarsa sekizlik → 5*8 + 2 = 42
    printf("Onaltilik: %d\n", 0x2A); // 0x ile başlarsa onaltılık → 2*16 + 10 = 42
    return 0;
}