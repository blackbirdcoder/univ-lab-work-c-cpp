// Work 1
// Practical task:
// Write a program using the Union data type that examines the properties of this data type
// (namely, the values, pointers, and size in bytes of each field),
// inputs and outputs the values of the union fields using variables and pointers.
// The type of one of the fields must be a pointer.

#include <iostream>

union Temperature{
    float cels;
    float *fahr;
};

int main() {
    float fahrValue;
    Temperature temp;
    temp.fahr = &fahrValue;

    std::cout << "----------- Input: ---------------" << std::endl;
    std::cout << "Enter temperature in Fahrenheit: ";
    std::cin >> *temp.fahr;

    temp.cels = (*temp.fahr - 32) / 1.8;

    std::cout << "----------- Result: ------------" << std::endl;
    std::cout << "Temperature in Celsius: " << temp.cels << std::endl;
    std::cout << "Temperature in Fahrenheit: " << fahrValue << std::endl;

    std::cout << "---------- Size: ---------------" << std::endl;
    std::cout << "Size of Temperature: " << sizeof(Temperature) << " bytes" << std::endl;
    std::cout << "Size of Celsius: " << sizeof(temp.cels) << " bytes" << std::endl;
    std::cout << "Size of Fahrenheit: " << sizeof(fahrValue) << " bytes" << std::endl;

    return 0;
}
