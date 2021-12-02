#ifndef H_PLJIT_REFERENCE
#define H_PLJIT_REFERENCE
#include <iostream>
//---------------------------------------------------------------------------
namespace pljit::codemanagement {
//---------------------------------------------------------------------------
/// struct that represents a lightweight reference inside the actual code
struct Reference {
    /// Constructors
    Reference() = default;
    /// Destructor
    ~Reference() = default;
    explicit Reference(size_t begin);
    Reference(size_t begin, size_t length);
    /// Member variables
    size_t begin = 0;
    size_t length = 1;
};
//---------------------------------------------------------------------------
} // namespace pljit::codemanagement
//---------------------------------------------------------------------------
#endif // H_PLJIT_REFERENCE
//---------------------------------------------------------------------------
