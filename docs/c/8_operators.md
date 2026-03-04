# Operators

## What is an Operator?

Operators are atoms that perform predefined operations on **objects** or **literals**. Operators cause the microprocessor to perform an operation and, as a result, **produce a value**. Each operator defined in programming languages corresponds to at least one machine instruction. Although they perform similar operations, operator atoms may differ from one programming language to another.

In the C programming language, expressions often include operators:
* `c = a * b / 2 + 3` (4 operators: `=`, `*`, `/`, `+`)
* `++x * y--` (3 operators: `++`, `*`, `--`)
* `a >= b` (1 operator: `>=`)

## What is an Operand?

The objects or literals that operators operate on are called **operands**. In C, operators can be divided into three groups based on the number of operands they take:

### 1. Unary Operators
These operators take a single operand.
* *Example:* `++` and `--` operators (`++x`).

### 2. Binary Operators
These operators take two operands.
* *Example:* Arithmetic operators like addition (`+`) and division (`/`) (`x + y`).

### 3. Ternary Operator
C has only one ternary operator, which is the **conditional operator** (`? :`).

Operators can also be grouped based on their position relative to their operand(s):

* **Postfix Operators:** Placed after their operand(s).
    * *Example:* Postfix `++` operator (`x++`).
* **Prefix Operators:** Placed before their operand(s).
    * *Example:* Logical NOT operator (`!x`).
* **Infix Operators:** Placed between their operands.
    * *Example:* Arithmetic addition operator (`x + y`).

## Operators Producing a Value

Operators produce a value as a result of the operation they perform. The value produced by an operator can be an operand for another operator within the same expression. The value produced by the last evaluated operator in an expression becomes the value of the expression.

The most important feature of operators is that they **produce a value** as a result of their operation. The programmer may or may not use the value produced by the operator.

The produced value can be used in the following ways:
* **Assigned to another variable:** `x = y + z;` (The value produced by `+` is assigned to `x`).
* **Sent as an argument to a function:** `func(y + z);` (The value produced by `+` is sent to `func`).
* **Used to form a function's return value:**
    ```c
    int func() {
        return (y + z); // The return value is the value produced by '+'
    }
    ```

Not using the value produced by an operator is not a syntax error in C, but compilers usually issue a **warning** to the programmer.
* *Example:* The expression `x + y;` produces the value 30, but since it is not used, a Borland compiler might issue the warning: `"code has no effect!"`.

## Operator Precedence and Associativity

In C, expressions have types and values. The compiler determines an expression's value by:
1. Operators producing values according to their **precedence order**.
2. The produced values being passed as operands to operators with lower precedence.
3. The final value remaining being the value of the expression.

Every programming language has operator precedence. Without precedence, the results of operations would vary across machines and compilers.

* C has **45 operators** across **15 distinct precedence levels**.
* **Associativity** (Precedence Direction) defines whether operators at the same precedence level are evaluated from left-to-right or right-to-left.
    * Levels 2, 13, and 14 are **right associative**.
    * All other levels are **left associative**.

A single symbol can be used for multiple operators (e.g., `*` for multiplication and the indirection operator, or `&` for bitwise AND and the address-of operator).

## Operator Side Effects

While the main function of C operators is to produce a value, some operators also **change the values of their operand objects**. This change, which is writing a new value to the object's memory location, is called a **side effect**.

* *Example:* The assignment operator (`=`) and the increment/decrement operators (`++`, `--`) have side effects.

## Constraints on Operators

Programming language rules impose certain constraints on operator usage.
* *Constraint Example 1:* The `++` operator requires its operand to be an expression that designates an object (an **lvalue**); otherwise, a compile-time error occurs.
* *Constraint Example 2:* The modulus operator (`%`) requires both operands to be of an **integer type** (`char`, `short`, `int`, `long`); using real number types is invalid.

## Classification of Operators by Function

Operators are classified based on the operations they perform:

* **Arithmetic Operators:** Addition, subtraction, multiplication, increment, decrement, and sign operators.
* **Relational Operators (Comparison):** Greater than, greater than or equal, less than, less than or equal, equal, not equal.
* **Logical Operators:** Logical AND, logical OR, logical NOT.
* **Pointer Operators:** Address-of, indirection (content), and subscript (`[]`) operators.
* **Bitwise Operators:** Bitwise NOT, bitwise shift, bitwise AND, OR, and XOR.
* **Assignment Operators:** Simple assignment and compound assignment operators.
* **Special Purpose Operators:** Conditional operator, `sizeof`, type cast operator.

