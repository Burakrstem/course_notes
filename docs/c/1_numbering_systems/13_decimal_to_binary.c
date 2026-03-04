#include <stdio.h>

void decimalToBinary(int decimal){
    int bits[32];
    int index = 0;
    while (decimal > 0){
        bits[index++] = decimal % 2;
        decimal /= 2;
    }
    for (int i = index - 1; i >= 0; i--){
        printf("%d", bits[i]);
    }
}


int main() {
    int n = 87;
    printf("%d in binary: ", n);
    decimalToBinary(n);
    return 0;
}