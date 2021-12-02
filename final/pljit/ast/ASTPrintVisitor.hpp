#ifndef H_PLJIT_ASTPRINTVISITOR
#define H_PLJIT_ASTPRINTVISITOR
#include "pljit/ast/AST.hpp"
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
/// Class that implements a Print Visitor
struct ASTPrintVisitor : ASTVisitor {
    /// Constructor
    explicit ASTPrintVisitor(ostream& out) : out(out) {}
    /// Destructor
    ~ASTPrintVisitor() override {}
    /// Visit functions
    void visit(const Constant&) override;
    void visit(const Parameter&) override;
    void visit(const Function&) override;
    void visit(const ASTStatement&) override;
    void visit(const AssignmentExpr&) override;
    void visit(const ReturnExpr&) override;
    void visit(const MulExpr&) override;
    void visit(const DivExpr&) override;
    void visit(const AddExpr&) override;
    void visit(const SubtractExpr&) override;
    void visit(const UnaryPlus&) override;
    void visit(const UnaryMinus&) override;

    private:
    /// Storage of the dot file
    ostream& out;
    /// Storage of the labels in the dot file
    size_t currentLabel = 1;
    size_t parentLabel = 0;
    /// Construct a new node
    void initNewNode(size_t localParent, string_view str);
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
#endif // H_PLJIT_ASTPRINTVISITOR
//---------------------------------------------------------------------------