## Arithmetic Operators

### Addition (`+`) and Subtraction (`-`) Operators
* Binary, infix operators.
* Produce the sum or difference of their operands.
* No requirement for operands to be of the same type.
* Precedence level 4; left associative.
* **No side effects**.

### Unary Sign Operators (`-` and `+`)
* Unary, prefix operators.
* **Sign Minus (`-`):** Produces the negative of its operand's value (compiler generates code to multiply the value by -1). It produces an rvalue (a value, not an object), so it cannot be assigned to.
    * *Example:* `-x` and `0 - (x)` are equivalent.
* **Sign Plus (`+`):** Added for mathematical similarity; has no effect on its operand's value and produces the same value as its operand.
    * *Example:* `+x` and `0 + (x)` are equivalent.
* Precedence level 2; right associative.
* No side effects.

### Multiplication (`*`) and Division (`/`) Operators
* Binary, infix operators.
* **Multiplication (`*`):** Produces the product of its operands.
* **Division (`/`):** Produces the quotient of the left operand divided by the right operand.
    * *Note:* If both operands are integer types, the result is an integer (integer division).
* Precedence level 3; left associative.
* No side effects.
* The `*` symbol is also used as a pointer (indirection) operator, but they do not conflict because multiplication is binary while indirection is unary.

### Modulus (`%`) Operator
* Binary, infix operator.
* **Constraint:** Both operands **must be integer types** (char, short, int, long). Real number types are invalid.
* Produces the remainder of the left operand divided by the right operand.
* No side effects.

### Increment (`++`) and Decrement (`--`) Operators
* Single-operand operators; can be used in **prefix** or **postfix** positions.
* Used to increase (`++`) or decrease (`--`) the value of a variable by 1.
* They **have side effects** (they change the value of the operand object in memory).
* Precedence level 2; higher than other arithmetic operators; right associative.

#### Usage
* **Isolated use (`++c;` or `c++;`):** No difference; both are equivalent to `c = c + 1;`.
* **In expressions:**
    * **Prefix (`++x`):** The value produced is the value *after* the increment/decrement.
    * **Postfix (`x++`):** The value produced is the value *before* the increment/decrement; the actual change to the object's value happens after the entire expression is evaluated.

---

## Important Terms in C Standards

### Behavior
The way a compiler interprets and understands a specific piece of code is called "compiler behavior".

### Undefined Behavior
Expressions that lead to interpretation differences not explicitly specified in the standards, which can vary from compiler to compiler. Programmers should avoid them, as there is no guarantee of the outcome. Code with undefined behavior is syntactically valid.
* **`++`/`--` Related Undefined Behavior:** If a variable is an operand of `++` or `--` in an expression, it should not appear again in that same expression.
    * *Example:* `y = ++x + ++x;`, `y = ++x + x`, and `a = ++a;` all exhibit undefined behavior.

### Unspecified Behavior
Situations where the compiler can interpret the source code differently, but the options are limited. Compilers are not required to document which option they chose. Programmers should avoid code that leads to unspecified behavior.

### Implementation-Dependent Behavior
Certain C features are left to the compiler writers' choice for flexibility (e.g., the length of `int`, whether default `char` is signed or unsigned). Compilers **must document** how these features were chosen.

### Diagnostic Messages
The notification given by the compiler about the cause of a problem when it encounters problematic code.
* A warning or error message should be issued when syntactical or semantic rules are violated. Warnings are typically for minor issues that can be fixed, while errors are for larger mistakes.

---

## Relational Operators (Comparison)

C has 6 relational operators:
* `<` (less than)
* `>` (greater than)
* `<=` (less than or equal)
* `>=` (greater than or equal)
* `==` (equal)
* `!=` (not equal)

All are **binary, infix** operators.

* The first four (`<`, `>`, `<=`, `>=`) are at precedence level 6.
* The last two (`==`, `!=`) are at precedence level 7.
* They have lower precedence than arithmetic operators.

