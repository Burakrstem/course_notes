# 🔄 Recursive Functions

A function can call itself, just as it can call another function. Functions of this type are called **recursive functions**. Algorithms can be divided into three separate groups based on this property:

1.  Algorithms that can be written with non-recursive functions.
2.  Algorithms that can be written with both non-recursive and recursive functions.
3.  Algorithms written only with recursive functions.

Typical algorithms that must be written with recursive functions are:

* Directory tree traversal algorithms
* Parsing algorithms
* Tree algorithms
* Many specialized algorithms

What is the criterion for whether an algorithm can be written with functions that call themselves? If a situation similar to the initial situation is encountered again as the algorithm progresses, the algorithm can most likely be written with a function that calls itself.

When a function calls itself, all its local variables are recreated. The same situation applies to the function's parameter variables. For this reason, recursive functions generally use the **stack area** more heavily compared to other functions.

Recursive functions call themselves for a period to perform the operation. Then, the process of exiting the functions begins; that is, all called functions begin to return.

## Typical Examples of Recursive Functions

An iterative function that calculates the factorial is written below:

    int fact(int n)
    {
        int result = 1;
        while (n)
            result *= n--;
        return result;
    }

The same function can also be written recursively:

    int fact(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        return n * fact(n - 1); // Recursive call
    }

The flow of the function is as follows (for $n = 5$):

* $n = 5$ for val = $5 \times \text{fact}(4)$;
* $n = 4$ for val = $4 \times \text{fact}(3)$;
* $n = 3$ for val = $3 \times \text{fact}(2)$;
* $n = 2$ for val = $2 \times \text{fact}(1)$;
* $n = 1$ for return 1;

It can be said that the iterative factorial function is more efficient.

An iterative function that prints an integer in the binary number system is defined below:

    #include <stdio.h>
    void bitprint(int i)
    {
        int k;
        for (k = sizeof(int) * 8 - 1; k >= 0; --k)
            putchar(((i >> k) & 1) + '0');
    }

The function can be defined recursively in the following form:

    #include <stdio.h>
    void bitprint(int i)
    {
        if (i == 0)
            return;
        bitprint(i >> 1); // Print the rest of the bits
        putchar((i & 1) + '0'); // Print the current LSB
    }

Again, it can be said that the non-recursive form is more efficient.

An iterative function that prints a string in reverse is defined below:

    #include <stdio.h>
    #include <string.h>
    void putsrev(const char *str)
    {
        int i;
        for (i = strlen(str) - 1; i >= 0; --i)
            putchar(str[i]);
        putchar('\n');
    }

The function can be defined recursively in the following form:

    #include <stdio.h>
    void putsrev(const char *str)
    {
        if (*str == '\0') // Base case: end of string
            return;
        putsrev(str + 1); // Recurse with the rest of the string
        putchar(*str); // Print the current character after recursion returns
    }

The `ters_yaz` (write\_reverse) function whose definition is given below prints a string entered from the keyboard in reverse:

    #include <stdio.h>
    void ters_yaz()
    {
        char ch;
        if ((ch = getchar()) != '\n') // If not newline
            ters_yaz(); // Recursive call
        putchar(ch); // Print current character (after recursion returns)
    }

An iterative function that prints an integer using only the `putchar` function is defined below:

    #include <stdio.h>
    #define SIZE 100
    void printd(int i)
    {
        char s[SIZE];
        int k = 0;
        int fnegative = 0;
        
        if (i < 0) {
            fnegative = 1;
            i = -i;
        }
        
        do {
            s[k++] = i % 10 + '0';
            i /= 10;
        } while(i);
        
        if(fnegative)
            s[k++] = '-';
            
        for (k--; k >= 0; --k) // Print in reverse order
            putchar(s[k]);
    }

The function can be defined recursively in the following form:

    #include <stdio.h>
    void print(int n)
    {
        if (n < 0) {
            putchar('-');
            n = -n;
        }
        if (n / 10) // Recurse with the rest of the digits
            print(n / 10);
        putchar(n % 10 + '0'); // Print the current digit
    }

The `power` function, which returns a specific integer power of an integer, is written recursively below:

    int power(int base, int exp)
    {
        if (exp == 0) // Base case: x^0 = 1
            return 1;
        return base * power(base, exp - 1); // Recursive step
    }

