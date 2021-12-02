#ifndef H_PLJIT_AST
#define H_PLJIT_AST
#include "pljit/ast/ASTOptimizer.hpp"
#include "pljit/ast/ASTVisitor.hpp"
#include "pljit/evaluation/EvaluationContext.hpp"
using namespace pljit::evaluation;
//---------------------------------------------------------------------------
namespace pljit::ast {
//---------------------------------------------------------------------------
/// Abstract class that represents a node in the ast (MILESTONE 4)
class ASTNode {
    public:
    /// All possible types of the ast nodes
    enum class Type {
        Constant,
        Parameter,
        Function,
        ASTStatement,
        AssignmentExpr,
        ReturnExpr,
        MulExpr,
        DivExpr,
        AddExpr,
        SubtractExpr,
        UnaryPlus,
        UnaryMinus
    };
    /// Constructors
    ASTNode() = default;
    explicit ASTNode(bool error) : error(error) {}
    /// Destructor
    virtual ~ASTNode() = default;
    /// Get the type of the ast node
    virtual ASTNode::Type getType() const = 0;
    /// Accept a visitor
    virtual void accept(ASTVisitor&) const = 0;
    /// Optimize the nodes
    virtual void optimize(ASTOptimizer&, unique_ptr<ASTNode>&) = 0;
    /// Evaluate the nodes
    virtual int64_t evaluate(EvaluationContext&) = 0;
    /// Return whether an error occurred during the semantic analysis stage
    bool errorOccurred() const { return error; }

    protected:
    /// Storage of the error
    bool error = false;
};
//---------------------------------------------------------------------------
class Constant : public ASTNode {
    public:
    /// Constructors
    Constant() = default;
    explicit Constant(int64_t value) : value(value) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::Constant; }
    /// Getter
    int64_t getValue() const { return value; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext&) override;

    private:
    /// Storage of the value
    int64_t value = 0;
};
//---------------------------------------------------------------------------
class Parameter : public ASTNode {
    public:
    /// Constructors
    Parameter() = default;
    explicit Parameter(string_view name) : name(name) {}
    explicit Parameter(bool error) : ASTNode(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::Parameter; }
    /// Getter
    string_view getName() const { return name; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;

    private:
    /// Storage of the name of the identifier
    string_view name;
};
//---------------------------------------------------------------------------
class BinaryExpr : public ASTNode {
    public:
    /// Constructors
    BinaryExpr() = default;
    BinaryExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right) : left(move(left)), right(move(right)) {}
    explicit BinaryExpr(bool error) : ASTNode(error) {}
    /// Getters
    const ASTNode& getLeft() const { return *left; }
    const ASTNode& getRight() const { return *right; }
    unique_ptr<ASTNode> releaseLeft() { return move(left); }
    unique_ptr<ASTNode> releaseRight() { return move(right); }

    protected:
    /// Storage of the left child
    unique_ptr<ASTNode> left;
    /// Storage of the right child
    unique_ptr<ASTNode> right;
};
//---------------------------------------------------------------------------
class UnaryExpr : public ASTNode {
    public:
    /// Constructors
    UnaryExpr() = default;
    explicit UnaryExpr(unique_ptr<ASTNode> child) : child(move(child)) {}
    explicit UnaryExpr(bool error) : ASTNode(error) {}
    /// Getters
    const ASTNode& getChild() const { return *child; }
    unique_ptr<ASTNode> releaseInput() { return move(child); }

