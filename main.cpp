#define TEST 1

#if TEST
#define CATCH_CONFIG_MAIN

#include "Test/catch.hpp"

#else
#include <iostream>
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
#endif