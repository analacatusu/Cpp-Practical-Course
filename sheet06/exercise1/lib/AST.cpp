#include "lib/AST.hpp"
#include <cmath>
#include <iostream>
//---------------------------------------------------------------------------
namespace ast {
// Constructor
Constant::Constant(double val) : ASTNode(), value(val) {}
//---------------------------------------------------------------------------
// Get the value
double Constant::getValue() const { return value; }
//---------------------------------------------------------------------------
// Set the value
void Constant::setValue(double val) { value = val; }
//---------------------------------------------------------------------------
// Overriden evaluate function
double Constant::evaluate(const EvaluationContext &) const { return value; }
//---------------------------------------------------------------------------
// Overriden optimize function
void Constant::optimize(std::unique_ptr<ASTNode> &) { return; }
//---------------------------------------------------------------------------
// Overriden accept function
void Constant::accept(ASTVisitor &visitor) const { visitor.visit(*this); }
//---------------------------------------------------------------------------
// Constructor
Parameter::Parameter(int indx) : ASTNode(), index(indx) {}
//---------------------------------------------------------------------------
// Get the index
size_t Parameter::getIndex() const { return index; }
//---------------------------------------------------------------------------
// Overriden evaluate function
double Parameter::evaluate(const EvaluationContext &context) const {
  double v = context.getParameter(index);
  return v;
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Parameter::optimize(std::unique_ptr<ASTNode> &) { return; }
//---------------------------------------------------------------------------
// Overriden accept function
void Parameter::accept(ASTVisitor &visitor) const { visitor.visit(*this); }
//---------------------------------------------------------------------------
// Contructor
UnaryASTNode::UnaryASTNode(std::unique_ptr<ASTNode> ch)
    : ASTNode(), child(std::move(ch)) {}
//---------------------------------------------------------------------------
// Transfer ownership to the caller
std::unique_ptr<ASTNode> UnaryASTNode::releaseInput() {
  return std::move(child);
}
//---------------------------------------------------------------------------
// Get cont reference to the child node
const ASTNode &UnaryASTNode::getInput() const { return *child; }
//---------------------------------------------------------------------------
// Constructor
UnaryMinus::UnaryMinus(std::unique_ptr<ASTNode> ch)
    : UnaryASTNode(std::move(ch)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double UnaryMinus::evaluate(const EvaluationContext &context) const {
  double val = child->evaluate(context);
  return -val;
}
//---------------------------------------------------------------------------
// Overriden optimize function
void UnaryMinus::optimize(std::unique_ptr<ASTNode> &thisRef) {
  child->optimize(child);

  switch (child.get()->getType()) {
  // Propagate constant
  case ASTNode::Type::Constant: {
    Constant &c = static_cast<Constant &>(*child);
    thisRef = std::make_unique<Constant>(-c.getValue());
    break;
  }

  // Convert -(-x) to x
  case ASTNode::Type::UnaryMinus: {
    UnaryMinus &m = static_cast<UnaryMinus &>(*child);
    std::unique_ptr<ASTNode> in = m.releaseInput();
    thisRef = std::move(in);
    break;
  }

  // Convert -(a - b) to b - a
  case ASTNode::Type::Subtract: {
    Subtract &s = static_cast<Subtract &>(*child);
    std::unique_ptr<ASTNode> a = s.releaseLeft();
    std::unique_ptr<ASTNode> b = s.releaseRight();
    thisRef = std::make_unique<Subtract>(std::move(b), std::move(a));
    break;
  }

  default:
    return;
  }

  // Try to optimize again if AST was changed
  thisRef->optimize(thisRef);
}
//---------------------------------------------------------------------------
// Overriden accept function
void UnaryMinus::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  visitor.visit(*this);
  child->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
UnaryPlus::UnaryPlus(std::unique_ptr<ASTNode> ch)
    : UnaryASTNode(std::move(ch)) {}
//---------------------------------------------------------------------------
// Overridden evaluate function
double UnaryPlus::evaluate(const EvaluationContext &context) const {
  return +child->evaluate(context);
}
//---------------------------------------------------------------------------
// Overriden optimize function
void UnaryPlus::optimize(std::unique_ptr<ASTNode> &thisRef) {
  child->optimize(child);
  std::unique_ptr<ASTNode> input = std::move(child);
  thisRef = std::move(input);
}
//---------------------------------------------------------------------------
// Overriden accept function
void UnaryPlus::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  visitor.visit(*this);
  child->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
BinaryASTNode::BinaryASTNode(std::unique_ptr<ASTNode> l,
                             std::unique_ptr<ASTNode> r)
    : ASTNode(), left(std::move(l)), right(std::move(r)) {}
//---------------------------------------------------------------------------
// Transfer ownership to the caller
std::unique_ptr<ASTNode> BinaryASTNode::releaseLeft() {
  return std::move(left);
}
//---------------------------------------------------------------------------
// Transfer ownership to the caller
std::unique_ptr<ASTNode> BinaryASTNode::releaseRight() {
  return std::move(right);
}
//---------------------------------------------------------------------------
// Get const reference of the left child node
const ASTNode &BinaryASTNode::getLeft() { return *left; }
//---------------------------------------------------------------------------
// Get const reference of the right child node
const ASTNode &BinaryASTNode::getRight() { return *right; }
//---------------------------------------------------------------------------
// Check if left child node is 0
bool BinaryASTNode::checkLeftValueZero() const {
  if (left.get()->getType() == ASTNode::Type::Constant) {
    auto *leftPtr = static_cast<Constant *>(left.get());
    if (leftPtr->getValue() == 0.0)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Check if left child node is 1
bool BinaryASTNode::checkLeftValueOne() const {
  if (left.get()->getType() == ASTNode::Type::Constant) {
    auto *leftPtr = static_cast<Constant *>(left.get());
    if (leftPtr->getValue() == 1.0)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Check if right child node is 0
bool BinaryASTNode::checkRightValueZero() const {
  if (right->getType() == ASTNode::Type::Constant) {
    auto *rightPtr = static_cast<Constant *>(right.get());
    if (rightPtr->getValue() == 0.0)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Check if right child node is 1
bool BinaryASTNode::checkRightValueOne() const {
  if (right->getType() == ASTNode::Type::Constant) {
    auto *rightPtr = static_cast<Constant *>(right.get());
    if (rightPtr->getValue() == 1.0)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Check if right child node is -1
bool BinaryASTNode::checkRightValueMinusOne() const {
  if (right->getType() == ASTNode::Type::Constant) {
    auto *rightPtr = static_cast<Constant *>(right.get());
    if (rightPtr->getValue() == -1.0)
      return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Optimize if children only have constants
bool BinaryASTNode::optimizeConstants(std::unique_ptr<ASTNode> &thisRef) {
  if (left->getType() == ASTNode::Type::Constant &&
      right->getType() == ASTNode::Type::Constant) {
    EvaluationContext context;
    double value = this->evaluate(context);
    thisRef = std::make_unique<Constant>(value);
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------
// Constructor
Subtract::Subtract(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    : BinaryASTNode(std::move(l), std::move(r)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double Subtract::evaluate(const EvaluationContext &context) const {
  return left->evaluate(context) - right->evaluate(context);
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Subtract::optimize(std::unique_ptr<ASTNode> &thisRef) {
  left->optimize(left);
  right->optimize(right);

  if (checkLeftValueZero()) {
    thisRef = std::make_unique<UnaryMinus>(std::move(right));
    return;
  }

  if (checkRightValueZero()) {
    thisRef = std::move(left);
    return;
  }

  if (optimizeConstants(thisRef)) {
    return;
  }

  // a - (-b) => a + b
  if (right->getType() == ASTNode::Type::UnaryMinus) {
    UnaryMinus &minusRight = static_cast<UnaryMinus &>(*right);
    std::unique_ptr<ASTNode> a = std::move(left);
    std::unique_ptr<ASTNode> b = minusRight.releaseInput();
    thisRef = std::make_unique<Add>(std::move(a), std::move(b));
    thisRef->optimize(thisRef);
    return;
  }
}
//---------------------------------------------------------------------------
// Overriden accept function
void Subtract::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  left->accept(visitor);
  visitor.visit(*this);
  right->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
Add::Add(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    : BinaryASTNode(std::move(l), std::move(r)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double Add::evaluate(const EvaluationContext &context) const {
  return left->evaluate(context) + right->evaluate(context);
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Add::optimize(std::unique_ptr<ASTNode> &thisRef) {
  left->optimize(left);
  right->optimize(right);

  // 0 + a => a
  if (checkLeftValueZero()) {
    std::unique_ptr<ASTNode> r = std::move(right);
    thisRef = std::move(r);
    return;
  }

  // a + 0 => a
  if (checkRightValueZero()) {
    std::unique_ptr<ASTNode> l = std::move(left);
    thisRef = std::move(l);
    return;
  }

  // -a + b => b - a
  if (left->getType() == ASTNode::Type::UnaryMinus) {
    UnaryMinus &minusLeft = static_cast<UnaryMinus &>(*left);
    std::unique_ptr<ASTNode> a = minusLeft.releaseInput();
    std::unique_ptr<ASTNode> b = std::move(right);
    thisRef = std::make_unique<Subtract>(std::move(b), std::move(a));
    thisRef->optimize(thisRef);
    return;
  }

  // a + (-b) => a - b
  if (right->getType() == ASTNode::Type::UnaryMinus) {
    UnaryMinus &minusRight = static_cast<UnaryMinus &>(*right);
    std::unique_ptr<ASTNode> a = std::move(left);
    std::unique_ptr<ASTNode> b = minusRight.releaseInput();
    ;
    thisRef = std::make_unique<Subtract>(std::move(a), std::move(b));
    thisRef->optimize(thisRef);
    return;
  }

  if (optimizeConstants(thisRef)) {
    return;
  }
}
//---------------------------------------------------------------------------
// Overriden accept function
void Add::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  left->accept(visitor);
  visitor.visit(*this);
  right->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
Multiply::Multiply(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    : BinaryASTNode(std::move(l), std::move(r)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double Multiply::evaluate(const EvaluationContext &context) const {
  return left->evaluate(context) * right->evaluate(context);
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Multiply::optimize(std::unique_ptr<ASTNode> &thisRef) {
  left->optimize(left);
  right->optimize(right);

  // 0 * a => 0
  if (checkLeftValueZero()) {
    thisRef = std::make_unique<Constant>(0);
    return;
  }

  // a * 0 => 0
  if (checkRightValueZero()) {
    thisRef = std::make_unique<Constant>(0);
    return;
  }

  // 1 * a => a
  if (checkLeftValueOne()) {
    thisRef = std::move(right);
    return;
  }

  // a * 1 => a
  if (checkRightValueOne()) {
    thisRef = std::move(left);
    return;
  }

  // (-a) * (-b) => a * b
  if (left->getType() == ASTNode::Type::UnaryMinus &&
      right->getType() == ASTNode::Type::UnaryMinus) {
    left = std::make_unique<UnaryMinus>(std::move(left));
    right = std::make_unique<UnaryMinus>(std::move(right));
    left->optimize(left);
    right->optimize(right);
    thisRef = std::make_unique<Multiply>(std::move(left), std::move(right));
    return;
  }

  if (optimizeConstants(thisRef)) {
    return;
  }
}
//---------------------------------------------------------------------------
// Overriden accept function
void Multiply::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  left->accept(visitor);
  visitor.visit(*this);
  right->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
Divide::Divide(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    : BinaryASTNode(std::move(l), std::move(r)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double Divide::evaluate(const EvaluationContext &context) const {
  return static_cast<double>(static_cast<double>(left->evaluate(context)) /
                             static_cast<double>(right->evaluate(context)));
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Divide::optimize(std::unique_ptr<ASTNode> &thisRef) {
  left->optimize(left);
  right->optimize(right);

  // 0 / a => 0
  if (checkLeftValueZero()) {
    thisRef = std::make_unique<Constant>(0);
    return;
  }

  // a / 1 => a
  if (checkRightValueOne()) {
    thisRef = std::move(left);
    return;
  }

  if (optimizeConstants(thisRef)) {
    return;
  }

  // a / constant => a * (1 / constant)
  if (right->getType() == ASTNode::Type::Constant) {
    Constant *rightPtr = static_cast<Constant *>(right.get());
    double value = rightPtr->getValue();
    value = static_cast<double>(1) / value;
    right = std::make_unique<Constant>(value);
    thisRef = std::make_unique<Multiply>(std::move(left), std::move(right));
    return;
  }

  // (-a) / (-b) => a / b
  if (left->getType() == ASTNode::Type::UnaryMinus &&
      right->getType() == ASTNode::Type::UnaryMinus) {
    left = std::make_unique<UnaryMinus>(std::move(left));
    right = std::make_unique<UnaryMinus>(std::move(right));
    left->optimize(left);
    right->optimize(right);
    thisRef = std::make_unique<Divide>(std::move(left), std::move(right));
    return;
  }
}
//---------------------------------------------------------------------------
// Overriden accept function
void Divide::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  left->accept(visitor);
  visitor.visit(*this);
  right->accept(visitor);
  std::cout << ")";
}
//---------------------------------------------------------------------------
// Constructor
Power::Power(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
    : BinaryASTNode(std::move(l), std::move(r)) {}
//---------------------------------------------------------------------------
// Overriden evaluate function
double Power::evaluate(const EvaluationContext &context) const {
  return std::pow(left->evaluate(context), right->evaluate(context));
}
//---------------------------------------------------------------------------
// Overriden optimize function
void Power::optimize(std::unique_ptr<ASTNode> &thisRef) {
  left->optimize(left);
  right->optimize(right);

  // a ^ 0 => 1
  if (checkRightValueZero()) {
    thisRef = std::make_unique<Constant>(1.0);
    return;
  }

  // a ^ 1 => a
  if (checkRightValueOne()) {
    thisRef = std::move(left);
    return;
  }

  // 0 ^ a => 0
  if (checkLeftValueZero()) {
    thisRef = std::make_unique<Constant>(0.0);
    return;
  }

  // 1 ^ a => 1
  if (checkLeftValueOne()) {
    thisRef = std::make_unique<Constant>(1.0);
    return;
  }

  // a ^ (-1) => 1 / a
  if (checkRightValueMinusOne()) {
    thisRef = std::make_unique<Divide>(std::make_unique<Constant>(1.0),
                                       std::move(left));
    return;
  }

  if (optimizeConstants(thisRef)) {
    return;
  }
}
//---------------------------------------------------------------------------
// Overriden accept function
void Power::accept(ASTVisitor &visitor) const {
  std::cout << "(";
  left->accept(visitor);
  visitor.visit(*this);
  right->accept(visitor);
  std::cout << ")";
}
} // namespace ast
//---------------------------------------------------------------------------
