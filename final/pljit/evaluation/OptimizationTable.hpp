#ifndef H_PLJIT_OPTIMIZATIONTABLE
#define H_PLJIT_OPTIMIZATIONTABLE
#include "pljit/evaluation/SymbolTable.hpp"
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
/// A symbol table class for the constant propagation pass and evaluation context (MILESTONE 5)
class OptimizationTable {
    public:
    /// Constructors
    OptimizationTable() = default;
    explicit OptimizationTable(SymbolTable symbolTable) : optimizationTable(move(symbolTable.symbolTable)) {}
    /// Get the value of a symbol
    int64_t getValue(string_view name) const;
    /// Set the value of a symbol
    void setValue(string_view name, int64_t val);
    /// Mark the symbol as constant
    void setConstant(string_view name, bool set);
    /// Set the values of the parameters
    void setParameterValues(const vector<int64_t>& parameters);
    /// Check whether the symbol is a constant
    bool isConstant(string_view name) const;

    private:
    /// Storage of the table
    unordered_map<string_view, Symbol> optimizationTable;
};
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
#endif // H_PLJIT_OPTIMIZATIONTABLE
//---------------------------------------------------------------------------
