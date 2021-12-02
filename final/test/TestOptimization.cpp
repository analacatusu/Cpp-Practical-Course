#include "pljit/ast/ASTOptimizerConstantPropagation.hpp"
#include "pljit/ast/ASTOptimizerDeadCode.hpp"
#include "pljit/semantic/SemanticAnalysis.hpp"
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::semanticanalysis;
//---------------------------------------------------------------------------
static void checkAssignmentIsConstant(ASTStatement* statement) {
    auto expression = statement->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Constant);
}
//---------------------------------------------------------------------------
static void checkReturnIsConstant(ASTStatement* statement) {
    auto expression = statement->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* retExpr = static_cast<ReturnExpr*>(expression.get());
    auto child = retExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Constant);
}
//---------------------------------------------------------------------------
static void checkReturnIsParameter(ASTStatement* statement) {
    auto expression = statement->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::ReturnExpr);
    ReturnExpr* retExpr = static_cast<ReturnExpr*>(expression.get());
    auto child = retExpr->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeDeadCode) {
    const auto code =
        "PARAM b;\n"
        "VAR a;\n"
        "BEGIN\n"
        "a := 2;\n"
        "RETURN a;\n"
        "RETURN b;\n"
        "RETURN 1\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    ASSERT_TRUE(function.getStatements().size() == 4);
    ASTOptimizerDeadCode astOptimizerDeadCode;
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerDeadCode, functionPtr);
    Function* func = static_cast<Function*>(functionPtr.get());
    ASSERT_TRUE(func->getStatements().size() == 2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation1) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 12 + (-1) - 5 + 2 - 3 + 12 / 2 * 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 10);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    checkAssignmentIsConstant(statement1);
    checkReturnIsConstant(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation2) {
    const auto code =
        "VAR a;\n"
        "CONST b = 1, c = 2;\n"
        "BEGIN\n"
        "a := b * (c + 1);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    checkAssignmentIsConstant(statement1);
    checkReturnIsConstant(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation3) {
    const auto code =
        "PARAM d;\n"
        "VAR a, e;\n"
        "BEGIN\n"
        "e := d;\n"
        "a := e + 1;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;
    parameters.push_back(1);
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 3);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    auto expression2 = statement2->releaseInput();
    ASSERT_TRUE(expression2.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr2 = static_cast<AssignmentExpr*>(expression2.get());
    auto left2 = assignmentExpr2->releaseLeft();
    ASSERT_TRUE(left2.get()->getType() == ASTNode::Type::Parameter);
    auto right2 = assignmentExpr2->releaseRight();
    ASSERT_TRUE(right2.get()->getType() == ASTNode::Type::AddExpr);

    checkReturnIsParameter(statement3);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation4) {
    const auto code =
        "VAR a, e;\n"
        "CONST b = 1;\n"
        "BEGIN\n"
        "e := 1;\n"
        "a := (e + b) + 1;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;

    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 3);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());

    checkAssignmentIsConstant(statement1);
    checkAssignmentIsConstant(statement2);
    checkReturnIsConstant(statement3);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation5) {
    const auto code =
        "VAR a, d;\n"
        "CONST b = 1, c = 2;\n"
        "BEGIN\n"
        "a := b + (c - 1);\n"
        "d := a + 1 + 1 - 1;\n"
        "d := d - -a;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 5);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 4);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[3].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());
    ASTStatement* statement4 = static_cast<ASTStatement*>(statements[3].get());

    checkAssignmentIsConstant(statement1);
    checkAssignmentIsConstant(statement2);
    checkAssignmentIsConstant(statement3);
    checkReturnIsConstant(statement4);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation6) {
    const auto code =
        "VAR a, d;\n"
        "BEGIN\n"
        "a := 1 + 2 * 3;\n"
        "d := a + 6 / 2;\n"
        "d := (d - -a) - 1;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 16);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 4);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[2].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[3].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());
    ASTStatement* statement3 = static_cast<ASTStatement*>(statements[2].get());
    ASTStatement* statement4 = static_cast<ASTStatement*>(statements[3].get());

    checkAssignmentIsConstant(statement1);
    checkAssignmentIsConstant(statement2);
    checkAssignmentIsConstant(statement3);
    checkReturnIsConstant(statement4);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OptimizeConstantPropagation7) {
    const auto code =
        "PARAM b, c;\n"
        "VAR a, d;\n"
        "CONST f = 3;\n"
        "BEGIN\n"
        "b := 1;\n"
        "c := 2 + b;\n"
        "a := b + 4;\n"
        "d := (a - c) * f;\n"
        "RETURN d\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1, 1};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 6);

    const auto& statements = func->getStatements();

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

    checkAssignmentIsConstant(statement1);
    checkAssignmentIsConstant(statement2);
    checkAssignmentIsConstant(statement3);
    checkAssignmentIsConstant(statement4);
    checkReturnIsConstant(statement5);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations1) {
    SCOPED_TRACE("(-a) * (-b) -> a * b");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := (-a) * (-b);\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1, 2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::MulExpr);

    MulExpr* mulExpr = static_cast<MulExpr*>(right.get());
    auto leftMul = mulExpr->releaseLeft();
    ASSERT_TRUE(leftMul.get()->getType() == ASTNode::Type::Parameter);
    auto rightMul = mulExpr->releaseRight();
    ASSERT_TRUE(rightMul.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations2) {
    SCOPED_TRACE("a * 0 -> 0");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a * 0;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 0);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    checkAssignmentIsConstant(statement1);
    checkReturnIsConstant(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations3) {
    SCOPED_TRACE("a * 1 -> a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a * 1;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations4) {
    SCOPED_TRACE("0 / a -> 0");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := 0 / a;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 0);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    checkAssignmentIsConstant(statement1);
    checkReturnIsConstant(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations5) {
    SCOPED_TRACE("a / 1 -> a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a / 1;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations6) {
    SCOPED_TRACE("(-a) / (-b) -> a / b");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := (-a) / (-b);\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {4, 2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::DivExpr);

    DivExpr* divExpr = static_cast<DivExpr*>(right.get());
    auto leftDiv = divExpr->releaseLeft();
    ASSERT_TRUE(leftDiv.get()->getType() == ASTNode::Type::Parameter);
    auto rightDiv = divExpr->releaseRight();
    ASSERT_TRUE(rightDiv.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations7) {
    SCOPED_TRACE("(-a) + b -> b - a");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := (-a) + b;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1, 2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 1);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::SubtractExpr);

    SubtractExpr* subExpr = static_cast<SubtractExpr*>(right.get());
    auto leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Parameter);
    auto rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations8) {
    SCOPED_TRACE("a + -b -> b - a");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a + -b;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1, 2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), -1);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::SubtractExpr);

    SubtractExpr* subExpr = static_cast<SubtractExpr*>(right.get());
    auto leftSub = subExpr->releaseLeft();
    ASSERT_TRUE(leftSub.get()->getType() == ASTNode::Type::Parameter);
    auto rightSub = subExpr->releaseRight();
    ASSERT_TRUE(rightSub.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations9) {
    SCOPED_TRACE("a - -b -> a + b");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a - -b;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {1, 2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);

    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Parameter);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations10) {
    SCOPED_TRACE("a + 0 -> a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a + 0;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations11) {
    SCOPED_TRACE("0 + a -> a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := 0 + a;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations12) {
    SCOPED_TRACE("a - 0 -> a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := a - 0;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizations13) {
    SCOPED_TRACE("0 - a -> -a");
    const auto code =
        "PARAM a;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := 0 - a;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), -2);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::UnaryMinus);

    UnaryMinus* um = static_cast<UnaryMinus*>(right.get());
    auto child = um->releaseInput();
    ASSERT_TRUE(child.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
TEST(TestOptimization, OtherOptimizationsNested) {
    SCOPED_TRACE("-(-a) + b / 1 -> a + b");
    const auto code =
        "PARAM a, b;\n"
        "VAR c;\n"
        "BEGIN\n"
        "c := -(-a) + b/1;\n"
        "RETURN c\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);

    ASTOptimizerConstantPropagation astOptimizerConstantProp(function.getSymbolTable());
    unique_ptr<ASTNode> functionPtr = make_unique<Function>(move(function));
    functionPtr->optimize(astOptimizerConstantProp, functionPtr);

    Function* func = static_cast<Function*>(functionPtr.get());
    vector<int64_t> parameters = {2, 1};
    EvaluationContext evaluationContext(func->getSymbolTable(), parameters);
    func->evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);

    const auto& statements = func->getStatements();

    ASSERT_TRUE(statements.size() == 2);
    ASSERT_TRUE(statements[0].get()->getType() == ASTNode::Type::ASTStatement);
    ASSERT_TRUE(statements[1].get()->getType() == ASTNode::Type::ASTStatement);

    ASTStatement* statement1 = static_cast<ASTStatement*>(statements[0].get());
    ASTStatement* statement2 = static_cast<ASTStatement*>(statements[1].get());

    auto expression = statement1->releaseInput();
    ASSERT_TRUE(expression.get()->getType() == ASTNode::Type::AssignmentExpr);
    AssignmentExpr* assignmentExpr = static_cast<AssignmentExpr*>(expression.get());
    auto left = assignmentExpr->releaseLeft();
    ASSERT_TRUE(left.get()->getType() == ASTNode::Type::Parameter);
    auto right = assignmentExpr->releaseRight();
    ASSERT_TRUE(right.get()->getType() == ASTNode::Type::AddExpr);

    AddExpr* addExpr = static_cast<AddExpr*>(right.get());
    auto leftAdd = addExpr->releaseLeft();
    ASSERT_TRUE(leftAdd.get()->getType() == ASTNode::Type::Parameter);
    auto rightAdd = addExpr->releaseRight();
    ASSERT_TRUE(rightAdd.get()->getType() == ASTNode::Type::Parameter);

    checkReturnIsParameter(statement2);
}
//---------------------------------------------------------------------------
