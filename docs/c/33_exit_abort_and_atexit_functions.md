# 🛑 The `exit`, `abort`, and `atexit` Functions

The execution of a C program begins at the `main` function and ends at the end of the `main` function, or when this function produces a return value. If the program is desired to be terminated during the execution of another function, the standard **`exit`** or **`abort`** functions can be called.

---

## 🚪 The `exit` Function

This standard function is declared in the `stdlib.h` header file:

    void exit(int status);

The function performs the following cleanup operations before terminating the running program:

i) It calls the functions previously registered with the `atexit` function in **reverse order** of registration.
ii) It **flushes** the buffer areas of all files opened for writing. It closes all open files.
iii) It deletes files opened with the `tmpfile` function.
iv) It returns control to the system where the program was run, with information communicating the **success status**.

* If the value sent to the function is $0$ or the symbolic constant **`EXIT_SUCCESS`**, the function communicates to the system that the program terminated due to success.
* If the argument sent to the function is $1$ or the symbolic constant **`EXIT_FAILURE`**, the function communicates to the system that the program terminated due to failure.

---

## 💥 The `abort` Function

This standard function is declared in the `stdlib.h` header file:

    void abort(void);

The function is called to terminate a C program in an **abnormal** manner. When a C program is terminated with a call to the `abort` function, functions previously registered with the `atexit` function are **not** called. Whether some cleanup operations are performed before the program terminates with an `abort` call is left to the compiler's choice.

This function is also called inside the standard `assert` macro.

---

## 🔔 The `atexit` Function

The declaration of this standard function is also in the `stdlib.h` header file:

    int atexit (void (*func)(void));

The `atexit` function is used to **register a function** that is desired to be called when the program terminates or when the `exit` function is called. The registered functions are **not** called when the program is terminated through abnormal means, such as `abort` or `raise`.

At least 32 functions can be registered with the `atexit` function.

The parameter of the function is the address of the function to be registered. The function's return value communicates the success status of the operation. A return value of $0$ indicates success, and a non-zero value indicates failure.

There is no way to unregister a registered function.

Registered functions are called in the **reverse order** of their registration. A function can be registered more than once. In this case, it is executed more than once.