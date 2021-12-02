#include "pljit/Pljit.hpp"
#include "pljit/ast/ASTOptimizerConstantPropagation.hpp"
#include "pljit/ast/ASTOptimizerDeadCode.hpp"
using namespace pljit::semanticanalysis;
//---------------------------------------------------------------------------
namespace pljit {
//---------------------------------------------------------------------------
// Overloaded function call
optional<int64_t> PljitHandle::operator()(const vector<int64_t>& parameters) {
    shared_ptr<CodeManagement> codeM = make_shared<CodeManagement>(code);
    {
        unique_lock lock(uniqueMutex);

        if (!compiled) {
            Lexer lexer(code.data(), codeM);
            Parsing parser(lexer, codeM);

            parser.parsing();
            if (parser.errorOccurred()) {
                return nullopt;
            }

            SemanticAnalysis semanticAnalysis(codeM);
            Function function = semanticAnalysis.getAST(parser);

            if (function.errorOccurred()) {
                return nullopt;
            }
            ASTOptimizerDeadCode astOptimizerDeadCode;

            functionsRef.push_back(make_unique<Function>(move(function)));
            position = functionsRef.size() - 1;
            functionsRef[position]->optimize(astOptimizerDeadCode, functionsRef[position]);

            auto& function1 = static_cast<Function&>(*functionsRef[position]);
            ASTOptimizerConstantPropagation astOptimizerConstantPropagation(function1.getSymbolTable());
            functionsRef[position]->optimize(astOptimizerConstantPropagation, functionsRef[position]);

            compiled = true;
        }
    }

    auto& function1 = static_cast<Function&>(*functionsRef[position]);
    EvaluationContext evaluationContext(function1.getSymbolTable(), parameters);
    unique_lock lock(uniqueMutex);
    functionsRef[position]->evaluate(evaluationContext);

    if (functionsRef[position]->errorOccurred()) {
        return nullopt;
    }

    return evaluationContext.getReturnValue();
}
//---------------------------------------------------------------------------
} // namespace pljit
//---------------------------------------------------------------------------
