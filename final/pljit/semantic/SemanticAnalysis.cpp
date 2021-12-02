#include "pljit/semantic/SemanticAnalysis.hpp"
//---------------------------------------------------------------------------
namespace pljit::semanticanalysis {
//---------------------------------------------------------------------------
// Return the ast
Function SemanticAnalysis::getAST(const Parsing& parser) {
    const FunctionDefinition& functionDefinition = parser.getTree();
    Function function = analyzeFunction(functionDefinition);
    return function;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a parameter
bool SemanticAnalysis::errorAnalyzeParameters(const FunctionDefinition& functionDefinition) {
    const optional<ParameterDeclarations>& parameterDeclarations = functionDefinition.getParamDeclarations();

    if (parameterDeclarations.has_value()) {
        const DeclaratorList& declaratorList = parameterDeclarations->getDeclList();
        const Reference& ref = declaratorList.getIdentifier().reference();

        if (!symbolTable.insert(codeM->getCharacters(ref), ref, false, true, 0, 0)) {
            codeM->errorRedeclaration(ref);
            return true;
        }

        const auto& children = declaratorList.getChildren();
        size_t parameterPos = 1;

        for (const auto& child : children) {
            const auto& [t, id] = child;
            const Reference& reference = id.reference();
            if (!symbolTable.insert(codeM->getCharacters(reference), reference, false, true, 0, parameterPos)) {
                codeM->errorRedeclaration(reference);
                return true;
            }
            parameterPos++;
        }
    }

    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a variable declaration
bool SemanticAnalysis::errorAnalyzeVariables(const FunctionDefinition& functionDefinition) {
    const optional<VariableDeclarations>& variableDeclarations = functionDefinition.getVariableDeclarations();

    if (variableDeclarations.has_value()) {
        const DeclaratorList& declaratorList = variableDeclarations->getDeclList();
        const Reference& ref = declaratorList.getIdentifier().reference();

        if (!symbolTable.insert(codeM->getCharacters(ref), ref, false, false)) {
            codeM->errorRedeclaration(ref);
            return true;
        }

        const auto& children = declaratorList.getChildren();

        for (const auto& child : children) {
            const auto& [t, id] = child;
            const Reference& reference = id.reference();
            if (!symbolTable.insert(codeM->getCharacters(reference), reference, false, false)) {
                codeM->errorRedeclaration(reference);
                return true;
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a function definition
bool SemanticAnalysis::errorAnalyzeConstants(const FunctionDefinition& functionDefinition) {
    const optional<ConstantDeclarations>& constantDeclarations = functionDefinition.getConstantDeclarations();

    if (constantDeclarations.has_value()) {
        const InitDeclaratorList& initDeclaratorList = constantDeclarations->getInitDeclaratorList();
        const Reference& ref = initDeclaratorList.getInitDecl().getIdentifier().reference();
        const int64_t val = initDeclaratorList.getInitDecl().getLiteral().value();

        if (!symbolTable.insert(codeM->getCharacters(ref), ref, true, true, val)) {
            codeM->errorRedeclaration(ref);
            return true;
        }

        const auto& children = initDeclaratorList.getChildren();

        for (const auto& child : children) {
            const auto& [t, init] = child;
            const Reference& reference = init.getIdentifier().reference();
            const int64_t value = init.getLiteral().value();
            if (!symbolTable.insert(codeM->getCharacters(reference), reference, true, true, value)) {
                codeM->errorRedeclaration(init.reference());
                return true;
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a statement
bool SemanticAnalysis::errorAnalyzeStatement(vector<unique_ptr<ASTNode>>& funcStatements, const Statement& statement) {
    ASTStatement astStatement;
    astStatement = analyzeStatement(statement);

    if (astStatement.errorOccurred()) {
        return true;
    }

    if (astStatement.getExpression().getType() == ASTNode::Type::ReturnExpr) {
        existingReturn = true;
    }

    funcStatements.push_back(make_unique<ASTStatement>(move(astStatement)));
    return false;
}
//---------------------------------------------------------------------------
// Return an ast node representing a function
Function SemanticAnalysis::analyzeFunction(const FunctionDefinition& functionDefinition) {
    if (errorAnalyzeParameters(functionDefinition)) {
        return Function(true);
    }

    if (errorAnalyzeVariables(functionDefinition)) {
        return Function(true);
    }

    if (errorAnalyzeConstants(functionDefinition)) {
        return Function(true);
    }

    const StatementList& statementList = functionDefinition.getCompoundStatement().getStatementList();
    const Statement& statement = statementList.getStatement();
    vector<unique_ptr<ASTNode>> funcStatements;

    if (errorAnalyzeStatement(funcStatements, statement)) {
        return Function(true);
    }

    const auto& statements = statementList.getChildren();

    if (!statements.empty()) {
        for (const auto& child : statements) {
            const auto& [t, st] = child;
            if (errorAnalyzeStatement(funcStatements, st)) {
                return Function(true);
            }
        }
    }

    if (!existingReturn) {
        codeM->errorMissingReturn();
        return Function(true);
    }

    return Function(move(funcStatements), OptimizationTable(move(symbolTable)));
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing an assignment expression
bool SemanticAnalysis::errorAnalyzeAssignmentExpression(const vector<shared_ptr<ParseTreeNode>>& parseExpr, unique_ptr<ASTNode>& astExpr) {
    AssignmentExpr assignmentExpr = analyzeAssignmentExpression(parseExpr[0]);
    if (assignmentExpr.errorOccurred()) {
        return true;
    }
    astExpr = make_unique<AssignmentExpr>(move(assignmentExpr));
    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a return expression
bool SemanticAnalysis::errorAnalyzeReturnExpression(const vector<shared_ptr<ParseTreeNode>>& parseExpr, unique_ptr<ASTNode>& astExpr) {
    ReturnExpr returnExpr = analyzeReturnExpression(parseExpr[1]);
    if (returnExpr.errorOccurred()) {
        return true;
    }
    astExpr = make_unique<ReturnExpr>(move(returnExpr));
    return false;
}
//---------------------------------------------------------------------------
// Return an ast node representing a statement
ASTStatement SemanticAnalysis::analyzeStatement(const Statement& statement) {
    unique_ptr<ASTNode> astExpr;
    const auto& parseExpr = statement.getChildren();

    if (statement.getData() == ParseTreeNode::Type::AssignmentExpression) {
        if (errorAnalyzeAssignmentExpression(parseExpr, astExpr)) {
            return ASTStatement(true);
        }
    } else {
        if (errorAnalyzeReturnExpression(parseExpr, astExpr)) {
            return ASTStatement(true);
        }
    }

    return ASTStatement(move(astExpr));
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a child of a additive expression
bool SemanticAnalysis::errorAnalyzeChildExpression(const AdditiveExpression& additiveExpression, unique_ptr<ASTNode>& child) {
    ASTNode::Type type = getTypeFromAdditiveExpression(additiveExpression);
    child = analyzeType(type, additiveExpression);
    if (!child) {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a child of a multiplicative expression
bool SemanticAnalysis::errorAnalyzeChildExpression(const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child) {
    ASTNode::Type type = getTypeFromMultiplicativeExpression(multiplicativeExpression);
    child = analyzeType(type, multiplicativeExpression);
    if (!child) {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a child of a unary expression
bool SemanticAnalysis::errorAnalyzeChildExpression(const UnaryExpression& unaryExpression, const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child) {
    ASTNode::Type type = getTypeFromUnaryExpression(unaryExpression);
    child = analyzeType(type, multiplicativeExpression);
    if (!child) {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Return an ast node representing a return expression
ReturnExpr SemanticAnalysis::analyzeReturnExpression(const shared_ptr<ParseTreeNode>& addExpr) {
    unique_ptr<ASTNode> child;
    const auto& additiveExpression = *static_cast<AdditiveExpression*>(addExpr.get());
    if (errorAnalyzeChildExpression(additiveExpression, child)) {
        return ReturnExpr(true);
    }
    return ReturnExpr(move(child));
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing the left side of an assignment expression
bool SemanticAnalysis::errorInitializationLeftChild(bool& prevUninitialized, const Identifier& identifier, string_view nameLeft) {
    optional<bool> isConstant = symbolTable.isConstant(nameLeft);

    if (!isConstant.has_value()) {
        codeM->errorUndeclaredIdentifier(identifier.reference());
        return true;
    } else if (isConstant.value()) {
        codeM->errorAssigningToConstant(identifier.reference());
        return true;
    } else if (!symbolTable.isInitialized(nameLeft)) {
        symbolTable.initialize(nameLeft);
        prevUninitialized = true;
    }

    return false;
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a parameter
bool SemanticAnalysis::errorAnalyzeParameter(const Identifier& identifier, unique_ptr<ASTNode>& ptr) {
    Parameter p = analyzeParameter(identifier);
    if (p.errorOccurred()) {
        return true;
    }
    ptr = make_unique<Parameter>(move(p));
    return false;
}
//---------------------------------------------------------------------------
// Return an ast node representing an assignment
AssignmentExpr SemanticAnalysis::analyzeAssignmentExpression(const shared_ptr<ParseTreeNode>& assignmentExpression) {
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    const auto& parseAssignmentExpr = *static_cast<AssignmentExpression*>(assignmentExpression.get());
    const auto& identifier = parseAssignmentExpr.getIdentifier();
    string_view nameLeft = codeM->getCharacters(identifier.reference());
    bool prevUninitialized = false;

    if (errorInitializationLeftChild(prevUninitialized, identifier, nameLeft)) {
        return AssignmentExpr(true);
    }

    if (errorAnalyzeParameter(identifier, left)) {
        return AssignmentExpr(true);
    }

    if (prevUninitialized) {
        symbolTable.uninitialize(nameLeft);
    }

    const AdditiveExpression& additiveExpression = parseAssignmentExpr.getAdditiveExpr();

    if (errorAnalyzeChildExpression(additiveExpression, right)) {
        return AssignmentExpr(true);
    }

    if (prevUninitialized) {
        symbolTable.initialize(nameLeft);
    }

    return AssignmentExpr(move(left), move(right), nameLeft);
}
//---------------------------------------------------------------------------
// Return an ast node representing an addition
AddExpr SemanticAnalysis::analyzeAddExpr(AdditiveExpression additiveExpression) {
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    if (!additiveExpression.getAdditiveExpression().has_value()) { //add expression is in primary expression
        PrimaryExpression primaryExpression = additiveExpression.getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression();
        auto children = primaryExpression.getChildren();
        auto add = children[1];
        auto& addexpr = static_cast<AdditiveExpression&>(*add);
        additiveExpression = addexpr;
    }

    const MultiplicativeExpression& multiplicativeExpression = additiveExpression.getMultiplicativeExpression();

    if (errorAnalyzeChildExpression(multiplicativeExpression, left)) {
        return AddExpr(true);
    }

    const auto& additiveExpression1 = *static_cast<AdditiveExpression*>(additiveExpression.getAdditiveExpression()->get());

    if (errorAnalyzeChildExpression(additiveExpression1, right)) {
        return AddExpr(true);
    }

    return AddExpr(move(left), move(right));
}
//---------------------------------------------------------------------------
// Return an ast node representing a subtraction
SubtractExpr SemanticAnalysis::analyzeSubtractExpr(AdditiveExpression additiveExpression) {
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    if (!additiveExpression.getAdditiveExpression().has_value()) { //add expression is in primary expression
        PrimaryExpression primaryExpression = additiveExpression.getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression();
        auto children = primaryExpression.getChildren();
        auto add = children[1];
        auto& addexpr = static_cast<AdditiveExpression&>(*add);
        additiveExpression = addexpr;
    }

    MultiplicativeExpression multiplicativeExpression = additiveExpression.getMultiplicativeExpression();
    if (errorAnalyzeChildExpression(multiplicativeExpression, left)) {
        return SubtractExpr(true);
    }

    const auto& additiveExpression1 = *static_cast<AdditiveExpression*>(additiveExpression.getAdditiveExpression()->get());

    if (errorAnalyzeChildExpression(additiveExpression1, right)) {
        return SubtractExpr(true);
    }

    return SubtractExpr(move(left), move(right));
}
//---------------------------------------------------------------------------
// Return an ast node representing a multiplication
MulExpr SemanticAnalysis::analyzeMulExpr(MultiplicativeExpression multiplicativeExpression) {
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    if (!multiplicativeExpression.getMultiplicativeExpression().has_value()) { // mul expression is in primary expression
        PrimaryExpression primaryExpression = multiplicativeExpression.getUnaryExpression().getPrimaryExpression();
        auto children = primaryExpression.getChildren();
        auto add = children[1];
        auto& addexpr = static_cast<AdditiveExpression&>(*add);
        multiplicativeExpression = addexpr.getMultiplicativeExpression();
    }
    UnaryExpression unaryExpression = multiplicativeExpression.getUnaryExpression();

    if (errorAnalyzeChildExpression(unaryExpression, multiplicativeExpression, left)) {
        return MulExpr(true);
    }

    const auto& multiplicativeExpression1 = *static_cast<MultiplicativeExpression*>(multiplicativeExpression.getMultiplicativeExpression()->get());
    if (errorAnalyzeChildExpression(multiplicativeExpression1, right)) {
        return MulExpr(true);
    }

    return MulExpr(move(left), move(right));
}
//---------------------------------------------------------------------------
// Return an ast node representing a division
DivExpr SemanticAnalysis::analyzeDivExpr(MultiplicativeExpression multiplicativeExpression) {
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    if (!multiplicativeExpression.getMultiplicativeExpression().has_value()) { // div expression is in primary expression
        PrimaryExpression primaryExpression = multiplicativeExpression.getUnaryExpression().getPrimaryExpression();
        auto children = primaryExpression.getChildren();
        auto add = children[1];
        auto& addexpr = static_cast<AdditiveExpression&>(*add);
        multiplicativeExpression = addexpr.getMultiplicativeExpression();
    }

    UnaryExpression unaryExpression = multiplicativeExpression.getUnaryExpression();
    if (errorAnalyzeChildExpression(unaryExpression, multiplicativeExpression, left)) {
        return DivExpr(true);
    }

    const auto& multiplicativeExpression1 = *static_cast<MultiplicativeExpression*>(multiplicativeExpression.getMultiplicativeExpression()->get());
    if (errorAnalyzeChildExpression(multiplicativeExpression1, right)) {
        return DivExpr(true);
    }

    return DivExpr(move(left), move(right));
}
//---------------------------------------------------------------------------
// Return an ast node representing a parameter
Parameter SemanticAnalysis::analyzeParameter(const Identifier& id) {
    string_view nameId = codeM->getCharacters(id.reference());
    Reference reference = symbolTable.findLocation(nameId);

    if (static_cast<int>(reference.begin) == -1) {
        codeM->errorUndeclaredIdentifier(id.reference());
        return Parameter(true);

    } else if (!symbolTable.isInitialized(nameId)) {
        codeM->errorUninitializedVariable(id.reference());
        return Parameter(true);
    }

    return Parameter(nameId);
}
//---------------------------------------------------------------------------
// Return an ast node representing a constant
Constant SemanticAnalysis::analyzeConstant(const Literal& literal) {
    return Constant(literal.value());
}
//---------------------------------------------------------------------------
// Return whether an error occurred whilst analyzing a unary expression
bool SemanticAnalysis::errorAnalyzeUnary(const MultiplicativeExpression& multiplicativeExpression, unique_ptr<ASTNode>& child) {
    PrimaryExpression primaryExpression = multiplicativeExpression.getUnaryExpression().getPrimaryExpression();
    ASTNode::Type type = getTypeFromPrimaryExpression(primaryExpression);

    if (type == ASTNode::Type::UnaryMinus || type == ASTNode::Type::UnaryPlus) {
        const auto& children = primaryExpression.getChildren();
        const auto& add = children[1];
        const auto& addexpr = static_cast<AdditiveExpression&>(*add);
        child = analyzeType(type, addexpr);
    } else {
        child = analyzeType(type, multiplicativeExpression);
    }

    if (!child)
        return true;

    return false;
}
//---------------------------------------------------------------------------
// Return an ast node representing a unary plus
UnaryPlus SemanticAnalysis::analyzeUnaryPlus(const MultiplicativeExpression& multiplicativeExpression) {
    unique_ptr<ASTNode> child;

    if (errorAnalyzeUnary(multiplicativeExpression, child)) {
        return UnaryPlus(true);
    }
    return UnaryPlus(move(child));
}
//---------------------------------------------------------------------------
// Return an ast node representing a unary minus
UnaryMinus SemanticAnalysis::analyzeUnaryMinus(const MultiplicativeExpression& multiplicativeExpression) {
    unique_ptr<ASTNode> child;

    if (errorAnalyzeUnary(multiplicativeExpression, child)) {
        return UnaryMinus(true);
    }

    return UnaryMinus(move(child));
}
//---------------------------------------------------------------------------
// Return an ast node based on the type it should have
unique_ptr<ASTNode> SemanticAnalysis::analyzeType(ASTNode::Type type, const MultiplicativeExpression& multiplicativeExpression) {
    switch (type) {
        case ASTNode::Type::Parameter: {
            Parameter parameter;
            PrimaryExpression primaryExpression = multiplicativeExpression.getUnaryExpression().getPrimaryExpression();
            const auto& children = primaryExpression.getChildren();
            const auto& identifier = *static_cast<Identifier*>(children[0].get());
            parameter = analyzeParameter(identifier);
            if (parameter.errorOccurred()) {
                return nullptr;
            }
            return make_unique<Parameter>(move(parameter));
        }

        case ASTNode::Type::Constant: {
            Constant constant;
            PrimaryExpression primaryExpression = multiplicativeExpression.getUnaryExpression().getPrimaryExpression();
            const auto& children = primaryExpression.getChildren();
            if (children.size() != 1) { // literal is inside primary
                auto& addexpr = static_cast<AdditiveExpression&>(*children[1]);
                PrimaryExpression primaryExpression1 = addexpr.getMultiplicativeExpression().getUnaryExpression().getPrimaryExpression();
                const auto& children1 = primaryExpression1.getChildren();
                const auto& literal = *static_cast<Literal*>(children1[0].get());
                constant = analyzeConstant(literal);
                if (constant.errorOccurred()) {
                    return nullptr;
                }
                return make_unique<Constant>(move(constant));
            } else {
                const auto& literal = *static_cast<Literal*>(children[0].get());
                constant = analyzeConstant(literal);
                if (constant.errorOccurred()) {
                    return nullptr;
                }
                return make_unique<Constant>(move(constant));
            }
        }

        case ASTNode::Type::UnaryPlus: {
            UnaryPlus unaryPlus = analyzeUnaryPlus(multiplicativeExpression);
            if (unaryPlus.errorOccurred()) {
                return nullptr;
            }
            return make_unique<UnaryPlus>(move(unaryPlus));
        }
        case ASTNode::Type::UnaryMinus: {
            auto& children = multiplicativeExpression.getUnaryExpression().getPrimaryExpression().getChildren();
            if (multiplicativeExpression.getUnaryExpression().getTerminalSymbol().has_value()) {
                UnaryMinus unaryMinus = analyzeUnaryMinus(multiplicativeExpression);
                if (unaryMinus.errorOccurred()) {
                    return nullptr;
                }
                return make_unique<UnaryMinus>(move(unaryMinus));
            } else {
                auto add = children[1];
                auto& addexpr = static_cast<AdditiveExpression&>(*add);
                return analyzeType(type, addexpr);
            }
        }
        case ASTNode::Type::MulExpr: {
            MulExpr mulExpr = analyzeMulExpr(multiplicativeExpression);
            if (mulExpr.errorOccurred()) {
                return nullptr;
            }
            return make_unique<MulExpr>(move(mulExpr));
        }
        case ASTNode::Type::DivExpr: {
            DivExpr divExpr = analyzeDivExpr(multiplicativeExpression);
            if (divExpr.errorOccurred()) {
                return nullptr;
            }
            return make_unique<DivExpr>(move(divExpr));
        }
        default: {
            auto& children = multiplicativeExpression.getUnaryExpression().getPrimaryExpression().getChildren();
            auto add = children[1];
            auto& addexpr = static_cast<AdditiveExpression&>(*add);
            return analyzeType(type, addexpr);
        }
    }
}
//---------------------------------------------------------------------------
// Return an ast node representing an ast node based on the type it should have 
unique_ptr<ASTNode> SemanticAnalysis::analyzeType(ASTNode::Type type, const AdditiveExpression& additiveExpression) {
    switch (type) {
        case ASTNode::Type::AddExpr: {
            AddExpr addExpr = analyzeAddExpr(additiveExpression);
            if (addExpr.errorOccurred()) {
                return nullptr;
            }
            return make_unique<AddExpr>(move(addExpr));
        }
        case ASTNode::Type::SubtractExpr: {
            SubtractExpr subtractExpr = analyzeSubtractExpr(additiveExpression);
            if (subtractExpr.errorOccurred()) {
                return nullptr;
            }
            return make_unique<SubtractExpr>(move(subtractExpr));
        }
        default: {
            return analyzeType(type, additiveExpression.getMultiplicativeExpression());
        }
    }
}
//---------------------------------------------------------------------------
// Return the type the ast node should have
ASTNode::Type SemanticAnalysis::getTypeFromPrimaryExpression(const PrimaryExpression& primaryExpression) {
    if (primaryExpression.getData() == ParseTreeNode::Type::Identifier) {
        return ASTNode::Type::Parameter;
    } else if (primaryExpression.getData() == ParseTreeNode::Type::Literal) {
        return ASTNode::Type::Constant;
    } else {
        auto children = primaryExpression.getChildren();
        auto add = children[1];
        auto& addexpr = static_cast<AdditiveExpression&>(*add);
        return getTypeFromAdditiveExpression(addexpr);
    }
}
//---------------------------------------------------------------------------
// Return the type the ast node should have
ASTNode::Type SemanticAnalysis::getTypeFromUnaryExpression(const UnaryExpression& unaryExpression) {
    if (!unaryExpression.getTerminalSymbol().has_value())
        return getTypeFromPrimaryExpression(unaryExpression.getPrimaryExpression());
    else {
        if (codeM->getCharacters(unaryExpression.getTerminalSymbol()->reference()) == "+") {
            return ASTNode::Type::UnaryPlus;
        } else {
            return ASTNode::Type::UnaryMinus;
        }
    }
}
//---------------------------------------------------------------------------
// Return the type the ast node should have
ASTNode::Type SemanticAnalysis::getTypeFromMultiplicativeExpression(const MultiplicativeExpression& multiplicativeExpression) {
    if (!multiplicativeExpression.getTerminalSymbol().has_value()) {
        return getTypeFromUnaryExpression(multiplicativeExpression.getUnaryExpression());
    } else {
        if (codeM->getCharacters(multiplicativeExpression.getTerminalSymbol()->reference()) == "*")
            return ASTNode::Type::MulExpr;
        return ASTNode::Type::DivExpr;
    }
}
//---------------------------------------------------------------------------
// Return the type the ast node should have
ASTNode::Type SemanticAnalysis::getTypeFromAdditiveExpression(const AdditiveExpression& additiveExpression) {
    if (!additiveExpression.getTerminalSymbol().has_value()) {
        return getTypeFromMultiplicativeExpression(additiveExpression.getMultiplicativeExpression());
    } else {
        if (codeM->getCharacters(additiveExpression.getTerminalSymbol()->reference()) == "+")
            return ASTNode::Type::AddExpr;
        return ASTNode::Type::SubtractExpr;
    }
}
//---------------------------------------------------------------------------
} // namespace pljit::semanticanalysis
//---------------------------------------------------------------------------
