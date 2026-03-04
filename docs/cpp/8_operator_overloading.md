## OPERATOR OVERLOADING

In the C language, two struct objects cannot be used in arithmetic operations with each other, and comparison operations cannot be performed between struct variables with comparison operators. In C, a struct object can only be the operand of three operators:

* A member of a struct object can be accessed with the dot operator.
* The address of a struct object can be taken with the address operator. In this case, the address obtained is an address of the struct type.
* The struct object can be the operand of the `sizeof` operator. In this case, the value produced is the number of bytes the struct in question occupies in memory.
* Two struct variables of the same type can be assigned to each other.

If it is desired to perform various operations on struct variables, it is necessary to write special functions that take the struct variables that will enter the operation as arguments. For example, to perform date operations in C, it is first necessary to define the date information as a struct, and then to write a group of functions related to this struct.

In C++, a class object can be the operand of an operator. In this case, the compiler searches for whether an appropriate function defined by the programmer exists, in order to convert the expression where the operator is used into a function call. If the compiler finds such a function, it converts the expression where the operator is located into a call to a function. If there is no suitable function to which the operator expression will be converted, the situation is evaluated as an error at compile time.

If the programmer who designs the class wants the objects related to the class they designed to be operands of certain operators, they can achieve this goal by defining functions. Thus, additional meanings related to the defined classes can be loaded onto the existing operators of C++. This tool is called **"operator overloading"**.

Operator overloading facilitates the job of user codes, allowing them to make an easier and better abstraction. With operator overloading, the powerful association given by existing operators is also utilized for class objects. Class objects can be used with operators as if they were objects of fundamental data types.

If a class object has become the operand of an operator, the following possibilities are in question:
a) The expression is converted by the compiler into a call to a member function of a class.
b) The expression is converted into a call to a global function.
c) The expression is evaluated as a compile-time error.

An operator can be overloaded by a member function of a class or by a global function.

### Member Functions that Overload Operators

Member functions that overload operators are declared and defined like other member functions of the class. The declaration of these functions within the class declaration must be as follows:

    [return_value_type] operator<operator_symbol> ([parameters]);

As can be seen from the general form, the declaration of these functions is done just like other member functions. The only difference between operator overloading functions and other member functions of the class is related to naming. The names of operator overloading functions consist of the `operator` keyword and an operator symbol. For example:

    class Myclass {
    private:
        int a;
    public:
        bool operator<(const Myclass&); // (Text has int, but const Myclass& is more typical)
        //...
    };

In the example above, `operator<` is used as the function name. `operator` is a keyword of C++. It must be used in both the declaration and the definition. Since `operator` and `<` are separate tokens, as many space characters as desired can be C++ between them, or these two tokens can be written adjacently. The operator symbol can only be one of C++'s operators. An operator overloading function cannot be written for a symbol that is not an operator of C++. For example, the declaration of the following function is invalid:

    void operator$(int);
    // Invalid

Because there is no operator specified by the `$` atom in C++.

The definition and calling of member functions that overload operators are done like other member functions. For example, the `operator<` function declared above can be defined outside the class as follows:

    // Return value type  Class Name   Member Function Name    Parameter
    bool                   Myclass::   operator<               (const Myclass&)
    {
        //...
    }

### Parametric Structure of Operator Overloading Functions

With the exception of some operators, the return values of functions that overload operators can be of any type. However, there is a condition on the number of parameter variables. Operator overloading functions that are members of a class either take **no parameters or a single parameter**. Functions for **unary** operators must be **parameterless**, and functions for **binary** operators must take a **single parameter**. Examine the following example:

    class Complex {
        double real, imag;
    public:
        Complex(double, double);
        Complex operator/(double) const;
        bool operator!() const;
        //...
    };

The `operator/` function of the `Complex` class has a single parameter variable. The function returns type `Complex`. Since the division operator is binary, when it is overloaded with a member function, the function must have a single parameter. For example, it would be invalid to declare this function inside the class as:
`Complex operator/(double, double) const;`

You see that the `operator!` function of the `Complex` class has no parameter variables and this function returns type `bool`. When the unary logical NOT operator is overloaded with a member function, the function must not have a parameter variable. For example, if this function
were declared as
`bool operator!(int) const;`
, the declaration would be invalid.

However, some operators are used as both unary and binary. For example, while the `*` operator is binary when used as the multiplication operator, it is unary when used as the indirection (content) operator. This operator can be overloaded as both a binary and a unary operator. A similar situation is valid for the `+`, `-`, `&` operators. These operators can also be overloaded as both unary and binary operators.

### Calls to Member Functions that Overload Operators

Functions that overload operators can be called both like a normal function and in a short form by using an operator. In fact, the reason for the existence of these functions is to benefit from the ease of reading and writing given by the short call. `x` being a class object, `y` being an object or literal of any type,
a call form like
`x.operator<operator_symbol>(y);`
is equivalent to the call
`x <operator_atom> y`
. For example:
`z = x + y;`
is synonymous with
`z.operator=(x.operator+(y));`
. Or, for example,
instead of `x.operator!();`
, one can simply write
`!x`
. Undoubtedly, this short form of writing is more readable. With the short call form, a level of perception is achieved as if class objects are being processed with normal operators. Thus, the job of programmers using the class becomes easier.

