#ifndef H_PLJIT
#define H_PLJIT
#include "pljit/semantic/SemanticAnalysis.hpp"
#include <mutex>
//---------------------------------------------------------------------------
namespace pljit {
//---------------------------------------------------------------------------
/// struct that represents a function handle
struct PljitHandle {
    /// Constructor
    PljitHandle(vector<unique_ptr<ASTNode>>& functionsRef, string_view code) : functionsRef(functionsRef), code(code) {}
    /// Destructor
    ~PljitHandle() = default;
    /// Overloaded function call
    optional<int64_t> operator()(const vector<int64_t>& parameters);
    /// Getters
    bool isCompiled() const { return compiled; }
    ASTNode& getFunctionRef() const { return *functionsRef[position]; }

    private:
    /// Storage of the functions reference
    vector<unique_ptr<ASTNode>>& functionsRef;
    /// Storage of the code
    string_view code;
    /// Storage of whether the function was already compiled
    bool compiled = false;
    /// Storage of the mutex
    mutex uniqueMutex;
    /// Storage of the position of the current function
    size_t position = 0;
};
/// Struct that represents the Pljit compiler
struct Pljit {
    /// Constructor
    Pljit() = default;
    /// Destructor
    ~Pljit() = default;
    /// Register a function from the user
    PljitHandle registerFunction(string_view input) {
        return PljitHandle(functions, input);
    }

    private:
    /// Storage of the functions
    vector<unique_ptr<ASTNode>> functions;
};
//---------------------------------------------------------------------------
} // namespace pljit
//---------------------------------------------------------------------------
#endif // H_PLJIT
//---------------------------------------------------------------------------
