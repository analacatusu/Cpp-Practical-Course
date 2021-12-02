#include "pljit/ast/ASTOptimizerDeadCode.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
// Optimize a constant
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(Constant& constant) {
    return make_unique<Constant>(move(constant));
}
//---------------------------------------------------------------------------
// Optimize a parameter
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(Parameter& parameter) {
    return make_unique<Parameter>(move(parameter));
}
//---------------------------------------------------------------------------
// Optimize a function
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(Function& function) {
    vector<unique_ptr<ASTNode>> optimizedStatements;
    auto& functionStatements = function.getStatements();
    for (auto& statement : functionStatements) {
        statement->optimize(*this, statement);
        optimizedStatements.push_back(move(statement));
        if (countReturnStatement == 1) {
            break;
        }
    }
    return make_unique<Function>(move(optimizedStatements), move(function.getSymbolTable()));
}
//---------------------------------------------------------------------------
// Optimize a statement
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(ASTStatement& astStatement) {
    unique_ptr<ASTNode> expr = astStatement.releaseInput();
    expr->optimize(*this, expr);
    return make_unique<ASTStatement>(move(expr));
}
//---------------------------------------------------------------------------
// Optimize an assignment
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(AssignmentExpr& assignmentExpr) {
    return make_unique<AssignmentExpr>(move(assignmentExpr));
}
//---------------------------------------------------------------------------
// Optimize a return statement
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(ReturnExpr& returnExpr) {
    countReturnStatement++;
    return make_unique<ReturnExpr>(move(returnExpr));
}
//---------------------------------------------------------------------------
// Optimize a multiplication
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(MulExpr& mulExpr) {
    return make_unique<MulExpr>(move(mulExpr));
}
//---------------------------------------------------------------------------
// Optimize a division
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(DivExpr& divExpr) {
    return make_unique<DivExpr>(move(divExpr));
}
//---------------------------------------------------------------------------
// Optimize an addition
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(AddExpr& addExpr) {
    return make_unique<AddExpr>(move(addExpr));
}
//---------------------------------------------------------------------------
// Optimize a subtraction
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(SubtractExpr& subtractExpr) {
    return make_unique<SubtractExpr>(move(subtractExpr));
}
//---------------------------------------------------------------------------
// Optimize a unary plus
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(UnaryPlus& unaryPlus) {
    return make_unique<UnaryPlus>(move(unaryPlus));
}
//---------------------------------------------------------------------------
// Optimize a unary minus
unique_ptr<ASTNode> ASTOptimizerDeadCode::visit(UnaryMinus& unaryMinus) {
    return make_unique<UnaryMinus>(move(unaryMinus));
}
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
