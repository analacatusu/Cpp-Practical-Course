#ifndef H_PLJIT_ASTOPTIMIZERDEADCODE
#define H_PLJIT_ASTOPTIMIZERDEADCODE
#include "pljit/ast/AST.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
/// Struct that represents the dead code elimination (MILESTONE 5)
struct ASTOptimizerDeadCode : ASTOptimizer {
    /// Constructor
    ASTOptimizerDeadCode() = default;
    /// Destructor
    ~ASTOptimizerDeadCode() override = default;
    /// Visit functions for each node type
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
    /// Storage of how many return statements were visited so far
    size_t countReturnStatement = 0;
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
#endif // H_PLJIT_ASTOPTIMIZERDEADCODE
//---------------------------------------------------------------------------
