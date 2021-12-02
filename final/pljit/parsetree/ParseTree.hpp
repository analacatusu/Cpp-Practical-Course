#ifndef H_PLJIT_PARSETREE
#define H_PLJIT_PARSETREE
#include "pljit/codem/Reference.hpp"
#include "pljit/parsetree/ParseTreeVisitor.hpp"
#include <memory>
#include <vector>
using namespace std;
using namespace pljit::codemanagement;
//---------------------------------------------------------------------------
namespace pljit::parsetree {
//---------------------------------------------------------------------------
/// class to represent a node in the parse tree (MILESTONE 3)
class ParseTreeNode {
    public:
    /// All possible ParseTree nodes based on the given grammer
    enum class Type {
        TerminalSymbol,
        Identifier,
        Literal,
        FunctionDefinition,
        ParameterDeclarations,
        VariableDeclarations,
        ConstantDeclarations,
        CompoundStatement,
        DeclaratorList,
        InitDeclaratorList,
        InitDeclarator,
        StatementList,
        Statement,
        AssignmentExpression,
        AdditiveExpression,
        MultiplicativeExpression,
        UnaryExpression,
        PrimaryExpression
    };
    /// Constructors
    ParseTreeNode() = default;
    explicit ParseTreeNode(Reference ref) : ref(ref) {}
    explicit ParseTreeNode(bool error) : error(error) {}
    /// Destructor
    virtual ~ParseTreeNode() = default;
    /// Get the type of the ParseTree node
    virtual ParseTreeNode::Type getType() const = 0;
    /// Accept the visitor
    virtual void accept(ParseTreeVisitor&) const = 0;
    /// Getters
    bool errorOccurred() const { return error; }
    const Reference& reference() const { return ref; }

