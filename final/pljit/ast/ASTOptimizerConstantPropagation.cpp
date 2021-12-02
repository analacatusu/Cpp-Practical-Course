#include "pljit/ast/ASTOptimizerConstantPropagation.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
// Optimize a constant
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(Constant& constant) {
    return make_unique<Constant>(move(constant));
}
//---------------------------------------------------------------------------
// Optimize a parameter
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(Parameter& parameter) {
    if (optimizationTable.isConstant(parameter.getName())) {
        return make_unique<Constant>(optimizationTable.getValue(parameter.getName()));
    }
    return make_unique<Parameter>(move(parameter));
}
//---------------------------------------------------------------------------
// Optimize a function
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(Function& function) {
    optimizationTable = function.getSymbolTable();
    auto& functionStatements = function.getStatements();
    for (auto& functionStatement : functionStatements) {
        functionStatement->optimize(*this, functionStatement);
    }
    return make_unique<Function>(move(functionStatements), move(optimizationTable));
}
//---------------------------------------------------------------------------
// Optimize a statement
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(ASTStatement& astStatement) {
    auto expr = astStatement.releaseInput();
    expr->optimize(*this, expr);
    return make_unique<ASTStatement>(move(expr));
}
//---------------------------------------------------------------------------
// Optimize an assignment
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(AssignmentExpr& assignmentExpr) {
    auto right = assignmentExpr.releaseRight();
    auto left = assignmentExpr.releaseLeft();

    right->optimize(*this, right);

    auto& leftRef = static_cast<Parameter&>(*left);

    if (right->getType() == ASTNode::Type::Constant) {
        auto& rightRef = static_cast<Constant&>(*right);
        int64_t value = rightRef.getValue();
        optimizationTable.setValue(leftRef.getName(), value);
        optimizationTable.setConstant(leftRef.getName(), true);
    } else {
        optimizationTable.setConstant(leftRef.getName(), false);
    }
    string_view nameLeft = leftRef.getName();
    return make_unique<AssignmentExpr>(move(left), move(right), nameLeft);
}
//---------------------------------------------------------------------------
// Optimize a return statement
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(ReturnExpr& returnExpr) {
    auto childNode = returnExpr.releaseInput();
    childNode->optimize(*this, childNode);
    return make_unique<ReturnExpr>(move(childNode));
}
//---------------------------------------------------------------------------
// Optimize a multiplication
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(MulExpr& mulExpr) {
    auto left = mulExpr.releaseLeft();
    auto right = mulExpr.releaseRight();

    left->optimize(*this, left);
    right->optimize(*this, right);

    if (checkValueOne(left.get())) {
        return right;
    }

    if (checkValueZero(left.get()) || checkValueZero(right.get())) {
        return make_unique<Constant>(0);
    }

    if (checkValueOne(right.get())) {
        return left;
    }

    if (left->getType() == ASTNode::Type::Constant && right->getType() == ASTNode::Type::Constant) {
        EvaluationContext evaluationContext(optimizationTable);
        MulExpr mulExpr1 = MulExpr(move(left), move(right));
        int64_t value = mulExpr1.evaluate(evaluationContext);
        return make_unique<Constant>(value);
    }

    if (left->getType() == ASTNode::Type::UnaryMinus && right->getType() == ASTNode::Type::UnaryMinus) {
        left = make_unique<UnaryMinus>(move(left));
        right = make_unique<UnaryMinus>(move(right));
        left->optimize(*this, left);
        right->optimize(*this, right);
        return make_unique<MulExpr>(move(left), move(right));
    }

    return make_unique<MulExpr>(move(left), move(right));
}
//---------------------------------------------------------------------------
// Optimize a division
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(DivExpr& divExpr) {
    auto left = divExpr.releaseLeft();
    auto right = divExpr.releaseRight();

    left->optimize(*this, left);
    right->optimize(*this, right);

    if (checkValueZero(right.get())) {
        return make_unique<DivExpr>(move(left), move(right));
    }

    if (checkValueZero(left.get())) {
        return make_unique<Constant>(0);
    }

    if (checkValueOne(right.get())) {
        return left;
    }

    if (left->getType() == ASTNode::Type::Constant && right->getType() == ASTNode::Type::Constant) {
        EvaluationContext evaluationContext(optimizationTable);
        DivExpr divExpr1 = DivExpr(move(left), move(right));
        int64_t value = divExpr1.evaluate(evaluationContext);
        return make_unique<Constant>(value);
    }

    if (left->getType() == ASTNode::Type::UnaryMinus && right->getType() == ASTNode::Type::UnaryMinus) {
        left = make_unique<UnaryMinus>(move(left));
        right = make_unique<UnaryMinus>(move(right));
        left->optimize(*this, left);
        right->optimize(*this, right);
        return make_unique<DivExpr>(move(left), move(right));
    }

    return make_unique<DivExpr>(move(left), move(right));
}
//---------------------------------------------------------------------------
// Optimize an addition
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(AddExpr& addExpr) {
    auto left = addExpr.releaseLeft();
    auto right = addExpr.releaseRight();

    left->optimize(*this, left);
    right->optimize(*this, right);

    if (checkValueZero(left.get())) {
        return right;
    }

    if (checkValueZero(right.get())) {
        return left;
    }

    if (left->getType() == ASTNode::Type::UnaryMinus) {
        left = make_unique<UnaryMinus>(move(left));
        unique_ptr<ASTNode> expr = make_unique<SubtractExpr>(move(right), move(left));
        expr->optimize(*this, expr);
        return expr;
    }

    if (right->getType() == ASTNode::Type::UnaryMinus) {
        right = make_unique<UnaryMinus>(move(right));
        unique_ptr<ASTNode> expr = make_unique<SubtractExpr>(move(left), move(right));
        expr->optimize(*this, expr);
        return expr;
    }

    if (left->getType() == ASTNode::Type::Constant && right->getType() == ASTNode::Type::Constant) {
        EvaluationContext evaluationContext(optimizationTable);
        AddExpr addExpr1 = AddExpr(move(left), move(right));
        int64_t value = addExpr1.evaluate(evaluationContext);
        return make_unique<Constant>(value);
    }

    return make_unique<AddExpr>(move(left), move(right));
}
//---------------------------------------------------------------------------
// Optimize a subtraction
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(SubtractExpr& subtractExpr) {
    auto left = subtractExpr.releaseLeft();
    auto right = subtractExpr.releaseRight();

    left->optimize(*this, left);
    right->optimize(*this, right);

    if (checkValueZero(right.get())) {
        return left;
    }

    if (checkValueZero(left.get())) {
        return make_unique<UnaryMinus>(move(right));
    }

    if (right->getType() == ASTNode::Type::UnaryMinus) {
        right = make_unique<UnaryMinus>(move(right));
        unique_ptr<ASTNode> expr = make_unique<AddExpr>(move(left), move(right));
        expr->optimize(*this, expr);
        return expr;
    }

    if (left->getType() == ASTNode::Type::Constant && right->getType() == ASTNode::Type::Constant) {
        EvaluationContext evaluationContext(optimizationTable);
        SubtractExpr subtractExpr1 = SubtractExpr(move(left), move(right));
        int64_t value = subtractExpr1.evaluate(evaluationContext);
        if (value < 0) {
            return make_unique<UnaryMinus>(make_unique<Constant>(-value));
        }
        return make_unique<Constant>(value);
    }

    return make_unique<SubtractExpr>(move(left), move(right));
}
//---------------------------------------------------------------------------
// Optimize a unary plus
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(UnaryPlus& unaryPlus) {
    auto childNode = unaryPlus.releaseInput();
    childNode->optimize(*this, childNode);
    return childNode;
}
//---------------------------------------------------------------------------
// Optimize a unary minus
unique_ptr<ASTNode> ASTOptimizerConstantPropagation::visit(UnaryMinus& unaryMinus) {
    auto childNode = unaryMinus.releaseInput();
    childNode->optimize(*this, childNode);

    if (childNode->getType() == ASTNode::Type::Constant) {
        auto& constant = static_cast<Constant&>(*childNode);
        return make_unique<Constant>(-constant.getValue());
    }

    if (childNode->getType() == ASTNode::Type::UnaryMinus) {
        auto& um = static_cast<UnaryMinus&>(*childNode);
        unique_ptr<ASTNode> granChild = um.releaseInput();
        return granChild;
    }

    if (childNode->getType() == ASTNode::Type::SubtractExpr) {
        auto& subtractExpr = static_cast<SubtractExpr&>(*childNode);
        auto left = subtractExpr.releaseLeft();
        auto right = subtractExpr.releaseRight();
        return make_unique<SubtractExpr>(move(right), move(left));
    }

    return make_unique<UnaryMinus>(move(childNode));
}
//---------------------------------------------------------------------------
// Helper function to check whether a node value evaluates to zero
bool ASTOptimizerConstantPropagation::checkValueZero(ASTNode* node) {
    if (node->getType() == ASTNode::Type::Constant) {
        auto& ref = static_cast<Constant&>(*node);
        if (ref.getValue() == 0)
            return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Helper function to check whether a node value evaluates to one
bool ASTOptimizerConstantPropagation::checkValueOne(ASTNode* node) {
    if (node->getType() == ASTNode::Type::Constant) {
        auto& ref = static_cast<Constant&>(*node);
        if (ref.getValue() == 1)
            return true;
    }
    return false;
}
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
