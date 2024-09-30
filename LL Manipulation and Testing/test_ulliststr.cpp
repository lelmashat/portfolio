#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
    ULListStr dat;
    dat.push_back("7");
    dat.push_front("8");
    dat.push_back("9");
    
    // Test front, back, and size
    std::cout << dat.front() << " " << dat.back() << std::endl;
    std::cout << "Size: " << dat.size() << std::endl;

    // Test pop_back and pop_front
    dat.pop_back();
    dat.pop_front();

    // Test front, back, and size after popping
    std::cout << dat.front() << " " << dat.back() << std::endl;
    std::cout << "Size: " << dat.size() << std::endl;

    // Test getValAtLoc
    /*
    const std::string* val = dat.getValAtLoc(0);
    if (val != nullptr) {
        std::cout << "Value at location 0: " << *val << std::endl;
    } else {
        std::cout << "Invalid location." << std::endl;
    }
    */

    return 0;
}
