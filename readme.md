Hashmap implementation in c++ only using STL (unordered map)

Run command: g++ --std=c++17 main.cpp hashmap.cpp && ./a.out


bug in hashmap
--------------
When we come up with the idx from the hash we use the size of the associative array, if that size increases, then the next time we try to access that value the idx will be different. The only solution I can think of is to create a bigger empty array, then re-insert all the old values into the array.

Solution
----------
To resize:
Create a new, larger array.
Rehash and reinsert all existing elements into the new array.


string key -> hash function -> hash output (unique) -> some transform (like modulo) -> index in an array

Hash collisions can occur when two keys have the same index in the array.

Resize when we fill 50% 

Todo: Switch to make file

structure
- hashmap class 
- main.cpp to use the class
