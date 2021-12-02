#include "pljit/evaluation/SymbolTable.hpp"
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
// Insert an identifier in the table
bool SymbolTable::insert(string_view name, Reference ref, bool isConstant, bool isInitialized, int64_t value, size_t parameterPos) {
    if (!symbolTable.empty()) {
        Reference reference = findLocation(name);
        if (static_cast<int>(reference.begin) != -1) {
            return false;
        }
    }
    symbolTable.insert({name, Symbol(ref, isConstant, isInitialized, value, parameterPos)});
    return true;
}
//---------------------------------------------------------------------------
// Initialize an identifier
void SymbolTable::initialize(string_view name) {
    auto symbolIterator = symbolTable.find(name);
    symbolIterator->second.isInitialized = true;
}
//---------------------------------------------------------------------------
// Uninitialize an identifier
void SymbolTable::uninitialize(string_view name) {
    auto symbolIterator = symbolTable.find(name);
    symbolIterator->second.isInitialized = false;
}
//---------------------------------------------------------------------------
// Return the reference in the code of an identifier
Reference SymbolTable::findLocation(string_view name) const {
    if (symbolTable.empty()) {
        return Reference(-1);
    }
    auto symbolIterator = symbolTable.find(name);
    if (symbolIterator == symbolTable.end())
        return Reference(-1);
    Symbol symbol = symbolIterator->second;
    return symbol.reference;
}
//---------------------------------------------------------------------------
// Check whether an identifier is a constant
optional<bool> SymbolTable::isConstant(string_view name) const {
    Reference ref = findLocation(name);
    if (static_cast<int>(ref.begin) == -1) {
        return nullopt;
    }
    auto symbolIterator = symbolTable.find(name);
    return symbolIterator->second.isConstant;
}
//---------------------------------------------------------------------------
// Check whether an identifier is initialized
bool SymbolTable::isInitialized(string_view name) const {
    auto symbolIterator = symbolTable.find(name);
    return symbolIterator->second.isInitialized;
}
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
