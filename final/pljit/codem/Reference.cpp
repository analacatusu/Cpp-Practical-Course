#include "pljit/codem/Reference.hpp"
//---------------------------------------------------------------------------
namespace pljit::codemanagement {
//---------------------------------------------------------------------------
// Constructor
Reference::Reference(size_t begin) : begin(begin) {
}
//---------------------------------------------------------------------------
// Constructor
Reference::Reference(size_t begin, size_t length) : begin(begin), length(length) {
}
//---------------------------------------------------------------------------
} // namespace pljit::codemanagement
//---------------------------------------------------------------------------
