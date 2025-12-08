#include <stdexcept>
#include <iostream>
#include <string>
#include <iomanip>


void PrintMemory(int number, bool invert = false) {
    int* ptr_int = &number;
    unsigned char* ptr_char = reinterpret_cast<unsigned char*>(ptr_int);
    if (!invert) {
        std::cout << "0x";
        for (unsigned int i = 0; i < sizeof(int); ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(ptr_char[i]);
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "0x";
        for (int i = sizeof(int) - 1; i >= 0; --i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(ptr_char[i]);
        }
        std::cout << std::endl;
    }

}

void PrintMemory(double number, bool invert = false) {
    double* ptr_doub = &number;
    unsigned char* ptr_char = reinterpret_cast<unsigned char*>(ptr_doub);
    if (!invert) {
        std::cout << "0x";
        for (unsigned int i = 0; i < sizeof(double); ++i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(ptr_char[i]);
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "0x";
        for (int i = sizeof(double) - 1; i >= 0; --i) {
            std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(ptr_char[i]);
        }
        std::cout << std::endl;
    }
}
