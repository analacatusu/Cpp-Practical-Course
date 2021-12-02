#include "pljit/parsetree/ParseTreePrintVisitor.hpp"
//---------------------------------------------------------------------------
namespace pljit::parsetree {
//---------------------------------------------------------------------------
// Draw a new node
void ParseTreePrintVisitor::initNewNode(size_t localParent, string_view str) {
    out << "\t" << localParent << "[label=\"" << str << "\"];\n";
    out << parentLabel << "-- " << localParent << ";\n";
}
//---------------------------------------------------------------------------
// Visit a terminal symbol
void ParseTreePrintVisitor::visit(const TerminalSymbol& terminalSymbol) {
    out << "\t" << currentLabel << "[label=\"";
    out << codeM->getCharacters(terminalSymbol.reference());
    out << "\"];\n";
    out << parentLabel << "-- " << currentLabel << ";\n";
    currentLabel++;
}
//---------------------------------------------------------------------------
// Visit an identifer
void ParseTreePrintVisitor::visit(const Identifier& identifier) {
    initNewNode(currentLabel, "identifier");
    currentLabel++;
    out << "\t" << currentLabel << "[label=\"";
    out << codeM->getCharacters(identifier.reference());
    out << "\"];\n";
    out << (currentLabel - 1) << "-- " << currentLabel << ";\n";
    currentLabel++;
}
//---------------------------------------------------------------------------
// Visit a literal
void ParseTreePrintVisitor::visit(const Literal& literal) {
    initNewNode(currentLabel, "literal");
    currentLabel++;
    out << "\t" << currentLabel << "[label=\"";
    out << codeM->getCharacters(literal.reference());
    out << "\"];\n";
    out << (currentLabel - 1) << "-- " << currentLabel << ";\n";
    currentLabel++;
}
//---------------------------------------------------------------------------
// Visit a function definition
void ParseTreePrintVisitor::visit(const FunctionDefinition& functionDefinition) {
    out << "graph {\n";
    out << "node [shape=plaintext, ordering=out];\n";
    const auto& params = functionDefinition.getParamDeclarations();
    size_t localParent = parentLabel;
    out << "\t" << localParent << "[label=\"function_definition\"];\n";
    if (params.has_value()) {
        params->accept(*this);
    }
    const auto& variables = functionDefinition.getVariableDeclarations();
    if (variables.has_value()) {
        parentLabel = localParent;
        variables->accept(*this);
    }
    const auto& constants = functionDefinition.getConstantDeclarations();
    if (constants.has_value()) {
        parentLabel = localParent;
        constants->accept(*this);
    }
    parentLabel = localParent;
    functionDefinition.getCompoundStatement().accept(*this);
    parentLabel = localParent;
    functionDefinition.getDot().accept(*this);
    out << "}\n";
}
//---------------------------------------------------------------------------
// Visit a parameter declaration
void ParseTreePrintVisitor::visit(const ParameterDeclarations& parameterDeclarations) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "parameter_declarations");
    parentLabel = localParent;
    parameterDeclarations.getBegin().accept(*this);
    parameterDeclarations.getDeclList().accept(*this);
    parentLabel = localParent;
    parameterDeclarations.getEndLine().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a variable declaration
void ParseTreePrintVisitor::visit(const VariableDeclarations& variableDeclarations) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "variable_declarations");
    parentLabel = localParent;
    variableDeclarations.getBegin().accept(*this);
    variableDeclarations.getDeclList().accept(*this);
    parentLabel = localParent;
    variableDeclarations.getEndLine().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a constant declaration
void ParseTreePrintVisitor::visit(const ConstantDeclarations& constantDeclarations) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "constant_declarations");
    parentLabel = localParent;
    constantDeclarations.getConstant().accept(*this);
    constantDeclarations.getInitDeclaratorList().accept(*this);
    parentLabel = localParent;
    constantDeclarations.getEndLine().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a declarator list
void ParseTreePrintVisitor::visit(const DeclaratorList& declaratorList) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "declarator_list");

    parentLabel = localParent;
    declaratorList.getIdentifier().accept(*this);
    const auto& children = declaratorList.getChildren();
    if (!children.empty()) {
        for (const auto& child : children) {
            const auto& [t, id] = child;
            t.accept(*this);
            id.accept(*this);
        }
    }
}
//---------------------------------------------------------------------------
// Visit an init declarator list
void ParseTreePrintVisitor::visit(const InitDeclaratorList& initDeclaratorList) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "init_declarator_list");

    parentLabel = localParent;
    initDeclaratorList.getInitDecl().accept(*this);
    const auto& children = initDeclaratorList.getChildren();

    if (!children.empty()) {
        for (const auto& child : children) {
            parentLabel = localParent;
            const auto& [t, init] = child;
            t.accept(*this);
            init.accept(*this);
        }
    }
}
//---------------------------------------------------------------------------
// Visit an init declarator
void ParseTreePrintVisitor::visit(const InitDeclarator& initDeclarator) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "init_declarator");

    parentLabel = localParent;

    initDeclarator.getIdentifier().accept(*this);
    initDeclarator.getEquals().accept(*this);
    initDeclarator.getLiteral().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a statement list
