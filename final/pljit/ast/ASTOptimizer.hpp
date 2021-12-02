#ifndef H_PLJIT_ASTOPTIMIZER
#define H_PLJIT_ASTOPTIMIZER
#include <memory>
using namespace std;
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
class ASTNode;
/// Struct that represents a virtual optimizer for an ast node (MILESTONE 5)
struct ASTOptimizer {
    /// Constructor
    ASTOptimizer() = default;
    /// Destructor
    virtual ~ASTOptimizer() = default;
    /// Virtual visit functions
    virtual unique_ptr<ASTNode> visit(Constant&) = 0;
    virtual unique_ptr<ASTNode> visit(Parameter&) = 0;
    virtual unique_ptr<ASTNode> visit(Function&) = 0;
    virtual unique_ptr<ASTNode> visit(ASTStatement&) = 0;
    virtual unique_ptr<ASTNode> visit(AssignmentExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(ReturnExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(MulExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(DivExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(AddExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(SubtractExpr&) = 0;
    virtual unique_ptr<ASTNode> visit(UnaryPlus&) = 0;
    virtual unique_ptr<ASTNode> visit(UnaryMinus&) = 0;
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
//---------------------------------------------------------------------------
#endif // H_PLJIT_ASTOPTIMIZER
//---------------------------------------------------------------------------
