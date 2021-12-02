#ifndef H_lib_EvaluationContext
#define H_lib_EvaluationContext
#include <vector>
//---------------------------------------------------------------------------
namespace ast {
/// Class to evaluate the AST
class EvaluationContext {
    public:
    /// Constructor
    EvaluationContext() = default;
    /// Destructor
    ~EvaluationContext() = default;
    /// Push a value
    void pushParameter(double value);
    /// Get the value
    double getParameter(unsigned index) const;

    private:
    /// Storage of the parameter values
    std::vector<double> params;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
