#ifndef H_PLJIT_ASTVISITOR
#define H_PLJIT_ASTVISITOR
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
class Constant;
class Parameter;
class Function;
class ASTStatement;
class AssignmentExpr;
class ReturnExpr;
class MulExpr;
class DivExpr;
class AddExpr;
class SubtractExpr;
class UnaryPlus;
class UnaryMinus;
/// Abstract class that represents a Visitor
struct ASTVisitor {
    /// Constructor
    ASTVisitor() = default;
    /// Destructor
    virtual ~ASTVisitor() = default;
    /// Virtual visit functions
    virtual void visit(const Constant&) = 0;
    virtual void visit(const Parameter&) = 0;
    virtual void visit(const Function&) = 0;
    virtual void visit(const ASTStatement&) = 0;
    virtual void visit(const AssignmentExpr&) = 0;
    virtual void visit(const ReturnExpr&) = 0;
    virtual void visit(const MulExpr&) = 0;
    virtual void visit(const DivExpr&) = 0;
    virtual void visit(const AddExpr&) = 0;
    virtual void visit(const SubtractExpr&) = 0;
    virtual void visit(const UnaryPlus&) = 0;
    virtual void visit(const UnaryMinus&) = 0;
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
#endif // H_PLJIT_ASTVISITOR
//---------------------------------------------------------------------------