void ParseTreePrintVisitor::visit(const StatementList& statementList) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "statement_list");

    parentLabel = localParent;
    statementList.getStatement().accept(*this);
    const auto& children = statementList.getChildren();

    if (!children.empty()) {
        for (const auto& child : children) {
            parentLabel = localParent;
            const auto& [t, stmt] = child;
            t.accept(*this);
            stmt.accept(*this);
        }
    }
}
//---------------------------------------------------------------------------
// Visit a statement
void ParseTreePrintVisitor::visit(const Statement& statement) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "statement");

    parentLabel = localParent;

    if (statement.getData() == ParseTreeNode::Type::AssignmentExpression) {
        statement.getChildren()[0]->accept(*this);
    } else {
        statement.getChildren()[0]->accept(*this);
        statement.getChildren()[1]->accept(*this);
    }
}
//---------------------------------------------------------------------------
// Visit a compound statement
void ParseTreePrintVisitor::visit(const CompoundStatement& compoundStatement) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "compound_statement");
    parentLabel = localParent;
    compoundStatement.getBegin().accept(*this);
    compoundStatement.getStatementList().accept(*this);
    parentLabel = localParent;
    compoundStatement.getEnd().accept(*this);
}
//---------------------------------------------------------------------------
// Visit an assignment expression
void ParseTreePrintVisitor::visit(const AssignmentExpression& assignmentExpression) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "assignment_expression");

    parentLabel = localParent;

    assignmentExpression.getIdentifier().accept(*this);
    assignmentExpression.getAssignment().accept(*this);
    assignmentExpression.getAdditiveExpr().accept(*this);
}
//---------------------------------------------------------------------------
// Visit an additive expression
void ParseTreePrintVisitor::visit(const AdditiveExpression& additiveExpression) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "additive_expression");

    parentLabel = localParent;
    additiveExpression.getMultiplicativeExpression().accept(*this);

    if (additiveExpression.getTerminalSymbol().has_value() && additiveExpression.getAdditiveExpression().has_value()) {
        parentLabel = localParent;
        additiveExpression.getTerminalSymbol()->accept(*this);
        additiveExpression.getAdditiveExpression()->get()->accept(*this);
    }
}
//---------------------------------------------------------------------------
// Visit a multiplicative expression
void ParseTreePrintVisitor::visit(const MultiplicativeExpression& multiplicativeExpression) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "multiplicative_expression");

    parentLabel = localParent;
    multiplicativeExpression.getUnaryExpression().accept(*this);

    if (multiplicativeExpression.getTerminalSymbol().has_value() && multiplicativeExpression.getMultiplicativeExpression().has_value()) {
        parentLabel = localParent;
        multiplicativeExpression.getTerminalSymbol()->accept(*this);
        multiplicativeExpression.getMultiplicativeExpression()->get()->accept(*this);
    }
}
//---------------------------------------------------------------------------
// Visit a unary expression
void ParseTreePrintVisitor::visit(const UnaryExpression& unaryExpression) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "unary_expression");
    parentLabel = localParent;

    if (unaryExpression.getTerminalSymbol().has_value()) {
        unaryExpression.getTerminalSymbol()->accept(*this);
    }

    unaryExpression.getPrimaryExpression().accept(*this);
}
//---------------------------------------------------------------------------
// Visit a primary expression
void ParseTreePrintVisitor::visit(const PrimaryExpression& primaryExpression) {
    size_t localParent = currentLabel;
    currentLabel++;
    initNewNode(localParent, "primary_expression");

    parentLabel = localParent;
    const auto& children = primaryExpression.getChildren();
    if (primaryExpression.getData() == ParseTreeNode::Type::Identifier || primaryExpression.getData() == ParseTreeNode::Type::Literal) {
        children[0]->accept(*this);
    } else {
        children[0]->accept(*this);
        children[1]->accept(*this);
        parentLabel = localParent;
        children[2]->accept(*this);
    }
}
//---------------------------------------------------------------------------
} // namespace pljit::parsetree
//---------------------------------------------------------------------------