The `get_gcd` function, which returns the greatest common divisor of two integers, is defined recursively below:

    int get_gcd(int a, int b)
    {
        if (a >= b && a % b == 0) // Base case: b is a divisor of a
            return b;
        if (a < b) // Swap arguments if a < b
            return(get_gcd(b, a));
        return get_gcd(b, a % b); // Euclidean algorithm step
    }

The `fibonacci` function defined below returns the $n$-th term of the Fibonacci series:

    int fibonacci(int n)
    {
        if (n == 1 || n == 2) // Base cases: fib(1) = 1, fib(2) = 1
            return 1;
        return fibonacci(n - 1) + fibonacci(n - 2); // Recursive step
    }

An iterative function that performs the same task would be much more efficient:

    int fibonacci(int n)
    {
        int x = 1;
        int y = 1;
        int k, result;
        
        if (n == 1 || n == 2)
            return 1;
            
        for (k = 2; k < n; ++k) {
            result = x + y;
            x = y;
            y = result;
        }
        return y; // y holds the nth term
    }

The recursively defined `rakam_yaz` (write\_digit) function below prints each digit of an integer as text to the screen:

    #include <stdio.h>
    void rakam_yaz(int n)
    {
        static const char *rakamlar[ ] = { "Zero", "One", "Two", "Three", "Four",
                                          "Five", "Six", "Seven", "Eight", "Nine" };
        if (n > 9) // Recurse if more than one digit
            rakam_yaz(n / 10);
        printf("%s ", rakamlar[n % 10]); // Print the current digit as text
    }

A recursive function named `to_hex` that prints an integer to the screen in the hexadecimal number system is defined below:

    void to_hex(int n)
    {
        static const char *htab[ ] = { "0", "1", "2", "3", "4", "5", "6", "7",
                                      "8", "9", "A", "B", "C", "D", "E", "F" };
        if (n > 15) // Recurse if more than one hex digit
            to_hex(n / 16);
        printf("%s", htab[n % 16]); // Print the current hex digit
    }

A function named `strrev_r` that reverses a string is defined below:

    #include <stdio.h>
    #include <string.h>
    #define SIZE 100
    
    void swapstr_recursive(char *str, int l, int r)
    {
        char temp;
        if (l >= r) // Base case: pointers meet or cross
            return;
            
        // Swap
        temp = str[l];
        str[l] = str[r];
        str[r] = temp;
        
        swapstr_recursive(str, l + 1, r - 1); // Recurse with inner segment
    }
    
    char *strrev_r(char *str)
    {
        // Wrapper function to start the recursive process
        swapstr_recursive(str, 0, strlen(str) - 1);
        return str;
    }
    
    int main()
    {
        char str[SIZE];
        printf("enter a string : ");
        gets(str);
        printf("string = (%s)\n", str);
        strrev_r(str);
        printf("string = (%s)\n", str);
        return 0;
    }

Undoubtedly, reversing the string could also be achieved with a non-recursive function. You see that the recursively written `strrev_r` function has three parameters (in its helper): the starting address of the string, and the index values of the first and last elements to be swapped.

Ensuring that the `strrev` function only receives the starting address of the string is achieved by writing a **wrapper function**. A wrapper function is not the function that performs the task itself. Wrapper functions are small functions that call the function that performs the task.

The `revprint` function defined in the program below prints the words of a string whose address it receives to the screen in **reverse order**:

    #include <stdio.h>
    #include <string.h>
    #define MAX_WORD_LEN 100
    #define ARRAY_SIZE 1000
    
    void revprint(const char *str)
    {
        char s[MAX_WORD_LEN + 1] = "";
        int index = 0;
        static const char seps[] = " \n\t,.:;!?";
        
        // 1. Skip leading separators
        while (*str && strchr(seps, *str))
            str++;
        
        if (!*str) // Base case: end of string/no more words
            return;
        
        // 2. Copy current word
        while (!strchr(seps, *str)) {
            if (index < MAX_WORD_LEN) // Safety check
                s[index++] = *str;
            str++;
        }
        s[index] = '\0'; // Null-terminate the word
        
        // 3. Recurse with the rest of the string
        revprint(str);
        
        // 4. Print current word after recursion returns
        printf("%s ", s);
    }
    
    int main()
    {
        char str[ARRAY_SIZE];
        printf("enter a sentence : ");
        gets(str);
        revprint(str);
        return 0;
    }