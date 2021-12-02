#include "lib/ObjectRepresentation.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
namespace object_representation {
//---------------------------------------------------------------------------
void printBinary(float value)
// Print the binary representation of a float value
{
    const std::byte byte{128};
    std::byte* bytes = reinterpret_cast<std::byte*>(&value);
    std::byte output{0};

    for (int i = sizeof(float) - 1; i >= 0; i--) {
        if (i == sizeof(float) - 1)
            std::cout << "sign: ";
        for (unsigned j = 0; j < 8; j++) {
            output = bytes[i] & byte;
            output = output >> 7;
            bytes[i] = bytes[i] << 1;

            if (j == 1 && i == (sizeof(float) - 1))
                std::cout << std::endl
                          << "exponent: ";

            if (j == 1 && i == (sizeof(float) - 2))
                std::cout << std::endl
                          << "mantissa: ";

            std::cout << std::to_integer<unsigned int>(output);
        }
    }
    std::cout << std::endl;
}
//---------------------------------------------------------------------------
void printBinary(double value)
// Print the binary representation of a double value
{
    const std::byte byte{128};
    std::byte* bytes = reinterpret_cast<std::byte*>(&value);
    std::byte output{0};

    for (int i = sizeof(double) - 1; i >= 0; i--) {
        if (i == sizeof(double) - 1)
            std::cout << "sign: ";
        for (unsigned j = 0; j < 8; j++) {
            output = bytes[i] & byte;
            output = output >> 7;
            bytes[i] = bytes[i] << 1;

            if (j == 1 && i == (sizeof(double) - 1))
                std::cout << std::endl
                          << "exponent: ";

            if (j == 4 && i == (sizeof(double) - 2))
                std::cout << std::endl
                          << "mantissa: ";

            std::cout << std::to_integer<unsigned int>(output);
        }
    }
    std::cout << std::endl;
}
//---------------------------------------------------------------------------
void push(vector<unsigned char>& stack, float value)
// Push a float onto buffer
{
    const std::byte* bytes = reinterpret_cast<const std::byte*>(&value);

    for (int i = sizeof(float) - 1; i >= 0; i--) {
        stack.push_back(static_cast<unsigned char>(bytes[i]));
    }

    unsigned char n = sizeof(float);
    stack.push_back(n);
}
//---------------------------------------------------------------------------
void push(vector<unsigned char>& stack, double value)
// Push a double onto buffer
{
    const std::byte* bytes = reinterpret_cast<const std::byte*>(&value);

    for (int i = sizeof(double) - 1; i >= 0; i--) {
        stack.push_back(static_cast<unsigned char>(bytes[i]));
    }

    unsigned char n = sizeof(double);

    stack.push_back(n);
}
//---------------------------------------------------------------------------
bool pop(vector<unsigned char>& stack, float& value)
// Pop a float from buffer
{
    if (stack.empty())
        return false;

    unsigned char n = stack.at(stack.size() - 1);
    unsigned int nrBytes = n;

    if (nrBytes != sizeof(float))
        return false;

    stack.pop_back();

    unsigned char* valuePointer = reinterpret_cast<unsigned char*>(&value);

    for (unsigned int i = 0; i < nrBytes; i++) {
        unsigned char byte = stack.at(stack.size() - 1);
        *valuePointer++ = byte;
        stack.pop_back();
    }
    return true;
}
//---------------------------------------------------------------------------
bool pop(vector<unsigned char>& stack, double& value)
// Pop a double from buffer
{
    if (stack.empty())
        return false;

    unsigned char n = stack.at(stack.size() - 1);
    unsigned int nrBytes = n;

    if (nrBytes != sizeof(double))
        return false;

    stack.pop_back();

    unsigned char* valuePointer = reinterpret_cast<unsigned char*>(&value);

    for (unsigned int i = 0; i < nrBytes; i++) {
        unsigned char byte = stack.at(stack.size() - 1);
        *valuePointer++ = byte;
        stack.pop_back();
    }

    return true;
}
//---------------------------------------------------------------------------
} // namespace object_representation
//---------------------------------------------------------------------------