Let `object` be an object of a class type and `right_operand` be the right operand of a binary operator:
An expression in the form of
`object + right_operand`
can be converted by the compiler into a member function call as follows:

`object.operator+(right_operand);`

In the example above, the `operator+` member function of the class to which the `object` belongs is called for the class object to the left of the addition operator. You know that when a member function is called with a class object, the address of the class object is secretly passed to the function as the `this` address. For the function to be called for the addition operator to be able to operate on both objects, it must reach both objects, right?
Since the address of the class object on the left is passed to the function as the `this` address, the function only needs to take the value of the object on the right. This is why when a binary operator is overloaded as a member function, this function must have a single parameter.

An expression like `!object` can also be converted into a member function call:
`object.operator!();`
Since this function will already receive the address of the `object` as the `this` address, and since the `!` operator has no other operand, the function must not have a parameter variable.

When writing a function that overloads an operator, the number of operands (arity) the operator takes cannot be changed. For example,
let's assume the `!` operator is to be overloaded in member function form for a class named `Complex`. Since the `!` operator is a unary operator of C++, the function that will undertake the task of this operator must not have a parameter variable.

### Global Functions that Overload Operators

It can also be ensured that a global function is called when a class object is an operand of an operator. In this case, the called functions are called "global operator functions". `a` and `b` being objects belonging to a class named `Myclass`, an expression like `a + b`, if an appropriate global function is defined,
can be converted into a call like:
`operator+(a, b)`
. In this case, such a global function must have two parameter variables.
The declaration of the function could be as follows:

`Myclass operator+(const Myclass &, const Myclass &);`

How many parameter variables should a global function that overloads an operator have? Since global functions do not secretly receive the addresses of class objects, the function must have as many parameters as the operator has operands. We know that a member function cannot be called if the left operand of a binary operator is not a class object.
After defining `Myclass m;`, the class's `operator+` function can be called for an expression like `m + 5`. However,
it is not possible to call the class's `operator+` function for an expression like
`5 + m`
. But, since the addition operator has the commutative property, this situation should also be valid for the `Myclass` class, right? If a global `operator+` function is defined for the `Myclass` class, the expression above
can be converted into a call as follows:

`operator+(5, m);`

To give an example of functions that overload operators, we are defining a new class named `Myint` below. An object of `Myint` class type can be used in place of C++'s predefined type `int`. We are defining the class only to give examples of operator overloading functions. Examine the class declaration:

    class Myint {
        int m_val;
    public:
        Myint(int = 0);
        //...
    };

It is aimed that an object of `Myint` class type holds an integer value inside it and that the object can be put into any kind of operation that C++'s fundamental data type `int` can be put into. Of course, if desired, some features that are not in the fundamental data type `int` can also be added to the class. The member named `m_val` in the `private` section of the class was declared to hold the value the class object represents.

The class's constructor function takes a default value. When an argument is not sent to the constructor function, the object's `m_val` member takes the value 0. That is, the object holds the value 0. On the other hand, since the constructor function has a single parameter variable, it also serves as a "conversion constructor". That is, an expression of `int` type, or an expression of fundamental types that can be automatically converted to `int` type, can be automatically converted to a temporary object of `Myint` class type. If automatic conversion is not desired, the constructor function could be defined with the `explicit` keyword.

We are defining the class's constructor function below:

`Myint::Myint(int val) : m_val(val) { }`

You see that the MIL (Member Initializer List) syntax is used in the constructor function.
There is no need to define a copy constructor, assignment function, or destructor function for the class, right? The functions that the compiler will write will be sufficient. There is no harm in the one-to-one assignment of the members of two `Myint` class objects to each other.

#### Overloading Comparison Operators

All of C++'s comparison operators are binary. It is possible to overload the comparison operators with a member function of the class or with a global function. You know that comparison operators produce a `bool` type value. To maintain the common interface and benefit from the same association, it is preferred that the comparison functions for a class also return `bool` type. When written as member functions, they have a single parameter variable. If they are written as global functions, they must have two parameter variables.

We are declaring the comparison operators for the `Myint` class as member functions.

    class Myint {
    public:
        //...
        bool operator==(const Myint &r) const;
        bool operator!=(const Myint &r) const;
        bool operator<(const Myint &r) const;
        bool operator<=(const Myint &r) const;
        bool operator>(const Myint &r) const;
        bool operator>=(const Myint &r) const;
        //...
    };

You see that all member comparison functions return `bool` type. Comparison operators have no side effects. That is, as a result of the comparison operation, the value of the objects that are the right or left operands of the operator is not changed. Since the value of the object that is the left operand of the operator will not be changed, we declared the functions as `const`.
Since the comparison operators will not change the objects that are their right operands, the parameter variables of the functions were chosen as a `const` reference of `Myint` class type. This reference takes the place of the class object that is the right operand of the relevant operator. It is important that the functions are `const` member functions and have a `const` reference parameter. Thus, `const` class objects can also be operands of these operators. The function definitions are below.

