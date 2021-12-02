#include "pljit/ast/ASTPrintVisitor.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
// Draw a new node
void ASTPrintVisitor::initNewNode(size_t localParent, string_view str) {
    out << "\t" << localParent << "[label=\"" << str << "\"];\n";
    out << parentLabel << "-- " << localParent << ";\n";
}
//---------------------------------------------------------------------------
// Visit a constant
void ASTPrintVisitor::visit(const Constant& constant) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Constant");
    parentLabel = localParent;
    string str = to_string(static_cast<int64_t>(constant.getValue()));
    string_view stringView{str};
    initNewNode(currentLabel++, stringView);
}
//---------------------------------------------------------------------------
// Visit a parameter
void ASTPrintVisitor::visit(const Parameter& parameter) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Parameter");
    parentLabel = localParent;
    initNewNode(currentLabel++, parameter.getName());
}
//---------------------------------------------------------------------------
// Visit a function
void ASTPrintVisitor::visit(const Function& function) {
    out << "graph {\n";
    out << "node [shape=plaintext, ordering=out];\n";
    size_t localParent = parentLabel;
    out << "\t" << localParent << "[label=\"Function\"];\n";
    const auto& statements = function.getStatements();
    for (const auto& statement : statements) {
        parentLabel = localParent;
        statement->accept(*this);
    }
    out << "}\n";
}
//---------------------------------------------------------------------------
// Visit a statement
void ASTPrintVisitor::visit(const ASTStatement& statement) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "ASTStatement");
    const auto& expression = statement.getExpression();
    parentLabel = localParent;
    expression.accept(*this);
}
//---------------------------------------------------------------------------
// Visit an assignment
void ASTPrintVisitor::visit(const AssignmentExpr& assignmentExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Assignment");
    parentLabel = localParent;
    assignmentExpr.getLeft().accept(*this);
    parentLabel = localParent;
    initNewNode(currentLabel++, ":=");
    parentLabel = localParent;
    assignmentExpr.getRight().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a return statement
void ASTPrintVisitor::visit(const ReturnExpr& returnExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Return");
    parentLabel = localParent;
    returnExpr.getChild().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a multiplication
void ASTPrintVisitor::visit(const MulExpr& mulExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Multiplication");
    parentLabel = localParent;
    mulExpr.getLeft().accept(*this);
    parentLabel = localParent;
    initNewNode(currentLabel++, "*");
    parentLabel = localParent;
    mulExpr.getRight().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a division
void ASTPrintVisitor::visit(const DivExpr& divExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Division");
    parentLabel = localParent;
    divExpr.getLeft().accept(*this);
    parentLabel = localParent;
    initNewNode(currentLabel++, "/");
    parentLabel = localParent;
    divExpr.getRight().accept(*this);
}
//---------------------------------------------------------------------------
// Visit an addition
void ASTPrintVisitor::visit(const AddExpr& addExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Addition");
    parentLabel = localParent;
    addExpr.getLeft().accept(*this);
    parentLabel = localParent;
    initNewNode(currentLabel++, "+");
    parentLabel = localParent;
    addExpr.getRight().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a subtraction
void ASTPrintVisitor::visit(const SubtractExpr& subtractExpr) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Subtraction");
    parentLabel = localParent;
    subtractExpr.getLeft().accept(*this);
    parentLabel = localParent;
    initNewNode(currentLabel++, "-");
    parentLabel = localParent;
    subtractExpr.getRight().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a unary plus
void ASTPrintVisitor::visit(const UnaryPlus& unaryPlus) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Unary Plus");
    parentLabel = localParent;
    unaryPlus.getChild().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a unary minus
void ASTPrintVisitor::visit(const UnaryMinus& unaryMinus) {
    size_t localParent = currentLabel++;
    initNewNode(localParent, "Unary Minus");
    parentLabel = localParent;
    unaryMinus.getChild().accept(*this);
}
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
