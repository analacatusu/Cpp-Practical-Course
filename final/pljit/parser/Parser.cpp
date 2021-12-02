#include "pljit/parser/Parser.hpp"
//---------------------------------------------------------------------------
namespace pljit::parser {
//---------------------------------------------------------------------------
// Parse a literal
Literal Parsing::literal() {
    Reference ref;
    int64_t value = 0;
    bool success;

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return Literal(true);
    }

    if (currentToken.tokenType() == Token::TokenType::Literal) {
        ref = currentToken.reference();
        value = computeVal(ref);
        success = true;
        currentToken = lex.next();
    } else {
        success = false;
    }
    return Literal(ref, value, success);
}
//---------------------------------------------------------------------------
// Parse a terminal symbol
TerminalSymbol Parsing::match(Token::TokenType type) {
    Reference ref;
    bool success;

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return TerminalSymbol(true);
    }

    if (currentToken.tokenType() == type) {
        ref = currentToken.reference();
        success = true;
        currentToken = lex.next();
    } else {
        ref = Reference(-1);
        success = false;
    }

    return TerminalSymbol(ref, success);
}
//---------------------------------------------------------------------------
// Parse an identifier
Identifier Parsing::identifier() {
    Reference ref;
    bool success;

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return Identifier(true);
    }

    if (currentToken.tokenType() == Token::TokenType::Identifier) {
        ref = currentToken.reference();
        success = true;
        currentToken = lex.next();
    } else {
        success = false;
    }

    return Identifier(ref, success);
}
//---------------------------------------------------------------------------
// Parse a primary expression
PrimaryExpression Parsing::primary_expression() {
    ParseTreeNode::Type data;
    vector<shared_ptr<ParseTreeNode>> children;
    Reference ref;

    Identifier id = identifier();

    if (id.errorOccurred()) {
        return PrimaryExpression(true);
    }

    if (id.success()) {
        data = ParseTreeNode::Type::Identifier;
        children.push_back(make_shared<Identifier>(id));
        ref = id.reference();
        return PrimaryExpression(ref, data, children);
    }

    Literal l = literal();

    if (l.errorOccurred()) {
        return PrimaryExpression(true);
    }

    if (l.success()) {
        data = ParseTreeNode::Type::Literal;
        children.push_back(make_shared<Literal>(l));
        ref = l.reference();
        return PrimaryExpression(ref, data, children);
    }

    TerminalSymbol leftParan = match(Token::TokenType::LeftParanthesis);

    if (leftParan.errorOccurred()) {
        return PrimaryExpression(true);
    }

    if (leftParan.success()) {
        ref = leftParan.reference();
        AdditiveExpression additiveExpression = additive_expression();

        if (additiveExpression.errorOccurred()) {
            return PrimaryExpression(true);
        }

        TerminalSymbol rightParan = match(Token::TokenType::RightParanthesis);

        if (rightParan.errorOccurred()) {
            return PrimaryExpression(true);
        }

        if (rightParan.success()) {
            data = ParseTreeNode::Type::AdditiveExpression;
            children.push_back(make_shared<TerminalSymbol>(leftParan));
            children.push_back(make_shared<AdditiveExpression>(additiveExpression));
            children.push_back(make_shared<TerminalSymbol>(rightParan));
            ref.length = rightParan.reference().begin + 1 - ref.begin;
        } else {
            codeM->errorMissingEndParanthesis(currentToken.reference());
            return PrimaryExpression(true);
        }
        return PrimaryExpression(ref, data, children);
    }

    codeM->errorInvalidPrimaryExpr(currentToken.reference());
    return PrimaryExpression(true);
}
//---------------------------------------------------------------------------
// Parse a unary expression
UnaryExpression Parsing::unary_expression() {
    Reference ref;
    optional<TerminalSymbol> terminalSymbol;
    PrimaryExpression primaryExpression;

    terminalSymbol = match(Token::TokenType::UnaryPlusOperator);

    if (static_cast<int>(terminalSymbol->reference().begin) == -1) {
        terminalSymbol = match(Token::TokenType::UnaryMinusOperator);
        if (static_cast<int>(terminalSymbol->reference().begin) == -1) {
            terminalSymbol = nullopt;
        } else {
            ref = terminalSymbol->reference();
        }
    } else {
        ref = terminalSymbol->reference();
    }

    primaryExpression = primary_expression();

    if (primaryExpression.errorOccurred()) {
        return UnaryExpression(true);
    }

    if (ref.begin == 0) {
        ref = primaryExpression.reference();
    } else {
        ref.length = primaryExpression.reference().length + 1;
    }

    return UnaryExpression(ref, terminalSymbol, primaryExpression);
}
//---------------------------------------------------------------------------
// Parse a multiplicative expression
MultiplicativeExpression Parsing::multiplicative_expression() {
    Reference ref;
    UnaryExpression unaryExpression;
    optional<TerminalSymbol> terminalSymbol;
    optional<shared_ptr<MultiplicativeExpression>> mulExpr;

    unaryExpression = unary_expression();

    if (unaryExpression.errorOccurred()) {
        return MultiplicativeExpression(true);
    }

    ref = unaryExpression.reference();
    terminalSymbol = match(Token::TokenType::MulOperator);

    if (static_cast<int>(terminalSymbol->reference().begin) != -1) {
        MultiplicativeExpression mul = multiplicative_expression();
        if (mul.errorOccurred()) {
            return MultiplicativeExpression(true);
        }

        mulExpr = make_shared<MultiplicativeExpression>(move(mul));

    } else {
        terminalSymbol = match(Token::TokenType::DivOperator);

        if (static_cast<int>(terminalSymbol->reference().begin) != -1) {
            MultiplicativeExpression mul = multiplicative_expression();
            if (mul.errorOccurred()) {
                return MultiplicativeExpression(true);
            }
            mulExpr = make_shared<MultiplicativeExpression>(move(mul));

        } else {
            terminalSymbol = nullopt;
            mulExpr = nullopt;
        }
    }
    ref.length = currentToken.reference().begin - ref.begin;
    return MultiplicativeExpression(ref, unaryExpression, terminalSymbol, move(mulExpr));
}
//---------------------------------------------------------------------------
// Parse an additive expression
AdditiveExpression Parsing::additive_expression() {
    Reference ref;
    MultiplicativeExpression multiplicativeExpression;
    optional<TerminalSymbol> terminalSymbol;
    optional<shared_ptr<AdditiveExpression>> addExpr;

    multiplicativeExpression = multiplicative_expression();

    if (multiplicativeExpression.errorOccurred()) {
        return AdditiveExpression(true);
    }

    ref = multiplicativeExpression.reference();
    terminalSymbol = match(Token::TokenType::BinaryPlusOperator);

    if (static_cast<int>(terminalSymbol->reference().begin) != -1) {
        AdditiveExpression add = additive_expression();
        if (add.errorOccurred()) {
            return AdditiveExpression(true);
        }
        addExpr = make_shared<AdditiveExpression>(move(add));

    } else {
        terminalSymbol = match(Token::TokenType::BinaryMinusOperator);

        if (static_cast<int>(terminalSymbol->reference().begin) != -1) {
            AdditiveExpression add = additive_expression();
            if (add.errorOccurred()) {
                return AdditiveExpression(true);
            }
            addExpr = make_shared<AdditiveExpression>(add);
        } else {
            terminalSymbol = nullopt;
            addExpr = nullopt;
        }
    }
    ref.length = currentToken.reference().begin - ref.begin;
    return AdditiveExpression(ref, multiplicativeExpression, terminalSymbol, addExpr);
}
//---------------------------------------------------------------------------
// Parse an assignment expression
AssignmentExpression Parsing::assignment_expression() {
    Identifier id;
    TerminalSymbol assignment;
    AdditiveExpression additiveExpression;
    Reference ref;

    id = identifier();
    if (id.errorOccurred()) {
        return AssignmentExpression(true);
    }

    assignment = match(Token::TokenType::AssignmentOperator);
    if (!assignment.success()) {
        codeM->errorMissingAssignmentOperator(currentToken.reference());
        return AssignmentExpression(true);
    }

    additiveExpression = additive_expression();
    if (additiveExpression.errorOccurred()) {
        return AssignmentExpression(true);
    }

    ref.begin = id.reference().begin;
    ref.length = additiveExpression.reference().length + additiveExpression.reference().begin - id.reference().begin;

    return AssignmentExpression(id, assignment, additiveExpression, ref);
}
//---------------------------------------------------------------------------
// Parse a statement
Statement Parsing::statement() {
    Reference ref;
    ParseTreeNode::Type data;
    vector<shared_ptr<ParseTreeNode>> children;

    if (currentToken.tokenType() == Token::TokenType::EndKeyword) {
        codeM->errorEndline(currentToken.reference());
        return Statement(true);
    }

    TerminalSymbol ret = match(Token::TokenType::ReturnKeyword);

    if (ret.errorOccurred()) {
        return Statement(true);
    }

    if (ret.success()) {
        children.push_back(make_shared<TerminalSymbol>(ret));
        AdditiveExpression additiveExpression = additive_expression();

        if (additiveExpression.errorOccurred()) {
            return Statement(true);
        }

        children.push_back(make_shared<AdditiveExpression>(additiveExpression));
        data = ParseTreeNode::Type::AdditiveExpression;
        ref.begin = ret.reference().begin;
        ref.length = additiveExpression.reference().length + additiveExpression.reference().begin - ret.reference().begin;
    } else {
        AssignmentExpression assignmentExpression = assignment_expression();
        if (assignmentExpression.errorOccurred()) {
            return Statement(true);
        }

        children.push_back(make_shared<AssignmentExpression>(assignmentExpression));
        data = ParseTreeNode::Type::AssignmentExpression;
        ref = assignmentExpression.reference();
    }
    return Statement(ref, data, children);
}
//---------------------------------------------------------------------------
// Parse a statement list
StatementList Parsing::statement_list() {
    Reference ref;
    Statement stmt;
    vector<pair<TerminalSymbol, Statement>> children;

    stmt = statement();

    if (stmt.errorOccurred()) {
        return StatementList(true);
    }

    ref = stmt.reference();
    TerminalSymbol t = match(Token::TokenType::EndLineSeparator);

    if (t.errorOccurred()) {
        return StatementList(true);
    }

    while (static_cast<int>(t.reference().begin) != -1) {
        Statement st = statement();

        if (st.errorOccurred()) {
            return StatementList(true);
        }

        children.emplace_back(pair<TerminalSymbol, Statement>(t, st));
        ref.length = st.reference().length + st.reference().begin - ref.begin;
        t = match(Token::TokenType::EndLineSeparator);
        if (t.errorOccurred()) {
            return StatementList(true);
        }
    }
    return StatementList(ref, stmt, children);
}
//---------------------------------------------------------------------------
// Parse a declarator list
DeclaratorList Parsing::declarator_list() {
    Reference ref;
    Identifier identif;
    vector<pair<TerminalSymbol, Identifier>> children;

    identif = identifier();

    if (identif.errorOccurred()) {
        return DeclaratorList(true);
    }

    if (!identif.success()) {
        codeM->errorBadIdentifier(currentToken.reference());
        return DeclaratorList(true);
    }

    ref = identif.reference();
    TerminalSymbol t = match(Token::TokenType::CommaSeparator);

    if (t.errorOccurred()) {
        return DeclaratorList(true);
    }

    while (static_cast<int>(t.reference().begin) != -1) {
        Identifier id = identifier();

        if (id.errorOccurred()) {
            return DeclaratorList(true);
        }

        if (!id.success()) {
            codeM->errorBadIdentifier(currentToken.reference());
            return DeclaratorList(true);
        }

        children.emplace_back(pair<TerminalSymbol, Identifier>(t, id));
        ref.length = id.reference().length + id.reference().begin - ref.begin;
        t = match(Token::TokenType::CommaSeparator);

        if (t.errorOccurred()) {
            return DeclaratorList(true);
        }
    }
    return DeclaratorList(ref, identif, children);
}
//---------------------------------------------------------------------------
// Parse an init declarator
InitDeclarator Parsing::init_declarator() {
    Identifier identif;
    TerminalSymbol equals;
    Literal l;
    Reference ref;

    identif = identifier();
    if (identif.errorOccurred()) {
        return InitDeclarator(true);
    }

    if (!identif.success()) {
        codeM->errorBadIdentifier(currentToken.reference());
        return InitDeclarator(true);
    }

    equals = match(Token::TokenType::AssignmentOperatorDecl);
    if (equals.errorOccurred()) {
        return InitDeclarator(true);
    }

    if (!equals.success()) {
        codeM->errorBadAssignment(currentToken.reference());
        return InitDeclarator(true);
    }

    l = literal();
    if (l.errorOccurred()) {
        return InitDeclarator(true);
    }

    if (!l.success()) {
        codeM->errorBadLiteral(currentToken.reference());
        return InitDeclarator(true);
    }

    ref.begin = identif.reference().begin;
    ref.length = l.reference().length + l.reference().begin - ref.begin;
    return InitDeclarator(identif, equals, l, ref);
}
//---------------------------------------------------------------------------
// Parse an init declarator list
InitDeclaratorList Parsing::initdeclarator_list() {
    Reference ref;
    InitDeclarator initDeclarator;
    vector<pair<TerminalSymbol, InitDeclarator>> children;

    initDeclarator = init_declarator();

    if (initDeclarator.errorOccurred()) {
        return InitDeclaratorList(true);
    }

    ref = initDeclarator.reference();
    TerminalSymbol t = match(Token::TokenType::CommaSeparator);

    if (t.errorOccurred()) {
        return InitDeclaratorList(true);
    }

    while (static_cast<int>(t.reference().begin) != -1) {
        InitDeclarator init = init_declarator();

        if (init.errorOccurred()) {
            return InitDeclaratorList(true);
        }

        children.emplace_back(pair<TerminalSymbol, InitDeclarator>(t, init));
        ref.length = init.reference().length + init.reference().begin - ref.begin;
        t = match(Token::TokenType::CommaSeparator);

        if (t.errorOccurred()) {
            return InitDeclaratorList(true);
        }
    }
    return InitDeclaratorList(ref, initDeclarator, children);
}
//---------------------------------------------------------------------------
// Parse the parameter declarations
ParameterDeclarations Parsing::parameter_declarations() {
    TerminalSymbol begin;
    DeclaratorList declaratorList;
    TerminalSymbol endLine;
    Reference ref;

    begin = match(Token::TokenType::ParamKeyword);

    if (begin.errorOccurred()) {
        return ParameterDeclarations(true);
    }

    if (!begin.success()) {
        codeM->errorWrongDeclaration(currentToken.reference());
        return ParameterDeclarations(true);
    }

    declaratorList = declarator_list();
    if (declaratorList.errorOccurred()) {
        return ParameterDeclarations(true);
    }

    endLine = match(Token::TokenType::EndLineSeparator);

    if (endLine.errorOccurred()) {
        return ParameterDeclarations(true);
    }

    if (!endLine.success()) {
        codeM->errorDeclarations(currentToken.reference());
        return ParameterDeclarations(true);
    }

    ref.begin = begin.reference().begin;
    ref.length = endLine.reference().length + endLine.reference().begin - ref.begin;
    return ParameterDeclarations(begin, declaratorList, endLine, ref);
}
//---------------------------------------------------------------------------
// Parse the variable declarations
VariableDeclarations Parsing::variable_declarations() {
    TerminalSymbol begin;
    DeclaratorList declaratorList;
    TerminalSymbol endLine;
    Reference ref;

    begin = match(Token::TokenType::VarKeyword);

    if (begin.errorOccurred()) {
        return VariableDeclarations(true);
    }

    if (!begin.success()) {
        codeM->errorWrongDeclaration(currentToken.reference());
        return VariableDeclarations(true);
    }

    declaratorList = declarator_list();
    if (declaratorList.errorOccurred()) {
        return VariableDeclarations(true);
    }
    endLine = match(Token::TokenType::EndLineSeparator);

    if (endLine.errorOccurred()) {
        return VariableDeclarations(true);
    }

    if (!endLine.success()) {
        codeM->errorDeclarations(currentToken.reference());
        return VariableDeclarations(true);
    }
    ref.begin = begin.reference().begin;
    ref.length = endLine.reference().length + endLine.reference().begin - ref.begin;

    return VariableDeclarations(begin, declaratorList, endLine, ref);
}
//---------------------------------------------------------------------------
// Parse the constant declarations
ConstantDeclarations Parsing::constant_declarations() {
    TerminalSymbol constant;
    InitDeclaratorList initDeclaratorList;
    TerminalSymbol endLine;
    Reference ref;

    constant = match(Token::TokenType::ConstKeyword);
    if (constant.errorOccurred()) {
        return ConstantDeclarations(true);
    }
    if (!constant.success()) {
        codeM->errorWrongDeclaration(currentToken.reference());
        return ConstantDeclarations(true);
    }

    initDeclaratorList = initdeclarator_list();
    if (initDeclaratorList.errorOccurred()) {
        return ConstantDeclarations(true);
    }
    endLine = match(Token::TokenType::EndLineSeparator);
    if (endLine.errorOccurred()) {
        return ConstantDeclarations(true);
    }

    if (!endLine.success()) {
        codeM->errorDeclarations(currentToken.reference());
        return ConstantDeclarations(true);
    }

    ref.begin = constant.reference().begin;
    ref.length = endLine.reference().length + endLine.reference().begin - ref.begin;
    return ConstantDeclarations(constant, initDeclaratorList, endLine, ref);
}
//---------------------------------------------------------------------------
// Parse a compound statement
CompoundStatement Parsing::compound_statement() {
    Reference ref;
    TerminalSymbol begin;
    StatementList statementList;
    TerminalSymbol end;

    begin = match(Token::TokenType::BeginKeyword);
    if (begin.errorOccurred()) {
        return CompoundStatement(true);
    }

    statementList = statement_list();
    if (statementList.errorOccurred()) {
        return CompoundStatement(true);
    }

    end = match(Token::TokenType::EndKeyword);
    if (end.errorOccurred()) {
        return CompoundStatement(true);
    }
    if (!end.success()) {
        codeM->errorAnalyzingStatements(currentToken.reference());
        return CompoundStatement(true);
    }
    ref.begin = begin.reference().begin;
    ref.length = end.reference().length + end.reference().begin - ref.begin;
    return CompoundStatement(ref, begin, statementList, end);
}
//---------------------------------------------------------------------------
// Parse a function definition
FunctionDefinition Parsing::function_definition() {
    Reference ref;
    optional<ParameterDeclarations> paramDecl;
    optional<VariableDeclarations> varDecl;
    optional<ConstantDeclarations> constDecl;
    CompoundStatement compoundStatement;
    TerminalSymbol dot;

    bool beginRef = false;

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return FunctionDefinition(true);
    }

    if (currentToken.tokenType() == Token::TokenType::ParamKeyword) {
        ParameterDeclarations params = parameter_declarations();
        if (params.errorOccurred()) {
            return FunctionDefinition(true);
        }
        paramDecl = params;
        ref.begin = params.reference().begin;
        beginRef = true;
    } else {
        paramDecl = nullopt;
    }

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return FunctionDefinition(true);
    }
    if (currentToken.tokenType() == Token::TokenType::VarKeyword) {
        VariableDeclarations vars = variable_declarations();
        if (vars.errorOccurred()) {
            return FunctionDefinition(true);
        }
        varDecl = vars;
        if (!beginRef) {
            ref.begin = vars.reference().begin;
            beginRef = true;
        }
    } else {
        varDecl = nullopt;
    }

    if (currentToken.tokenType() == Token::TokenType::Unexpected) {
        return FunctionDefinition(true);
    }

    if (currentToken.tokenType() == Token::TokenType::ConstKeyword) {
        ConstantDeclarations constants = constant_declarations();
        if (constants.errorOccurred()) {
            return FunctionDefinition(true);
        }
        constDecl = constants;
        if (!beginRef) {
            ref.begin = constants.reference().begin;
            beginRef = true;
        }
    } else {
        constDecl = nullopt;
    }

    if (currentToken.tokenType() != Token::TokenType::BeginKeyword) {
        codeM->errorMissingBegin(currentToken.reference());
        return FunctionDefinition(true);
    }

    compoundStatement = compound_statement();
    if (compoundStatement.errorOccurred()) {
        return FunctionDefinition(true);
    }
    if (!beginRef) {
        ref.begin = compoundStatement.reference().begin;
    }

    dot = match(Token::TokenType::Dot);

    if (dot.errorOccurred()) {
        codeM->errorMissingDot();
        return FunctionDefinition(true);
    }

    ref.length = dot.reference().length + dot.reference().begin - ref.begin;
    return FunctionDefinition(ref, paramDecl, varDecl, constDecl, compoundStatement, dot);
}
//---------------------------------------------------------------------------
// Start the parsing process
void Parsing::parsing() {
    currentToken = lex.next();
    funcDef = function_definition();
    if (funcDef.errorOccurred()) {
        error = true;
    }
}
//---------------------------------------------------------------------------
// Compute the actual value of a literal
int64_t Parsing::computeVal(Reference ref) {
    string_view str = codeM->getCharacters(ref);
    return stoi(string{str});
}
//---------------------------------------------------------------------------
} // namespace pljit::parser
//---------------------------------------------------------------------------
