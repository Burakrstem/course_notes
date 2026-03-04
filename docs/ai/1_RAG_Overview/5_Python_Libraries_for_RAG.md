# Ungraded Lab 1: A Brief Python Refresher

Welcome to this ungraded lab on Python fundamentals! This lab is designed to get you comfortable with some basic concepts in Python that will be used throughout this course. By the end of this lab, you'll know how to work with strings, lists, list comprehensions, dictionaries, and prompt augmentation using f-strings. **This lab is designed for developers more familiar with other programming languages, or who would appreciate a quick Python refresher. If you're a confident Python programmer, feel free to skip this ungraded lab!**

### In this lab, you'll learn:
- How to manipulate and work with strings
- Constructing and utilizing lists and list comprehensions
- Understanding and using dictionaries for structuring prompts
- Implementing prompt augmentation using f-strings for dynamic text generation


# Table of Contents
- [ 1 - Lists](#1)
  - [ 1.1 Introduction](#1-1)
  - [ 1.2 List Comprehensions](#1-2)
- [ 2 - Dictionaries](#2)
  - [ 2.1 Introduction](#2-1)
  - [ 2.2 The method `.items`](#2-2)
- [ 3 - f-strings](#3)
  - [ 3.1 Introduction](#3-1)
  - [ 3.2 f-strings in Action](#3-2)

<a id='1'></a>
## 1 - Lists

<a id='1-1'></a>
### 1.1 Introduction

A list is a built-in data type in Python used to store collections of items. Lists are ordered, changeable, and allow duplicate values.

```python
# Example of a list
l1 = ['RAG', 'is', 'awesome']
print(f"Original list: {l1}")

# Adding an item
l1.append('!')
print(f"List after adding '!': {l1}")

# Removing an item
l1.remove('awesome')
print(f"List after removing 'awesome': {l1}")
```

```python
# .remove and .append change the list and have no return
result = l1.append("this is a test")
print(result)
```

<a id='1-2'></a>
### 1.2 List Comprehensions

List comprehensions provide a concise way to create lists, making your code more readable and expressive. They serve as a simpler alternative to using `for` loops. While [there is a small performance gain](https://stackoverflow.com/a/22108640) when using list comprehensions, their primary advantage lies in their readability and simplicity rather than any significant performance improvement.

```python
# An example of list comprehension to create a list of squares
squares = [x**2 for x in range(10)]
print(f"Squares of numbers from 0 to 9: {squares} (with list comprehension)")


# The same example using for loop
squares_for_loop = []
for x in range(10):
    squares_for_loop.append(x**2)
print(f"Squares of numbers from 0 to 9: {squares_for_loop} (without list comprehension)")
```

```python
# Conditional list comprehension
even_squares = [x**2 for x in range(10) if x % 2 == 0]
print(f"Squares of even numbers from 0 to 9: {even_squares} (with list comprehension)")

# Without list comprehension
even_squares_for_loop = []
for x in range(10):
    if x % 2 == 0:
        even_squares_for_loop.append(x**2)
print(f"Squares of even numbers from 0 to 9: {even_squares_for_loop} (without list comprehension)")
```

<a id='2'></a>
## 2 - Dictionaries

<a id='2-1'></a>
### 2.1 Introduction
Dictionaries are used to store data values in `key:value` pairs and are unordered, changeable, and do not allow duplicates.

```python
# Example of a dictionary
person = {
    'name': 'Alice',
    'age': 25,
    'city': 'New York'
}
print(f"Person dictionary: {person}")

# Accessing a value
print(f"Name: {person['name']}")

# Adding a new key-value pair
person['email'] = 'alice@example.com'
print(f"Updated person dictionary: {person}")
```

<a id='2-2'></a>
### 2.2 The method `.items`

You can also iterate over the pairs key/values in the dictionary with the method `.items`:

```python
for key, value in person.items():
    print(f"Key: {key}\tValue: {value}")
```

If you itereate directly on the dictionary, you will be iterating over its `keys`:

```python
for val in person:
    print(val)
```


<a id='3'></a>
## 3 - f-strings

<a id='3-1'></a>
### 3.1 Introduction

Python's f-strings (formatted string literals) provide a means to embed expressions inside string literals, using curly braces `{}`. You just need to add an "f" before the string to turn it into an f-string. 


```python
# Basic f-string example
name = "John"
age = 30
greeting = f"Hello, {name}. You are {age} years old."
print(greeting)
```

<a id='3-2'></a>
### 3.2 f-strings in Action

A common way to generate a string from a set of data is by using the following method. Suppose you have a list of dictionaries containing people's information, and you want to create strings in the format:


Name: Alice Johnson, Age: 28, E-mail: alice.johnson@example.com, Location: New York, NY
Name: Michael Smith, Age: 34, E-mail: michael.smith@example.com, Location: Los Angeles, CA
... (continues)

```python
# A list of dictionaries - this structure will come up a lot in this course!
people = [
    {
        "name": "Alice Johnson",
        "age": 28,
        "email": "alice.johnson@example.com",
        "location": "New York, NY"
    },
    {
        "name": "Michael Smith",
        "age": 34,
        "email": "michael.smith@example.com",
        "location": "Los Angeles, CA"
    },
    {
        "name": "Emily Davis",
        "age": 22,
        "email": "emily.davis@example.com",
        "location": "Austin, TX"
    },
    {
        "name": "John Brown",
        "age": 45,
        "email": "john.brown@example.com",
        "location": "Chicago, IL"
    },
    {
        "name": "Sarah Wilson",
        "age": 31,
        "email": "sarah.wilson@example.com",
        "location": "Seattle, WA"
    }
]
```


```python
# First, create an empty list to store the sentences:
t = []
# Iterate over the list of dictionary
for person_info_dict in people:
    # person_info_dict is a dict and you can access its values using the keys
    layout_string = f"Name: {person_info_dict['name']}, Age: {person_info_dict['age']}, E-mail: {person_info_dict['email']}, Location: {person_info_dict['location']}"
    # Append the string with the desired information into the list
    t.append(layout_string) # Add a new line character at the end
# Create the result layout by using the .join method
# The .join function concatenates every string in the list 't', separated by the specified delimiter. Here, each element of 't' is joined using the newline character '\n'.print(formatted_string)
formatted_string = "\n".join(t) 
print(formatted_string)
```

**IMPORTANT**: When accessing values in a dictionary, remember that the keys are strings. Therefore, you need to use quotation marks consistently. In this example, single quotes (`'`) are used for the keys in the dictionary, whereas double quotes (`"`) are used to delineate the string within an f-string. Not doing so will result in an error as the parser won't be able to handle the quotes properly.


```python
# Another way of creating strings that depend on parameters is the following:
template = "Name: {name}, Age: {age}, E-mail: {email}, Location: {location}"
t = []
for person_info_dict in people:
    # person_info_dict is a dict and you can access its values using the keys
    # Append the string with a new information using the .format method
    layout_string = template.format(name = person_info_dict['name'], 
                         age = person_info_dict['age'], 
                         email = person_info_dict['email'], 
                         location = person_info_dict['location'])
    t.append(layout_string)
formatted_string = "\n".join(t)
print(formatted_string)
```

Great! You finished the ungraded lab on basic Python concepts used in this RAG course!
