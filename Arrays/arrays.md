Problem: Implement a Generic Dynamic Array
Design a generic dynamic array in C++ using a class template. The array must support dynamic memory management and provide a complete set of operations for manipulating, accessing, searching, and processing elements.

Implement an Array<T> class with private data members and public member functions, following object-oriented programming principles, encapsulation, and production-level coding practices.

Your implementation must support the following operations:
- display(): Display all elements.
- add() / append(): Add an element to the array.
- insert(index, value): Insert an element at a specified index.
- delete(index): Remove an element at a specified index.
- search(value): Search using linear search or binary search.
- get(index): Retrieve an element at a specified index.
- set(index, value): Update an element.
- max() / min(): Find the maximum and minimum elements.
- sum() / avg(): Calculate the sum and average of elements.
- reverse(): Reverse the array.
- shift(positions): Shift elements left or right.
- rotate(positions): Rotate elements left or right.
- merge(other): Merge two arrays.
- union(other): Return the distinct elements from both arrays.
- intersection(other): Return the distinct common elements of two arrays.
Constraints
1. Use C++ templates to support multiple compatible data types.
2. Implement dynamic memory allocation without using std::vector for internal storage.
3. Maintain separate logical size and allocated capacity.
4. Handle invalid indices, empty arrays, and memory allocation failures safely.
5. Binary search must operate on sorted arrays.
6. Implement appropriate constructors, destructors, and copy/move semantics.
7. Ensure each operation has a clearly defined return value, error-handling behaviour, and time complexity.
Goal: Build a reusable, memory-safe dynamic array library that demonstrates a comprehensive understanding of array operations, algorithms, memory management, and object-oriented programming.