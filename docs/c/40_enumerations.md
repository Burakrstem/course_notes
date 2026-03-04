# 🔢 Enumerations

In many programs written, the need arises to use variables that can only take specific meaningful values. For example, a "Boolean" variable can only have two values: "True" and "False." A variable to hold a day of the week can take one of seven different values, as there are seven days in the week.

Another example is a variable to hold the suit of a playing card. Such a variable can only take 4 different values: Clubs, Diamonds, Hearts, Spades.

Such variables can be defined as integer types:

    int suit;
    suit = 1;

In the example above, the variable named `suit` holds the suit information of a playing card. Assigning the value 1 to this variable indicates that the suit value is Diamond.

Such a technique can certainly be used in applications. However, this technique has some drawbacks.

1.  The person reading the code does not receive direct information about what the integer literals used in the assignments to the variable named `suit` represent. The readability of the code decreases. For example, an assignment like:

        suit = 1;

    cannot be directly interpreted as the value "diamond" being assigned to the `suit` variable.

2.  The compiler cannot perform an additional check with the `suit` variable. The compiler is not aware that the `suit` variable should only take one of 4 different values. No such information has been given to the compiler. For example, assigning a value like 10 to such a variable is meaningless. However, the compiler cannot find this error during compilation and cannot issue an error or warning message.

The C language has a tool that allows the creation of a type that can take specific named integer values. This tool is called an **enumeration**, and the literals associated with this tool are called **"enumeration constants."**

The declaration of an enumeration type and the constants related to an enumeration type is done as follows:

    enum [enum type name] {constant1, constant2, ......};

`enum` is a keyword. The compiler maps the named constants between the curly braces to increasing integer values, starting from the value **0**. Example:

    enum Suit {Clubs, Diamonds, Hearts, Spades};

With the declaration above, the `Clubs` constant takes the value 0, the `Diamonds` constant takes the value 1, the `Hearts` constant takes the value 2, and the `Spades` constant takes the value 3.

    enum Bool {TRUE, FALSE};

Here, the `TRUE` constant takes the value 0, and the `FALSE` constant takes the value 1.

    enum Months {January, February, March, April, May, June, July, August,
                 September, October, November, December};

With this declaration, the enumeration constants are given increasing values in the form: $\text{January} = 0, \text{February} = 1, \dots \text{December} = 11$.

Values can be given to enumeration constants with the assignment operator inside the curly braces. The value of the constant following an enumeration constant given a value in this manner is one greater than the previous value.

    enum Months {January = 1, February, March, April, May, June, July,
                 August, September, October, November, December};

With this declaration, the enumeration constants are given increasing values in the form: $\text{January} = 1, \text{February} = 2, \dots \text{December} = 12$.

Positive or negative values within the integer type limits can be given to `enum` constants:

    enum RTVals {
        RT1 = -127,
        RT2,
        RT3,
        RT4 = 12,
        RT5,
        RT6,
        RT7 = 0,
        RT8,
        RT9 = 90
    };

With the declaration above, the values that the enumeration constants will take are as follows:

$\text{RT1} = -127, \text{RT2} = -126, \text{RT3} = -125, \text{RT4} = 12, \text{RT5} = 13, \text{RT6} = 14, \text{RT7} = 0, \text{RT8} = 1, \text{RT9} = 90$.

Different enumeration constants used in an enumeration declaration can have the same value. The following declaration is valid:

    enum Bool {FALSE, FALSE_AGAIN = 0, TRUE_VAL = 1, TRUE = 1};

The name of an enumeration constant must be different from all names used in the same scope. It is invalid for the name of a variable declared in the same scope as an enumeration constant, or the name of another enumeration constant, to be the same.

Enumeration tags (`enum tag`) follow the scope rules, just like structure and union tags. These names must be different from other enumeration, structure, and union tags in the same scope.

The enumeration tag may not be specified in declarations at all. In this case, the statement is usually terminated with a semicolon after the definition of the object(s) of that enumeration type immediately following the closing curly brace.

    enum {Sunday = 1, Monday, Tuesday, Wednesday, Thursday, Friday,
          Saturday} day1, day2, day3;

In the example above, `day1`, `day2`, and `day3` are variables created from the declared enumeration type (no specific type name was chosen). The disadvantage of such a declaration + definition operation is that another variable of the same enumeration type cannot be created again.

It is also not mandatory to define an object of a declared enumeration type:

    enum {MIN_SIZE = 10, HIGH = 20};

The declaration above is valid. The declared type has no name, but the enumeration constants `MIN_SIZE` and `HIGH` can be used everywhere this declaration is visible.

### `sizeof` Values of Enumeration Types

For an object defined from an enumeration type, the compiler allocates a space equal to the length of the **`int` type** on the system used. There is physically no difference between an object of an enumeration type and an object of an `int` type for the compiler.

For example, under Unix:

$$\text{sizeof}(\text{enum Days}) == \text{sizeof}(\text{int}) == 4$$

The expression is correct.

Of course, a drawback of this rule is that the largest enumeration constant value that can be used on a system where the `int` type is 2 bytes long can be $32767$.

### Enumerations and `typedef` Declarations

