#include "pljit/ast/ASTPrintVisitor.hpp"
#include "pljit/semantic/SemanticAnalysis.hpp"
#include <sstream>
#include <gtest/gtest.h>
//---------------------------------------------------------------------------
using namespace std;
using namespace pljit::semanticanalysis;
using namespace pljit::ast;
//---------------------------------------------------------------------------
static const char* ast1 = "graph {\n"
                          "node [shape=plaintext, ordering=out];\n"
                          "\t0[label=\"Function\"];\n"
                          "\t1[label=\"ASTStatement\"];\n"
                          "0-- 1;\n"
                          "\t2[label=\"Assignment\"];\n"
                          "1-- 2;\n"
                          "\t3[label=\"Parameter\"];\n"
                          "2-- 3;\n"
                          "\t4[label=\"d\"];\n"
                          "3-- 4;\n"
                          "\t5[label=\":=\"];\n"
                          "2-- 5;\n"
                          "\t6[label=\"Addition\"];\n"
                          "2-- 6;\n"
                          "\t7[label=\"Parameter\"];\n"
                          "6-- 7;\n"
                          "\t8[label=\"a\"];\n"
                          "7-- 8;\n"
                          "\t9[label=\"+\"];\n"
                          "6-- 9;\n"
                          "\t10[label=\"Parameter\"];\n"
                          "6-- 10;\n"
                          "\t11[label=\"b\"];\n"
                          "10-- 11;\n"
                          "\t12[label=\"ASTStatement\"];\n"
                          "0-- 12;\n"
                          "\t13[label=\"Assignment\"];\n"
                          "12-- 13;\n"
                          "\t14[label=\"Parameter\"];\n"
                          "13-- 14;\n"
                          "\t15[label=\"d\"];\n"
                          "14-- 15;\n"
                          "\t16[label=\":=\"];\n"
                          "13-- 16;\n"
                          "\t17[label=\"Multiplication\"];\n"
                          "13-- 17;\n"
                          "\t18[label=\"Parameter\"];\n"
                          "17-- 18;\n"
                          "\t19[label=\"d\"];\n"
                          "18-- 19;\n"
                          "\t20[label=\"*\"];\n"
                          "17-- 20;\n"
                          "\t21[label=\"Parameter\"];\n"
                          "17-- 21;\n"
                          "\t22[label=\"c\"];\n"
                          "21-- 22;\n"
                          "\t23[label=\"ASTStatement\"];\n"
                          "0-- 23;\n"
                          "\t24[label=\"Return\"];\n"
                          "23-- 24;\n"
                          "\t25[label=\"Parameter\"];\n"
                          "24-- 25;\n"
                          "\t26[label=\"d\"];\n"
                          "25-- 26;\n"
                          "}\n";
//---------------------------------------------------------------------------
static const char* ast2 = "graph {\n"
                          "node [shape=plaintext, ordering=out];\n"
                          "\t0[label=\"Function\"];\n"
                          "\t1[label=\"ASTStatement\"];\n"
                          "0-- 1;\n"
                          "\t2[label=\"Assignment\"];\n"
                          "1-- 2;\n"
                          "\t3[label=\"Parameter\"];\n"
                          "2-- 3;\n"
                          "\t4[label=\"d\"];\n"
                          "3-- 4;\n"
                          "\t5[label=\":=\"];\n"
                          "2-- 5;\n"
                          "\t6[label=\"Multiplication\"];\n"
                          "2-- 6;\n"
                          "\t7[label=\"Unary Minus\"];\n"
                          "6-- 7;\n"
                          "\t8[label=\"Constant\"];\n"
                          "7-- 8;\n"
                          "\t9[label=\"1\"];\n"
                          "8-- 9;\n"
                          "\t10[label=\"*\"];\n"
                          "6-- 10;\n"
                          "\t11[label=\"Division\"];\n"
                          "6-- 11;\n"
                          "\t12[label=\"Constant\"];\n"
                          "11-- 12;\n"
                          "\t13[label=\"12\"];\n"
                          "12-- 13;\n"
                          "\t14[label=\"/\"];\n"
                          "11-- 14;\n"
                          "\t15[label=\"Unary Minus\"];\n"
                          "11-- 15;\n"
                          "\t16[label=\"Constant\"];\n"
                          "15-- 16;\n"
                          "\t17[label=\"6\"];\n"
                          "16-- 17;\n"
                          "\t18[label=\"ASTStatement\"];\n"
                          "0-- 18;\n"
                          "\t19[label=\"Assignment\"];\n"
                          "18-- 19;\n"
                          "\t20[label=\"Parameter\"];\n"
                          "19-- 20;\n"
                          "\t21[label=\"e\"];\n"
                          "20-- 21;\n"
                          "\t22[label=\":=\"];\n"
                          "19-- 22;\n"
                          "\t23[label=\"Addition\"];\n"
                          "19-- 23;\n"
                          "\t24[label=\"Parameter\"];\n"
                          "23-- 24;\n"
                          "\t25[label=\"d\"];\n"
                          "24-- 25;\n"
                          "\t26[label=\"+\"];\n"
                          "23-- 26;\n"
                          "\t27[label=\"Unary Plus\"];\n"
                          "23-- 27;\n"
                          "\t28[label=\"Constant\"];\n"
                          "27-- 28;\n"
                          "\t29[label=\"2\"];\n"
                          "28-- 29;\n"
                          "\t30[label=\"ASTStatement\"];\n"
                          "0-- 30;\n"
                          "\t31[label=\"Assignment\"];\n"
                          "30-- 31;\n"
                          "\t32[label=\"Parameter\"];\n"
                          "31-- 32;\n"
                          "\t33[label=\"e\"];\n"
                          "32-- 33;\n"
                          "\t34[label=\":=\"];\n"
                          "31-- 34;\n"
                          "\t35[label=\"Unary Minus\"];\n"
                          "31-- 35;\n"
                          "\t36[label=\"Unary Minus\"];\n"
                          "35-- 36;\n"
                          "\t37[label=\"Unary Minus\"];\n"
                          "36-- 37;\n"
                          "\t38[label=\"Parameter\"];\n"
                          "37-- 38;\n"
                          "\t39[label=\"e\"];\n"
                          "38-- 39;\n"
                          "\t40[label=\"ASTStatement\"];\n"
                          "0-- 40;\n"
                          "\t41[label=\"Return\"];\n"
                          "40-- 41;\n"
                          "\t42[label=\"Parameter\"];\n"
                          "41-- 42;\n"
                          "\t43[label=\"e\"];\n"
                          "42-- 43;\n"
                          "\t44[label=\"ASTStatement\"];\n"
                          "0-- 44;\n"
                          "\t45[label=\"Return\"];\n"
                          "44-- 45;\n"
                          "\t46[label=\"Parameter\"];\n"
                          "45-- 46;\n"
                          "\t47[label=\"d\"];\n"
                          "46-- 47;\n"
                          "}\n";
