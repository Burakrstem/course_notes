# Ungraded Lab 2: LLM Calls and Crafting Simple Augmented Prompts


Welcome to **LLM Calls and Crafting Simple Augmented Prompts**. In this lab, you'll get hands-on practice with using two essential functions that let you interact with Large Language Models (LLMs). These functions help you both send single prompts to an LLM, and have a back-and-forth conversation. The main aim is to show you how to add extra information to your prompts, making them more detailed and useful. This added context helps the model give you better and more precise responses.

In this lab, you'll learn:

- How to set up and send questions to an LLM for both single questions and conversations.
- How to use additional data to make your prompts richer, improving the model's replies.


# Table of Contents
- [ 1 - Understanding the functions to call LLMs](#1)
  - [ 1.1 `generate_with_single_input`](#1-1)
  - [ 1.2 `generate_with_multiple_input`](#1-2)
- [ 2 - Integrating Data into an LLM Prompt](#2)
  - [ 2.1 Understanding the data structure](#2-1)
  - [ 2.2 Creating the Prompt](#2-2)

```python
from utils import (
    generate_with_single_input, 
    generate_with_multiple_input,
    get_proxy_url,
    get_proxy_headers,
    get_together_key
)
```


<a id='1'></a>
## 1 - Understanding the functions to call LLMs

In this section you will explore the one function that will be used to call LLMs in this course. This function calls the [together.ai](https://www.together.ai/) API to call the models. Here in the Coursera environment some steps in reaching the Together API are handled on your behalf via a proxy server, so if you try to run this notebook outside the Coursera environment it won't work right away. With small adjustments, however, you can pass an optional parameter with a together.ai API key, which will allow you to run these notebooks on your local machine.

<a id='1-1'></a>
### 1.1 `generate_with_single_input`

This function allows you to generate text from a language model based on a single input prompt. For now, let's just focus on a simple call with only a few basic parameters. You will explore different parameters to call an LLM and their impact on the output in Module 4. Here's the parameters you'll have access to for now.

#### Parameters:

- `prompt` (str): The input text prompt you want to send to the language model.
- `max_tokens` (int): Maximum tokens to generate in the response.
- `model` (str): The model name. Default is `"meta-llama/Llama-3.2-3B-Instruct-Turbo"`.
- `together_api_key`: An optional API key for authentication; defaults to `None`. If `None` you will use our proxy, otherwise a direct call to together.ai will be performed with the provided API key.


```python
# Example call
output = generate_with_single_input(
    prompt="What is the capital of France?"
)

print("Role:", output['role'])
print("Content:", output['content'])
```

<a id='1-2'></a>
### 1.2 `generate_with_multiple_input`

This function is designed to handle multiple input messages in a conversational context. The input format is a dictionary with two keys:

1. 'role' - the role that the message is being passed (usually assistant, system or user)
2. 'content' - the prompt

#### Parameters:

- `messages` (List[Dict]): A list of dictionaries, each containing 'role' and 'content' keys to represent each message in the conversation.
- `max_tokens` (int): Determines token limit for the response.
- `model` (str): Model to be used, default is `"meta-llama/Llama-3.2-3B-Instruct-Turbo"`.

```python
# Example call
messages = [
    {'role': 'user', 'content': 'Hello, who won the FIFA world cup in 2018?'},
    {'role': 'assistant', 'content': 'France won the 2018 FIFA World Cup.'},
    {'role': 'user', 'content': 'Who was the captain?'}
]

output = generate_with_multiple_input(
    messages=messages,
    max_tokens=100
)

print("Role:", output['role'])
print("Content:", output['content'])
```

### 1.3 Integration with OpenAI library

[Together.ai](together.ai) endpoints are [OpenAI compatible](https://docs.together.ai/docs/openai-api-compatibility) so you can use the [OpenAI library](https://github.com/openai/openai-python) to make the calls. In this section you will explore how to do it.  

```python
from openai import OpenAI, DefaultHttpxClient
import httpx

base_url = get_proxy_url() # If using together endpoint, add it here https://api.together.xyz/

# Custom transport to bypass SSL verification. This is only needed if using our proxy. Otherwise you can ignore it.
transport = httpx.HTTPTransport(local_address="0.0.0.0", verify=False)

# Create a DefaultHttpxClient instance with the custom transport
http_client = DefaultHttpxClient(transport=transport, headers=get_proxy_headers())

client = OpenAI(
    api_key = get_together_key(), # Set any as our proxy does not use it. Set the together api key if using the together endpoint.
    base_url=base_url, 
    http_client=http_client, # ssl bypass to make it work via proxy calls, remove it if running with together.ai endpoint 
)

messages = [
    {'role': 'user', 'content': 'Hello, who won the FIFA world cup in 2018?'},
    {'role': 'assistant', 'content': 'France won the 2018 FIFA World Cup.'},
    {'role': 'user', 'content': 'Who was the captain?'}
]

response = client.chat.completions.create(messages = messages, model ="meta-llama/Llama-3.2-3B-Instruct-Turbo")

print(response)
```

Notice that the response has several attributes. To access the response content, you may run:response.choices[0].message.content

```python
print(response.choices[0].message.content)
```

### 1.4 Note on Together.ai Integration for This Course

[Together.ai](https://together.ai) has generously provided credits for using the LLMs they host throughout this course. While there is technically a credit limit, it is set to be about 10 times more than what you would typically use, even with extensive usage. This is to ensure you have plenty of room to experiment and make your learning experience as smooth as possible.

There are two main types of errors you might encounter when making LLM calls during this course:

1. **500 and 429 Error**: This happens when too many calls are made to the system and it's overloaded. It's usually resolved by waiting for a moment. 
   
2. If you ever run out of credits, you will be notified. In this case, please reach out to our team in our Discourse community.

Grading your assignment will never use any of your credits. Our hope is that you never need to think about the credit limit, and that in the unlikely situation that you hit it, you'll know what happened and we can resolve it for you rapidly.

<a id='2'></a>
## 2 - Integrating Data into an LLM Prompt

In this section, you will learn how to effectively incorporate data into a prompt before passing it to a Large Language Model (LLM). We will work with a small dataset consisting of JSON files that contain information about houses. It will help you understand how to augment prompts in the context of RAG.

<a id='2-1'></a>
### 2.1 Understanding the data structure

Let's have a quick look in the data structure. It is a tiny dataset of houses. A list containing one dictionary per house.

```python
house_data = [
    {
        "address": "123 Maple Street",
        "city": "Springfield",
        "state": "IL",
        "zip": "62701",
        "bedrooms": 3,
        "bathrooms": 2,
        "square_feet": 1500,
        "price": 230000,
        "year_built": 1998
    },
    {
        "address": "456 Elm Avenue",
        "city": "Shelbyville",
        "state": "TN",
        "zip": "37160",
        "bedrooms": 4,
        "bathrooms": 3,
        "square_feet": 2500,
        "price": 320000,
        "year_built": 2005
    }
]
```

<a id='2-2'></a>
### 2.2 Creating the Prompt

Let's begin by constructing the prompt. The first step is to design a layout for the data.

```python
# First, let's create a layout for the houses

def house_info_layout(houses):
    # Create an empty string
    layout = ''
    # Iterate over the houses
    for house in houses:
        # For each house, append the information to the string using f-strings
        # The following way using brackets is a good way to make the code readable as in each line you can start a new f-string that will appended to the previous one
        layout += (f"House located at {house['address']}, {house['city']}, {house['state']} {house['zip']} with "
            f"{house['bedrooms']} bedrooms, {house['bathrooms']} bathrooms, "
            f"{house['square_feet']} sq ft area, priced at ${house['price']}, "
            f"built in {house['year_built']}.\n") # Don't forget the new line character at the end!
    return layout

# Check the layout
print(house_info_layout(house_data))
```


Now create a function that generates the prompt to be passed to the Language Learning Model (LLM). The function will take a user-provided query and the available housing data as inputs to effectively address the user's query.

```python
def generate_prompt(query, houses):
    # The code made above is modular enough to accept any list of houses, so you could also choose a subset of the dataset.
    # This might be useful in a more complex context where you want to give only some information to the LLM and not the entire data
    houses_layout = house_info_layout(houses)
    # Create a hard-coded prompt. You can use three double quotes (") in this cases, so you don't need to worry too much about using single or double quotes and breaking the code
    PROMPT = f"""
Use the following houses information to answer users queries.
{houses_layout}
Query: {query}    
             """
    return PROMPT

print(generate_prompt("What is the most expensive house?", houses = house_data))

```

Now let's call the LLM!

```python
query = "What is the most expensive house? And the bigger one?"
# Asking without the augmented prompt, let's pass the role as user
query_without_house_info = generate_with_single_input(prompt = query, role = 'user')
# With house info, given the prompt structuer, let's pass the role as assistant
enhanced_query = generate_prompt(query, houses = house_data)
query_with_house_info = generate_with_single_input(prompt = enhanced_query, role = 'assistant')

# Without house info
print(query_without_house_info['content'])

# With house info
print(query_with_house_info['content'])
```

Keep it up! You finished the introductory ungraded lab on how to call LLMs and augment prompts!