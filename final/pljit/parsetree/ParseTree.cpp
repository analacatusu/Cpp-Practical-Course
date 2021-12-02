#include "pljit/parsetree/ParseTree.hpp"
//---------------------------------------------------------------------------
namespace pljit::parsetree {
//---------------------------------------------------------------------------
// Overridden accept function
void Literal::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
Literal::Literal(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
Literal::Literal(Reference ref, int64_t val, bool succ) : ParseTreeNode(ref), val(val), succ(succ) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
TerminalSymbol::TerminalSymbol(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
TerminalSymbol::TerminalSymbol(Reference ref, bool succ) : ParseTreeNode(ref), succ(succ) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void TerminalSymbol::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
Identifier::Identifier(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
Identifier::Identifier(Reference ref, bool succ) : ParseTreeNode(ref), succ(succ) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void Identifier::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
PrimaryExpression::PrimaryExpression(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
PrimaryExpression::PrimaryExpression(Reference ref, ParseTreeNode::Type data, vector<shared_ptr<ParseTreeNode>> children)
    : ParseTreeNode(ref), data(data), children(move(children)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void PrimaryExpression::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
UnaryExpression::UnaryExpression(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
UnaryExpression::UnaryExpression(Reference ref, optional<TerminalSymbol> terminalSymbol, PrimaryExpression primaryExpression)
    : ParseTreeNode(ref), terminalSymbol(move(terminalSymbol)), primaryExpression(move(primaryExpression)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void UnaryExpression::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
MultiplicativeExpression::MultiplicativeExpression(Reference ref, UnaryExpression unaryExpression, optional<TerminalSymbol> terminalSymbol, optional<shared_ptr<MultiplicativeExpression>> mulExpr)
    : ParseTreeNode(ref), unaryExpression(move(unaryExpression)), terminalSymbol(move(terminalSymbol)), mulExpr(move(mulExpr)) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
MultiplicativeExpression::MultiplicativeExpression(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void MultiplicativeExpression::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
AdditiveExpression::AdditiveExpression(Reference ref, MultiplicativeExpression multiplicativeExpression, optional<TerminalSymbol> terminalSymbol, optional<shared_ptr<AdditiveExpression>> addExpr)
    : ParseTreeNode(ref), multiplicativeExpression(move(multiplicativeExpression)), terminalSymbol(move(terminalSymbol)), addExpr(move(addExpr)) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
AdditiveExpression::AdditiveExpression(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void AdditiveExpression::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
AssignmentExpression::AssignmentExpression(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
AssignmentExpression::AssignmentExpression(Identifier id, TerminalSymbol assignment, AdditiveExpression additiveExpression, Reference ref)
    : ParseTreeNode(ref), id(move(id)), assignment(move(assignment)), additiveExpression(move(additiveExpression)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void AssignmentExpression::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
Statement::Statement(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
Statement::Statement(Reference ref, ParseTreeNode::Type data, vector<shared_ptr<ParseTreeNode>> children)
    : ParseTreeNode(ref), data(data), children(move(children)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void Statement::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
StatementList::StatementList(Reference ref, Statement statement, vector<pair<TerminalSymbol, Statement>> children)
    : ParseTreeNode(ref), statement(move(statement)), children(move(children)) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
StatementList::StatementList(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void StatementList::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
DeclaratorList::DeclaratorList(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
DeclaratorList::DeclaratorList(Reference ref, Identifier identifier, vector<pair<TerminalSymbol, Identifier>> children)
    : ParseTreeNode(ref), identifier(move(identifier)), children(move(children)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void DeclaratorList::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
InitDeclarator::InitDeclarator(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
InitDeclarator::InitDeclarator(Identifier identifier, TerminalSymbol equals, Literal literal, Reference ref)
    : ParseTreeNode(ref), identifier(move(identifier)), equals(move(equals)), literal(move(literal)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void InitDeclarator::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
InitDeclaratorList::InitDeclaratorList(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
InitDeclaratorList::InitDeclaratorList(Reference ref, InitDeclarator initDeclarator, vector<pair<TerminalSymbol, InitDeclarator>> children)
    : ParseTreeNode(ref), initDeclarator(move(initDeclarator)), children(move(children)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void InitDeclaratorList::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
Declarations::Declarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref)
    : ParseTreeNode(ref), begin(move(begin)), declaratorList(move(declaratorList)), endLine(move(endLine)) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
Declarations::Declarations(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
ParameterDeclarations::ParameterDeclarations(bool error) : Declarations(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
ParameterDeclarations::ParameterDeclarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref)
    : Declarations(move(begin), move(declaratorList), move(endLine), ref) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void ParameterDeclarations::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
VariableDeclarations::VariableDeclarations(bool error) : Declarations(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
VariableDeclarations::VariableDeclarations(TerminalSymbol begin, DeclaratorList declaratorList, TerminalSymbol endLine, Reference ref)
    : Declarations(move(begin), move(declaratorList), move(endLine), ref) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void VariableDeclarations::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
ConstantDeclarations::ConstantDeclarations(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
ConstantDeclarations::ConstantDeclarations(TerminalSymbol constant, InitDeclaratorList initDeclaratorList, TerminalSymbol endLine, Reference ref)
    : ParseTreeNode(ref), constant(move(constant)), initDeclaratorList(move(initDeclaratorList)), endLine(move(endLine)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void ConstantDeclarations::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
CompoundStatement::CompoundStatement(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
CompoundStatement::CompoundStatement(Reference ref, TerminalSymbol begin, StatementList statementList, TerminalSymbol end)
    : ParseTreeNode(ref), begin(move(begin)), statementList(move(statementList)), end(move(end)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void CompoundStatement::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
// Constructor in case an error occurred
FunctionDefinition::FunctionDefinition(bool error) : ParseTreeNode(error) {
}
//---------------------------------------------------------------------------
// Constructor with given children nodes
FunctionDefinition::FunctionDefinition(Reference ref, optional<ParameterDeclarations> paramDecl, optional<VariableDeclarations> varDecl, optional<ConstantDeclarations> constDecl, CompoundStatement compoundStatement, TerminalSymbol dot)
    : ParseTreeNode(ref), paramDecl(move(paramDecl)), varDecl(move(varDecl)), constDecl(move(constDecl)), compoundStatement(move(compoundStatement)), dot(move(dot)) {
}
//---------------------------------------------------------------------------
// Overridden accept function
void FunctionDefinition::accept(ParseTreeVisitor& visitor) const {
    visitor.visit(*this);
}
//---------------------------------------------------------------------------
} // namespace pljit::parsetree
//---------------------------------------------------------------------------
