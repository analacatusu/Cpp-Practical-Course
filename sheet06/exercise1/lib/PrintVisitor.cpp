#include "lib/PrintVisitor.hpp"
#include <iostream>
//---------------------------------------------------------------------------
namespace ast {
// Visit functions of each node
void PrintVisitor::visit(const UnaryPlus&) {
    std::cout << "+";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const UnaryMinus&) {
    std::cout << "-";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Add&) {
    std::cout << " + ";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Subtract&) {
    std::cout << " - ";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Multiply&) {
    std::cout << " * ";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Divide&) {
    std::cout << " / ";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Power&) {
    std::cout << " ^ ";
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Constant& c) {
    std::cout << c.getValue();
}
//---------------------------------------------------------------------------
void PrintVisitor::visit(const Parameter& p) {
    std::cout << "P" << p.getIndex();
}
} // namespace ast
//---------------------------------------------------------------------------
