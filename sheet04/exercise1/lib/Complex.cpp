#include "lib/Complex.hpp"
#include <cmath>
//---------------------------------------------------------------------------
namespace arithmetic {
//---------------------------------------------------------------------------
// Constructors
Complex::Complex()
    : realPart(0.0), imaginaryPart(0.0)
// Construct default complex number
{
}
//---------------------------------------------------------------------------
Complex::Complex(double realPart)
    : realPart(realPart), imaginaryPart(0.0)
// Construct from real number
{
}
//---------------------------------------------------------------------------
Complex::Complex(double realPart, double imaginaryPart)
    : realPart(realPart), imaginaryPart(imaginaryPart)
// Construct from given real and imaginary part
{
}
//---------------------------------------------------------------------------
// Member functions
double Complex::real()
// Get the real part of the data
{
    return realPart;
}
//---------------------------------------------------------------------------
double Complex::imag()
// Get the imaginary part of the data
{
    return imaginaryPart;
}
//---------------------------------------------------------------------------
double Complex::abs() const
// Get the absolute value of a complex number
{
    return sqrt(pow(realPart, 2.0) + pow(imaginaryPart, 2.0));
}
//---------------------------------------------------------------------------
double Complex::norm() const
// Get the norm of a complex number
{
    return pow(abs(), 2.0);
}
//---------------------------------------------------------------------------
double Complex::arg() const
// Get the angle between the real and imaginary part of a complex number
{
    return atan2(imaginaryPart, realPart);
}
Complex Complex::conj() const
// Get the conjugate of a complex number
{
    return Complex(realPart, -imaginaryPart);
}
//---------------------------------------------------------------------------
// Operators
Complex Complex::operator-() const
// Unary minus
{
    return Complex(-realPart, -imaginaryPart);
}
//---------------------------------------------------------------------------
Complex Complex::operator+() const
// Unary plus
{
    return Complex(+realPart, +imaginaryPart);
}
//---------------------------------------------------------------------------
Complex Complex::operator+(const Complex& other) const
// Binary plus
{
    return Complex(realPart + other.realPart, imaginaryPart + other.imaginaryPart);
}
//---------------------------------------------------------------------------
Complex Complex::operator-(const Complex& other) const
// Binary minus
{
    return Complex(realPart - other.realPart, imaginaryPart - other.imaginaryPart);
}
//---------------------------------------------------------------------------
Complex Complex::operator*(const Complex& other) const
// Multiply two complex numbers
{
    return Complex(realPart * other.realPart - imaginaryPart * other.imaginaryPart, realPart * other.imaginaryPart + imaginaryPart * other.realPart);
}
//---------------------------------------------------------------------------
Complex Complex::operator/(const Complex& other) const
// Divide two complex numbers
{
    if (other.imaginaryPart == 0.0)
        return Complex(realPart / other.realPart, imaginaryPart / other.realPart);

    Complex numerator = (*this) * other.conj();
    Complex denominator = other * other.conj();

    return Complex(numerator.realPart / denominator.realPart, numerator.imaginaryPart / denominator.realPart);
}
//---------------------------------------------------------------------------
bool Complex::operator==(const Complex& other) const
// Equals operator
{
    if (realPart == other.realPart && imaginaryPart == other.imaginaryPart)
        return true;

    return false;
}
//---------------------------------------------------------------------------
} // namespace arithmetic
//---------------------------------------------------------------------------
