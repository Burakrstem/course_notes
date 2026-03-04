# ⚙️ Control Statements

You know that the sentences of a program written in the C language are called **statements**.

Some statements only provide information to the compiler program. These statements do not cause the compiler to generate executing code. Such statements are called **"declaration statements."**

Some statements cause the compiler to generate executing code. Such statements are called **"executable statements."**

Executable statements can also be divided into different groups:

### Simple Statement:

Statements formed by an expression terminated with a terminating token (semicolon) are called **simple statements**:

    x = 10;
    y++;
    func();

Three separate simple statements are written above.

### Null Statement:

In the C language, a solitary terminating token (semicolon) ` ; ` constitutes a statement by itself. This statement is called the **null statement**. An empty block also constitutes a null statement:

    ;
    {}

Both statements above are null statements.

### Compound Statement:

A structure formed by one or more statements enclosed within a block is called a **compound statement**. A compound statement is shown below:

    {
        x = 10;
        y++;
        func();
    }

### Control Statement:

**Control statements** are statements that can change the flow of execution of a program. With control statements, the program's flow can be directed to different points. They conform to certain predefined syntactic rules of the C language and contain at least one keyword within their own syntax. The following control statements exist in the C language:

* `if` statement
* `while` loop statement
* `do while` loop statement
* `for` loop statement
* `break` statement
* `continue` statement
* `switch` statement
* `goto` statement
* `return` statement