//---------------------------------------------------------------------------
static const char* ast3 = "graph {\n"
                          "node [shape=plaintext, ordering=out];\n"
                          "\t0[label=\"Function\"];\n"
                          "\t1[label=\"ASTStatement\"];\n"
                          "0-- 1;\n"
                          "\t2[label=\"Assignment\"];\n"
                          "1-- 2;\n"
                          "\t3[label=\"Parameter\"];\n"
                          "2-- 3;\n"
                          "\t4[label=\"b\"];\n"
                          "3-- 4;\n"
                          "\t5[label=\":=\"];\n"
                          "2-- 5;\n"
                          "\t6[label=\"Subtraction\"];\n"
                          "2-- 6;\n"
                          "\t7[label=\"Parameter\"];\n"
                          "6-- 7;\n"
                          "\t8[label=\"a\"];\n"
                          "7-- 8;\n"
                          "\t9[label=\"-\"];\n"
                          "6-- 9;\n"
                          "\t10[label=\"Subtraction\"];\n"
                          "6-- 10;\n"
                          "\t11[label=\"Parameter\"];\n"
                          "10-- 11;\n"
                          "\t12[label=\"c\"];\n"
                          "11-- 12;\n"
                          "\t13[label=\"-\"];\n"
                          "10-- 13;\n"
                          "\t14[label=\"Constant\"];\n"
                          "10-- 14;\n"
                          "\t15[label=\"2\"];\n"
                          "14-- 15;\n"
                          "\t16[label=\"ASTStatement\"];\n"
                          "0-- 16;\n"
                          "\t17[label=\"Return\"];\n"
                          "16-- 17;\n"
                          "\t18[label=\"Parameter\"];\n"
                          "17-- 18;\n"
                          "\t19[label=\"b\"];\n"
                          "18-- 19;\n"
                          "}\n";
//---------------------------------------------------------------------------
TEST(TestASTPrintVisitor, printAST1) {
    const auto code = "PARAM a, b; VAR d; CONST c = 2; BEGIN d := (a + b); d := d * c; RETURN d END.";
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    SemanticAnalysis semanticAnalysis(codeM);
    const Function& function = semanticAnalysis.getAST(parser);

    ASSERT_FALSE(function.errorOccurred());

    ostringstream buf;
    ASTPrintVisitor astPrintVisitor(buf);
    function.accept(astPrintVisitor);

    ASSERT_EQ(buf.str(), ast1);
}
//---------------------------------------------------------------------------
TEST(TestASTPrintVisitor, printAST2) {
    const auto code = "VAR d, e; BEGIN d := -1 * (12 / (-6)); e := d + +2; e := -(-(-e)); RETURN e; RETURN d END.";
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    SemanticAnalysis semanticAnalysis(codeM);
    const Function& function = semanticAnalysis.getAST(parser);

    ASSERT_FALSE(function.errorOccurred());

    ostringstream buf;
    ASTPrintVisitor astPrintVisitor(buf);
    function.accept(astPrintVisitor);

    ASSERT_EQ(buf.str(), ast2);
}
//---------------------------------------------------------------------------
TEST(TestASTPrintVisitor, printAST3) {
    const auto code = "PARAM a; VAR b; CONST c = 1; BEGIN b := a - c - 2; RETURN b END.";
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    Lexer lex(code, codeM);
    Parsing parser(lex, codeM);
    parser.parsing();

    ASSERT_FALSE(parser.errorOccurred());

    SemanticAnalysis semanticAnalysis(codeM);
    const Function& function = semanticAnalysis.getAST(parser);

    ASSERT_FALSE(function.errorOccurred());

    ostringstream buf;
    ASTPrintVisitor astPrintVisitor(buf);
    function.accept(astPrintVisitor);

    ASSERT_EQ(buf.str(), ast3);
}
//---------------------------------------------------------------------------
