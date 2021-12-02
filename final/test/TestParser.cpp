#include "pljit/parser/Parser.hpp"
#include "pljit/parsetree/ParseTree.hpp"
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::parser;
//---------------------------------------------------------------------------
TEST(TestParser, correctParserProgram1) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    const auto& funcDef = parser.getTree();

    ASSERT_FALSE(funcDef.getParamDeclarations().has_value());
    ASSERT_FALSE(funcDef.getConstantDeclarations().has_value());
    ASSERT_TRUE(funcDef.getVariableDeclarations().has_value());
    ASSERT_EQ(codeM->getCharacters(funcDef.getDot().reference()), ".");

    const auto& varDecl = funcDef.getVariableDeclarations();
    const auto& begin = varDecl->getBegin();
    const auto& declList = varDecl->getDeclList();
    const auto& endLine = varDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(begin.reference()), "VAR");

    const auto& var = declList.getIdentifier();
    const auto& children = declList.getChildren();

    ASSERT_TRUE(children.empty());
    ASSERT_EQ(codeM->getCharacters(var.reference()), "d");
    ASSERT_EQ(codeM->getCharacters(endLine.reference()), ";");

    const auto& compoundStatement = funcDef.getCompoundStatement();
    const auto& beginKeyword = compoundStatement.getBegin();

    ASSERT_EQ(codeM->getCharacters(beginKeyword.reference()), "BEGIN");

    const auto& endKeyword = compoundStatement.getEnd();
    ASSERT_EQ(codeM->getCharacters(endKeyword.reference()), "END");

    const auto& statementList = compoundStatement.getStatementList();

    const auto& statement = statementList.getStatement().getChildren();
    const auto& statementChildren = statementList.getChildren();

    ASSERT_TRUE(statement.size() == 1);
    ASSERT_TRUE(statement[0]->getType() == ParseTreeNode::Type::AssignmentExpression);
    ASSERT_TRUE(statementChildren.size() == 1);

    AssignmentExpression* assignmentExpression = static_cast<AssignmentExpression*>(statement[0].get());
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getIdentifier().reference()), "d");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAssignment().reference()), ":=");

    Literal* literal = static_cast<Literal*>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression().getChildren()[0].get());

    ASSERT_EQ(codeM->getCharacters((literal->reference())), "1");

    const auto& returnStatement = statementChildren[0].second;
    ASSERT_EQ(codeM->getCharacters(returnStatement.reference()), "RETURN d\n");
}
//---------------------------------------------------------------------------
TEST(TestParser, correctParserProgram2) {
    const auto code =
        "PARAM a, b, c;\n"
        "VAR d;\n"
        "CONST f = 1;\n"
        "BEGIN\n"
        "d := f + (-1);\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    const auto& funcDef = parser.getTree();

    ASSERT_TRUE(funcDef.getParamDeclarations().has_value());
    ASSERT_TRUE(funcDef.getConstantDeclarations().has_value());
    ASSERT_TRUE(funcDef.getVariableDeclarations().has_value());
    ASSERT_EQ(codeM->getCharacters(funcDef.getDot().reference()), ".");

    const auto& paramDecl = funcDef.getParamDeclarations();
    const auto& beginParam = paramDecl->getBegin();
    const auto& declListParam = paramDecl->getDeclList();
    const auto& endLineParam = paramDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(beginParam.reference()), "PARAM");

    const auto& param = declListParam.getIdentifier();
    const auto& childrenParam = declListParam.getChildren();

    ASSERT_TRUE(childrenParam.size() == 2);
    ASSERT_EQ(codeM->getCharacters(param.reference()), "a");
    ASSERT_EQ(codeM->getCharacters(childrenParam[0].second.reference()), "b");
    ASSERT_EQ(codeM->getCharacters(childrenParam[1].second.reference()), "c");
    ASSERT_EQ(codeM->getCharacters(endLineParam.reference()), ";");

    const auto& constDecl = funcDef.getConstantDeclarations();
    const auto& beginConst = constDecl->getConstant();
    const auto& declListConst = constDecl->getInitDeclaratorList();
    const auto& endLineConst = constDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(beginConst.reference()), "CONST");

    const auto& constant = declListConst.getInitDecl().getIdentifier();
    const auto& childrenConst = declListConst.getChildren();

    ASSERT_TRUE(childrenConst.empty());
    ASSERT_EQ(codeM->getCharacters(constant.reference()), "f");
    ASSERT_EQ(codeM->getCharacters(endLineConst.reference()), ";");

    const auto& varDecl = funcDef.getVariableDeclarations();
    const auto& beginVar = varDecl->getBegin();
    const auto& declListVar = varDecl->getDeclList();
    const auto& endLineVar = varDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(beginVar.reference()), "VAR");

    const auto& var = declListVar.getIdentifier();
    const auto& children = declListVar.getChildren();

    ASSERT_TRUE(children.empty());
    ASSERT_EQ(codeM->getCharacters(var.reference()), "d");
    ASSERT_EQ(codeM->getCharacters(endLineVar.reference()), ";");

    const auto& compoundStatement = funcDef.getCompoundStatement();
    const auto& beginKeyword = compoundStatement.getBegin();

    ASSERT_EQ(codeM->getCharacters(beginKeyword.reference()), "BEGIN");

    const auto& endKeyword = compoundStatement.getEnd();
    ASSERT_EQ(codeM->getCharacters(endKeyword.reference()), "END");

    const auto& statementList = compoundStatement.getStatementList();

    const auto& statement = statementList.getStatement().getChildren();
    const auto& statementChildren = statementList.getChildren();

    ASSERT_TRUE(statement.size() == 1);
    ASSERT_TRUE(statement[0]->getType() == ParseTreeNode::Type::AssignmentExpression);
    ASSERT_TRUE(statementChildren.size() == 1);

    AssignmentExpression* assignmentExpression = static_cast<AssignmentExpression*>(statement[0].get());
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getIdentifier().reference()), "d");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAssignment().reference()), ":=");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAdditiveExpr().reference()), "f + (-1)");

    Identifier* identifier = static_cast<Identifier*>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression().getChildren()[0].get());
    ASSERT_EQ(codeM->getCharacters(identifier->reference()), "f");
    ASSERT_TRUE(assignmentExpression->getAdditiveExpr().getAdditiveExpression().has_value());

    PrimaryExpression primary = static_cast<PrimaryExpression>(assignmentExpression->getAdditiveExpr().getAdditiveExpression()->get()->getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression());
    ASSERT_EQ(codeM->getCharacters(primary.reference()), "(-1)");

    const auto& returnStatement = statementChildren[0].second;
    ASSERT_EQ(codeM->getCharacters(returnStatement.reference()), "RETURN d\n");
}
//---------------------------------------------------------------------------
TEST(TestParser, correctParserProgram3) {
    const auto code =
        "PARAM a;\n"
        "VAR d;\n"
        "CONST f = 10, e = 2;\n"
        "BEGIN\n"
        "d := f - e - a;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    const auto& funcDef = parser.getTree();

    ASSERT_TRUE(funcDef.getParamDeclarations().has_value());
    ASSERT_TRUE(funcDef.getConstantDeclarations().has_value());
    ASSERT_TRUE(funcDef.getVariableDeclarations().has_value());
    ASSERT_EQ(codeM->getCharacters(funcDef.getDot().reference()), ".");

    const auto& paramDecl = funcDef.getParamDeclarations();
    const auto& beginParam = paramDecl->getBegin();
    const auto& declListParam = paramDecl->getDeclList();
    const auto& endLineParam = paramDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(beginParam.reference()), "PARAM");

    const auto& param = declListParam.getIdentifier();
    const auto& childrenParam = declListParam.getChildren();

    ASSERT_TRUE(childrenParam.empty());
    ASSERT_EQ(codeM->getCharacters(param.reference()), "a");
    ASSERT_EQ(codeM->getCharacters(endLineParam.reference()), ";");

    const auto& constDecl = funcDef.getConstantDeclarations();
    const auto& beginConst = constDecl->getConstant();
    const auto& declListConst = constDecl->getInitDeclaratorList();
    const auto& endLineConst = constDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(beginConst.reference()), "CONST");

    const auto& constant = declListConst.getInitDecl().getIdentifier();
    const auto& childrenConst = declListConst.getChildren();

    ASSERT_TRUE(childrenConst.size() == 1);
    ASSERT_EQ(codeM->getCharacters(constant.reference()), "f");
    ASSERT_EQ(codeM->getCharacters(childrenConst[0].second.getIdentifier().reference()), "e");
    ASSERT_EQ(codeM->getCharacters(endLineConst.reference()), ";");

    const auto& varDecl = funcDef.getVariableDeclarations();
    const auto& begin = varDecl->getBegin();
    const auto& declList = varDecl->getDeclList();
    const auto& endLine = varDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(begin.reference()), "VAR");

    const auto& var = declList.getIdentifier();
    const auto& children = declList.getChildren();

    ASSERT_TRUE(children.empty());
    ASSERT_EQ(codeM->getCharacters(var.reference()), "d");
    ASSERT_EQ(codeM->getCharacters(endLine.reference()), ";");

    const auto& compoundStatement = funcDef.getCompoundStatement();
    const auto& beginKeyword = compoundStatement.getBegin();

    ASSERT_EQ(codeM->getCharacters(beginKeyword.reference()), "BEGIN");

    const auto& endKeyword = compoundStatement.getEnd();
    ASSERT_EQ(codeM->getCharacters(endKeyword.reference()), "END");

    const auto& statementList = compoundStatement.getStatementList();

    const auto& statement = statementList.getStatement().getChildren();
    const auto& statementChildren = statementList.getChildren();

    ASSERT_TRUE(statement.size() == 1);
    ASSERT_TRUE(statement[0]->getType() == ParseTreeNode::Type::AssignmentExpression);
    ASSERT_TRUE(statementChildren.size() == 1);

    AssignmentExpression* assignmentExpression = static_cast<AssignmentExpression*>(statement[0].get());
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getIdentifier().reference()), "d");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAssignment().reference()), ":=");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAdditiveExpr().reference()), "f - e - a");

    Identifier* identifier = static_cast<Identifier*>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression().getChildren()[0].get());
    ASSERT_EQ(codeM->getCharacters(identifier->reference()), "f");
    ASSERT_TRUE(assignmentExpression->getAdditiveExpr().getAdditiveExpression().has_value());

    PrimaryExpression left = static_cast<PrimaryExpression>(assignmentExpression->getAdditiveExpr().getAdditiveExpression()->get()->getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression());

    ASSERT_EQ(codeM->getCharacters(left.reference()), "e");

    PrimaryExpression right = static_cast<PrimaryExpression>(assignmentExpression->getAdditiveExpr().getAdditiveExpression()->get()->getAdditiveExpression()->get()->getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression());

    ASSERT_EQ(codeM->getCharacters(right.reference()), "a");

    const auto& returnStatement = statementChildren[0].second;
    ASSERT_EQ(codeM->getCharacters(returnStatement.reference()), "RETURN d\n");
}
//---------------------------------------------------------------------------
TEST(TestParser, correctParserProgram4) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 1 * 2 / ((+(3)));\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    const auto& funcDef = parser.getTree();

    ASSERT_FALSE(funcDef.getParamDeclarations().has_value());
    ASSERT_FALSE(funcDef.getConstantDeclarations().has_value());
    ASSERT_TRUE(funcDef.getVariableDeclarations().has_value());
    ASSERT_EQ(codeM->getCharacters(funcDef.getDot().reference()), ".");

    const auto& varDecl = funcDef.getVariableDeclarations();
    const auto& begin = varDecl->getBegin();
    const auto& declList = varDecl->getDeclList();
    const auto& endLine = varDecl->getEndLine();

    ASSERT_EQ(codeM->getCharacters(begin.reference()), "VAR");

    const auto& var = declList.getIdentifier();
    const auto& children = declList.getChildren();

    ASSERT_TRUE(children.empty());
    ASSERT_EQ(codeM->getCharacters(var.reference()), "d");
    ASSERT_EQ(codeM->getCharacters(endLine.reference()), ";");

    const auto& compoundStatement = funcDef.getCompoundStatement();
    const auto& beginKeyword = compoundStatement.getBegin();

    ASSERT_EQ(codeM->getCharacters(beginKeyword.reference()), "BEGIN");

    const auto& endKeyword = compoundStatement.getEnd();
    ASSERT_EQ(codeM->getCharacters(endKeyword.reference()), "END");

    const auto& statementList = compoundStatement.getStatementList();

    const auto& statement = statementList.getStatement().getChildren();
    const auto& statementChildren = statementList.getChildren();

    ASSERT_TRUE(statement.size() == 1);
    ASSERT_TRUE(statement[0]->getType() == ParseTreeNode::Type::AssignmentExpression);
    ASSERT_TRUE(statementChildren.size() == 1);

    AssignmentExpression* assignmentExpression = static_cast<AssignmentExpression*>(statement[0].get());
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getIdentifier().reference()), "d");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAssignment().reference()), ":=");
    ASSERT_EQ(codeM->getCharacters(assignmentExpression->getAdditiveExpr().reference()), "1 * 2 / ((+(3)))");

    Literal* literal = static_cast<Literal*>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression().getChildren()[0].get());
    ASSERT_EQ(codeM->getCharacters(literal->reference()), "1");

    PrimaryExpression left = static_cast<PrimaryExpression>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getMultiplicativeExpression()->get()->getUnaryExpression().getPrimaryExpression());

    ASSERT_EQ(codeM->getCharacters(left.reference()), "2");

    PrimaryExpression right = static_cast<PrimaryExpression>(assignmentExpression->getAdditiveExpr().getMultiplicativeExpression().getMultiplicativeExpression()->get()->getMultiplicativeExpression()->get()->getUnaryExpression().getPrimaryExpression());

    ASSERT_EQ(codeM->getCharacters(right.reference()), "((+(3)))");

    const auto& returnStatement = statementChildren[0].second;
    ASSERT_EQ(codeM->getCharacters(returnStatement.reference()), "RETURN d\n");
}
//---------------------------------------------------------------------------
TEST(TestParser, missingEndline) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 1 + 1\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestParser, missingParanthesis) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := (1 + 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestParser, missingAssignmentOperator) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d 5;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestParser, missingKeyword) {
    const auto code =
        "VAR d;\n"
        "d := 5;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestParser, wrongExpression) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 5 ++ 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestParser, extraEndline) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 1;\n"
        "d := d + 1;\n"
        "RETURN d;\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_TRUE(parser.errorOccurred());
}
//---------------------------------------------------------------------------
