#include "pljit/lexer/Lexer.hpp"
#include <vector>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::lexer;
//---------------------------------------------------------------------------
TEST(TestLexer, correctLexerProgram1) {
    const auto code =
        "VAR d, e;\n"
        "BEGIN\n"
        "d := 1;\n"
        "e := d + 3;\n"
        "RETURN e\n"
        "END.\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::CommaSeparator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::BeginKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::BinaryPlusOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::ReturnKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndKeyword,
                                           Token::TokenType::Dot};
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    size_t i{0};
    for (auto token = lex.next(); token.tokenType() != Token::TokenType::EndToken; token = lex.next()) {
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
        i++;
    }
}
//---------------------------------------------------------------------------
TEST(TestLexer, correctLexerProgram2) {
    const auto code =
        "PARAM a,          b    ; \n"
        "VAR d,e;\n"
        "CONST f=10;\n"
        "  BEGIN\n"
        "  d       := +(+5);\n"
        "e :=        -(f- 2);\n"
        "  RETURN   e\n"
        "END   .\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::ParamKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::CommaSeparator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::CommaSeparator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::ConstKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperatorDecl,
                                           Token::TokenType::Literal,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::BeginKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::UnaryPlusOperator,
                                           Token::TokenType::LeftParanthesis,
                                           Token::TokenType::UnaryPlusOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::RightParanthesis,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::UnaryMinusOperator,
                                           Token::TokenType::LeftParanthesis,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::BinaryMinusOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::RightParanthesis,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::ReturnKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndKeyword,
                                           Token::TokenType::Dot};

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    size_t i{0};
    for (auto token = lex.next(); token.tokenType() != Token::TokenType::EndToken; token = lex.next()) {
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
        i++;
    }
}
//---------------------------------------------------------------------------
TEST(TestLexer, correctLexerProgram3) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d123 := 2;\n"
        "RETURN d\n"
        "END.\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::BeginKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::Literal,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::ReturnKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndKeyword,
                                           Token::TokenType::Dot};

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    size_t i{0};
    for (auto token = lex.next(); token.tokenType() != Token::TokenType::EndToken; token = lex.next()) {
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
        i++;
    }
}
//---------------------------------------------------------------------------
TEST(TestLexer, correctLexerProgram4) {
    const auto code =
        "VAR d\n"
        "BEGIN\n"
        "d = 1\n"
        "undef := ((undef * 2);\n"
        "RETURN d;\n"
        "END.\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::BeginKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperatorDecl,
                                           Token::TokenType::Literal,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::LeftParanthesis,
                                           Token::TokenType::LeftParanthesis,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::MulOperator,
                                           Token::TokenType::Literal,
                                           Token::TokenType::RightParanthesis,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::ReturnKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::EndKeyword,
                                           Token::TokenType::Dot};

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    size_t i{0};
    for (auto token = lex.next(); token.tokenType() != Token::TokenType::EndToken; token = lex.next()) {
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
        i++;
    }
}
//---------------------------------------------------------------------------
TEST(TestLexer, misspelledKeyword1) {
    const auto code =
        "PARM a;\n"
        "VAR d;\n"
        "BEGIN\n"
        "d := 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    auto token = lex.next();
    ASSERT_EQ(token.tokenType(), Token::TokenType::Unexpected);
}
//---------------------------------------------------------------------------
TEST(TestLexer, misspelledKeyword2) {
    const auto code =
        "PARAM a;\n"
        "VAR d;\n"
        "BEEGIN\n"
        "d := a;\n"
        "RETURN d\n"
        "END.\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::ParamKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::Unexpected};
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    for (size_t i = 0; i < tokenTypes.size(); i++) {
        auto token = lex.next();
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
    }
}
//---------------------------------------------------------------------------
TEST(TestLexer, unknownCharacter) {
    const auto code =
        "PARAM a;\n"
        "VAR d;\n"
        "BEGIN\n"
        "d := ?a;\n"
        "RETURN ?d\n"
        "END.\n";

    vector<Token::TokenType> tokenTypes = {Token::TokenType::ParamKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::VarKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::EndLineSeparator,
                                           Token::TokenType::BeginKeyword,
                                           Token::TokenType::Identifier,
                                           Token::TokenType::AssignmentOperator,
                                           Token::TokenType::Unexpected};
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    for (size_t i = 0; i < tokenTypes.size(); i++) {
        auto token = lex.next();
        ASSERT_EQ(token.tokenType(), tokenTypes[i]);
    }
}
//---------------------------------------------------------------------------
