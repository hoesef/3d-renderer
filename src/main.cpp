// Standard library imports
#include <iostream>
#include <cstdint>

// 3rd party imports

// Local imports
#include "..\include\allocation_metrics\allocaion_metrics.h"

// Check the allocation metrics to find signs of a memory leak
void detect_mem_leak() {
    uint32_t size = s_allocation_metrics.getCurrentMemory();
    std::cout << "\n\n";
    if (size) {
        std::cout << "!!!MEMORY LEAK DETECTED!!!\n";
        std::cout << size << " bytes still allocated at program termination!\n";
    } else {
        std::cout << "No memory leak detected.\n";
        std::cout << "All memory seems to be deallocated at program termination\n";
    }
    std::cout << std::endl;
}

class Foo {

    private:
        int num = 5;

    public:
        Foo(){}
        int getNum() {return num;};

};

int main() {

    std::atexit(detect_mem_leak);

    memInfo();

    int* array = new int[5];
    for (int i = 0; i < 5; i ++) {
        array[i] = i;
        std::cout << "Index " << i << ": " << array[i] << "\n";
    }

    memInfo();

    delete[] array;

    memInfo();

    return 0;

}