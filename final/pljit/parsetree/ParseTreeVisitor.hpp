#ifndef H_PLJIT_PARSETREEVISITOR
#define H_PLJIT_PARSETREEVISITOR
//---------------------------------------------------------------------------
namespace pljit::parsetree {
//---------------------------------------------------------------------------
class TerminalSymbol;
class Identifier;
class Literal;
class FunctionDefinition;
class ParameterDeclarations;
class VariableDeclarations;
class ConstantDeclarations;
class CompoundStatement;
class DeclaratorList;
class InitDeclaratorList;
class InitDeclarator;
class StatementList;
class Statement;
class AssignmentExpression;
class AdditiveExpression;
class MultiplicativeExpression;
class UnaryExpression;
class PrimaryExpression;
//---------------------------------------------------------------------------
/// Abstract class to represent a visitor
struct ParseTreeVisitor {
    /// Constructor
    ParseTreeVisitor() = default;
    /// Destructor
    virtual ~ParseTreeVisitor() = default;
    /// Visit functions
    virtual void visit(const TerminalSymbol&) = 0;
    virtual void visit(const Identifier&) = 0;
    virtual void visit(const Literal&) = 0;
    virtual void visit(const FunctionDefinition&) = 0;
    virtual void visit(const ParameterDeclarations&) = 0;
    virtual void visit(const VariableDeclarations&) = 0;
    virtual void visit(const ConstantDeclarations&) = 0;
    virtual void visit(const DeclaratorList&) = 0;
    virtual void visit(const InitDeclaratorList&) = 0;
    virtual void visit(const InitDeclarator&) = 0;
    virtual void visit(const StatementList&) = 0;
    virtual void visit(const Statement&) = 0;
    virtual void visit(const CompoundStatement&) = 0;
    virtual void visit(const AssignmentExpression&) = 0;
    virtual void visit(const AdditiveExpression&) = 0;
    virtual void visit(const MultiplicativeExpression&) = 0;
    virtual void visit(const UnaryExpression&) = 0;
    virtual void visit(const PrimaryExpression&) = 0;
};
//---------------------------------------------------------------------------
} // namespace pljit::parsetree
//---------------------------------------------------------------------------
#endif // H_PLJIT_PARSETREEVISITOR
//---------------------------------------------------------------------------
