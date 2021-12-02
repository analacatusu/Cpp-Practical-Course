#ifndef H_lib_PrintVisitor
#define H_lib_PrintVisitor
#include "lib/AST.hpp"
//---------------------------------------------------------------------------
namespace ast {
/// Class to print the AST
struct PrintVisitor : ASTVisitor {
    /// Constructor
    PrintVisitor() : ASTVisitor() {}
    /// Destructor
    ~PrintVisitor() override = default;
    /// Visit functions of each node
    void visit(const UnaryPlus&) override;
    void visit(const UnaryMinus&) override;
    void visit(const Add&) override;
    void visit(const Subtract&) override;
    void visit(const Multiply&) override;
    void visit(const Divide&) override;
    void visit(const Power&) override;
    void visit(const Constant& c) override;
    void visit(const Parameter& p) override;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
