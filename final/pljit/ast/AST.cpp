#include "pljit/ast/AST.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
// Overridden accept function
void Constant::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void Constant::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t Constant::evaluate(EvaluationContext&) {
    return value;
}
//---------------------------------------------------------------------------
// Overridden accept function
void Parameter::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void Parameter::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t Parameter::evaluate(EvaluationContext& evaluationContext) {
    return evaluationContext.getValue(name);
}
//---------------------------------------------------------------------------
// Overridden accept function
void UnaryPlus::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void UnaryPlus::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t UnaryPlus::evaluate(EvaluationContext& evaluationContext) {
    return child->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden accept function
void UnaryMinus::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void UnaryMinus::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t UnaryMinus::evaluate(EvaluationContext& evaluationContext) {
    return -child->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden accept function
void DivExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t DivExpr::evaluate(EvaluationContext& evaluationContext) {
    if (right->evaluate(evaluationContext) == 0) {
        evaluationContext.setError();
        evaluationContext.errorDivisionByZero();
        return 0;
    }
    return left->evaluate(evaluationContext) / right->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void DivExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden accept function
void MulExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t MulExpr::evaluate(EvaluationContext& evaluationContext) {
    return left->evaluate(evaluationContext) * right->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void MulExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden accept function
void SubtractExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t SubtractExpr::evaluate(EvaluationContext& evaluationContext) {
    return left->evaluate(evaluationContext) - right->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void SubtractExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden accept function
void AddExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void AddExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t AddExpr::evaluate(EvaluationContext& evaluationContext) {
    return left->evaluate(evaluationContext) + right->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden accept function
void AssignmentExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void AssignmentExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t AssignmentExpr::evaluate(EvaluationContext& evaluationContext) {
    int64_t value = right->evaluate(evaluationContext);
    evaluationContext.setValue(nameLeft, value);
    return 0;
}
//---------------------------------------------------------------------------
// Overridden accept function
void ReturnExpr::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void ReturnExpr::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t ReturnExpr::evaluate(EvaluationContext& evaluationContext) {
    int64_t value = child->evaluate(evaluationContext);
    evaluationContext.setReturnValue(value);
    return 0;
}
//---------------------------------------------------------------------------
// Overridden accept function
void ASTStatement::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t ASTStatement::evaluate(EvaluationContext& evaluationContext) {
    return expression->evaluate(evaluationContext);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void ASTStatement::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden accept function
void Function::accept(ASTVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden optimize function
void Function::optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) {
    thisRef = astOptimizer.visit(*this);
}
//---------------------------------------------------------------------------
// Overridden evaluate function
int64_t Function::evaluate(EvaluationContext& evaluationContext) {
    int64_t value = 0;
    for (auto& i : statements) {
        auto& statement = static_cast<ASTStatement&>(*i);
        value = statement.evaluate(evaluationContext);
        if (evaluationContext.errorOccurred()) {
            error = true;
            return 0;
        }
        if (statement.getExpression().getType() == ASTNode::Type::ReturnExpr) {
            return value;
        }
    }
    return value;
}
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