In C (unlike C++ or Java), there is no dedicated boolean data type. Relational operators produce an **`int` type value**:
* **1** if the proposition is **True**.
* **0** if the proposition is **False**.

---

## Logical Operators

These operators perform logical operations on their operands. They interpret their operands as True or False. C has three logical operators with different precedence levels:

* `!` (logical NOT)
* `&&` (logical AND)
* `||` (logical OR)

Since C does not have a boolean type, `int` is used, where **1 is True** and **0 is False**. Any expression can be an operand to a logical operator. If the expression's numeric value is **non-zero, it is interpreted as True (1)**; if it is **0, it is interpreted as False (0)**.

### Logical NOT Operator (`!`)
* Unary, prefix operator.
* Produces the inverse logical value of its operand.
    * If the operand is True (non-zero), it produces **0**.
    * If the operand is False (0), it produces **1**.

### Logical AND Operator (`&&`)
* Lower precedence than relational operators, but higher than `||`.
* Produces **1 (True)** only if both operands are True; otherwise, it produces **0 (False)**.

### Logical OR Operator (`||`)
* Lowest precedence logical operator.
* Produces **1 (True)** if at least one operand is True; produces **0 (False)** only if both are False.

### Short Circuit Behavior (`&&` and `||`)
C guarantees that the left operand is evaluated first for both `&&` and `||`. This feature, called **short circuit behavior**, allows for more efficient code:
* **`&&`:** If the left operand is evaluated as False (0), the right operand is **never evaluated**.
* **`||`:** If the left operand is evaluated as True (non-zero), the right operand is **never evaluated**.

Logical operators perform their operation by first interpreting their operands as 1 or 0, but they **have no side effects** on the memory values of their operands.

---

## Assignment Operators

Assignment operators are at precedence level 14 (second lowest, only higher than the comma operator) and are **right associative**.

### Simple Assignment Operator (`=`)
* Like other operators, the assignment operator produces a value in addition to performing the assignment.
* The value produced is **the value assigned to the object**.
* The value produced by the assignment is **not an object**; therefore, expressions like `(b = c) = a;` are invalid in C.
* Its right-to-left associativity allows chained assignments like `a = b = c = d = 5;`.

### Compound Assignment Operators (`+=`, `-=`, `*=`, etc.)
Used when the operand being operated on and the object receiving the result are the same.
* `<object1> = <object1> operation <operand2>` is equivalent to `<object1> operation= <operand2>`.
* They are at the same precedence level as the simple assignment operator.
* Preferred for readability and brevity.
* **Example:** `x += 5;` is equivalent to `x = x + 5;`.

All assignment operators have **side effects**. The side effect is the modification of the left operand's value in memory, by assigning the value of the right operand expression to the object on the left.

---

## Comma Operator (`,`)

The comma operator combines two separate expressions into a single expression. It has the **lowest precedence** in C (level 15).

* The evaluation of the left operand's expression is guaranteed to occur **before** the evaluation of the right operand's expression.
* The value produced by the operator is **the value produced by the right-hand expression**. The left operand's value does not affect the result.

## Precedence Operator (`()`)

The parentheses operator is used to **increase the precedence** of an expression.
* It is in the **highest precedence group** (level 1).
* It follows the **left-to-right** associativity rule.
* If the operand expression designates an object, the expression produced by the precedence operator also designates an object.

## Operator Precedence vs. Order of Execution

Operator precedence **does not guarantee** that an operation will be performed sooner by the processor.
* *Example:* In `x = func1() * func2() + func3();`, the higher precedence of multiplication (`*`) does not guarantee that `func1()` will be called before `func3()`.

However, the following 4 C operators **do guarantee** the order of operation for their operands:
1. **Logical AND (`&&`)**
2. **Logical OR (`||`)**
3. **Conditional (`? :`)**
4. **Comma (`,`)**

The order is guaranteed to ensure the **short circuit behavior** for `&&`/`||`, the required evaluation of the first operand for the conditional operator, and the left-to-right execution of the comma operator.

---

## C Language Operator Precedence Table

