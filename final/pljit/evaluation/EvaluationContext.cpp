#include "pljit/evaluation/EvaluationContext.hpp"
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
// Get the value from an identifier
int64_t EvaluationContext::getValue(string_view name) const {
    return optimizationTable.getValue(name);
}
//---------------------------------------------------------------------------
// Set a value to an identifier
void EvaluationContext::setValue(string_view name, int64_t val) {
    optimizationTable.setValue(name, val);
}
//---------------------------------------------------------------------------
// Set the return value
void EvaluationContext::setReturnValue(int64_t value) {
    returnValue = value;
}
//---------------------------------------------------------------------------
// Runtime error
void EvaluationContext::errorDivisionByZero() {
    cerr << "runtime error : division by zero" << endl;
}
//---------------------------------------------------------------------------
// Indicate that an error occurred
void EvaluationContext::setError() {
    error = true;
}
//---------------------------------------------------------------------------
// Return whether an error occurred
bool EvaluationContext::errorOccurred() const {
    return error;
}
//---------------------------------------------------------------------------
// Get the return value of the program
int64_t EvaluationContext::getReturnValue() const {
    return returnValue;
}
//---------------------------------------------------------------------------
// Constructor
EvaluationContext::EvaluationContext(OptimizationTable& optimizationTable1, const vector<int64_t>& parameters) : optimizationTable(optimizationTable1) {
    optimizationTable.setParameterValues(parameters);
}
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
