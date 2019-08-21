#include "SimplerUniqPtr.h"
#include <iostream>
#include <cstdint>


int main() {

    SimpleUniquePtr p(3);
    p[0] = (int8_t) 1;
    p[2] = (int8_t) 3;
    std::cout << "In p[0] is " << (int) p[0] << std::endl;



}
