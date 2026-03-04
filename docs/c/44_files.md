# 🧠 C Programming Basics
# 📂 Files

Regions defined in secondary memory are called **files**. File operations are entirely under the control of the operating system. Every file has a name. However, file naming rules can vary from system to system.

The operating system is also a program. This program also works in the form of separately written functions calling each other. For example, running a program by typing its name on the command line is actually done by calling several system functions. Functions that receive the text written on the command line, search for a file on the disk, load a file into memory, and run the program in memory are called sequentially.

Functions belonging to the operating system, which the operating system itself calls during its operation and which the system programmer can call from outside, are called **system functions**. These types of functions are called API (Application Programming Interface) functions in Windows systems, and **system calls** in the UNIX operating system.

In fact, all file operations, regardless of the programming language used, are performed by the operating system's system functions. The names and parametric structures of system functions can vary from system to system.

## Opening a File

A file must be opened before operations can be performed on it. To open a file, a system function named "file open" of the operating system is used. Various initial operations related to the file are performed by the operating system during the file opening process.

When a file is opened, the file information is written to a table within the operating system called the **"File Table."** The format of the file table can vary from system to system. For example, a typical file table might look like the following:

| **File Table** | | | | |
| :--- | :--- | :--- | :--- | :--- |
| **Sequence No** | **File Name** | **File Location on Disk** | **File Properties** | **Others** |
| 0 | AUTOEXEC.BAT | ...... | ...... | ...... |
| 1 | ... | | | |
| ... | | | | |
| 12 | ... | | | |

The system functions of the operating system also have parameter variables and return values. The parameter of the "file open" system function is the name of the file to be opened. The function returns with the sequence number where the file information is written in the file table, which is called the **"file handle."** This handle value is passed as a parameter to other file functions. Additionally, other important operations are performed during the file opening process.

## Closing a File

Closing a file reverses the operations performed during opening. For example, during file closing, the information related to this file in the operating system's file table is deleted. Every opened file must be closed. Not closing a file can lead to various problems.

## Writing and Reading Information to a File

Operating systems have system functions that write $n$ bytes of data to a file and read $n$ bytes of data from a file. Writing and reading operations are performed using these functions.

## File Position Indicator

A file consists of bytes. Each byte in the file is assigned a number starting from 0 and increasing sequentially. This number is called the **offset number** of the relevant byte. The file position indicator is an internally held `long` type variable, specifying an offset value, i.e., a byte number. Standard functions that write to and read from a file always perform these writing and reading operations starting from the location indicated by the file position indicator. These functions do not request a value indicating where in the file to write or where in the file to read from. For example, let the location indicated by the file position indicator be the 100th offset. When a system function is called to read 10 bytes of information from the file, 10 bytes of information are read starting from the 100th offset. The operating system has a system function that positions the file indicator. When a file is first opened, the file position indicator points to the 0th offset. For example, if 10 bytes are desired to be read starting from the 100th byte of a file, the following operations must be performed sequentially:

* The relevant file is opened.
* The file position indicator is positioned to the 100th offset.
* 10 bytes are read from the file.
* The file is closed.

File operations in the C language can be performed in two ways:

1.  By directly calling the operating system's system functions.
2.  By using standard C functions.

The names of all standard file functions declared in `stdio.h` start with the letter **`f`**. Standard C functions also call the operating system's system functions to perform their tasks. The system functions of the operating system are **not portable**. Their names and parametric structures can vary from system to system. Therefore, the use of **standard C functions is recommended**.

## The `fopen` Function

    FILE *fopen (const char *fname, const char *mode);

The first parameter of the function is the name of the file to be opened. The second parameter is the **opening mode** information. Both pieces of information are conveyed to the function as a string. The file name can also include path information. The character `/` can also be used for directory traversal. A file can be opened in specific modes. The opening mode information determines which operations can be performed on the file to be opened. The opening mode information also determines how the function will behave if the file desired to be opened does not exist. The table below lists the strings that must be passed to the `fopen` function to convey the opening mode information:

| Mode | Meaning |
| :--- | :--- |
| `"w"` | Opens the file for writing. Cannot read from the file. The file does not have to exist. If the file does not exist, a file with the given name is created. If the file exists, the file is zeroed out (truncated). Opening an existing file in this mode causes the file to be lost. |
| `"w+"` | Opens the file for both writing and reading. The file does not have to exist. If the file does not exist, a file with the given name is created. If the file exists, the file is zeroed out. Opening an existing file in this mode causes the file to be lost. |
| `"r"` | Opens the file for reading. Cannot write to the file. If the file does not exist, it cannot be opened. |
| `"r+"` | Opens the file for both reading and writing. If the file does not exist, it cannot be opened. |
| `"a"` | Opens the file for appending. Cannot read from the file. The file does not have to exist. If the file does not exist, a file with the given name is created. If the file exists, the file is not zeroed out. |
| `"a+"` | Opens the file for both appending and reading. The file does not have to exist. If the file does not exist, a file with the given name is created. If the file exists, the file is not zeroed out. |

The return value of the function is an address of type **`FILE *`** (a pointer to the `FILE` structure). The function stores some information related to the opened file in the members of an object of type `FILE` structure and returns the address of this object. The `FILE` structure related to the function's return value is declared in the `stdio.h` header file. The members of this structure are not standard. They can vary from system to system. Programmers do not need to access the members of this structure directly.

The `fopen` function calls the operating system's file open system function to open the file, writes some information related to the file to the members of an object of type `FILE` structure, and returns the starting address of this object. For example, the "file handle" value is also contained within this structure.

The `FILE *` address returned by the `fopen` function is a **safe address**. The file may not be opened due to various reasons. In this case, the `fopen` function returns the **NULL address**. The return value of the function must definitely be checked. A typical check operation can be done as follows:

    /*…..*/
    FILE *f;
    if ((f = fopen("letter.txt", "r")) == NULL) {
        printf("cannot open file...\n");
        exit(EXIT_FAILURE);
    }

In the example above, a file named `letter.txt` is attempted to be opened for reading. If the file is not opened, an error message is printed to the screen, and the program is terminated with the standard `exit` function. You see that the code snippet above utilizes the fact that the value produced by the assignment operator is the value assigned to the object. Undoubtedly, terminating the program is not mandatory if a file desired to be opened with the `fopen` function cannot be opened. However, in the code examples to be given later, the program will be terminated for now if a file cannot be opened.

The file name can contain information such as the drive and path regarding the file's location. Care must be taken when providing path information if the file name is provided with a string literal. Path information may contain the `\` (backslash) character. Using the `\` character inside a string literal can cause the `\` character and the character following it to be interpreted as a predetermined escape sequence. For example:

    fopen("C:\source\new.dat", "r");

