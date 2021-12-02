#ifndef H_PLJIT_ASTOPTIMIZERCONSTANTPROPAGATION
#define H_PLJIT_ASTOPTIMIZERCONSTANTPROPAGATION
#include "pljit/ast/AST.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
/// Struct that represents a constant propagation pass (MILESTONE 5)
struct ASTOptimizerConstantPropagation : ASTOptimizer {
    /// Constructors
    explicit ASTOptimizerConstantPropagation(OptimizationTable& optimizationTable) : optimizationTable(optimizationTable){};
    ASTOptimizerConstantPropagation() = default;
    /// Destructor
    ~ASTOptimizerConstantPropagation() override = default;
    /// Visit functions
    unique_ptr<ASTNode> visit(Constant&) override;
    unique_ptr<ASTNode> visit(Parameter&) override;
    unique_ptr<ASTNode> visit(Function&) override;
    unique_ptr<ASTNode> visit(ASTStatement&) override;
    unique_ptr<ASTNode> visit(AssignmentExpr&) override;
    unique_ptr<ASTNode> visit(ReturnExpr&) override;
    unique_ptr<ASTNode> visit(MulExpr&) override;
    unique_ptr<ASTNode> visit(DivExpr&) override;
    unique_ptr<ASTNode> visit(AddExpr&) override;
    unique_ptr<ASTNode> visit(SubtractExpr&) override;
    unique_ptr<ASTNode> visit(UnaryPlus&) override;
    unique_ptr<ASTNode> visit(UnaryMinus&) override;

    private:
    /// Storage of the symboltable
    OptimizationTable optimizationTable;
    /// Helper function to check whether a node value evaluates to zero
    static bool checkValueZero(ASTNode* node);
    /// Helper function to check whether a node value evaluates to one
    static bool checkValueOne(ASTNode* node);
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
#endif // H_PLJIT_ASTOPTIMIZERCONSTANTPROPAGATION
//---------------------------------------------------------------------------