    protected:
    /// Storage of the occurrence of an error
    bool error = false;
    /// Storage of the reference of a node
    Reference ref;
};
//---------------------------------------------------------------------------
class Literal : public ParseTreeNode {
    public:
    /// Constructors
    Literal() = default;
    explicit Literal(bool error);
    Literal(Reference ref, int64_t val, bool succ);
    /// Overriden function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::Literal; }
    /// Getters
    bool success() const { return succ; }
    int64_t value() const { return val; }
    /// Overriden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the value
    int64_t val = 0;
    /// Indicates if the parsing process was a success or not
    bool succ = false;
};
//---------------------------------------------------------------------------
class TerminalSymbol : public ParseTreeNode {
    public:
    /// Constructor
    TerminalSymbol() = default;
    explicit TerminalSymbol(bool error);
    TerminalSymbol(Reference ref, bool succ);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::TerminalSymbol; }
    /// Getters
    //const Reference& reference() const { return ref; }
    bool success() const { return succ; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Indicates if the parsing process was a success or not
    bool succ = false;
};
//---------------------------------------------------------------------------
class Identifier : public ParseTreeNode {
    public:
    /// Constructors
    Identifier() = default;
    explicit Identifier(bool error);
    Identifier(Reference ref, bool succ);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::Identifier; }
    /// Getters
    bool success() const { return succ; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Indicates if the parsing process was a success or not
    bool succ = false;
};
//---------------------------------------------------------------------------
class PrimaryExpression : public ParseTreeNode {
    public:
    /// Constructors
    PrimaryExpression() = default;
    explicit PrimaryExpression(bool error);
    PrimaryExpression(Reference ref, ParseTreeNode::Type data, vector<shared_ptr<ParseTreeNode>> children);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::PrimaryExpression; }
    /// Getters
    const ParseTreeNode::Type& getData() const { return data; }
    const vector<shared_ptr<ParseTreeNode>>& getChildren() const { return children; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the type of the primary expression
    ParseTreeNode::Type data;
    /// Storage of the different children
    vector<shared_ptr<ParseTreeNode>> children;
};
//---------------------------------------------------------------------------
class UnaryExpression : public ParseTreeNode {
    public:
    /// Constructors
    UnaryExpression() = default;
    explicit UnaryExpression(bool error);
    UnaryExpression(Reference ref, optional<TerminalSymbol> terminalSymbol, PrimaryExpression primaryExpression);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::UnaryExpression; }
    /// Getters
    const optional<TerminalSymbol>& getTerminalSymbol() const { return terminalSymbol; }
    const PrimaryExpression& getPrimaryExpression() const { return primaryExpression; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the terminal symbol (+/-)
    optional<TerminalSymbol> terminalSymbol;
    /// Storage of the primary expression
    PrimaryExpression primaryExpression;
};
//---------------------------------------------------------------------------
class MultiplicativeExpression : public ParseTreeNode {
    public:
    /// Constructors
    MultiplicativeExpression() = default;
    MultiplicativeExpression(Reference ref, UnaryExpression unaryExpression, optional<TerminalSymbol> terminalSymbol, optional<shared_ptr<MultiplicativeExpression>> mulExpr);
    explicit MultiplicativeExpression(bool error);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::MultiplicativeExpression; }
    /// Getters
    const UnaryExpression& getUnaryExpression() const { return unaryExpression; }
    const optional<TerminalSymbol>& getTerminalSymbol() const { return terminalSymbol; }
    const optional<shared_ptr<MultiplicativeExpression>>& getMultiplicativeExpression() const { return mulExpr; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the unary expression
    UnaryExpression unaryExpression;
    /// Storage of the terminal symbol (* / '/')
    optional<TerminalSymbol> terminalSymbol;
    /// Storage of the multiplicative expression
    optional<shared_ptr<MultiplicativeExpression>> mulExpr;
};
//---------------------------------------------------------------------------
class AdditiveExpression : public ParseTreeNode {
    public:
    /// Constructors
    AdditiveExpression() = default;
    AdditiveExpression(Reference ref, MultiplicativeExpression multiplicativeExpression, optional<TerminalSymbol> terminalSymbol, optional<shared_ptr<AdditiveExpression>> addExpr);
    explicit AdditiveExpression(bool error);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::AdditiveExpression; }
    /// Getters
    const MultiplicativeExpression& getMultiplicativeExpression() const { return multiplicativeExpression; }
    const optional<TerminalSymbol>& getTerminalSymbol() const { return terminalSymbol; }
    const optional<shared_ptr<AdditiveExpression>>& getAdditiveExpression() const { return addExpr; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the multiplicative expression
    MultiplicativeExpression multiplicativeExpression;
    /// Storage of the terminal symbol (+/-)
    optional<TerminalSymbol> terminalSymbol;
    /// Storage of the additive expression
    optional<shared_ptr<AdditiveExpression>> addExpr;
};
//---------------------------------------------------------------------------
class AssignmentExpression : public ParseTreeNode {
    public:
    /// Constructors
    AssignmentExpression() = default;
    explicit AssignmentExpression(bool error);
    AssignmentExpression(Identifier id, TerminalSymbol assignment, AdditiveExpression additiveExpression, Reference ref);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::AssignmentExpression; }
    /// Getters
    const Identifier& getIdentifier() const { return id; }
    const TerminalSymbol& getAssignment() const { return assignment; }
    const AdditiveExpression& getAdditiveExpr() const { return additiveExpression; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the identifier
    Identifier id;
    /// Storage of the assignment operator :=
    TerminalSymbol assignment;
    /// Storage of the additive expression
    AdditiveExpression additiveExpression;
};
//---------------------------------------------------------------------------
class Statement : public ParseTreeNode {
    public:
    /// Constructors
    Statement() = default;
    explicit Statement(bool error);
    Statement(Reference ref, ParseTreeNode::Type data, vector<shared_ptr<ParseTreeNode>> children);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::Statement; }
    /// Getters
    const ParseTreeNode::Type& getData() const { return data; }
    const vector<shared_ptr<ParseTreeNode>>& getChildren() const { return children; }
    //const Reference& reference() const { return ref; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the different data types of the node
    ParseTreeNode::Type data;
    /// Storage of the children of the node
    vector<shared_ptr<ParseTreeNode>> children;
};
//---------------------------------------------------------------------------
class StatementList : public ParseTreeNode {
    public:
    /// Constructors
    StatementList() = default;
    explicit StatementList(bool error);
    StatementList(Reference ref, Statement statement, vector<pair<TerminalSymbol, Statement>> children);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::StatementList; }
    /// Getters
    const Statement& getStatement() const { return statement; }
    const vector<pair<TerminalSymbol, Statement>>& getChildren() const { return children; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of a statement
    Statement statement;
    /// Storage of possible following statements
    vector<pair<TerminalSymbol, Statement>> children;
};
//---------------------------------------------------------------------------
class DeclaratorList : public ParseTreeNode {
    public:
    /// Constructors
    DeclaratorList() = default;
    explicit DeclaratorList(bool error);
    DeclaratorList(Reference ref, Identifier identifier, vector<pair<TerminalSymbol, Identifier>> children);
    /// Overriden function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::DeclaratorList; }
    /// Getters
    const Identifier& getIdentifier() const { return identifier; }
    const vector<pair<TerminalSymbol, Identifier>>& getChildren() const { return children; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of an identifier
    Identifier identifier;
    /// Storage of possible following indentifiers
    vector<pair<TerminalSymbol, Identifier>> children;
};
//---------------------------------------------------------------------------
class InitDeclarator : public ParseTreeNode {
    public:
    /// Constructors
    InitDeclarator() = default;
    explicit InitDeclarator(bool error);
    InitDeclarator(Identifier identifier, TerminalSymbol equals, Literal literal, Reference ref);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::InitDeclarator; }
    /// Getters
    const Identifier& getIdentifier() const { return identifier; }
    const TerminalSymbol& getEquals() const { return equals; }
    const Literal& getLiteral() const { return literal; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of an identifier
    Identifier identifier;
    /// Storage of the equals operator ( = )
    TerminalSymbol equals;
    /// Storage of a literal
    Literal literal;
};
//---------------------------------------------------------------------------
class InitDeclaratorList : public ParseTreeNode {
    public:
    /// Constructors
    InitDeclaratorList() = default;
    explicit InitDeclaratorList(bool error);
    InitDeclaratorList(Reference ref, InitDeclarator initDeclarator, vector<pair<TerminalSymbol, InitDeclarator>> children);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::InitDeclaratorList; }
    /// Getters
    const InitDeclarator& getInitDecl() const { return initDeclarator; }
    const vector<pair<TerminalSymbol, InitDeclarator>> getChildren() const { return children; }
    //const Reference& reference() const { return ref; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of an init declarator
    InitDeclarator initDeclarator;
    /// Storage of possible following init declarators
    vector<pair<TerminalSymbol, InitDeclarator>> children;
};
//---------------------------------------------------------------------------
class Declarations : public ParseTreeNode {
    public:
    /// Constructors
    Declarations() = default;
    Declarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref);
    explicit Declarations(bool error);
    /// Getters
    const TerminalSymbol& getBegin() const { return begin; }
    const DeclaratorList& getDeclList() const { return declaratorList; }
    const TerminalSymbol& getEndLine() const { return endLine; }

    protected:
    /// Storage of a terminal symbol that represents a keyword
    TerminalSymbol begin;
    /// Storage of the declarator list
    DeclaratorList declaratorList;
    /// Storage of the endline terminal symbol ( ; )
    TerminalSymbol endLine;
};
//---------------------------------------------------------------------------
class ParameterDeclarations : public Declarations {
    public:
    /// Constructors
    ParameterDeclarations() = default;
    explicit ParameterDeclarations(bool error);
    ParameterDeclarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::ParameterDeclarations; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;
};

