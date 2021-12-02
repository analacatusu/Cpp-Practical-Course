#ifndef H_PLJIT_SYMBOL
#define H_PLJIT_SYMBOL
#include "pljit/codem/Reference.hpp"
using namespace std;
using namespace pljit::codemanagement;
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
/// Class that represents a symbol in the symbol table and its properties
class Symbol {
    friend class SymbolTable;
    friend class OptimizationTable;

    public:
    /// Constructor
    explicit Symbol(Reference reference, bool isConstant = false, bool isInitialized = true, int64_t value = 0, size_t parameterPos = -1)
        : reference(reference), isConstant(isConstant), isInitialized(isInitialized), value(value), parameterPos(parameterPos) {}

    private:
    /// Storage of the reference of the symbol in the actual program
    Reference reference;
    /// Mark whether the symbol is a constant
    bool isConstant = false;
    /// Mark whether the symbol is initialized
    bool isInitialized = false;
    /// Storage of the value of a symbol
    int64_t value = 0;
    /// Position of the parameter in the parameter list
    size_t parameterPos = 0;
};
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
#endif // H_PLJIT_SYMBOL
//---------------------------------------------------------------------------
