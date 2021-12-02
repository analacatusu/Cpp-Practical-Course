#ifndef H_lib_Rational
#define H_lib_Rational
#include <compare>
//---------------------------------------------------------------------------
namespace arithmetic {
//---------------------------------------------------------------------------

class Rational {
    private:
    /// Numerator
    long long numerator;
    /// Denominator
    long long denominator;
    /// For overloaded constructor without canonalization
    bool noCanonalization;

    /// Calculate the greatest common divisior
    long long gcd(long long a, long long b) const;

    public:
    /// Construct a default rational number
    Rational();
    /// Implicit construction from a real number
    // NOLINTNEXTLINE
    Rational(long long numerator);
    /// Construction from numerator and denominator
    Rational(long long num, long long den);
    /// Construction without canonalization
    Rational(long long num, long long den, bool noCanon);

    /// Get the numerator
    long long num();
    /// Get the denominator
    long long den();
    /// Get the inverse
    Rational inv() const;

    /// Unary minus
    Rational operator-() const;
    /// Unary plus
    Rational operator+() const;
    /// Binary plus
    Rational operator+(const Rational& other) const;
    /// Binary minus
    Rational operator-(const Rational& other) const;
    /// Multiplication
    Rational operator*(const Rational& other) const;
    /// Division
    Rational operator/(const Rational& other) const;
    /// Equals
    bool operator==(const Rational& other) const;
    /// Third-way comparison
    std::strong_ordering operator<=>(const Rational& other) const;
    /// Explicit conversion to double
    explicit operator double() const;
};

//---------------------------------------------------------------------------
} // namespace arithmetic
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
