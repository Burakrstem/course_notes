#include <stdio.h>
#include <stdarg.h>

// Çok basit bir mini printf: sadece %d destekli
void mini_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    while (*fmt) {
        if (*fmt == '%' && *(fmt + 1) == 'd') {
            int val = va_arg(args, int);
            printf("%d", val);
            fmt += 2;
        } else {
            putchar(*fmt++);
        }
    }
    va_end(args);
}

int main(void) {
    mini_print("Sonuc: %d + %d = %d\n", 2, 3, 5);
    return 0;
}