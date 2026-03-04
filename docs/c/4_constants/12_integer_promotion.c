#include <stdio.h>

int main() {
    // 'A' is an integer constant (ASCII 65)
    char start_char = 'A'; 
    int offset = 3; 

    // The character constant 'A' is promoted to an int (65) for the addition.
    // The result (68) is then assigned back to the char variable.
    char result = start_char + offset; // 65 + 3 = 68 ('D')

    printf("Character constant 'A' value: %d\n", 'A');
    printf("Result of 'A' + 3: %c\n", result);

    return 0;
}