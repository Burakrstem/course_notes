#include <stdio.h>

int main(void) {
    int a = 5;
    double b = 2.0;
    double result;

    // Implicit casting: int → double
    result = a + b;  
    printf("a + b = %.2f\n", result);

    // Explicit casting: double → int
    int truncated = (int)b;
    printf("b cast to int = %d\n", truncated);

    return 0;
}
