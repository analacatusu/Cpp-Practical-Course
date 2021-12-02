#include "lib/EvaluationContext.hpp"
//---------------------------------------------------------------------------
namespace ast {
// Push a value
void EvaluationContext::pushParameter(double value) {
    params.push_back(value);
}
//---------------------------------------------------------------------------
// Get a value at a given index
double EvaluationContext::getParameter(unsigned index) const {
    return params[index];
}
} // namespace ast
//---------------------------------------------------------------------------
