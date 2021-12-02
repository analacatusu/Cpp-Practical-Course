#ifndef H_PLJIT_PARSER
#define H_PLJIT_PARSER
#include "pljit/lexer/Lexer.hpp"
#include "pljit/parsetree/ParseTree.hpp"
using namespace pljit::lexer;
using namespace pljit::parsetree;
//---------------------------------------------------------------------------
namespace pljit::parser {
//---------------------------------------------------------------------------
/// Class that represents the parser (MILESTONE 3)
class Parsing {
    public:
    /// Constructor
    Parsing(Lexer& lex, shared_ptr<CodeManagement> codeM) : lex(lex), codeM(move(codeM)) {}
    /// Start the parsing
    void parsing();
    /// Get the parse tree structure
    const FunctionDefinition& getTree() const { return funcDef; }
    /// Return whether an error occurred during parsing
    bool errorOccurred() const { return error; }

    private:
    /// Functions that parse a specific node from the grammer given the code
    FunctionDefinition function_definition();
    CompoundStatement compound_statement();
    ConstantDeclarations constant_declarations();
    VariableDeclarations variable_declarations();
    ParameterDeclarations parameter_declarations();
    InitDeclaratorList initdeclarator_list();
    InitDeclarator init_declarator();
    DeclaratorList declarator_list();
    StatementList statement_list();
    Statement statement();
    AssignmentExpression assignment_expression();
    AdditiveExpression additive_expression();
    MultiplicativeExpression multiplicative_expression();
    UnaryExpression unary_expression();
    PrimaryExpression primary_expression();
    Identifier identifier();
    TerminalSymbol match(Token::TokenType type);
    Literal literal();
    /// Compute the actual value of a literal
    int64_t computeVal(Reference ref);
    /// Storage of whether an error occurred during parsing
    bool error = false;
    /// Storage of the lexer
    Lexer lex;
    /// Storage of the code management unit
    shared_ptr<CodeManagement> codeM;
    /// Storage of the parse tree
    FunctionDefinition funcDef;
    /// Storage of the current token from the lexer
    Token currentToken;
};
//---------------------------------------------------------------------------
} // namespace pljit::parser
//---------------------------------------------------------------------------
#endif //H_PLJIT_PARSER
//---------------------------------------------------------------------------
