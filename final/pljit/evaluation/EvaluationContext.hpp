#ifndef H_PLJIT_EVALUATIONCONTEXT
#define H_PLJIT_EVALUATIONCONTEXT
#include "pljit/evaluation/OptimizationTable.hpp"
//---------------------------------------------------------------------------
namespace pljit::evaluation {
//---------------------------------------------------------------------------
/// Class that evaluates an ast node (MILESTONE 5)
class EvaluationContext {
    public:
    /// Constructors
    explicit EvaluationContext(OptimizationTable& optimizationTable) : optimizationTable(optimizationTable) {}
    EvaluationContext(OptimizationTable& optimizationTable1, const vector<int64_t>& parameters);
    /// Get the value of a constant
    int64_t getValue(string_view name) const;
    /// Set the value of a constant
    void setValue(string_view name, int64_t val);
    /// Set the return value of a program
    void setReturnValue(int64_t value);
    /// Runtime error
    void errorDivisionByZero();
    /// Set the error
    void setError();
    /// Return whether an error occurred
    bool errorOccurred() const;
    /// Get the return value of a program
    int64_t getReturnValue() const;

    private:
    /// Storage of the symbol table
    OptimizationTable optimizationTable;
    /// Storage of the return value
    int64_t returnValue = 0;
    /// Storage of the error
    bool error = false;
};
//---------------------------------------------------------------------------
} // namespace pljit::evaluation
//---------------------------------------------------------------------------
#endif // H_PLJIT_EVALUATIONCONTEXT
//---------------------------------------------------------------------------