In the function call above, the compiler interprets the `\n` character as the "newline" character, and the `\s` character as "undefined." Avoiding this problem is possible by using **`\\`** instead of the `\` character:

    fopen("C:\\source\\new.dat", "r");

The append modes (`"a"`, `"a+"`) are not frequently used modes. There is a difference between the `"w"` mode and the `"a"` mode when writing to a file. In the `"w"` mode, data can be written over existing bytes in the file. In the `"a"` mode, the file content is preserved, and writing can only be done at the end of the file.

Care must be taken when a file is opened for both reading and writing, i.e., when the `+` character is used in the string specifying the opening mode. Between reading and writing operations, the file position indicator must definitely be repositioned (e.g., with the `fseek` function) or the file's buffer area must be flushed. This topic will be addressed in detail later.

Whether a file can be opened can be checked with the following small program:

When the program is executed from the command line as:

    canopen file.dat

the screen prints "file.dat can be opened" or "file.dat cannot be opened."

    #include <stdio.h>
    #include <stdlib.h>
    int main(int argc, char *argv[])
    {
        FILE *fp;
        if (argc != 2) {
            printf("usage: canopen filename\n");
            return 1;
        }
        // Try to open the file for reading
        if ((fp = fopen(argv[1], "r")) == NULL) { 
            printf("%s file cannot be opened\n", argv[1]);
            return 2;
        }
        printf("%s file can be opened\n", argv[1]);
        fclose(fp); // Close the file
        return 0;
    }

The symbolic constant **`FOPEN_MAX`** is defined in the `stdio.h` header file. The `FOPEN_MAX` symbolic constant is also the maximum number of files that can be opened simultaneously.

## The `fclose` Function

This standard function's declaration in the `stdio.h` header file is as follows:

    int fclose(FILE *stream);

This function closes an opened file. The function takes the `FILE *` address obtained from the `fopen` or `freopen` function as a parameter and closes the open file. If the return value of the function is $0$, it means the file was closed successfully. If the return value of the function is **`EOF`**, the file could not be closed.

**`EOF`** is a symbolic constant defined in the `stdio.h` header file, defined as $(-1)$ in most compilers:

    #define EOF (-1)

The success of the function should only be checked when in doubt. Under normal conditions, there is no reason for the file not to be closed.

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        FILE *f;
        if ((f = fopen("letter.txt", "w")) == NULL) {
            printf("letter.txt file cannot be created!\n");
            exit(EXIT_FAILURE);
        }
        fclose(f);
        printf("letter.txt file closed!\n");
        return 0;
    }

There is also a non-standard function named **`fcloseall`** that is present in most compilers:

    int fcloseall(void);

When this function is called, all open files are closed. The return value of the function is the number of files closed.

Now let's examine the standard C functions that read from an opened file or write to an opened file:

## The `fgetc` Function

    int fgetc(FILE *f);

Standard C functions that perform writing and reading advance the file position indicator by the number of offsets written and read. The `fgetc` function reads the byte at the location indicated by the file indicator and returns the integer value of this byte as the return value. If the function fails, i.e., the reading operation cannot be performed, it returns the value **`EOF`**, defined as a symbolic constant in the `stdio.h` file.

Assigning the return value of the `fgetc` function to a `char` type variable can lead to incorrect results; care must be taken in this regard, and the function's return value must be stored in an **`int` type variable**.

    char ch;
    ch = fgetc(fp);

Suppose the character read from the file is the ASCII character number 255 ($0\text{x}00\text{FF}$). When this number is assigned to a `char` type variable, its high-order byte is lost, and the value $0\text{x}\text{FF}$ is assigned to the variable $ch$. In this case, since the variable $ch$ is of type signed `char`, the meaning is that a negative integer is held inside the variable $ch$.

In a comparison statement like:

    if (ch == EOF)

automatic type conversion is performed so that the comparison operation inside the `if` parenthesis can be done, i.e., $ch$ is promoted to an integer (integral promotion). In this automatic type conversion, the variable $ch$, which will be converted to the signed `int` type, is padded with the $\text{FF}$ byte because it is negative. In this case, the equality comparison gives a correct result, i.e., it is interpreted that the end of the file has been reached (or reading could not be done for another reason). However, if $ch$ were of type `int`, the value assigned to the variable $ch$ would be $0\text{x}00\text{FF}$. In this case, when the comparison is made, the result would be that $ch$ is not equal to the value $\text{EOF}$ ($0\text{x}\text{FFFF}$).

The `fgetc` function can be used to read a file opened for reading character by character. The program below prints the content of a file whose name is received from the keyboard to the screen:

    #include <stdio.h>
    #include <stdlib.h>
    #define FILENAME_LEN 256
    int main()
    {
        FILE *f;
        char file_name[FILENAME_LEN];
        int ch;
        printf("Name of the file to be printed : ");
        gets(file_name);
        if ((f = fopen(file_name, "r")) == NULL) {
            printf("cannot open file...\n");
            exit(EXIT_FAILURE);
        }
        while ((ch = fgetc(f)) != EOF)
            putchar(ch);
        fclose(f);
        return 0;
    }

Examine the code above. First, the name of the file to be printed is received from the keyboard and placed into the array named `file_name`. The file whose name is received into the `file_name` array is opened for reading with the call made to the `fopen` function. The program is terminated if the `fopen` function fails.

With the loop statement:

    while ((ch = fgetc(f)) != EOF)
        putchar(ch);

a character is read from the file until the `fgetc` function returns the $\text{EOF}$ value, and the image of the read character is printed to the screen with the standard `putchar` function. When the reading operation is complete, the file is closed with the standard `fclose` function.

Now examine the following program to be run from the command line. The function is executed from the command line as:

    <count> <file name> <character>

The program prints the count of the character given as the third command line argument in the file whose name is given, to the screen. First examine the program, then compile and run it:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define FILENAME_LEN 256
    int main(int argc, char **argv)
    {
        FILE *f;
        char file_name[FILENAME_LEN];
        int ch, cval;
        int char_counter = 0;
        
        if (argc != 3) {
            printf("File name : ");
            gets(file_name);
            printf("character to be counted : ");
            cval = getchar();
        }
        else {
            strcpy(file_name, argv[1]);
            cval = *argv[2]; // Use the first character of the string argument
        }
        
        if ((f = fopen(file_name, "r")) == NULL) {
            printf("%s file cannot be opened!\n", file_name);
            exit(EXIT_FAILURE);
        }
        
        while ((ch = fgetc(f)) != EOF)
            if (ch == cval)
                char_counter++;
                
        fclose(f);
        // Corrected output (ch is EOF after loop, use cval)
        printf("%s file has %d occurrences of character %c!\n", file_name, char_counter, cval); 
        return 0;
    }

Finally, let us add this. `fgetc` is a function. However, a macro named **`getc`** is also defined in the `stdio.h` header file. Most compilers also define a function with the same name as the `getc` macro. However, `fgetc` is a function, not a macro. The topic of macros will be addressed in later sections.

## The `fputc` Function

    int fputc(int ch, FILE *p);

This function writes 1 byte of information to the location indicated by the file position indicator. The first parameter of the function is the character to be written, and the second parameter is the `FILE *` address related to the file to be written to. If the return value of the function is **`EOF`**, it means the writing operation failed. If the writing operation was successful, the function returns the sequence number of the character written.

A frequent mistake is confusing the order of the arguments to be sent to the function. For example, let $f$ be a pointer pointing to an object of type `FILE *`. If the `fputc` function is mistakenly called in the form:

    fputc(f, 'A'); // Incorrect order

instead of:

    fputc('A', f);

the address $f$ is converted to the `int` type, and the integer value 'A' is converted to a `FILE *` type address. In this case, the writing operation undoubtedly fails.

Below you see the code of a program that makes a copy of a file using the `fgetc` and `fputc` functions. The program is executed from the command line as:

    <copy> <source file name> <target file name>

The execution of the program creates a copy of the file whose name is given by the second command line argument, with the name given by the third command line argument. Carefully examine the program:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define MAX_FILE_NAME_LEN 256
    int main(int argc, char **argv)
    {
        FILE *fsource, *fdest;
        char source_name[MAX_FILE_NAME_LEN];
        char dest_name[MAX_FILE_NAME_LEN];
        int ch;
        int byte_counter = 0;
        
        if (argc != 3) {
            printf("name of the file to be copied : ");
            gets(source_name);
            printf("name of the copy file : ");
            gets (dest_name);
        }
        else {
            strcpy(source_name, argv[1]);
            strcpy(dest_name, argv[2]);
        }
        
        if ((fsource = fopen(source_name, "r")) == NULL) { // Open source for reading
            printf("%s file cannot be opened\n", source_name);
            exit(EXIT_FAILURE);
        }
        printf("%s file opened!\n", source_name);
        
        if ((fdest = fopen(dest_name, "w")) == NULL) { // Open destination for writing
            printf("%s file cannot be created\n", dest_name);
            fclose(fsource); // Close source file before exiting
            exit(EXIT_FAILURE);
        }
        printf("%s file created!\n", dest_name);
        
        // Copy loop (byte by byte)
        while ((ch = fgetc(fsource)) != EOF) {
            fputc(ch, fdest);
            byte_counter++;
        }
        
        fclose(fsource);
        printf("%s file closed!\n", source_name);
        fclose(fdest);
        printf("%s file closed!\n", dest_name);
        printf("copy of %s file with name %s and length %d successfully created!\n",
               source_name, dest_name, byte_counter);
        return 0;
    }

`fputc` is a function. However, a macro named **`putc`** is also defined in the `stdio.h` header file. Most compilers also define a function with the same name as the `putc` macro. However, `fputc` is a function, not a macro.

## The `fprintf` Function

    int fprintf(FILE *stream, const char *format, …);

This function is just like the `printf` function. However, its first parameter specifies which file the writing operation will be performed on. Its other parameters are the same as in the `printf` function. While the `printf` function writes to the screen, the `fprintf` function writes to the file specified in the first parameter variable.

Examine the following example:

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        FILE *f;
        int i, ch;
        if ((f = fopen("data.txt", "w")) == NULL) { // Open for writing
            printf("cannot open file...\n");
            exit(EXIT_FAILURE);
        }
        printf("data.txt file created!\n");
        for (i = 0; i < 10; ++i)
            fprintf(f, "number = %d\n", i); // Write formatted data to file
        fclose(f);
        printf("data.txt file closed!\n");
        
        if ((f = fopen("data.txt", "r")) == NULL) { // Open for reading
            printf("cannot open file...\n");
            exit(EXIT_FAILURE);
        }
        printf("data.txt file opened for reading!\n");
        while ((ch = fgetc(f)) != EOF) // Read back and print content
            putchar(ch);
        fclose(f);
        return 0;
    }

## The `fscanf` Function

This is a function that reads from a file. It is very similar to the `scanf` function. Just as the `fprintf` function performs the writing operation on the file specified by its first parameter instead of writing to the screen, the **`fscanf`** function reads from a specified file instead of reading from the keyboard. The `fscanf` function, unlike the `scanf` function, takes a `FILE *` address as its first parameter variable. The declaration of the function is as follows:

    int fscanf(FILE *stream, const char *format, …);

The return value of the function is the number of values read from the file and written to the memory locations. If no assignment is made to any memory location, the function returns $0$. If the end of the file is reached before the first assignment can be made, or if an error occurs, the function returns the value **`EOF`**. The format specifiers to be used in the string passed as the second parameter are the same as in the `scanf` function.

Carefully examine the following program:

... (The provided code is a lengthy application involving file creation, reading, and processing student grades, which is summarized here based on the instructions).

The code demonstrates:

1.  Creating a file (`notlar.txt`) with random name, surname, and grade data using `fprintf`.
2.  Reading this file line by line using **`fscanf`** to extract the name, surname, and grade into corresponding variables.
3.  Based on the `grade` (compared to `PASS_GRADE`), writing the record to either a "gecen.txt" (passed) or "kalan.txt" (failed) file, also using `fprintf`.
4.  Using `fcloseall` to close all opened files at the end.

Let's address an important detail related to the format specifiers used in the `fscanf` function: It is not mandatory that every read from the file be converted and written to a memory location. If a character group separated by whitespace characters is desired to be removed from the file buffer without being assigned to a memory location, the **`*` character** is used after the `%` character in the format specifier group. For example, suppose the following line is located at the position indicated by the file position indicator in a text file:

    1376 ---------- 4567

Suppose only the values 1376 and 4567 need to be transferred to the variables $x$ and $y$ as a result of the reading operation. A call like the following can be made for this:

    fscanf(f, "%d%*s%d", &x, &y); // %*s skips the next string (the '--------' part)

## The `fgets` Function

    char *fgets(char *buf, int n, FILE *f);

This function reads one line of information starting from the location indicated by the file position indicator. The function reads until it reads the `\n` character, writes it to the address given in its first parameter, and then terminates its operation.

The first parameter of the function is the address of the location in memory where the information to be read will be placed. The second parameter is the maximum number of characters to be read. The `fgets` function reads at most $n - 1$ characters. It appends the null terminator to the end of the read characters and terminates its operation. If the number of characters on the line is less than $n - 1$, it reads the entire line and terminates its operation. For example, suppose this parameter is entered as 10. Let there be 20 characters on the line. The function reads 9 characters and places them into the array, appending the null terminator to the end. However, if there were 5 characters on the line, including `\n`, the function would read all 5 characters, append the null terminator to the end, and terminate its operation. Passing the size of a `char` array or a dynamically obtained block as the second parameter of the function directly prevents overflow errors. This is because the `fgets` function writes at most one character less than the array size to the array and writes the value of the null terminator to the last element of the array.

The return value of the function is the same address specified by the first parameter if at least 1 character was read; it is the **`NULL` address** if no characters were read.

The entire file can be read by continuously calling the `fgets` function within a loop.

Examine the following program that prints the content of a file line by line using the `fgets` function:

    #include <stdio.h>
    #include <stdlib.h>
    #define MAX_FILE_NAME_LEN 256
    #define BUFFER_SIZE 100
    int main()
    {
        FILE *f;
        char file_name[MAX_FILE_NAME_LEN];
        char buf[BUFFER_SIZE];
        printf("File name : ");
        gets(file_name);
        if ((f = fopen(file_name, "r")) == NULL) {
            printf("cannot open the file %s\n", file_name);
            exit(EXIT_FAILURE);
        }
        while (fgets(buf, BUFFER_SIZE, f) != NULL)
            printf("%s", buf);
        fclose(f);
        return 0;
    }

With the loop:

    while (fgets(buf, BUFFER_SIZE, f) != NULL)
        printf("%s", buf);

reading is done line by line from the file indicated by $f$, and the read characters are written to the `buf` array. If no character remains to be read from the file, the `fgets` function returns the **`NULL` address**.

## The `fputs` Function

The declaration of the function is as follows:

    int fputs(const char *str, FILE *stream);

The function writes the string at the address passed to its first parameter to the file associated with the `FILE *` type address passed to its second parameter. The null terminator at the end of the string is **not** written to the file by the function. If the function fails in the writing operation, it returns the value **`EOF`**. In case of success, the function's return value is a non-negative integer.

The following program copies a text file using the `fputs` and `fgets` functions:

    #include <stdio.h>
    #include <stdlib.h>
    #define FILE_NAME_LEN 256
    #define BUFFER_SIZE 100
    int main()
    {
        char source_file_name[FILE_NAME_LEN];
        char dest_file_name[FILE_NAME_LEN];
        char buffer [BUFFER_SIZE];
        FILE *fs, *fd;
        
        printf("source file name: ");
        gets(source_file_name);
        printf("copy file name: ");
        gets(dest_file_name);
        
        fs = fopen(source_file_name, "r");
        if (fs == NULL) {
            printf("%s file cannot be opened!\n", source_file_name);
            exit(EXIT_FAILURE);
        }
        
        fd = fopen(dest_file_name, "w");
        if (fd == NULL) {
            printf("%s file cannot be created!\n", dest_file_name);
            fclose(fs); // Close source file before exiting
            exit(EXIT_FAILURE);
        }
        
        while (fgets(buffer, BUFFER_SIZE, fs)) // Read line by line
            fputs(buffer, fd); // Write line by line
            
        printf("copy completed successfully!\n");
        fclose(fs);
        fclose(fd);
        return 0;
    }

## Text Files and Binary Files

A file can be opened in **text mode** or **binary mode**. The default opening mode is text mode. That is, if the mode in which the file is opened is not explicitly specified, it is assumed that the file is opened in text mode. To open the file in binary mode, the character **`b`** must be added to the opening mode string. Valid strings that can be sent to the `fopen` function to open a file in binary mode are given below:

`"rb"`, `"r+b"`, `"rb+"`, `"w+b"`, `"wb+"`, `"a+b"`, `"ab+"`

In some operating systems, such as DOS and WINDOWS, there are some important differences between opening a file in text mode and binary mode:

In the DOS operating system, if a character is to appear at the beginning of the next line when a file is printed, the **CR (carriage return)** and **LF (line feed)** characters must be present before that character. The CR character is denoted by `\r` in C (ASCII character number 13). The LF character is denoted by `\n` in C (ASCII character number 10).

For example, let the file content be in the form `a\r\nb`. On UNIX-based systems, only the LF character is used to move to the beginning of the next line. The file equivalent of the image `a b` on the screen in the UNIX operating system is in the form `a\nb`.

In the DOS operating system, the LF character means move down one line, and the CR character means move to the beginning of the current line. For example, if the content of a file in the DOS operating system is in the form `a\nb`, the image `a b` is obtained when the file is printed. If the content of the file is in the form `a\rb`, the image `b` is obtained when the file is printed.

The `\n` character in the `printf` function is used to move to the beginning of the next line on the screen. Actually, when `\n` is placed inside the string that is the first parameter of the `printf` function, this transition is achieved with only `\n` in UNIX, and with `\r` and `\n` in the DOS operating system.

To work easily with text files, files are divided into text and binary. When a file is opened in **text mode**, if the `\n` character is desired to be written to the file, the file functions automatically write the **`\r` and `\n`** characters to the file. Similarly, if the file is opened in text mode and the file indicator points to the `\r\n` pair, only the `\n` character is read from the file. Another difference between text and binary files in the DOS operating system is the assumption that **CTRL Z (ASCII character number 26) terminates the file**. However, when the file is opened in binary mode, no such assumption is made.

In the UNIX operating system, there is **no difference** between text mode and binary mode. That is, there is no problem with opening a file in text mode instead of binary mode in the UNIX operating system. However, opening a non-text file in text mode instead of binary mode under DOS can have drawbacks. For example, suppose an exe file is opened in text mode instead of binary mode under DOS. When ASCII characters number 10 and number 13 are located next to each other in this file, only 1 byte is read from the file. Similarly, when the ASCII character number 26 is read from the file, no more reading can be done from the file. It is assumed that the end of the file has been reached.

## EOF State

There is no special character at the end of the file. The operating system can tell whether the end of the file has been reached by looking at the file's length. The **EOF (end of file) state** is the situation where the file position indicator points to the last character that is not in the file. In the EOF state, the offset value of the file position indicator is the same as the file length. If reading is attempted from the file in the EOF state, the functions that read from the file fail. However, if the opening mode is appropriate, writing can be done to the file, and appending is performed in this case.

As mentioned before, information related to a file opened in the C language is held inside an object of type `FILE`. The members of this structure provide information about the file's properties. The C programmer does not deal directly with the values of the members of this structure, as the return value of the `fopen` function is a pointer of type `FILE *` pointing to this structure object, and C language functions that operate on files mostly access information related to the desired file by taking this address as a parameter.

One of the members of the `FILE` structure in question is the **EOF flag**, which is used as a flag. In most compilers, it is actually only a specific bit of an `int` type flag. Some C language functions that operate on files change the value of the EOF flag. That is, they set or clear the EOF flag. Functions that perform reading check the value of this flag before reading. If the EOF flag is set, reading is unsuccessful. The EOF flag must be cleared again for a successful reading operation to be performed. Functions that open a file clear the EOF flag in the `FILE` structure. In addition to these functions, functions that change the value of the file position indicator (`fseek`, `rewind`, `fsetpos`) and the `clearerr` function also clear the EOF bit.

## Formatted and Unformatted Writing

Suppose integer values are to be written to a file. What does it mean to write an `int` type value to a file? For example, on a system where the `int` type is 4 bytes long, let the integer value to be written to the file be $1234567890$. This value is desired to be written to a file and then read back from that file.

This operation can be done with the `fprintf` function, right? Let $f$ be a pointer to a file opened for writing.

    fprintf(f, "%d", 1234567890);

With the call above, 10 bytes are added to the file, starting from the location indicated by the file position indicator. The bytes written to the file are the sequence numbers of the digits that represent the place values of the number $1234567890$. Assuming ASCII character encoding is used on the system, the following bytes are written to the file:

$$\text{49 50 51 42 53 54 55 56 57 59 48 (ASCII for "1234567890")}$$

However, a value like $1234567890$ is expressed in a 4-byte area on a 32-bit system, right? For example, the memory image of the number $1234567890$ is as follows:

$$\text{0100 1001 1001 0110 0000 0010 1101 0010}$$

Can't these 4 bytes be written to the file just as they are in RAM? Writing in this way to the file is **unformatted writing**. Two important standard C functions transfer a specific number of bytes from RAM to the file and from the file to RAM in an unformatted manner. We will examine these functions now:

## The `fread` and `fwrite` Functions

These two functions are among the most frequently used functions in C. They generally perform **transfer** between the file and RAM. The declaration of both functions is the same:

    size_t fread(void *adr, size_t block_size, size_t n_blocks, FILE *stream);
    size_t fwrite(const void *adr, size_t block_size, size_t n_blocks, FILE *stream);

Recall that the type `size_t` is the `typedef` new name for the `unsigned int` or `unsigned long` type in almost all systems.

The `fread` function copies the product of the values copied to its second and third parameters of bytes, starting from the location indicated by the file position indicator, to the memory location starting from the address indicated by its first parameter. Generally, the second parameter of the function is provided as the length of a data structure element, and the third parameter is provided as the number of elements. The return value of the function is the number of elements read from the file or written to the file from memory.

With these functions, arrays and structure objects can be transferred to a file with a single call. For example, a 10-element `int` array can be written to a file with a single call as follows:

    int a[5] = {3, 4, 5, 7, 8};
    fwrite (a, sizeof(int), 5, f);

In the example above, since the array name $a$ is address information of type `int *`, it can be sent as the 1st argument to the `fwrite` function. A total of $\text{sizeof}(\text{int}) \times 5$ bytes are written from the address $a$ in memory to the file associated with the `FILE *` pointer $f$.

The following code snippet transfers a structure object from memory to a file:

    typedef struct {
        char name[20];
        char fname[20];
        int no;
    } Person;
    int main()
    {
        FILE *f;
        Person per = {"Necati", "Ergin", 325};
        f = fopen("person.dat", "wb"); // Open in binary mode
        /*********************************/
        fwrite(&per, sizeof(Person), 1, f); // Write the structure object unformatted
        /****/
        // fclose(f) should be called here
        return 0;
    }

The `fwrite` function writes the numbers to the file with their memory image. That is, it does not write formatted like the `fprintf` function. For example, in the DOS operating system:

    int i = 1535;
    fwrite(&i, sizeof(int), 1, f);

Here, if the file is printed, random characters appear for 2 bytes. This is because the `int` type is 2 bytes long in the DOS operating system. What we see are the random bytes of the number 1525. The `fprintf` function can be used to write the information to the file with their ASCII equivalents.

Since the `fread` and `fwrite` functions transfer information that is in memory, it is appropriate for the files to also be opened in **binary mode**.

    #include <stdio.h>
    #include <stdlib.h>
    int main()
    {
        FILE *f;
        int i;
        int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int b[10];
        
        if ((f = fopen("data", "w+b")) == NULL) { // Open binary for read/write
            printf("cannot open file...\n");
            exit(EXIT_FAILURE);
        }
        
        fwrite (a, sizeof(int), 10, f); // Write array a
        fseek(f, 0, SEEK_SET); // Reset file position to the beginning
        fread(b, sizeof(int), 10, f); // Read into array b
        
        for (i = 0; i < 10; ++i)
            printf("%d\n", b[i]);
            
        fclose(f);
        return 0;
    }

The return values of the `fread` and `fwrite` functions are the number of elements read or written, as specified by the third parameter. For example:

    n = fread(a, sizeof(int), 10, f);

With the call, $\text{sizeof}(\text{int}) \times 10$ bytes are desired to be read from the file indicated by $f$ and written to the address $a$ in RAM. That is, if all the numbers from the position indicated by the file position indicator can be read, the function returns the value 10. If the number of remaining bytes in the file is less than the number desired to be read, the function reads all the bytes, and the return value is the number of read elements multiplied by the value specified by the 2nd parameter. For example, let's assume we are working under the DOS operating system. Let 10 bytes of information remain in the file. The function returns the value 5 with:

    n = fread(a, sizeof(int), 10, f); // Reads 5 integers (5 * 2 bytes = 10 bytes)

Examine the following two calls:

    fread(str, 100, 1, f); // Reads 1 block of 100 bytes
    fread(str, 1, 100, f); // Reads 100 blocks of 1 byte

Both function calls can be used to read 100 bytes from the file associated with the `FILE *` pointer $f$ to the address $str$ in RAM. However, while the return value could be either 0 or 1 in the first call, the return value could be any value in the range [0, 100] in the second function call.

## The `fseek`, `ftell`, and `rewind` Functions

The file position indicator can be positioned with standard C functions:

### The `fseek` Function

    int fseek(FILE *f, long offset, int origin);

This function is called to position the file position indicator to a desired offset value. With the call to this function, it becomes possible to read from a desired location or write to a desired location of an opened file.

* The third parameter specifies the point from which the positioning will be made. One of the symbolic constants **`SEEK_SET`**, **`SEEK_CUR`**, or **`SEEK_END`** declared in `stdio.h` must be passed to this parameter.

If the value **`SEEK_SET`** is passed to the last parameter, positioning is done from the beginning of the file. In this case, the second parameter must be $\ge 0$. For example:

    fseek(f, 10L, SEEK_SET); // Positions the file indicator to the 10th offset.

If the value **`SEEK_CUR`** is passed to the third parameter variable of the function, positioning is done relative to the file indicator's current position. In this case, the second parameter can have a positive or negative value. A positive value means forward, and a negative value means backward. For example, let the file indicator point to the 10th byte.

    fseek(f, -1, SEEK_CUR); // Positions the file indicator to the 9th offset.

If the value **`SEEK_END`** is passed to the third parameter variable of the function, positioning is done from the EOF state, i.e., from the end of the file. In this case, the value passed to the second parameter must be $\le 0$. For example, to position the file indicator to the end of the file:

    fseek(f, 0L, SEEK_END); // Positions to the end of the file.

The function's return value provides information about the success of the operation. If the return value is $0$, the operation was successful; if it is a non-zero value, the operation failed. Checking the return value is only recommended in problematic situations.

The file indicator must be positioned with a positioning function between writing and reading operations. Alternatively, the file buffer area must be flushed with a call to the `fflush` function. If necessary, positioning can be done to the current location with an empty `fseek` call: `fseek(f, 0L, SEEK_CUR)`.

For example, let a character be read from the file, and the next character be written as the read character plus 1:

    ch = fgetc(f);
    fputc(ch + 1, f);

The operation above is erroneous. The situation exhibits **undefined behavior** related to runtime. The file indicator must be positioned when transitioning from writing to reading, or from reading to writing. The only exception to this situation is when the end of the file is reached with the last reading operation. In this case, it is guaranteed that writing can be done at the end of the file without repositioning.

### The `rewind` Function

This function positions the file position indicator to the **beginning** of the file. The declaration of the function is as follows:

    void rewind(FILE *fp);

The call `rewind(f);` is synonymous with the call `(void) fseek(f, 0L, SEEK_SET);`.

### The `ftell` Function

This function is called to obtain the value of the file position indicator. The declaration of the function is as follows:

    long ftell(FILE *stream);

The return value of the function is the value of the file position indicator. This value is given as the byte count from the beginning of the file. In case of an error, the function returns the value $-1\text{L}$. The length of a binary file can be obtained with calls to the `fseek` and `ftell` functions:

    fseek(f, 0, SEEK_END);
    length = ftell(f);

## File Position Functions (`fgetpos`, `fsetpos`)

These functions are used in conjunction with each other to obtain the value of the file position indicator or to change its value. With these functions, a point in the file can be marked, and later the file position indicator can be positioned to the same point for reading or writing. The value of the file position indicator is obtained with the **`fgetpos`** function, and the **`fsetpos`** function is used to return to this position later.

    int fgetpos(FILE *stream, fpos_t *pos);

The function obtains the value of the file position indicator of the file associated with the address passed to its first parameter and writes it to the address passed to its second parameter. The type `fpos_t` is a standard `typedef` type declared in the `stdio.h` header file. This type is used only in the `fgetpos` and `fsetpos` functions.

    int fsetpos(FILE *stream, const fpos_t *pos);

The function positions the file position indicator of the file associated with the address passed to its first parameter to the value read from the address passed to its second parameter. The address of an object carrying a value obtained from the `fgetpos` function must be passed to the second parameter of the function.

The `fgetpos`/`fsetpos` functions should be preferred over the `fseek` function, especially when large files are in question. This is because the second parameter of the `fseek` function is of type `long`, while the `fpos_t` type used in the `fgetpos`/`fsetpos` functions can be an internally defined structure type large enough to hold the position information of very large files.

## Other Standard Functions Operating on Files

### The `remove` Function

This function deletes a file. The declaration of the function is:

    int remove (const char *filename);

The name of the file to be deleted is sent as an argument to the function. The return value of the function is $0$ if the file can be successfully deleted; otherwise, i.e., if the file could not be deleted, it is a non-zero value. Since the ability to delete an open file is system-dependent, for the portability of the written code, a file to be deleted should be closed first if it is open.

### The `rename` Function

This function is used to change the name of a file. The declaration of the function is:

    int rename (const char *old, const char *new);

The old name of the file must be sent as the first argument to the function, and the new name of the file must be sent as the second argument. The return value of the function is $0$ if the renaming operation is successful; otherwise, i.e., if the file name could not be changed, it is a non-zero value. In most systems, the function fails and returns a non-zero value if an attempt is made to change the name of an open file.

### The `tmpfile` Function

The function is used to open a temporary file. The declaration of the function is:

    FILE *tmpfile(void);

The `tmpfile` function opens the temporary file it creates in **`"wb"` mode**. The opened file is automatically deleted when it is closed with the `fclose` function or when the program terminates if the file is not closed. The return value of the function is an address of type `FILE *` that is used to establish a connection with the opened temporary file. If the temporary file cannot be opened for any reason, the function returns the **`NULL` address**.

The symbolic constant **`TMP_MAX`** defined in the `stdio.h` header file indicates the maximum number of temporary files that can be created with the `tmpfile` function. The number of temporary files opened simultaneously in a written source code should not be greater than the value of `TMP_MAX`.

### The `tmpnam` Function

This function is used to generate a name for a file that will be used temporarily. The declaration of the function in the `stdio.h` header file is:

    char *tmpnam(char *s);

The function writes the file name it generates to the `char *` address sent to it. The function also writes the same file name into a static duration array and returns the starting address of this array. If the **`NULL` address** is sent as an argument to the function, the function only returns the address of the static duration array. What should be the size of the array of type `char` when its address is sent as an argument to the function? That is, how many characters long is the file name that the `tmpnam` function generates? This value is specified by the symbolic constant **`L_tmpnam`** defined in the `stdio.h` file.

It is guaranteed that the file name generated by the `tmpnam` function is a file name that has not been used before in the current directory. That is, the generated file name is unique in the current directory. Suppose a file is to be opened for later deletion in a program, and after some information is written to this file, the file will be deleted or given another name. In this case, since the relevant file will be opened in writing mode, the name of an existing file should not be given to this file. If the name of an existing file is given, the existing file will be zeroed out (truncated), and the file will be lost. To avoid this risk, the file to be used temporarily should be opened using the `tmpfile` function. However, if the `tmpfile` function is used, the opened file cannot be made permanent. That is, if the temporary file is desired not to be deleted for any reason, or if the file is desired to be made permanent, the file must be opened with the `fopen` function. In this case, the temporary file must be opened with the name generated by the `tmpnam` function to avoid risking another file.

So, what is the maximum number of reliable file names that can be generated with the `tmpnam` function? This value is determined by the symbolic constant **`TMP_MAX`** defined in `stdio.h`.

## Streams

In the C language, some input and output units (like the keyboard and screen) are treated directly as a file. Any input/output unit is named a **stream**. A stream can be a file, or it can be an input/output unit treated as a file. For example, small programs generally receive their input from a single stream (e.g., the keyboard) and convey their output to a single stream (e.g., the screen).

### The `stdout`, `stdin`, and `stderr` Streams

Inputs made to a program are accepted as coming from a **byte stream (input stream)** flowing towards the program. Similarly, the output of a program is considered as bytes flowing outwards from the program (**output stream**). Functions that perform reading and writing related to files can read directly from the input stream and write to the output stream.

It is accepted that 3 streams are automatically opened when a C program starts running. These streams can be used as files and are associated with predefined values of type `FILE *`:

* **`stdin`**: Represents the standard input unit. This stream is normally connected to the keyboard.
* **`stdout`**: Represents the standard output stream. This stream is normally connected to the screen.
* **`stderr`**: Represents the standard error stream. This stream is also normally connected to the screen.

The functions we previously learned as input functions from the keyboard (`getchar`, `gets`, `scanf`) are actually functions that read from the `stdin` stream. The functions we previously learned as output functions to the screen (`putchar`, `puts`, `printf`) are actually functions that write to the `stdout` stream.

Functions that read from files can be passed `stdin`, and functions that write to files can be passed `stdout` and `stderr` as `FILE *` type values. For example:

    fprintf(stdout, "Necati Ergin"); // Prints "Necati Ergin" to the screen.

Similarly:

    fputc('A', stdout); // Prints the character 'A' to the screen.

    fscanf(stdin, "%d", &val); // Assigns the value read from the keyboard to the variable 'val'.

### Redirecting Streams

Most operating systems allow input and output streams to be redirected to other files. For example, suppose a program named `primenumwriter` prints prime numbers in the range $1 - 1000$ to the screen when executed. Let the `printf` function be called for the printing operation in the program's source code. When this program is executed from the command line in DOS/WINDOWS operating systems as:

    primenumwriter

its output is written to the screen.

If the `primenumwriter` program is executed from the command line as:

    primenumwriter > primes.txt

everything that the `primenumwriter` program sends to the `stdout` stream, i.e., the screen, is written to the `primes.txt` file. The `>` symbol used here is called the **"redirection"** symbol.

Similarly, the `<` redirection symbol is used for the `stdin` stream. For example, if a program named `process` is executed in the form:

    process < numbers.txt

all information that would normally be read from the keyboard is read from the `numbers.txt` file.

Both redirection symbols can be used together:

    process < numbers.txt > prime.txt

When the `process` function is executed as above, it reads its input from the `numbers.txt` file and writes its output to the `prime.txt` file.

In addition to these, there is another redirection symbol in the UNIX operating system in the form `|`. In an operation like:

    x | y

where $x$ and $y$ are two programs, these two programs are executed simultaneously. Everything that program $x$ writes to the screen is treated as if it were input from the keyboard in program $y$. This redirection operation is called a **pipe**.

The `stderr` file is also normally redirected to the screen. That is, if a writing operation is performed to the `stderr` file with the standard `fprintf` function, the written information still appears on the screen. However, if the `stdout` stream is redirected to another file, the `stderr` stream is unaffected by the redirection operation and remains connected to the screen. That is, even if redirection is performed from the command line:

    fprintf(stderr, "error!\n");

a call like this results in the word "Error" being written to the screen, not to the file. Error messages should be written to the `stderr` stream with the `fprintf` function instead of being printed to the screen with the `printf` function.

### Calling the `fgets` Function with the `stdin` Value:

You know that the `fgets` function requires a value of type `FILE *` as its third parameter:

    fgets(char *str, int n, FILE *f);

When the `stdin` value is passed to this parameter of the function, the line to be placed into the array is read from the keyboard. Such a call should be preferred over a call to the `gets` function because the risk of a pointer error is eliminated.

In the call to the `gets` function above:

    char str[20];
    gets(str);

entering 20 or more characters from the keyboard causes a pointer error. However, when the call is made in the form:

    fgets(str, 20, stdin);

at most 19 characters are written to the array. That is, there is no risk of a pointer error occurring. The only point to note here is the possibility that the `\n` character is also written to the array by the `fgets` function. Examine the following code:

    #include <stdio.h>
    #include <string.h>
    int main()
    {
        char str[20];
        printf("enter a name : ");
        fgets(str, 20, stdin);
        if (!strcmp(str, "NECATI"))
            printf("equal\n");
        else
            printf("not equal\n");
        return 0;
    }

When the program above is executed and the name "NECATI" is entered from the keyboard, the screen prints "not equal." This is because the `fgets` function also places the entered newline character into the array after the "NECATI" input is made. That is, the `strcmp` function actually compares the strings "N E C A T I \n" and "N E C A T I \n".

A statement like the following could have been used before the comparison operation:

    if ((ptr = strchr(str, '\n')) != NULL)
        *ptr = '\0';

In the statement above, the `\n` character is searched for in the string at the address $str$ with the `strchr` function. If the `\n` character is found in the string, the null terminator is written in its place. That is, if the `\n` character is present at the end of the string, it is deleted from the string.

## The `freopen` Function

This function redirects a previously opened file to the file it opens. The declaration of the function is:

    FILE *freopen(const char *filename, const char *mode, FILE *stream);

It is mostly used in applications for redirecting standard files (`stdin`, `stdout`, `stderr`) to other files. For example, if the output of a program is desired to be written to the file named `data.dat`:

    if (freopen("data.dat", "w", stdout) == NULL) {
        printf("data.dat file cannot be opened\n");
        exit(EXIT_FAILURE);
    }

With the function call above, the file to which the `stdout` file was redirected is closed, and the `stdout` file is redirected to the `data.dat` file. This redirection operation might have been done from the command line, or it might have been performed with a previous call to the `freopen` function.

The return value of the `freopen` function is the `FILE *` type pointer that is the third argument sent to the function. `freopen` returns the **`NULL` address** if the file to which the redirection will be made cannot be opened. If the old file to which the redirection was made cannot be closed, the `freopen` function does not provide an indication in this case.

## The `feof` Function

If reading is performed from a file when the file position indicator points to the end of the file, the reading operation is unsuccessful. In this case, an internally held flag is set. Functions that perform reading check the value of this flag first. If the flag is set, they do not perform reading. The **`feof`** function retrieves the value of this flag:

    int feof(FILE *stream);

If reading was performed from the file when the file position indicator pointed to the end of the file, the function returns a non-zero value. Otherwise, the function returns $0$.

A typical mistake made with the `feof` function is thinking that the function checks whether the file position indicator points to the end of the file:

    if (feof(f))
        /******/

A check like this cannot be performed with the statement above. This is because the `feof` function returns $0$ if the file position indicator points to the end of the file but no reading attempt has been made from this location yet.

The following C code, which tries to print the content of a text file to the screen, is erroneous. Try to find out why it is erroneous:

    #include <stdio.h>
    #include <stdlib.h>
    #define FILE_NAME_LEN 256
    #define BUFFER_SIZE 20
    int main()
    {
        char source_file_name[FILE_NAME_LEN];
        char buffer [BUFFER_SIZE];
        FILE *fs;
        printf("file name to be printed: ");
        gets(source_file_name);
        fs = fopen(source_file_name, "r");
        if (fs == NULL) {
            printf("%s file cannot be opened!\n", source_file_name);
            exit(EXIT_FAILURE);
        }
        // Error: feof checks after an *unsuccessful* read. This loop structure 
        // will perform the read one last time after EOF is reached, and print 
        // the content of the buffer twice (the last good read + the content of 
        // the buffer after the failed read).
        while (!feof(fs)) { 
            fgets(buffer, BUFFER_SIZE, fs);
            printf("%s", buffer);
        }
        fclose(fs);
        return 0;
    }

## The `ferror` Function

Functions that perform reading or writing set an internally held flag (often in a bit field) when an error occurs during the reading or writing operation. Functions that perform reading or writing check the value of this flag first. If the flag is set, a new reading or writing operation cannot be performed. The flags must be cleared again first. The **`ferror`** function checks whether the error flag has been set:

    int ferror(FILE *stream);

If the error flag is set, the function returns a non-zero value. If the error flag is not set, the function returns $0$.

## The `clearerr` Function

    void clearerr(FILE *stream);

We said that the error flag is set when an error occurs during the reading or writing operation, and the EOF flag is set when an attempt is made to read from the end of the file. A reading or writing operation cannot be performed while these flags are set. The **`clearerr`** function can be called to clear the flags. The function receives the `FILE *` value related to the file and clears the EOF and Error flags of this file.

## The `ungetc` Function

This function puts the character read from the file **back** into the file's buffer area.

    int ungetc(int c, FILE *f);

The file must be opened in reading mode for the `ungetc` function. The value $c$ is read in the first reading operation performed after the function is called. If the function is successful, it returns the value $c$. In case of failure, no change occurs in the file's buffer area, and the $\text{EOF}$ value is returned. The function also clears the $\text{EOF}$ flag after placing the character back into the buffer area. The `ungetc` function should not be called consecutively without the file position indicator being repositioned.

## File Buffering Functions

Operations performed with secondary memory (floppy disk, hard disk, etc.) are very slow compared to operations performed in memory. Therefore, directly accessing the file every time a character is read from a file or a character is written to a file is not an efficient method. The efficiency of the operation is increased through **buffering**. Data to be written to a file is first stored in a buffer area in memory. When this buffer area is full, or when the file to be written to is closed, whatever data is in the buffer is written to the file. This is called **flushing** the buffer area. Input files can also be buffered similarly. Bytes received from an input device, such as the keyboard, are first written to the buffer. Buffering files causes a very large increase in efficiency. This is because reading a character from the buffer, i.e., from memory, or writing a character to the buffer is done in a negligible amount of time. The transfer between the buffer and the file undoubtedly still takes time, but a single block transfer takes much less time than the total of many small transfers.

Functions that operate on files and are declared in the `stdio.h` header file perform buffering automatically. That is, this task is done in the background without the programmer being aware of it; the programmer does not need to do anything for the files to be buffered. However, in some situations, the programmer may want to be in control of the buffering. In these situations, the programmer uses the file buffering functions (`fflush`, `setbuf`, `setvbuf`):

### The `fflush` Function

Input/output operations on files are mostly done through buffering. When a function that performs a writing operation to a file is called, the function writes the data to a buffer area in memory if buffering is enabled. The data in the buffer is written to the file when the file is closed or when the buffering area is full. With a call to the **`fflush`** function, the data in the buffer area is written to the file without waiting for the file to be closed or the buffering area to be full. This operation can be done as frequently as desired.

    int fflush (FILE *stream);

The buffer of the file associated with the `FILE *` pointer $fp$ is flushed with the call `fflush(fp);`. If the **`NULL` address** is sent to the `fflush` function, the buffers of all open files are flushed.

If the flushing operation is successful, the `fflush` function returns $0$; otherwise, it returns the value **`EOF`**.

### The `setvbuf` Function

The `setvbuf` function is used to change the buffering method of a file and to change the location and size of the buffer area. The declaration of the function is as follows:

    int setvbuf(FILE *stream, char *buf, int mode, size_t size);

The third argument sent to the function specifies the buffering method. The value of the third argument is determined by the symbolic constants defined in the `stdio.h` header file.

* **`_IOFBF` (full buffering)**: Data is written to the file when the buffering area is full. Or, if input buffering is in question, reading is performed from the file when the buffering area is empty.
* **`_IOLBF` (line buffering)**: Reading or writing between the buffering area and the file is done line by line.
* **`_IONBF` (no buffering)**: Reading from or writing to the file is performed directly without buffering.

The second argument sent to the `setvbuf` function is the starting address of the block in RAM where the buffering will be performed. The area where the buffering will be performed can have static or dynamic storage duration, or it can be obtained with dynamic memory functions.

The last argument sent to the function is the number of bytes to be held in the buffering area. The `setvbuf` function must be called after the file is opened but before any operation is performed on the file. If the function is successful, it returns $0$. If the third argument sent to the function is invalid, or if the function cannot perform the relevant buffering, the return value is a non-zero value. The file must not be closed before the validity of the buffer area sent to the function ends, i.e., before its lifespan is complete.