A `typedef` declaration can also be made for an enumeration type. This eliminates the need to use the `enum` keyword when using the type:

    typedef enum tagSuit {CLUBS, DIAMONDS, HEARTS, SPADES} Suit;

After the declaration, a definition like:

    Suit card1, card2, card3, card4;

can be made without using the `enum` keyword. After the `typedef` declaration, `Suit` now specifies a type name.

Now let's look at the following example:

    typedef enum {FALSE, TRUE} Bool;

Now, `Bool` is the name of a type that can take the values `FALSE` and `TRUE`.

> \[In the C++ language, since the names (tags) related to structure, union, and enumeration types can also be used as the general name of the type, a `typedef` declaration like the one above is not necessary.]

### Using Enumeration Types

Since a new type is created with the `enum` declaration, objects or pointers of this type can be defined. The return values and/or parameter variables of the functions to be defined can also be of such a type:

    typedef enum {Sunday, Monday, Tuesday, Wednesday, Thursday,
                 Friday, Saturday} Days;
    typedef struct {int d, m, y} Date;

In a structure type declaration, members can be selected from an enumeration type:

    typedef struct {
        Days day;
        // Assuming another enum Months is defined
        int year;
    } Date;

In the example above, the members named `day` and `month` (assuming `month` was intended) of the `Date` structure type are of enumeration types `Days` and `Months`.

### Enumeration Constants Can Be Used as Constant Expressions

An enumeration constant forms a **constant expression**. Therefore, enumeration constants can be used where a constant expression is required. Examine the following code:

    enum {MIN_SIZE = 100, AVERAGE_SIZE = 500, MAX_SIZE = 1000};
    void func()
    {
        int a[MIN_SIZE];      // Valid: MIN_SIZE is a constant expression
        int b[AVERAGE_SIZE];  // Valid:
        int c[MAX_SIZE];      // Valid:
        /***/
    }

The sizes of the names $a$, $b$, and $c$ defined in the `main` function (should be `func` context) above are determined by enumeration constants. The use of enumeration constants as the `case` expressions of the `switch` statement is a very frequent situation:

    Suit suit;
    /***/
    switch (suit) {
        case CLUBS:    /***/
        case DIAMONDS: /***/
        case HEARTS:   /***/
        case SPADES:   /***/
    }

### Comparison of Enumeration Types and `#define` Constants

The `#define` preprocessor directive concerns the preprocessor program. However, enumeration constants are processed during the **compilation phase**.

There is no concept of scope for a `#define` symbolic constant, as scope is a concept interpreted by the compiler. However, scope rules apply to enumeration types and constants. If an enumeration type is declared within a function, the enumeration constants related to this type are not known outside the function in question.

Even if multiple `#define` symbolic constants are used in a logical relationship, the compiler is unaware of this relationship. Therefore, the compiler program has no chance of generating a warning message regarding the incorrect use of these symbolic constants. However, the compiler is aware of the logical relationship between enumeration constants declared within the same type scope. It can produce a warning message if they are used incorrectly.

Enumeration constants, like symbolic constants defined with the `#define` directive, do not denote objects. For example:

    enum Metal {Iron, Copper, Tin, Zinc, Lead};
    /***/
    Tin = 3; /* Invalid */ // Cannot assign to enum constant

Enumeration constants are preferred for a specific number of definitions that are in a logical relationship. Including some names in a logical relationship under a type scope increases readability. For example:

    enum Day {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

Header files provided by compilers for systems define many enumeration types and enumeration constants related to these types. For example, the following enumeration declaration is taken from the `graphics.h` header file of a Borland compiler running on 80x86 systems:

    enum COLORS {
        BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
        DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA,
        YELLOW, WHITE
    };

### Type Conversions Related to Enumeration Types

In the C language, an enumeration type is physically treated as the **`int` type** by the compiler. Implicit type conversion is involved between enumeration types and other native types. For example, an `int` type value can be assigned to an enumeration variable. Or an enumeration constant can be assigned to an `int` type variable:

    typedef enum {OFF, HOLD, STANDBY, ON} Position;
    void func()
    {
        Position pos = 2;   /* Valid: 2 is assigned (implicitly converted) */
        int x = ON;         /* Valid: ON (which is 3) is assigned */
        /***/
    }

However, using the type cast operator when assigning other native types to enumeration variables increases the program's readability:

    pos = (Position)2;

### Printing Enumeration Constants to the Screen

An enumeration value can be printed to the screen with the standard `printf` function by matching it with the `%d` format specifier. There is no direct way to print the name of the enumeration constant, rather than its integer value, to the screen. A function can be written for this purpose:

    #include <stdio.h>
    #include <stdlib.h>
    typedef enum {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday,
                  Saturday} Days;
    
    void print_day(Days day)
    {
        // Use a static array of strings to map integer value to name
        static const char *days[] = {"Sunday", "Monday", "Tuesday",
                                     "Wednesday", "Thursday", "Friday", "Saturday"};
        printf("%s ", days[day]);
    }
    
    int main()
    {
        Days day;
        int k;
        for (k = 0; k < 10; ++k) {
            day = (Days)(rand() % 7); // Explicit cast is good practice
            print_day(day);
        }
        return 0;
    }