#ifndef H_PLJIT_PARSETREEPRINTVISITOR
#define H_PLJIT_PARSETREEPRINTVISITOR
#include "pljit/codem/CodeManagement.hpp"
#include "pljit/parsetree/ParseTree.hpp"
#include <ostream>
//---------------------------------------------------------------------------
namespace pljit::parsetree {
//---------------------------------------------------------------------------
/// Class that implements a Print Visitor
struct ParseTreePrintVisitor : ParseTreeVisitor {
    /// Constructor
    ParseTreePrintVisitor(ostream& out, shared_ptr<CodeManagement> codeM) : out(out), codeM(move(codeM)) {}
    /// Destructor
    ~ParseTreePrintVisitor() override {}
    /// Visit functions
    void visit(const TerminalSymbol&) override;
    void visit(const Identifier&) override;
    void visit(const Literal&) override;
    void visit(const FunctionDefinition&) override;
    void visit(const ParameterDeclarations&) override;
    void visit(const VariableDeclarations&) override;
    void visit(const ConstantDeclarations&) override;
    void visit(const DeclaratorList&) override;
    void visit(const InitDeclaratorList&) override;
    void visit(const InitDeclarator&) override;
    void visit(const StatementList&) override;
    void visit(const Statement&) override;
    void visit(const CompoundStatement&) override;
    void visit(const AssignmentExpression&) override;
    void visit(const AdditiveExpression&) override;
    void visit(const MultiplicativeExpression&) override;
    void visit(const UnaryExpression&) override;
    void visit(const PrimaryExpression&) override;

    private:
    /// Storage of the dot file
    ostream& out;
    /// Storage of the Code Management unit
    shared_ptr<CodeManagement> codeM;
    /// Storage of label numbers in the dot file
    size_t currentLabel = 1;
    size_t parentLabel = 0;
    /// Draw a new node
    void initNewNode(size_t localParent, string_view str);
};
//---------------------------------------------------------------------------
} // namespace pljit::parsetree
//---------------------------------------------------------------------------
#endif //H_PLJIT_PARSETREEPRINTVISITOR
//---------------------------------------------------------------------------
