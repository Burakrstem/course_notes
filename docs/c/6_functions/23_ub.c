#include <stdio.h>

int main(void) {
    // UYARI: Aşağıdaki satır tanımsız davranıştır (UB).
    // %d tamsayı beklerken double gönderilirse sonuç belirsizdir.
    printf("%d\n", 3.14);

    // Doğrusu:
    printf("%f\n", 3.14);

    return 0;
}