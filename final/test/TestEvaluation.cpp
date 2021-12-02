#include "pljit/semantic/SemanticAnalysis.hpp"
#include <vector>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::semanticanalysis;
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateMultiplication) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 * 2 * 3;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 6);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateDivision) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 18 / 3;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 6);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateAddition) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 + 1 + 8 + 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 12);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateSubtraction) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 - 11;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), -10);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateUnary) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := +(-(-(+(+3))));\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateNested1) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 - 5 + 3 * 2 / 1 - 3 * 5 * 2;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 20);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateNested2) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := ((1 - -(-1)) + 1) * 2 - (((+1 + 1) / +2 - 2) + 1);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 2);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateMultipleStatements1) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 2 + 5;\n"
        "a := 1 - -3;\n"
        "a := -(-a) + 1;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 5);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateMultipleStatements2) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 2 * 3 - (-1);\n"
        "a := a * 9 / 3 - 2;\n"
        "a := 15 - -(-a);\n"
        "a := +(+a - 1) * 2 - ((3 * 2) + 5);\n"
        "a := 1 + -(-a);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), -20);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateMultipleStatements3) {
    const auto code =
        "PARAM b, c, d;\n"
        "VAR a, h, i;\n"
        "CONST f = 2, g = 10;\n"
        "BEGIN\n"
        "a := f + ((g - b) * 2) + 1;\n"
        "h := (d + a) + a + (1 * c);\n"
        "i := h + -a - (-2 * -3) + (3 * b) - d;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters = {3, 2, 1};
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 17);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, EvaluateFirstReturn) {
    const auto code =
        "VAR a, b;\n"
        "BEGIN\n"
        "a := 1 + 2;\n"
        "b := 1;\n"
        "RETURN a;\n"
        "RETURN b\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_EQ(evaluationContext.getReturnValue(), 3);
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, ErrorDivision) {
    const auto code =
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 / 0;\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters;
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
TEST(TestEvaluation, ErrorDivisionNested) {
    const auto code =
        "PARAM b, c;\n"
        "VAR a;\n"
        "BEGIN\n"
        "a := 1 / ((b - c) - 1);\n"
        "RETURN a\n"
        "END.\n";

    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    SemanticAnalysis semanticAnalysis(codeM);

    auto function = semanticAnalysis.getAST(parser);
    vector<int64_t> parameters = {3, 2};
    EvaluationContext evaluationContext(function.getSymbolTable(), parameters);
    function.evaluate(evaluationContext);
    ASSERT_TRUE(function.errorOccurred());
}
//---------------------------------------------------------------------------
