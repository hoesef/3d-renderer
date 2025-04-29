# Contents
- [Allocation Metrics](#allocation-metrics)
- [Function overrides](#function-overrides)
    - [Operator new and the new keyword](#operator-new-and-the-new-keyword)
    - [Operator delete and the delete keyword](#operator-delete-and-the-delete-keyword)
- [Example: operator new and operator delete](#example-operator-new-and-operator-delete)
- [Examlpe: new and delete keywords](#example-new-and-delete-keywords)
- [Notes](#notes)
- [References](#referencees)

# Allocation Metrics
Allocation metrics is a struct that is used to track the number of bytes allocated and deallocated during the runtime of a program, allowing us to idnetify when a program might be leaking memory. The struct is comprised of three components; two variables to track the total number of bytes allocated and deallocated, and a function that returns the difference between these two variables (the number of bytes still currently allocated).

# Function overrides
allocation_metrics.cpp also contains overrides of the operator new and operator delete functions (and operator new[] and operator delete[] for array allocations).

## Operator new and the new keyword
In c++ we have two ways we can allocaate memory, we can either use the new keyword or operator new. Operator new works similar to how malloc works in C, it assigns a raw block of memory to the heap, it does nothing to initalize this block or modify it in any way. 

The new keyword, on the other hand, does initialize the memory. For example, if you use the new keyword to create a pointer to an object, the raw block of memory needed to store that object is allocated on the heap (using operator new) and then the objects constructor is called on this block of memory. Now it is safe to access areas of that block (such member variables) as you know that they have been initialized.<sup>N1</sup>

As the new keyword calls opertor new to allocate the raw memory needed to store an object, if we override the operator new function inorder to track the number of bytes allocated, then when we use the new keyword our tracking variable will still be updated (as again, the new keyword calls the operator new function).

## Operator delete and the delete keyword
Similar to operator new and the new keyword, operator delete and the delete keyword work with raw memory and initalized memory respectivly. 

The operator delete function deallocates a block of raw memory without doing anything to said block of memory before hand. If, in that block, we had some unique reference to another dynamically allocated block of memory, when operator delete frees our block of memory all references to this other block are lost, causing a memory leak. 

The delete keyword first calls the destructor for whatever type the memroy is before freeing it. This ensures that any memory that is dynamically allocated during an objects lifetime is properly deallocated<sup>N2</sup>, preventing memory leaks. 

The actual deallocation is done by calling the operator delete function under the hood (similar to how the new keyword calls the operator new function). This means that any override done to the operator delete function propergates to the delete keyword. Therefor, we can override the operator delete function to update out tracker variable, and anytime we use the delete keyword we are also updating our tracker variable.

## Example: operator new and operator delete
``` c++
#include <iostream>

// Dummy class
class Foo {
    private:
        int num = 5;
    public:
        Foo() {}
        int getNum() {return num;}
};

int main() {

    // Allocates a raw block of memory the size of a Foo object to the heap (void* ptr)
    // Casts the void* ptr to a Foo*
    Foo* f = static_cast<Foo*>(operator new(sizeof(Foo)));

    std::cout << f->getNum(); // Undefined behaviour, num is not initalized

    // Frees the block of memory
    operator delete(f);

    return 0;
}

---------------------------------------------
output:
Num: -27852735623 (undefined behaviour)
```

## Example: new and delete keywords
``` c++
#include <iostream>

// Dummy class
class Foo {
    private:
        int num = 5;
    public:
        Foo() {}
        int getNum() {return num;}
};

int main() {

    // Allocates a raw block of memory
    // Initializes the block of memory using the Foo constructor.
    Foo* f = new Foo;
    
    std::cout f->getNum(); // expected behaviour, num is valid

    // Calls the destructor
    // Frees the block of memory
    delete f;

    return 0;
}

---------------------------------------------
output:
Num: 5 (expected behaviour)
```

# Notes
- N1: "Now it is safe to access areas of that block (such member variables) as you know that they have been initialized". Obviously this is assuming that the member variable was initialized to a value at some point (either in the constructor or in when you defined it).

```c++
int num; // Initalizes num but gives it no value
std::cout << num; // Undefined behaviour
```
- N2: This assumes that the objects destructor functions correctly and actually deallocates any memory that was dynamically allocated during the objects life that it tied to the object.
```c++
class Foo{

    private:
        int* ptr;
    public:
        Foo() {ptr = new int[100]; } // dynamic memory allocation
        ~Foo() {
            // Correctly deallocates ptr
            // Without this deallocation, a memory leak is introduced
            if (ptr) { 
                delete[] ptr
            }
        }
};

```
- N3: If you use the operator new function to allocate a block of memory, you can still initalize the block using placement new. Howevere, you must now manually call the destructor to tidy up any memory allocated to the heap within the object, and then must also still call the operator delete function. Just using the delete keyword will only free the block of memory without calling the constructor, as it was initially assigned using the operator new function. However, this should only be used if you have a specific reason to be using it, otherwise it can just lead to errors (like forgetting to call the destructor, using the delete keyword rather than the operator delete, etc). In most cases you just want to use the new and delete keywords.

```c++
int main() {
    // Allocate block of memory
    // Cast to Foo*
    Foo* f = static_cast<Foo*>(operator new(sizeof(Foo)));

    // Use placement new to call the Foo constructor on the block of memory
    new (f) Foo();

    // Call the Foo destrucor
    f.~Foo();

    // Free the block of memory
    operator delete(f);

}
```

# Referencees:
- Allocation metrics: https://www.youtube.com/watch?v=sLlGEUO_EGE&list=LL&index=1&pp=gAQBiAQB
- Operator new: https://en.cppreference.com/w/cpp/memory/new/operator_new
- Operator delete: https://en.cppreference.com/w/cpp/memory/new/operator_delete
- New keyword: https://en.cppreference.com/w/cpp/language/new
- Delete keyword: https://en.cppreference.com/w/cpp/language/delete