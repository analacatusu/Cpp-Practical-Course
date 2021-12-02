#ifndef H_PLJIT_SYMBOLTABLE
#define H_PLJIT_SYMBOLTABLE
#include "pljit/evaluation/Symbol.hpp"
#include <unordered_map>
#include <vector>
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
/// Class that represents the symbol table of a program (MILESTONE 4)
class SymbolTable {
    friend class OptimizationTable;

    public:
    /// Constructor
    SymbolTable() = default;
    /// Insert a symbol in the table
    bool insert(string_view name, Reference ref, bool isConstant = false, bool isInitialized = true, int64_t value = 0, size_t parameterPos = -1);
    /// Initialize a symbol
    void initialize(string_view name);
    /// Mark the symbol a uninitialized
    void uninitialize(string_view name);
    /// Return the reference of a symbol
    Reference findLocation(string_view name) const;
    /// Return whether the symbol is a constant
    optional<bool> isConstant(string_view name) const;
    /// Return whether the symbol is initialized
    bool isInitialized(string_view name) const;

    private:
    /// Storage of the symboltable
    unordered_map<string_view, Symbol> symbolTable;
};
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
#endif // H_PLJIT_SYMBOLTABLE
//---------------------------------------------------------------------------