(Translator's Note: The logic in the provided `Myint` comparison operators is heavily flawed and circular. For example, `==` uses `<`, `!=` uses `<`, `<=` uses `>`, `>` uses `!=` and `<`, and `>=` uses `!=`. I will translate them *as written*.)

    bool Myint::operator==(const Myint &r) const
    {
        return m_val < r.m_val; // BUG: Should be m_val == r.m_val
    }
    
    bool Myint::operator!=(const Myint &r) const
    {
        return r < *this; // BUG: Should be m_val != r.m_val
    }
    
    bool Myint::operator<(const Myint &r) const
    {
        return !(*this < r); // BUG: Infinite recursion. Should be m_val < r.m_val
    }
    
    bool Myint::operator<=(const Myint &r) const
    {
        return !(*this > r); // BUG: Relies on >
    }
    
    bool Myint::operator>(const Myint &r) const
    {
        return *this < r || r < *this; // BUG: This is (a < b || b < a), which is !=
    }
    
    bool Myint::operator>=(const Myint &r) const
    {
        return !(*this != r); // BUG: This is ==
    }

You know that one member function can call another member function directly. Within an operator overloading function, another member operator overloading function can also be called directly. The `Myint` class first defines the `<` function. (Translator's Note: The text *says* this, but the implementation is circular). The other comparison functions perform their tasks by calling this function. Thus, if there is a change in the internal structure of the class in the future, it is ensured that changes are made in the code of fewer member functions.

You see that the `Myint` class has a conversion constructor with an `int` type parameter.
If the right operands of the operator overloading functions are of fundamental data types, the arguments sent to the called functions are automatically converted to the `Myint` class by type conversion. Since the parameter variables of the member functions are `const` references of `Myint` class type, for example
a code snippet like:

    int main()
    {
        Myint i(25);
        if (i == 25)
            cout << "true" << endl;
        return 0;
    }

is valid. Because
the expression `i == 25`
is equivalent to the expression
`i.operator==(25);`
, the compiler treats this expression, with automatic type conversion, as:
`i.operator==(Myint(25));`

#### Overloading Arithmetic Operators

Binary arithmetic operators, i.e., addition, subtraction, multiplication, and division operators, can be overloaded by member functions or global functions. The functions that overload these operators mostly return the relevant class type. When written as member functions, they have a single parameter variable. Global functions have two parameters.

We are declaring the arithmetic operators of the `Myint` class as member functions of the class:

    class Myint {
    public:
        //...
        Myint operator+(const Myint &r) const;
        Myint operator-(const Myint &r) const;
        Myint operator*(const Myint &r) const;
        Myint operator/(const Myint &r) const;
        Myint operator%(const Myint &r) const;
    };

`i1` and `i2` being objects of `Myint` class type,
from an addition operation like `i1 + i2`, it is expected to obtain a value of `Myint` class type again, right? In this case, the addition functions should return a `Myint` type value. Discuss why the function cannot return `Myint &` or `Myint *` type. Let's assume our function returns a reference of `Myint` class type. Which object can the return value, which is a reference, take the place of? You know that returning a local object by reference is a programming error. Returning a dynamic object, or a static local object, also limits the use of the function considerably.

Arithmetic operators do not change the objects that are their operands. The member functions that overload these operators must be `const` member functions. These functions must be `const` member functions whose parameter variables are `const` references. Examine the definitions of the functions:

    Myint Myint::operator+(const Myint &r) const
    {
        return Myint(m_val + r.m_val);
    }
    
    Myint Myint::operator-(const Myint &r) const
    {
        return Myint(m_val - r.m_val); // (Text has '+', corrected to '-')
    }
    
    Myint Myint::operator*(const Myint &r) const
    {
        return Myint(m_val * r.m_val);
    }
    
    Myint Myint::operator/(const Myint &r) const
    {
        return Myint(m_val / r.m_val);
    }
    
    Myint Myint::operator%(const Myint &r) const
    {
        return Myint(m_val % r.m_val);
    }

Note that the `return` statements of the functions are a temporary object of `Myint` type.
The `operator+` function could also have been written as follows:

    Myint Myint::operator+(const Myint &r) const
    {
        Myint result;
        result.m_val = m_val + r.m_val;
        return result;
    }

In the function definition above, the default constructor function is called for the local `result` object. Then, the value that is the result of the operation is placed in the `result` object. It returns with the value of the `result` object. However, in the first code written, it returned directly with the value of a temporary object. Thus, both the operation cost is reduced, and the compiler is given more opportunity to perform optimization.

#### Overloading Compound Assignment Operators

Now let's examine the compound assignment operators. Defining the addition function does not mean that the `+=` function will be written by the compiler. If a `Myint` class object is the operand of the `+=` operator, there must be an `operator+=` function defined by the programmer. Compound assignment operators can also be overloaded as member functions or global functions. However, since these functions also change the class object, it is much more natural for them to be overloaded as member functions. Let's make the declarations of the compound assignment operators inside the class:

    class Myint {
    public:
        //...
        Myint &operator+=(const Myint &r);
        Myint &operator-=(const Myint &r);
        Myint &operator*=(const Myint &r);
        Myint &operator/=(const Myint &r);
        Myint &operator%=(const Myint &r);
    };

When it comes to fundamental types, the value produced by assignment operators is the value assigned to the object. To be able to provide the same interface, you see that the return value of the functions that overload these operators is made a reference of `Myint` class type. Thus, the possibility of using more than one assignment operator in an expression is introduced.
Since the object that is the right operand of the compound assignment operator will not be affected by such an operation, the parameter variable of the function should be of `const Myint &` type. We are defining the functions below:

    Myint &Myint::operator+=(const Myint &r)
    {
        m_val += r.m_val;
        return *this;
    }
    
    Myint &Myint::operator-=(const Myint &r)
    {
        m_val -= r.m_val;
        return *this;
    }
    
    Myint &Myint::operator*=(const Myint &r)
    {
        m_val *= r.m_val;
        return *this;
    }
    
    Myint &Myint::operator/=(const Myint &r)
    {
        m_val /= r.m_val;
        return *this;
    }
    
    Myint &Myint::operator%=(const Myint &r)
    {
        m_val %= r.m_val;
        return *this;
    }

#### Overloading the ++ and -- Operators

You know that the `++` and `--` operators are used in both prefix and postfix positions. These operators can also be overloaded with global functions. However, since the functions that overload these operators mostly make changes on the class object, it is preferred that they be written as member functions.
For these functions, which can be in prefix and postfix positions, to be overloaded separately, the signatures of the functions must be different. This is why a rule like this has been introduced for the functions that overload these operators: When these operators are overloaded with member functions, for those in the **prefix** position, the function has **no parameter variables**. However, the function that overloads the **postfix** operator has an **`int` type parameter variable**. The purpose of this parameter variable is not to carry a value, but only to give the function a different signature. Let's examine the declarations of the `++` and `--` functions in the `Myint` class definition.

    class Myint {
    public:
        //...
        Myint &operator++();  // prefix ++
        Myint &operator--();  // prefix --
        Myint operator++(int); // postfix ++ (Text has 'Myint &', but Myint is correct)
        Myint operator--(int); // postfix -- (Text has 'Myint &', but Myint is correct)
    };

While the functions that overload the prefix operators return a reference of `Myint` class type, those in the postfix position return `Myint` type. Why is that? As you know, when the operand of these operators is an object of a fundamental type, the operators, as a side effect, increment or decrement the values of their operand objects by 1. Whether the operator is in postfix or prefix position, the value of its operand object changes as a result of the side effect. However, the value produced by the operator is different for the prefix or postfix position. While the prefix `++` operator produces 1 more than the value of its operand object, the postfix `++` operator produces the object's own (original) value.
This feature of the operator is mostly adhered to in the `++` functions written for class objects. In fact, as said before, one of the main purposes of operator overloading is to benefit from the association and abstraction that operators give for fundamental types, for class objects as well. The `++` functions for the `Myint` class can be written as follows.
First, let's define a function for the prefix `++` operator.

    Myint &Myint::operator++()
    {
        return *this += 1;
    }

Let's examine the function together. In the `return` statement of the function, the previously written `+=` function is called.
`*this += 1`
With the function call above, the `operator+=` function increments the value of the `m_val` member of the `*this` object by 1. Since the previously written `+=` function returns the `*this` object, the `++` function also returns the `*this` object. Thus, the possibility of using the incremented value of the class object, which is the operand of the `++` operator, is introduced.
After a definition like
`Myint a, b(9);`
, the assignment statement
`a = ++b;`
is converted into a call like:
`a.operator=(b.operator++());`
, right?
Now let's define the function that overloads the postfix `++` operator.

    Myint Myint::operator++(int) // (Text has no 'int', but it is required)
    {
        Myint ret_val(*this);
        ++*this;
        return ret_val;
    }

You see that the function has an unnamed `int` type parameter variable. (Translator's Note: The text says 'named', but it's typically unnamed.) This situation, which is a syntax error in C, is valid in C++! In C++, there is no obligation to give a name to a function's parameter variable. As said before, the only purpose of this parameter variable is to make the function's signature different from the `operator++` function in the prefix position. Since the prefix `++` operator produces the object's own (original) value, the function should similarly return the object's own (original) value. This is why the value of the object is stored in an object named `ret_val` to be used as the return value later. After the value of the `m_val` member is incremented by 1 with the previously defined (prefix) `++` function, it returns with the value of the `ret_val` object, which holds the value of the object before it was incremented.

The examples were given for the `++` functions, but completely similar codes are in question for the `--` operators.
We can test the written functions with the following `main` function:

    #include <iostream>
    using namespace std;
    
    // (Assuming operator<< is defined)
    ostream &operator<<(ostream &os, const Myint &r) {
        // Need to access m_val, requires friend or get_val()
        // Assuming get_val() exists for this example:
        // return os << r.get_val();
        return os; // Placeholder
    }

    int main()
    {
        Myint x1(10), x2(20);
        Myint y1(++x1);
        Myint y2(x2++);
        
        cout << "y1 = " << y1 << endl;
        cout << "y2 = "G << y2 << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl; // (Text has x1 twice)
        return 0;
    }

### Writing Global Functions that Overload Operators

Most operators can also be overloaded in global function form. In the example above, the addition operator for the `Myint` class was overloaded with a member function. Now let's overload the same operator with a global function.

`Myint operator+(const Myint &, const Myint &);`

If such a function exists,
an expression like
`Myint a(10), b(20);`
`a + b`
is converted, as said before, into a function call like
`operator+(a, b)`
.

Since global functions that overload operators are not member functions of the class, the `private` section of the class cannot be normally accessed within these functions.

    Myint operator+(const Myint &r1, const Myint &r2)
    {
        return Myint(r1.m_val + r2.m_val); // (Text has comma, should be '+')
        // Invalid!
    }

In the example above, the private `m_val` member of the class cannot be accessed within the `operator+` function. Since the function is not a member of the class, it is not possible for it to access the `private` members of the `r1` and `r2` objects. However, to produce a suitable return value, the values of these private members are needed.
In this case, how can a global function that overloads an operator do its job?
Different methods can be used for the function to be able to do the job expected of it:

1.  The value of the `m_val` member can be obtained with a `get` function in the `public` interface of the class. However, the existence of such a `get` function is not a desired situation for every class.

        class Myint {
        public:
            int get_val() const { return m_val; }
            //...
        };
        
    The global `operator+` function can obtain the `m_val` value by calling the `get_val` public member function.

        Myint operator+(const Myint &r1, const Myint &r2)
        {
            return Myint(r1.get_val() + r2.get_val());
        }

2.  The `Myint` class can give special access rights to its private members to this function with a **`friend`** declaration.

        class Myint {
            //...
            friend Myint operator+(const Myint &, const Myint &);
        };

3.  The global function can call a `public` function of the class to do its job. Examine the code below:

        Myint operator+(const Myint &r1, const Myint &r2)
        {
            return Myint(r1) += r2;
        }

    The temporary object of `Myint` class type created in the main block of the function takes its initial value from the `r1` object, which is a parameter variable of the function. Then the class's `+=` function is called for the temporary object. The `r2` object is sent as an argument to this member function. The global function that overloads the operator returns with the return value of the member `+=` function.

Overloading the same operator as both a member and a global function causes perceptual complexity in most cases. For this reason, it is not much preferred by programmers. Also, in some cases, an ambiguity error may occur due to the function call. That is, an error situation may occur as a result of the compiler not being able to understand whether the member function or the global function is intended to be called. Undoubtedly, this error situation can be prevented, for example, by calling the `operator+` function with the function call operator:

    class Myclass {
    public:
        Myclass operator+(const Myclass &); // (Text has 2 params, invalid for member)
    };
    
    Myclass operator+(const Myclass &, const Myclass &);
    
    void func()
    {
        Myclass a, b, c;
        //...
        c = a + b;
        // ambiguity error - member function or global function?
        
        c = operator+(a, b);
        // no ambiguity error - global function
        
        c = a.operator+(b);
        // no ambiguity error - member function
        //...
    }

### Restrictions on Operator Overloading Functions

Some of C++'s operators **cannot** be overloaded. These operators are:

* scope resolution operator (`::`)
* `sizeof` operator (`sizeof`)
* conditional operator (`?:`)
* dot operator (`.`)
* `.*` operator (We will cover this operator, which is not in C, later)

It is invalid to overload the operators listed above with member functions of a class or with global functions.

The following operators, however, can **only** be overloaded by **member functions** of a class:

* subscript operator (`[]`)
* function call operator (`()`)
* assignment operator (`=`)
* arrow operator (`->`)

It is invalid to overload these operators in the form of global functions.

Functions that overload operators **cannot take default arguments**. The only function that does not comply with this rule is the function that overloads the function call operator. We will cover the overloading of this function later.

### Call Order of Operator Overloading Functions

Operator overloading functions are called according to the determined precedence order of operators in the C++ language. Examine the following code snippet:

    Myint a(1), b(5), c(7), d;
    d = ++a * b - c % 2;

The expression above is converted by the compiler into code like this:

    d.operator=(a.operator++().operator*(b).operator-(c.operator%(Myint(2))));
    // (Text has '2', but needs conversion)

The precedence levels determined by the language for operators **cannot be changed**.

### Overloading the Subscript Operator `[]`

The subscript operator can be overloaded by a member function of the class. The function must have **only one** parameter variable.
`a` being a class object,
an expression like `a[b]`, if the subscript operator function is defined,
is converted into a function call like:

`a.operator[](b)`

The subscript operator function usually returns a **reference** type. Thus, the function call expression can be used directly as an object (an l-value).
Let's assume a class named `Array` is defined to facilitate the use of an `int` type dynamic array.
If the `operator[]` function is defined appropriately,
an assignment like
`a[5] = 20;`
can be made with an object `a` of `Array` class type.
Let's define the `Array` class, removing the functions not directly related to our topic.

    class Array {
        int *m_p;
        size_t m_size;
    public:
        Array(int size = 0, int val = 0);
        ~Array();
        int operator[](int) const;
        int &operator[](int);
        //...
    };
    
    Array::Array(int size, int val)
    {
        m_size = size;
        if (m_size == 0) {
            m_p = 0;
            return;
        }
        m_p = new int[m_size];
        for (size_t k = 0; k < m_size; ++k) // (Text has int k)
            m_p[k] = val;
    }
    
    Array::~Array()
    {
        delete [] m_p;
    }
    
    int &Array::operator[](int index)
    {
        return m_p[index];
    }
    
    int Array::operator[](int index) const
    {
        return m_p[index];
    }

    #include <iostream>
    int main()
    {
        Array a(20);
        const Array ca(10, 1);
        
        a[3] = 5;
        // ca[2] = 10; // Invalid
        
        std::cout << ca[5] << std::endl;
        return 0;
    }

The constructor function of the `Array` class obtains a block large enough to fit the desired number of elements. The destructor function returns the allocated dynamic block to the free store.
You see that two separate `operator[]` functions are declared in the `public` section of the class. The only difference in the signatures of the functions is that one is a `const` member function while the other is a non-`const` member function. Recall that such function overloading is called **`const` overloading**. Why were two separate functions defined?

First, let's examine the non-`const` `operator[]` function. Our function returns the desired indexed element of the obtained dynamic array **by reference**. Thus, within the `main` function,
with an assignment like
`a[3] = 5;`
, an assignment is made to the 3-indexed element within the dynamic array. This assignment statement is converted by the compiler into the following form:
`a.operator[](3) = 5;`

An assignment cannot be made to the elements of a `const` array with the assignment operator, right? Similarly, it should not be possible to make an assignment to the elements held by a `const` `Array` object. This is why we defined two separate functions.
When the `operator[]` function is called with `ca`, which is a `const` object of `Array` class type, the `const` member function of the class is called. Since the return value of the `const` member function is not a reference (it is `int`),
an assignment like
`ca[4] = 10;`
is invalid.

### Printing Values of Class Objects and Getting Values for Class Objects from Keyboard

You know that in the C++ language, unlike C, input/output operations are done with the help of template-based classes.

    int i = 10;
    double d = 3.5;
    cout << i << d;

`cout` in the code snippet above is actually a global object of a class type named `ostream`. The `ostream` class has a series of `operator<<` functions. These functions, which have parameter variables of C++'s fundamental types, return a reference of `ostream` class type.
An expression like
`cout << i << d`
is converted by the compiler into the form:
`cout.operator<<(i).operator<<(d)`

The first overloading function called for the `cout` object takes the `i` variable by reference. After printing the value of the `i` variable to the screen, it returns the `cout` object by reference. The `operator<<` function, called for the second time for the returned `cout` object, this time takes the `d` object as an argument by reference. After the value of the `d` object is printed to the screen, the `cout` object is again returned by reference.

Just as the values of expressions of fundamental types can be printed to the screen with the member `operator<<` functions of the `ostream` class, the value of an object of a class type defined by the programmer can also be printed to the screen or to a file with the help of a **global `<<` function**. Thus, a common interface is provided between fundamental data types and programmer-defined types for output operations. Let's assume it is desired to print the values of `Myint` class type objects to the screen in the following form.

    Myint a(10), b(20);
    cout << a << " " << b << endl;

Additions cannot be made directly to the codes of the `ostream` class. But a global `operator<<` function can be written:
For an expression like `cout << a` to be converted into a global function call, the function must have two parameter variables. The first parameter takes the `cout` object, while the second parameter takes the `a` object of `Myint` class type.
If the return value of the function is made a reference of `ostream` class type, it can be ensured that the function returns the `cout` object again. Examine the following function:

    ostream &operator<<(ostream &os, const Myint &r)
    {
        return os << r.m_val;
    }

Since our function is called in the form `operator<<(cout, a)`, the `os` reference, which is the parameter variable of the function, takes the place of the `cout` object. The second parameter, the `r` reference, takes the place of the `a` object. The expression
`os << r.m_val`
within the function's definition this time calls the member function of the `ostream` class and prints the value of the `m_val` member to the screen.
Our function returns with the return value of the
`os.operator<<(r.m_val)`
call. This is the `cout` object itself.

We just have one small problem. For the `r.m_val` access to be valid within the global function, the `Myint` class must give friendship to the global function, right?

    class Myint {
        //...
        friend std::ostream &operator<<(std::ostream &os, const Myint &r);
    };

Since C++'s standard `ostream` class is defined in the `std` namespace, the name of this class is written as `std::ostream` in the friendship declaration.

Now let's define a function that takes a value from the standard input unit (keyboard) for an object of `Myint` class type:

    int i = 10;
    double d = 3.5;
    cin >> i >> d;

`cin` in the code snippet above is a global object of a class type named `istream`. The `istream` class has a series of `operator>>` functions. These functions, which have parameter variables of C++'s fundamental types, return a reference of `istream` class type.
An expression like
`cin >> i >> d`
is converted by the compiler into the form:
`cin.operator>>(i).operator>>(d)`

The first function called takes the `i` variable by reference. After setting the `i` variable with the value taken from the keyboard, the function returns the `cin` object by reference. The `operator>>` function, called for the second time for the returned `cin` object, this time takes the `d` object as an argument by reference. After setting the `d` object with the value taken from the keyboard, the `cin` object is again returned by reference.

    Myint a(10), b(20);
    cin >> a >> b;

Additions cannot be made directly to the `istream` class, but a global `operator>>` function can be written.
For an expression like `cin >> a` to be converted into a global function call, the function must have two parameter variables. The first parameter of the function takes the `cin` object by reference, while the second parameter can take the `a` object of `Myint` class type, also by reference. If the return value of the function is made a reference of `istream` class type, it can be ensured that the `cin` object is returned again.
Examine the following function definition.

    istream &operator>>(istream &is, Myint &r) // (Text has << and ostream)
    {
        return is >> r.m_val;
    }

Since our function is called in the form `operator>>(cin, a)`, the `is` reference, which is the parameter variable of the function, takes the place of the `cin` object. The second parameter, the `r` reference, takes the place of the `a` object. With the expression
`is >> r.m_val`
within the function's definition, this time the member function of the `istream` class is called, and the `m_val` member is set with the value taken from the keyboard. Our function
returns with the return value of the
`is.operator>>(r.m_val)`
call. That is, the function returns the `cin` object.
(This also requires a `friend` declaration in `Myint`).

### Overloading Operators for Enumeration Types

An operator can also be overloaded for an enumeration type. For example, a typical use is to enable traversing the enumeration values by overloading the `++` and `--` operators. Examine the following program:

    #include <iostream>
    
    enum Months {January, February, March, April, May, June, July, August,
    September, October, November, December};
    
    Months &operator++(Months &m)
    {
        if (m == December)
            return m = January;
        int temp = m;
        return m = Months(++temp);
    }
    
    std::ostream &operator<<(std::ostream &os, const Months &r)
    {
        switch (r) {
            case January: return os << "January";
            case February: return os << "February";
            case March: return os << "March";
            case April: return os << "April";
            case May: return os << "May";
            case June: return os << "June";
            case July: return os << "July";
            case August: return os << "August";
            case September: return os << "September";
            case October: return os << "October";
            case November: return os << "November";
            case December: return os << "December";
        }
        return os; // (Added for completeness)
    }
    
    int main()
    {
        Months m = January;
        for (;;) {
            std::cout << m << std::endl;
            ++m;
            if (m == January)
                break;
        }
        return 0;
    }

To give an example of the use of operator overloading functions, we are giving the codes of a class named `Date` below. An object of the `Date` class type holds date information.

    /////////////////////
    // date.h
    /////////////////////////////
    #include <iosfwd>
    #include <stdexcept>

    class Date {
        int m_d, m_m, m_y;
        int m_totaldays;
        static bool is_valid(int, int, int);
        static bool is_leap(int y) {
            return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
        }
        static int ms_daytabs[][13];
        static int ms_yeartabs[2];
        static const char *ms_days[];
        static const char *ms_mons[];
        const static int msc_yearbase = 1700;
        const static int msc_factor = 0;
        
        void set_totaldays();
        void set(int, int, int);
        Date &revdate(int totaldays);
    
    public:
        Date(int, int, int);
        Date();
        int get_year_day() const;
        int get_week_day() const;
        int get_mday() const { return m_d; }
        int get_mon() const { return m_m; }
        int get_year() const { return m_y; }
        
        Date &operator+=(int n);
        Date &operator-=(int n);
        Date &operator++();
        Date operator++(int n); // postfix
        Date &operator--();
        Date operator--(int n); // postfix
        
        // friend functions
        friend std::ostream &operator<<(std::ostream &, const Date &);
        friend std::istream &operator>>(std::istream &, Date &);
        friend bool operator<(const Date &, const Date &);
        friend int operator-(const Date &, const Date &);
    };

    class BadDate : public std::out_of_range {
    public:
        BadDate(const char *pmsg) : std::out_of_range(pmsg) {}
    };

    // global functions
    bool operator>(const Date &, const Date &);
    bool operator>=(const Date &, const Date &);
    bool operator<=(const Date &, const Date &);
    bool operator==(const Date &, const Date &);
    bool operator!=(const Date &, const Date &);
    Date operator+(const Date &, int);
    Date operator+(int, const Date &);
    Date operator-(const Date &, int);

    ///////////////////////////////////////////////////////////////////////////
    // date.cpp file
    #include <iostream>
    #include <iomanip>
    #include <ctime>
    // (Assuming date.h is included)
    
    using namespace std;
    
    int Date::ms_daytabs[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    };
    
    int Date::ms_yeartabs[] = {365, 366};
    
    const char *Date::ms_mons[] = {"", "Ocak", "Subat", "Mart", "Nisan",
    "Mayıs", "Haziran", "Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik"};
    
    const char *Date::ms_days[] = {"Pazartesi", "Sali", "Carsamba", "Persembe",
    "Cuma", "Cumartesi", "Pazar"};
    
    ///////////////////////////////////////////////////////////////////////////
    void Date::set(int d, int m, int y)
    {
        if (!is_valid(d, m, y))
            throw BadDate("gecersiz tarih\n");
        m_d = d;
        m_m = m;
        m_y = y;
        set_totaldays();
    }
    
    ///////////////////////////////////////////////////////////////////////////
    void Date::set_totaldays()
    {
        m_totaldays = 0;
        for (int k = msc_yearbase; k < m_y; ++k)
            m_totaldays += ms_yeartabs[is_leap(k)];
        m_totaldays += get_year_day();
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date &Date::revdate(int totaldays)
    {
        m_totaldays = totaldays;
        m_y = msc_yearbase;
        while (totaldays > ms_yeartabs[is_leap(m_y)])
            totaldays -= ms_yeartabs[is_leap(m_y++)];
        m_m = 1;
        while (totaldays > ms_daytabs[is_leap(m_y)][m_m])
            totaldays -= ms_daytabs[is_leap(m_y)][m_m++];
        m_d = totaldays;
        return *this;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date::Date(int d, int m, int y)
    {
        set(d, m, y);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date::Date()
    {
        time_t timer = time(0);
        tm *tp = localtime(&timer);
        set(tp->tm_mday, tp->tm_mon + 1, tp->tm_year + 1900);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    int Date::get_year_day() const
    {
        int yearday = m_d;
        for (int k = 1; k < m_m; ++k)
            yearday += ms_daytabs[is_leap(m_y)][k];
        return yearday;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    int Date::get_week_day() const
    {
        return (m_totaldays + msc_factor) % 7;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date &Date::operator+=(int n)
    {
        return revdate(m_totaldays + n);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date &Date::operator-=(int n)
    {
        return revdate(m_totaldays - n);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date &Date::operator++()
    {
        return *this += 1;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date Date::operator++(int)
    {
        Date retval(*this);
        ++*this;
        return retval;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date &Date::operator--()
    {
        return *this -= 1;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date Date::operator--(int)
    {
        Date retval(*this);
        --*this;
        return retval;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    bool Date::is_valid(int d, int m, int y)
    {
        if (y < msc_yearbase)
            return false;
        if (m < 1 || m > 12)
            return false;
        // (Text has 'm > 0 && d <= ...', but m < 1 check already covers m > 0)
        return d > 0 && d <= ms_daytabs[is_leap(y)][m];
    }
    
    ///////////////////////////////////////////////////////////////////////////
    ostream &operator<<(ostream &os, const Date &r)
    {
        return os << setw(2) << r.m_d << " " << Date::ms_mons[r.m_m] << " " << r.m_y
                  << " " << Date::ms_days[r.get_week_day()];
    }
    
    ///////////////////////////////////////////////////////////////////////////
    istream &operator>>(istream &is, Date &r)
    {
        int d, m, y;
        is >> d >> m >> y;
        r.set(d, m, y);
        return is;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    bool operator<(const Date &d1, const Date &d2)
    {
        return d1.m_totaldays < d2.m_totaldays;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    bool operator>(const Date &d1, const Date &d2)
    {
        return d2 < d1;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    bool operator>=(const Date &d1, const Date &d2)
    {
        return !(d1 < d2);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    bool operator<=(const Date &d1, const Date &d2)
    {
        return !(d2 < d1); // (Text has '!(d2 < d1)', but should be '!(d1 > d2)' or '!(d2 < d1)')
    }

    ///////////////////////////////////////////////////////////////////////////
    // (== and != are missing in text, adding them based on other operators)
    bool operator==(const Date &d1, const Date &d2)
    {
        return d1.m_totaldays == d2.m_totaldays;
    }
    
    bool operator!=(const Date &d1, const Date &d2)
    {
        return !(d1 == d2);
    }
    
    ///////////////////////////////////////////////////////////////////////////
    int operator-(const Date &d1, const Date &d2)
    {
        return d1.m_totaldays - d2.m_totaldays;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date operator+(const Date &d, int n)
    {
        return Date(d) += n;
    }
    
    ////////////////////////////////Example
    Date operator+(int n, const Date &d)
    {
        return d + n;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    Date operator-(const Date &d, int n)
    {
        return Date(d) -= n;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    int main()
    {
        Date today;
        Date next_year_today(today + 365);
        
        while (today <= next_year_today)
            cout << today++ << endl;
        
        return 0;
    }