class VariableDeclarations : public Declarations {
    public:
    /// Constructors
    VariableDeclarations() = default;
    explicit VariableDeclarations(bool error);
    VariableDeclarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::VariableDeclarations; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;
};
//---------------------------------------------------------------------------
class ConstantDeclarations : public ParseTreeNode {
    public:
    /// Constructors
    ConstantDeclarations() = default;
    explicit ConstantDeclarations(bool error);
    ConstantDeclarations(TerminalSymbol constant, InitDeclaratorList initDeclaratorList, TerminalSymbol endLine, Reference ref);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::ConstantDeclarations; }
    /// Getters
    const TerminalSymbol& getConstant() const { return constant; }
    const InitDeclaratorList& getInitDeclaratorList() const { return initDeclaratorList; }
    const TerminalSymbol& getEndLine() const { return endLine; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of a terminal symbol
    TerminalSymbol constant;
    /// Storage of the init declarator list
    InitDeclaratorList initDeclaratorList;
    /// Storage of the endline symbol ( ; )
    TerminalSymbol endLine;
};
//---------------------------------------------------------------------------
class CompoundStatement : public ParseTreeNode {
    public:
    /// Constructors
    CompoundStatement() = default;
    explicit CompoundStatement(bool error);
    CompoundStatement(Reference ref, TerminalSymbol begin, StatementList statementList, TerminalSymbol end);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::CompoundStatement; }
    /// Getters
    const TerminalSymbol& getBegin() const { return begin; }
    const StatementList& getStatementList() const { return statementList; }
    const TerminalSymbol& getEnd() const { return end; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of a terminal symbol that represents a keyword
    TerminalSymbol begin;
    /// Storage of a statement list
    StatementList statementList;
    /// Storage of a terminal symbol that represents a keyword
    TerminalSymbol end;
};
//---------------------------------------------------------------------------
class FunctionDefinition : public ParseTreeNode {
    public:
    /// Constructors
    FunctionDefinition() = default;
    explicit FunctionDefinition(bool error);
    FunctionDefinition(Reference ref, optional<ParameterDeclarations> paramDecl, optional<VariableDeclarations> varDecl, optional<ConstantDeclarations> constDecl, CompoundStatement compoundStatement, TerminalSymbol dot);
    /// Overridden getType function
    ParseTreeNode::Type getType() const override { return ParseTreeNode::Type::FunctionDefinition; }
    /// Getters
    const optional<ParameterDeclarations>& getParamDeclarations() const { return paramDecl; }
    const optional<VariableDeclarations>& getVariableDeclarations() const { return varDecl; }
    const optional<ConstantDeclarations>& getConstantDeclarations() const { return constDecl; }
    const CompoundStatement& getCompoundStatement() const { return compoundStatement; }
    const TerminalSymbol& getDot() const { return dot; }
    const Reference& reference() const { return ref; }
    /// Overridden accept function
    void accept(ParseTreeVisitor& visitor) const override;

    private:
    /// Storage of the parameter declarations
    optional<ParameterDeclarations> paramDecl;
    /// Storage of the variable declarations
    optional<VariableDeclarations> varDecl;
    /// Storage of the constant declarations
    optional<ConstantDeclarations> constDecl;
    /// Storage of the compound statement
    CompoundStatement compoundStatement;
    /// Storage of a terminal symbol ( . )
    TerminalSymbol dot;
};
//---------------------------------------------------------------------------
} // namespace pljit::parsetree
//---------------------------------------------------------------------------
#endif // H_PLJIT_PARSETREE
//---------------------------------------------------------------------------