    protected:
    /// Storage of the child node
    unique_ptr<ASTNode> child;
};
//---------------------------------------------------------------------------
class UnaryPlus : public UnaryExpr {
    public:
    /// Constructors
    UnaryPlus() = default;
    explicit UnaryPlus(unique_ptr<ASTNode> child) : UnaryExpr(move(child)) {}
    explicit UnaryPlus(bool error) : UnaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryPlus; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
};
//---------------------------------------------------------------------------
class UnaryMinus : public UnaryExpr {
    public:
    /// Constructors
    UnaryMinus() = default;
    explicit UnaryMinus(unique_ptr<ASTNode> child) : UnaryExpr(move(child)) {}
    explicit UnaryMinus(bool error) : UnaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryMinus; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
};
//---------------------------------------------------------------------------
class DivExpr : public BinaryExpr {
    public:
    /// Constructors
    DivExpr() = default;
    DivExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right) : BinaryExpr(move(left), move(right)) {}
    explicit DivExpr(bool error) : BinaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::DivExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
};
//---------------------------------------------------------------------------
class MulExpr : public BinaryExpr {
    public:
    /// Constructors
    MulExpr() = default;
    MulExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right) : BinaryExpr(move(left), move(right)) {}
    explicit MulExpr(bool error) : BinaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::MulExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
};
//---------------------------------------------------------------------------
class SubtractExpr : public BinaryExpr {
    public:
    /// Constructors
    SubtractExpr() = default;
    SubtractExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right) : BinaryExpr(move(left), move(right)) {}
    explicit SubtractExpr(bool error) : BinaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::SubtractExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
};
//---------------------------------------------------------------------------
class AddExpr : public BinaryExpr {
    public:
    /// Constructors
    AddExpr() = default;
    AddExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right) : BinaryExpr(move(left), move(right)) {}
    explicit AddExpr(bool error) : BinaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::AddExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
};
//---------------------------------------------------------------------------
class AssignmentExpr : public BinaryExpr {
    public:
    /// Constructors
    AssignmentExpr() = default;
    AssignmentExpr(unique_ptr<ASTNode> left, unique_ptr<ASTNode> right, string_view nameLeft) : BinaryExpr(move(left), move(right)), nameLeft(nameLeft) {}
    explicit AssignmentExpr(bool error) : BinaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::AssignmentExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;

    private:
    /// Storage of the identifier name left of the assignment
    string_view nameLeft;
};
//---------------------------------------------------------------------------
class ReturnExpr : public UnaryExpr {
    public:
    /// Constructors
    ReturnExpr() = default;
    explicit ReturnExpr(unique_ptr<ASTNode> child) : UnaryExpr(move(child)) {}
    explicit ReturnExpr(bool error) : UnaryExpr(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::ReturnExpr; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
};
//---------------------------------------------------------------------------
class ASTStatement : public ASTNode {
    public:
    /// Constructors
    ASTStatement() = default;
    explicit ASTStatement(unique_ptr<ASTNode> expression) : expression(move(expression)) {}
    explicit ASTStatement(bool error) : ASTNode(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::ASTStatement; }
    /// Getters
    const ASTNode& getExpression() const { return *expression; }
    unique_ptr<ASTNode> releaseInput() { return move(expression); }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;

    private:
    /// Storage of the expression
    unique_ptr<ASTNode> expression;
};
//---------------------------------------------------------------------------
class Function : public ASTNode {
    public:
    /// Constructors
    Function() = default;
    Function(vector<unique_ptr<ASTNode>> statements, OptimizationTable optimizationTable) : statements(move(statements)), optimizationTable(move(optimizationTable)) {}
    explicit Function(bool error) : ASTNode(error) {}
    /// Overridden getType function
    ASTNode::Type getType() const override { return ASTNode::Type::Function; }
    /// Getters
    const vector<unique_ptr<ASTNode>>& getStatements() const { return statements; }
    vector<unique_ptr<ASTNode>>& getStatements() { return statements; }
    OptimizationTable& getSymbolTable() { return optimizationTable; }
    /// Overridden accept function
    void accept(ASTVisitor& visitor) const override;
    /// Overridden optimize function
    void optimize(ASTOptimizer& astOptimizer, unique_ptr<ASTNode>& thisRef) override;
    /// Overridden evaluate function
    int64_t evaluate(EvaluationContext& evaluationContext) override;

    private:
    /// Storage of the statements
    vector<unique_ptr<ASTNode>> statements;
    /// Storage of the symbol table
    OptimizationTable optimizationTable;
};
//---------------------------------------------------------------------------
} // namespace pljit::ast
#endif // H_PLJIT_AST
//---------------------------------------------------------------------------
