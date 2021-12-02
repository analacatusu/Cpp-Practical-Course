#include "pljit/evaluation/OptimizationTable.hpp"
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
// Get the value of a symbol
int64_t OptimizationTable::getValue(string_view name) const {
    auto symbolIterator = optimizationTable.find(name);
    return symbolIterator->second.value;
}
//---------------------------------------------------------------------------
// Set the value of a symbol
void OptimizationTable::setValue(string_view name, int64_t val) {
    auto symbolIterator = optimizationTable.find(name);
    symbolIterator->second.value = val;
}
//---------------------------------------------------------------------------
// Set the symbol as constant
void OptimizationTable::setConstant(string_view name, bool set) {
    auto symbolIterator = optimizationTable.find(name);
    symbolIterator->second.isConstant = set;
}
//---------------------------------------------------------------------------
// Set the parameter values for the respective symbols
void OptimizationTable::setParameterValues(const vector<int64_t>& parameters) {
    for (auto symbol : optimizationTable) {
        if (static_cast<int>(symbol.second.parameterPos) != -1) {
            setValue(symbol.first, parameters[symbol.second.parameterPos]);
        }
    }
}
//---------------------------------------------------------------------------
// Check whether a symbol is a constant
bool OptimizationTable::isConstant(string_view name) const {
    auto symbolIterator = optimizationTable.find(name);
    return symbolIterator->second.isConstant;
}
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
