# HashMap Implementation in C++

An implementation of a hashmap in C++ using only the Standard Template Library (STL) (not `std::unordered_map`).

## Basic Concept

The hashmap works as follows:

1. A **string key** is hashed using a hash function.
2. The hash output (a unique value) is transformed (e.g., using modulo) to produce an **index**.
3. The index determines the location of the key-value pair in an **array**.

## Supported Types

The hashmap supports the following value types:
- `int`
- `float`
- `double`
- `bool`
- `char`
- `std::string`

## How to Run

1. Compile the code:
   - `make`

2. Run the program:
   - `./a.out`
