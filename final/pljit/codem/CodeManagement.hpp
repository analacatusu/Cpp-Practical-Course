#ifndef H_PLJIT_CODEMANAGEMENT
#define H_PLJIT_CODEMANAGEMENT
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
namespace pljit::codemanagement {
//---------------------------------------------------------------------------
class Reference;
/// struct that represents the code management unit (Milestone 1)
struct CodeManagement {
    /// Constructor
    explicit CodeManagement(string_view code) : code(code) {}
    /// Destructor
    ~CodeManagement() = default;
    /// Helper struct for identifying the line and the position
    struct Location {
        size_t line = 0;
        size_t position = 0;
    };
    /// Identifying the line and the position inside the code
    Location resolveReference(Reference ref);
    /// Functions to return the string given a position in the code
    string_view getCharacters(size_t start, size_t length);
    string_view getCharacters(Reference ref);
    /// Functions to print different errors during the compilation
    void errorMissingEndParanthesis(Reference ref);
    void errorMissingAssignmentOperator(Reference ref);
    void errorTypo(Reference ref);
    void errorUnknownCharacter(Reference ref);
    void errorInvalidPrimaryExpr(Reference ref);
    void errorUndeclaredIdentifier(Reference ref);
    void errorRedeclaration(Reference ref);
    void errorAssigningToConstant(Reference ref);
    void errorUninitializedVariable(Reference ref);
    void errorAnalyzingStatements(Reference ref);
    void errorDeclarations(Reference ref);
    void errorMissingBegin(Reference ref);
    void errorEndline(Reference ref);
    void errorBadAssignment(Reference ref);
    void errorBadLiteral(Reference ref);
    void errorBadIdentifier(Reference ref);
    void errorWrongDeclaration(Reference ref);
    static void errorMissingDot();
    static void errorMissingReturn();
    /// Helper functions that do the actual printing of the errors
    void printError(Reference ref, string_view message);
    void printError2(Reference ref, string_view message);

    private:
    /// Functions to return the string given a location in the code
    string_view getLine(Location location);
    /// Storage of the code
    string_view code;
};
//---------------------------------------------------------------------------
} // namespace pljit::codemanagement
//---------------------------------------------------------------------------
#endif // H_PLJIT_CODEMANAGEMENT
//---------------------------------------------------------------------------
