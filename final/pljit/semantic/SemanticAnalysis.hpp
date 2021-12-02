#ifndef H_PLJIT_SEMANTICANALYSIS
#define H_PLJIT_SEMANTICANALYSIS
#include "pljit/ast/AST.hpp"
#include "pljit/parser/Parser.hpp"
using namespace pljit::parser;
using namespace pljit::ast;
//---------------------------------------------------------------------------
namespace pljit::semanticanalysis {
//---------------------------------------------------------------------------
/// Class that represents the semantic analysis given a parse tree (MILESTONE 4)
class SemanticAnalysis {
    public:
    /// Constructor
    explicit SemanticAnalysis(shared_ptr<CodeManagement> codeM) : codeM(move(codeM)) {}
    /// Return the ast
    Function getAST(const Parsing& parser);

    private:
    /// Functions that return whether an error occurred during the semantic analysis
    bool errorAnalyzeParameters(const FunctionDefinition& functionDefinition);
    bool errorAnalyzeVariables(const FunctionDefinition& functionDefinition);
    bool errorAnalyzeConstants(const FunctionDefinition& functionDefinition);
    bool errorAnalyzeStatement(vector<unique_ptr<ASTNode>>& funcStatements, const Statement& statement);
    bool errorAnalyzeAssignmentExpression(const vector<shared_ptr<ParseTreeNode>>& parseExpr, unique_ptr<ASTNode>& astExpr);
    bool errorAnalyzeReturnExpression(const vector<shared_ptr<ParseTreeNode>>& parseExpr, unique_ptr<ASTNode>& astExpr);
    bool errorAnalyzeChildExpression(const AdditiveExpression& additiveExpression, unique_ptr<ASTNode>& child);
    bool errorAnalyzeChildExpression(const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child);
    bool errorAnalyzeChildExpression(const UnaryExpression& unaryExpression, const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child);
    bool errorInitializationLeftChild(bool& prevUninitialized, const Identifier& identifier, string_view nameLeft);
    bool errorAnalyzeParameter(const Identifier& identifier, unique_ptr<ASTNode>& ptr);
    bool errorAnalyzeUnary(const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child);
    /// Functions that perform the semantic analysis
    Function analyzeFunction(const FunctionDefinition& functionDefinition);
    ASTStatement analyzeStatement(const Statement& statement);
    ReturnExpr analyzeReturnExpression(const shared_ptr<ParseTreeNode>& addExpr);
    AssignmentExpr analyzeAssignmentExpression(const shared_ptr<ParseTreeNode>& assignmentExpression);
    AddExpr analyzeAddExpr(AdditiveExpression additiveExpression);
    SubtractExpr analyzeSubtractExpr(AdditiveExpression additiveExpression);
    MulExpr analyzeMulExpr(MultiplicativeExpression multiplicativeExpression);
    DivExpr analyzeDivExpr(MultiplicativeExpression multiplicativeExpression);
    UnaryPlus analyzeUnaryPlus(const MultiplicativeExpression& multiplicativeExpression);
    UnaryMinus analyzeUnaryMinus(const MultiplicativeExpression& multiplicativeExpression);
    Parameter analyzeParameter(const Identifier& id);
    Constant analyzeConstant(const Literal& literal);
    /// Functions that return the type that an ast node should have, given a node in the parse tree
    ASTNode::Type getTypeFromPrimaryExpression(const PrimaryExpression& primaryExpression);
    ASTNode::Type getTypeFromUnaryExpression(const UnaryExpression& unaryExpression);
    ASTNode::Type getTypeFromMultiplicativeExpression(const MultiplicativeExpression& multiplicativeExpression);
    ASTNode::Type getTypeFromAdditiveExpression(const AdditiveExpression& additiveExpression);
    /// Functions that analyze and return an ast node, given the type of the ast node and a parse tree node
    unique_ptr<ASTNode> analyzeType(ASTNode::Type type, const AdditiveExpression& additiveExpression);
    unique_ptr<ASTNode> analyzeType(ASTNode::Type type, const MultiplicativeExpression& multiplicativeExpression);
    /// Storage of the symbol table
    SymbolTable symbolTable;
    /// Storage of whether there exists a return statement in the program
    bool existingReturn = false;
    /// Storage of the code management unit
    shared_ptr<CodeManagement> codeM;
};
//---------------------------------------------------------------------------
} // namespace pljit::semanticanalysis
//---------------------------------------------------------------------------
#endif //H_PLJIT_SEMANTICANALYSIS
//---------------------------------------------------------------------------