| Level | Operator | Description | Associativity |
| :---: | :---: | :--- | :--- |
| **1** | `()`, `[]`, `.`, `->` | Precedence, Subscript, Structure Access | left-to-right |
| **2** | `+`, `-`, `++`, `--`, `~`, `!`, `*`, `&`, `sizeof`, `(type)` | Unary Signs, Inc/Dec, Bitwise/Logical NOT, Indirection, Address Of, sizeof, Type Cast | right-to-left |
| **3** | `*`, `/`, `%` | Multiplication, Division, Modulus | left-to-right |
| **4** | `+`, `-` | Addition, Subtraction | left-to-right |
| **5** | `<<`, `>>` | Bitwise Shift Left/Right | left-to-right |
| **6** | `<`, `>`, `<=`, `>=` | Relational Operators | left-to-right |
| **7** | `==`, `!=` | Equality Operators | left-to-right |
| **8** | `&` | Bitwise AND | left-to-right |
| **9** | `^` | Bitwise Exclusive OR (XOR) | left-to-right |
| **10** | `|` | Bitwise OR | left-to-right |
| **11** | `&&` | Logical AND | left-to-right |
| **12** | `||` | Logical OR | left-to-right |
| **13** | `?:` | Conditional Operator | right-to-left |
| **14** | `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=`, `&=`, `|=`, `^=` | Assignment Operators (Simple & Compound) | right-to-left |
| **15** | `,` | Comma Operator | left-to-right |

## Additional examples
### 1. Arithmetic, Unary & Side Effects
This example focuses on basic arithmetic, the difference between prefix and postfix increment/decrement, and the concept of an operator producing a value and having a side effect.
```c
#include <stdio.h>

void basic_operators_demo() {
    int a = 10;
    int b = 3;
    int result;

    printf("--- 1. Basic Arithmetic (Binary Infix) ---\n");
    // Binary Infix Operators: +, -, *, /, %
    printf("Addition: 10 + 3 = %d\n", a + b);     // Produces 13
    printf("Division (Integer): 10 / 3 = %d\n", a / b); // Produces 3 (integer division)
    printf("Modulus (Remainder): 10 %% 3 = %d\n", a % b); // Produces 1 (Constraint: requires integer types)
    
    // Unary Prefix Operator: - (Sign Minus)
    printf("Unary Minus: -10 = %d\n", -a); // Produces -10

    printf("\n--- 2. Unary Inc/Dec Operators (Side Effects) ---\n");
    
    int x = 5;
    printf("Initial x: %d\n", x); // x is 5

    // Prefix Increment: ++x
    // Action: 1. Changes x (side effect) 2. Value produced is the NEW value
    result = ++x; 
    printf("Prefix ++x: Value produced = %d, x after operation = %d\n", result, x); // Output: 6, 6

    x = 5; // Reset x
    
    // Postfix Increment: x++
    // Action: 1. Value produced is the OLD value 2. Changes x (side effect)
    result = x++;
    printf("Postfix x++: Value produced = %d, x after operation = %d\n", result, x); // Output: 5, 6

    // Note: If used in isolation (e.g., x++;), prefix and postfix are functionally identical.
}

/*
To compile and run:
gcc basic_operators.c -o basic_demo
./basic_demo
*/
```

