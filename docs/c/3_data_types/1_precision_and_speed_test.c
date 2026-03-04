#include <stdio.h>
#include <time.h> // For performance measurement (clock_t)
#include <limits.h> // For loop limits

// Test parameters
#define ITERATIONS 100000000
#define CLOCK_UNIT CLOCKS_PER_SEC // Defined in <time.h>

void analyze_float_precision() {
    float f = 123456789.0f; 
    double d = 123456789.0;

    printf("--- 1. Precision Test ---\n");
    // float has around 6-7 digits of precision. The last digits are lost.
    printf("Float (low precision): %.2f\n", f); 
    // Double retains higher precision.
    printf("Double (high precision): %.2f\n", d); 
    printf("\n");
}

void analyze_performance_difference() {
    clock_t start, end;
    double time_used;
    long i;

    printf("--- 2. Performance Test (Iteration Count: %d) ---\n", ITERATIONS);

    // Integer Arithmetic Test (Fast)
    long int_sum = 0;
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        int_sum += (i & 0x0F); // Simple bitwise operation to ensure constant work
    }
    end = clock();
    time_used = ((double)(end - start)) / CLOCK_UNIT;
    printf("Integer Time (int_sum): %.4f seconds\n", time_used);


    // Floating-Point Arithmetic Test (Slower)
    double float_sum = 0.0;
    start = clock();
    for (i = 0; i < ITERATIONS; i++) {
        float_sum += (i * 1.0) / 10.0; // Floating point division and addition
    }
    end = clock();
    time_used = ((double)(end - start)) / CLOCK_UNIT;
    printf("Float Time (float_sum): %.4f seconds\n", time_used);

    // Note: The integer operations are expected to be significantly faster due to the CPU architecture.
}

int main() {
    analyze_float_precision();
    analyze_performance_difference();
    return 0;
}