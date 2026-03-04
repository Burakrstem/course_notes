#include <stdio.h>

int main(void) {
    printf("%10s\n", "C");      // sağa yasla
    printf("%-10s\n", "C");     // sola yasla
    printf("%04d\n", 7);        // sıfırla doldur
    printf("%+d\n", 42);        // işaret göster
    printf("%.3f\n", 3.14159);  // ondalık basamak
    printf("%#x\n", 255);       // alternatif biçim -> 0xff
    return 0;
}