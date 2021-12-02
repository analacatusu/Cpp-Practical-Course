#include "pljit/semantic/SemanticAnalysis.hpp"
#include <vector>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::semanticanalysis;
//---------------------------------------------------------------------------
TEST(TestAST, Add) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 + 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);
    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Constant);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Subtract) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 - 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::SubtractExpr);
    SubtractExpr* subExpr = static_cast<SubtractExpr*>(right.get());
    auto leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Constant);
    auto rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Division) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 / 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::DivExpr);
    DivExpr* divExpr = static_cast<DivExpr*>(right.get());
    auto leftDiv = divExpr->releaseLeft();
    ASSERT_TRUE(leftDiv.get()->getType() == ASTNode::Type::Constant);
    auto rightDiv = divExpr->releaseRight();
    ASSERT_TRUE(rightDiv.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Multiplication) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 * 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::MulExpr);
    MulExpr* mulExpr = static_cast<MulExpr*>(right.get());
    auto leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::Constant);
    auto rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, UnaryMinus) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := -(-1);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::UnaryMinus);
    UnaryMinus* um = static_cast<UnaryMinus*>(right.get());
    auto childUm = um->releaseInput();
    ASSERT_TRUE(childUm.get()->getType() == ASTNode::Type::UnaryMinus);
    UnaryMinus* um2 = static_cast<UnaryMinus*>(childUm.get());
    auto constant = um2->releaseInput();
    ASSERT_TRUE(constant.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, UnaryPlus) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := -1 + +2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);
    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::UnaryMinus);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::UnaryPlus);

    UnaryMinus* um = static_cast<UnaryMinus*>(leftAdd.get());
    auto constant = um->releaseInput();
    ASSERT_TRUE(constant.get()->getType() == ASTNode::Type::Constant);

    UnaryPlus* up = static_cast<UnaryPlus*>(rightAdd.get());
    auto constant2 = up->releaseInput();
    ASSERT_TRUE(constant2.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Nested1) {
    const auto code =
        "PARAM b, c;\n"
        "VAR a;\n"
        "CONST d = 12;\n"
        "BEGIN\n"
        "a := (-b + c) * (d / 4);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 2);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::MulExpr);

    MulExpr* mulExpr = static_cast<MulExpr*>(right.get());
    auto leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::AddExpr);
    auto rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::DivExpr);

    AddExpr* addExpr = static_cast<AddExpr*>(leftMul.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::UnaryMinus);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Parameter);

    UnaryMinus* um = static_cast<UnaryMinus*>(leftAdd.get());
    auto ch = um->releaseInput();
    ASSERT_TRUE(ch.get()->getType() == ASTNode::Type::Parameter);

    DivExpr* divExpr = static_cast<DivExpr*>(rightMul.get());
    auto leftDiv = divExpr->releaseLeft();
    ASSERT_TRUE(leftDiv.get()->getType() == ASTNode::Type::Parameter);
    auto rightDiv = divExpr->releaseRight();
    ASSERT_TRUE(rightDiv.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression2.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Nested2) {
    const auto code =
        "PARAM b, c;\n"
        "VAR a;\n"
        "CONST d = 1;\n"
        "BEGIN\n"
        "a := b + c;\n"
        "a := a * d * 2;\n"
        "a := 12 - (5 + a);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 4);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[3].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());
    ASTStatement* statement4 = static_cast<ASTStatement*>(statements[3].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);

    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Parameter);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Parameter);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::AssignmentExpr);
    assignmentExpr = static_cast<AssignmentExpr*>(expression2.get());
    left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::MulExpr);

    MulExpr* mulExpr = static_cast<MulExpr*>(right.get());
    auto leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::Parameter);
    auto rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::MulExpr);

    mulExpr = static_cast<MulExpr*>(rightMul.get());
    leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::Parameter);
    rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::Constant);

    auto expression3 = statement3->releaseInput();
    ASSERT_TRUE(expression3.get()->getType() == ASTNode::Type::AssignmentExpr);
    assignmentExpr = static_cast<AssignmentExpr*>(expression3.get());
    left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::SubtractExpr);

    SubtractExpr* subExpr = static_cast<SubtractExpr*>(right.get());
    auto leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Constant);
    auto rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::AddExpr);

    addExpr = static_cast<AddExpr*>(rightSub.get());
    leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Constant);
    rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Parameter);

    auto expression4 = statement4->releaseInput();
    ASSERT_TRUE(expression4.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression4.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Nested3) {
    const auto code =
        "VAR a, b, c, d;\n"
        "BEGIN\n"
        "a := 1 + -2;\n"
        "b := +2 * 3;\n"
        "c := 18 / (-9);\n"
        "d := a - b - c;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    const auto& statements = function.getStatements();

    ASSERT_TRUE(statements.size() == 5);

    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[3].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[4].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());
    ASTStatement* statement4 = static_cast<ASTStatement*>(statements[3].get());
    ASTStatement* statement5 = static_cast<ASTStatement*>(statements[4].get());

    auto expression1 = statement1->releaseInput();
    ASSERT_TRUE(expression1.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression1.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);

    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Constant);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::UnaryMinus);

    UnaryMinus* um = static_cast<UnaryMinus*>(rightAdd.get());
    auto ch = um->releaseInput();
    ASSERT_TRUE(ch.get()->getType() == ASTNode::Type::Constant);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::AssignmentExpr);
    assignmentExpr = static_cast<AssignmentExpr*>(expression2.get());
    left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::MulExpr);

    MulExpr* mulExpr = static_cast<MulExpr*>(right.get());
    auto leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::UnaryPlus);
    auto rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::Constant);

    UnaryPlus* up = static_cast<UnaryPlus*>(leftMul.get());
    ch = up->releaseInput();
    ASSERT_TRUE(ch.get()->getType() == ASTNode::Type::Constant);

    auto expression3 = statement3->releaseInput();
    ASSERT_TRUE(expression3.get()->getType() == ASTNode::Type::AssignmentExpr);
    assignmentExpr = static_cast<AssignmentExpr*>(expression3.get());
    left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::DivExpr);

    DivExpr* divExpr = static_cast<DivExpr*>(right.get());
    auto leftDiv = divExpr->releaseLeft();
    ASSERT_TRUE(leftDiv.get()->getType() == ASTNode::Type::Constant);
    auto rightDiv = divExpr->releaseRight();
    ASSERT_TRUE(rightDiv.get()->getType() == ASTNode::Type::UnaryMinus);

    um = static_cast<UnaryMinus*>(rightDiv.get());
    ch = um->releaseInput();
    ASSERT_TRUE(ch.get()->getType() == ASTNode::Type::Constant);

    auto expression4 = statement4->releaseInput();
    ASSERT_TRUE(expression4.get()->getType() == ASTNode::Type::AssignmentExpr);
    assignmentExpr = static_cast<AssignmentExpr*>(expression4.get());
    left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::SubtractExpr);

    SubtractExpr* subExpr = static_cast<SubtractExpr*>(right.get());
    auto leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Parameter);
    auto rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::SubtractExpr);

    subExpr = static_cast<SubtractExpr*>(rightSub.get());
    leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Parameter);
    rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::Parameter);

    auto expression5 = statement5->releaseInput();
    ASSERT_TRUE(expression5.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* returnExpr = static_cast<ReturnExpr*>(expression5.get());
    auto child = returnExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestAST, Redeclaration) {
    const auto code =
        "PARAM a;\n"
        "VAR a;\n"
        "BEGIN\n"
        "a := 1;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestAST, UndeclaredIdentifier) {
    const auto code =
        "PARAM a;\n"
        "BEGIN\n"
        "a := 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestAST, AssigningToConstant) {
    const auto code =
        "CONST d = 1;\n"
        "BEGIN\n"
        "d := 2;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestAST, UninitializedVariable) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestAST, MissingReturn) {
    const auto code =
        "VAR d;\n"
        "BEGIN\n"
        "d := 1\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    const auto& function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