### 2. Relational, Logical & Short-Circuiting
This example demonstrates how Relational and Logical operators produce integer values (1 or 0) and illustrates the crucial short-circuit behavior of && and ||
```c
#include <stdio.h>

int check_function(const char* name) {
    printf("-> Evaluating function: %s\n", name);
    return 0; // Always returns 0 (False)
}

void intermediate_operators_demo() {
    int val1 = 10, val2 = 20;

    printf("--- 1. Relational Operators (Produce 1 or 0) ---\n");
    // Relational Operators: <, >, <=, >=, ==, !=
    
    // val1 < val2 (10 < 20) is True, so it produces 1.
    printf("10 < 20: %d\n", val1 < val2); 

    // val1 == val2 (10 == 20) is False, so it produces 0.
    printf("10 == 20: %d\n", val1 == val2); 

    printf("\n--- 2. Logical Operators (!, &&, ||) ---\n");
    
    // Logical NOT: !
    // ! (10 < 20) -> ! (1) -> 0
    printf("! (10 < 20): %d\n", !(val1 < val2)); 

    // Logical AND: &&
    // (10 < 20) && (10 != 20) -> 1 && 1 -> 1
    printf("(10 < 20) && (10 != 20): %d\n", (val1 < val2) && (val1 != val2)); 

    printf("\n--- 3. Short Circuit Behavior (&&) ---\n");
    int x = 5;
    
    // Condition: (x is 0/False) && (Call function)
    // The left side (x != 5) is 0 (False).
    // The right operand is NOT evaluated. The function is NOT called.
    if ((x != 5) && check_function("RightOperand_AND")) {
        // This block is skipped
    } else {
        printf("&& Short Circuit: Left side was False (0), RightOperand_AND was NOT called.\n");
    }

    printf("\n--- 4. Short Circuit Behavior (||) ---\n");
    
    // Condition: (x is non-zero/True) || (Call function)
    // The left side (x == 5) is 1 (True).
    // The right operand is NOT evaluated. The function is NOT called.
    if ((x == 5) || check_function("RightOperand_OR")) {
        printf("|| Short Circuit: Left side was True (1), RightOperand_OR was NOT called.\n");
    }
}

/*
To compile and run:
gcc intermediate_operators.c -o intermediate_demo
./intermediate_demo
*/

```

### 3. Precedence, Ternary, Comma & Undefined Behavior
This example explores the more complex aspects: Precedence, the ternary operator, the low-precedence comma operator, and a demonstration of an expression with Undefined Behavior (for instructional purposes, to highlight what to avoid).
```c
#include <stdio.h>

void advanced_operators_demo() {
    int a = 20, b = 5, c = 2, d;

    printf("--- 1. Precedence and Associativity ---\n");
    
    // Expression: d = a + b * c;
    // Precedence: * (Level 3) is higher than + (Level 4).
    // Evaluation: d = a + (b * c) -> d = 20 + 10 -> 30
    d = a + b * c;
    printf("a + b * c (20 + 5 * 2) = %d\n", d); // Output: 30

    // Expression: d = (a + b) * c;
    // Parentheses (Level 1) force a higher precedence.
    // Evaluation: d = (20 + 5) * 2 -> d = 25 * 2 -> 50
    d = (a + b) * c;
    printf("(a + b) * c ( (20 + 5) * 2 ) = %d\n", d); // Output: 50

    printf("\n--- 2. Conditional (Ternary) Operator (?:) ---\n");
    // The C-only Ternary Operator: <condition> ? <value_if_true> : <value_if_false>
    // Right Associative (Level 13)
    
    int max = (a > b) ? a : b; // Condition (a > b) is True, max gets a (20)
    printf("Max of 20 and 5 is: %d\n", max); 

    int abs_val = (b < 0) ? -b : b; // Condition (b < 0) is False, abs_val gets b (5)
    printf("Absolute value of 5 is: %d\n", abs_val);

    printf("\n--- 3. Comma Operator (,) ---\n");
    // Lowest Precedence (Level 15). Guarantees left-to-right evaluation.
    // The value produced by the whole expression is the value of the RIGHT operand.
    
    int e = 0;
    // (e = 10, e + 5)
    // 1. e = 10 (Side effect: e is now 10)
    // 2. e + 5 -> 10 + 5 -> 15 (Value produced by the expression is 15)
    d = (e = 10, e + 5); 
    printf("Comma Operator (e = 10, e + 5): Result = %d, e value = %d\n", d, e); // Output: 15, 10
    
    printf("\n--- 4. WARNING: Undefined Behavior ---\n");
    
    int x = 10;
    // **DANGER!** A variable 'x' is modified by '++' and also appears elsewhere in the expression.
    // C Standard says: "If a side effect on a scalar object is unsequenced relative to either 
    // a second side effect on the same scalar object or a value computation using the value 
    // of the same scalar object, the behavior is undefined."
    // The outcome of the following line is NOT guaranteed and should be AVOIDED.
    // Depending on the compiler/optimization, the result could be 22, 23, or something else.
    int result_ub = ++x + x; 
    
    printf("++x + x (Initial x=10). The result is: %d (!!! Undefined Behavior !!!)\n", result_ub);
    printf("Final x value: %d\n", x);
}

/*
To compile and run:
gcc advanced_operators.c -o advanced_demo
./advanced_demo
*/

```