#ifndef H_lib_AST
#define H_lib_AST
#include "lib/ASTVisitor.hpp"
#include "lib/EvaluationContext.hpp"
#include <memory>
//---------------------------------------------------------------------------
namespace ast {
//---------------------------------------------------------------------------
/// Base class for AST nodes
class ASTNode {
    public:
    /// All possible types of ASTNodes
    enum class Type {
        UnaryPlus,
        UnaryMinus,
        Add,
        Subtract,
        Multiply,
        Divide,
        Power,
        Constant,
        Parameter
    };
    /// Constructor
    ASTNode() = default;
    /// Destructor
    virtual ~ASTNode() = default;
    /// Get the type of the node
    virtual ASTNode::Type getType() const = 0;
    /// Evaluate the given ASTNode
    virtual double evaluate(const EvaluationContext&) const = 0;
    /// Optimize the given ASTNode
    virtual void optimize(std::unique_ptr<ASTNode>& thisRef) = 0;
    /// Accept the visitor
    virtual void accept(ASTVisitor&) const = 0;
};

/// Class that represents a constant
class Constant final : public ASTNode {
    public:
    /// Constructor
    explicit Constant(double val);
    /// Get the value
    double getValue() const;
    /// Set a value
    void setValue(double val);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Constant; }
    /// Destructor
    ~Constant() override = default;

    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;

    private:
    /// Storage of the value
    double value;
};

/// Class that represents a parameter
class Parameter final : public ASTNode {
    public:
    /// Constructor
    Parameter(int indx);
    /// Get the index
    size_t getIndex() const;
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Parameter; }
    /// Destructor
    ~Parameter() override = default;

    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;

    private:
    /// Storage of the index
    size_t index;
};

/// Class that represents a Unary Operation on ASTNodes
class UnaryASTNode : public ASTNode {
    public:
    /// Constructor
    UnaryASTNode(std::unique_ptr<ASTNode> ch);
    /// Get a const reference to the child node
    const ASTNode& getInput() const;
    /// Transfer ownership to the caller
    std::unique_ptr<ASTNode> releaseInput();
    /// Destructor
    ~UnaryASTNode() override = default;

    protected:
    /// Storage of the child ASTNode
    std::unique_ptr<ASTNode> child;
};

/// Class that represents a UnaryMinus ASTNode
class UnaryMinus final : public UnaryASTNode {
    public:
    /// Constructor
    UnaryMinus(std::unique_ptr<ASTNode> ch);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryMinus; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~UnaryMinus() override = default;
};

/// Class that represents a UnaryPlus ASTNode
class UnaryPlus final : public UnaryASTNode {
    public:
    /// Constructor
    UnaryPlus(std::unique_ptr<ASTNode> ch);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::UnaryPlus; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~UnaryPlus() override = default;
};

/// Class that represents a binary operation on ASTNodes
class BinaryASTNode : public ASTNode {
    public:
    /// Constructor
    BinaryASTNode(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get a const reference to the left child
    const ASTNode& getLeft();
    /// Get a const reference to the right child
    const ASTNode& getRight();
    /// Transfer the ownership of the left child to the caller
    std::unique_ptr<ASTNode> releaseLeft();
    /// Transfer the ownership of the right child to the caller
    std::unique_ptr<ASTNode> releaseRight();
    /// Destructor
    ~BinaryASTNode() override = default;

    protected:
    /// Storage of the left child
    std::unique_ptr<ASTNode> left;
    /// Storage of the right child
    std::unique_ptr<ASTNode> right;
    /// Helper function to check if the left child is 0
    bool checkLeftValueZero() const;
    /// Helper function to check if the left child is 1
    bool checkLeftValueOne() const;
    /// Helper function to check if the right child is 0
    bool checkRightValueZero() const;
    /// Helper function to check if the right child is 1
    bool checkRightValueOne() const;
    /// Helper function to check if the right child is -1
    bool checkRightValueMinusOne() const;
    /// Helper function to get a const reference of one of the children
    const ASTNode& getChild(std::unique_ptr<ASTNode>& child) const;
    /// Helper function to optimize if node only contains constants
    bool optimizeConstants(std::unique_ptr<ASTNode>& thisRef);
};

/// Class to represent a Subtract ASTNode
class Subtract final : public BinaryASTNode {
    public:
    /// Constructor
    Subtract(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Subtract; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~Subtract() override = default;
};

/// Class to represent an Add ASTNode
class Add final : public BinaryASTNode {
    public:
    /// Constructor
    Add(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Add; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~Add() override = default;
};

/// Class to represent a Multiply ASTNode
class Multiply final : public BinaryASTNode {
    public:
    /// Constructor
    Multiply(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Multiply; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~Multiply() override = default;
};

/// Class to represent a Divide ASTNode
class Divide final : public BinaryASTNode {
    public:
    /// Constructor
    Divide(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Divide; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~Divide() override = default;
};

/// Class to represent a Power ASTNode
class Power final : public BinaryASTNode {
    public:
    /// Constructor
    Power(std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);
    /// Get the type
    ASTNode::Type getType() const override { return ASTNode::Type::Power; }
    /// Overridden evaluate function
    double evaluate(const EvaluationContext&) const override;
    /// Overriden optimize function
    void optimize(std::unique_ptr<ASTNode>&) override;
    /// Overriden accept function
    void accept(ASTVisitor&) const override;
    /// Destructor
    ~Power() override = default;
};

//---------------------------------------------------------------------------
} // namespace ast
//---------------------------------------------------------------------------
#endif
