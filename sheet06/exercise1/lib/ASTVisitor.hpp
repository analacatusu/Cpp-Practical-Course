#ifndef H_lib_ASTVisitor
#define H_lib_ASTVisitor
//---------------------------------------------------------------------------
namespace ast {
/// Forward declarations of the nodes
class UnaryPlus;
class UnaryMinus;
class Add;
class Subtract;
class Multiply;
class Divide;
class Power;
class Constant;
class Parameter;

/// Class that implements visitor pattern
struct ASTVisitor {
    /// Constructor
    ASTVisitor() = default;
    /// Destructor
    virtual ~ASTVisitor() = default;
    /// Visit functions of each node
    virtual void visit(const UnaryPlus&) = 0;
    virtual void visit(const UnaryMinus&) = 0;
    virtual void visit(const Add&) = 0;
    virtual void visit(const Subtract&) = 0;
    virtual void visit(const Multiply&) = 0;
    virtual void visit(const Divide&) = 0;
    virtual void visit(const Power&) = 0;
    virtual void visit(const Constant&) = 0;
    virtual void visit(const Parameter&) = 0;
};
} // namespace ast
//---------------------------------------------------------------------------
#endif
