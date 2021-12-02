#include "lib/Rational.hpp"
//---------------------------------------------------------------------------
namespace arithmetic {
//---------------------------------------------------------------------------
long long Rational::gcd(long long a, long long b) const
// Calculate the greatest common divisior
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
//---------------------------------------------------------------------------
// Constructors
Rational::Rational()
    : numerator(0), denominator(1)
// Construct default rational
{
}
//---------------------------------------------------------------------------
Rational::Rational(long long numerator)
    : numerator(numerator), denominator(1)
// Construct from real number
{
}
//---------------------------------------------------------------------------
Rational::Rational(long long num, long long den)
// Construct in canonical form from numerator and denominator
{
    long long div = gcd(num, den);

    if (div < 0)
        div = -div;

    num /= div;
    den /= div;

    if ((num >= 0 && den >= 0) || (num < 0 && den >= 0)) {
        numerator = num;
        denominator = den;
    } else {
        numerator = -num;
        denominator = -den;
    }
}
//---------------------------------------------------------------------------
Rational::Rational(long long num, long long den, bool noCanon)
// Construct without canonical form from numerator and denominator
{
    numerator = num;
    denominator = den;
    // otw. I get unused parameter warning
    noCanonalization = noCanon;
}
//---------------------------------------------------------------------------
//Member functions
long long Rational::num()
// Get numerator
{
    return numerator;
}
long long Rational::den()
// Get denominator
{
    return denominator;
}
//---------------------------------------------------------------------------
Rational Rational::inv() const
// Get inverse
{
    return Rational(-denominator, -numerator, true);
}
//---------------------------------------------------------------------------
//Operators
Rational Rational::operator-() const
// Unary minus
{
    return Rational(-numerator, denominator);
}
//---------------------------------------------------------------------------
Rational Rational::operator+() const
// Unary plus
{
    return Rational(+numerator, +denominator);
}
//---------------------------------------------------------------------------
Rational Rational::operator+(const Rational& other) const
// Binary plus
{
    return Rational(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
}
Rational Rational::operator-(const Rational& other) const
// Binary minus
{
    return Rational(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
}
Rational Rational::operator*(const Rational& other) const
// Multiplication
{
    return Rational(numerator * other.numerator, denominator * other.denominator);
}
//---------------------------------------------------------------------------
Rational Rational::operator/(const Rational& other) const
// Division
{
    return (*this) * other.inv();
}
//---------------------------------------------------------------------------
bool Rational::operator==(const Rational& other) const
// Equals
{
    if (numerator == other.numerator && denominator == other.denominator)
        return true;

    return false;
}
//---------------------------------------------------------------------------
std::strong_ordering Rational::operator<=>(const Rational& other) const
// Third way comparison
{
    if (denominator == other.denominator) {
        return numerator <=> other.numerator;
    }
    return (numerator * other.denominator) <=> (other.numerator * denominator);
}
//---------------------------------------------------------------------------
Rational::operator double() const
// Explicit conversion to double
{
    return static_cast<double>(static_cast<double>(numerator) / static_cast<double>(denominator));
}
//---------------------------------------------------------------------------
} // namespace arithmetic
//---------------------------------------------------------------------------
