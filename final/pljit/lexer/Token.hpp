#ifndef H_PLJIT_TOKEN
#define H_PLJIT_TOKEN
#include "pljit/codem/Reference.hpp"
using namespace std;
using namespace pljit::codemanagement;
//---------------------------------------------------------------------------
namespace pljit::lexer {
//---------------------------------------------------------------------------
/// struct that represents a token
struct Token {
    /// enum that lists all possible token types
    enum TokenType {
        ReturnKeyword,
        EndKeyword,
        VarKeyword,
        ConstKeyword,
        ParamKeyword,
        BeginKeyword,
        Identifier,
        CommaSeparator,
        EndLineSeparator,
        Literal,
        UnaryPlusOperator,
        UnaryMinusOperator,
        BinaryPlusOperator,
        BinaryMinusOperator,
        MulOperator,
        DivOperator,
        AssignmentOperator,
        AssignmentOperatorDecl,
        LeftParanthesis,
        RightParanthesis,
        Dot,
        Unexpected,
        EndToken
    };
    /// Constructors
    Token() = default;
    Token(TokenType type, Reference ref) : type(type), ref(ref) {}
    /// Getters
    TokenType tokenType() const { return type; }
    Reference reference() const { return ref; }

    private:
    /// Storage of the type
    TokenType type = EndToken;
    /// Storage of the reference within the code
    Reference ref;
};
//---------------------------------------------------------------------------
} // namespace pljit::lexer
//---------------------------------------------------------------------------
#endif // H_PLJIT_TOKEN
//---------------------------------------------------------------------------
