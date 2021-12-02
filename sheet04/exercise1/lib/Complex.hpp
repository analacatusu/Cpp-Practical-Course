#ifndef H_lib_Complex
#define H_lib_Complex
//---------------------------------------------------------------------------
namespace arithmetic {
//---------------------------------------------------------------------------

class Complex {
    private:
    /// Real part of the complex number
    double realPart;
    /// Imaginary part of the complex number
    double imaginaryPart;

    public:
    /// Construct a default complex number
    Complex();
    /// Implicit construction from a real number
    // NOLINTNEXTLINE
    Complex(double realPart);
    /// Construct from a real and an imaginary part
    Complex(double realPart, double imaginaryPart);

    /// Get the real part
    double real();
    /// Get the imaginary part
    double imag();
    /// Calculate the absolute value
    double abs() const;
    /// Calculte the norm
    double norm() const;
    /// Calculate the angle between real and imaginary part
    double arg() const;
    /// Calculate a complex conjugate
    Complex conj() const;

    /// Unary minus
    Complex operator-() const;
    /// Unary plus
    Complex operator+() const;
    /// Binary plus
    Complex operator+(const Complex& other) const;
    /// Binary minus
    Complex operator-(const Complex& other) const;
    /// Multiplication
    Complex operator*(const Complex& other) const;
    /// Division
    Complex operator/(const Complex& other) const;
    /// Equals operator
    bool operator==(const Complex& other) const;
};

//---------------------------------------------------------------------------
} // namespace arithmetic
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
