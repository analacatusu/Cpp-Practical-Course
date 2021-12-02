#include "pljit/codem/CodeManagement.hpp"
#include "pljit/codem/Reference.hpp"
#include <iomanip>
//---------------------------------------------------------------------------
namespace pljit::codemanagement {
//---------------------------------------------------------------------------
// Identifying the line and the position inside the code
CodeManagement::Location CodeManagement::resolveReference(Reference ref) {
    size_t pos;
    size_t position;
    size_t lineNr = 0;
    size_t prevPos = 0;

    while ((pos = code.find("\n"sv, prevPos + 1)) && pos <= ref.begin) {
        lineNr++;
        prevPos = pos;
    }

    if (lineNr == 0) {
        position = ref.begin;
    } else {
        position = ref.begin - prevPos - 1;
    }

    Location location;
    location.position = position;
    location.line = lineNr;
    return location;
}
//---------------------------------------------------------------------------
// Function to return the string given a position in the code
string_view CodeManagement::getCharacters(size_t start, size_t length) {
    return code.substr(start, length);
}
//---------------------------------------------------------------------------
// Function to return the string given a position in the code
string_view CodeManagement::getCharacters(Reference ref) {
    return code.substr(ref.begin, ref.length);
}
//---------------------------------------------------------------------------
// Function to return the string given a location in the code
string_view CodeManagement::getLine(Location location) {
    string_view line;
    size_t startPos = 0;
    size_t endPos = 0;
    size_t lineNr = location.line;

    if (lineNr == 0) {
        endPos = code.find("\n"sv, 0);
        size_t length = endPos - 1 - startPos;
        line = code.substr(startPos, length);
        return line;
    }

    lineNr++;

    while (lineNr >= 1) {
        startPos = endPos;
        lineNr--;
        endPos = code.find("\n"sv, startPos + 1);
    }
    size_t length = endPos - 1 - startPos;
    line = code.substr(startPos + 1, length);

    return line;
}
//---------------------------------------------------------------------------
// Helper function that do the actual printing of the errors
void CodeManagement::printError(Reference ref, string_view message) {
    Location location = resolveReference(ref);
    cerr << location.line << ":" << location.position << ": " << message << endl;
    string_view errorLine = getLine(location);
    cerr << errorLine << endl;
    cerr << setw(static_cast<int>(location.position + 1)) << "^" << endl;
}
//---------------------------------------------------------------------------
// Helper functions that do the actual printing of the errors
void CodeManagement::printError2(Reference ref, string_view message) {
    Location location = resolveReference(ref);
    cerr << location.line << ":" << location.position << ": " << message << endl;
    string_view errorLine = getLine(location);
    cerr << errorLine << endl;
    cerr << setw(static_cast<int>(location.position + 1)) << "^" << string(ref.length - 1, '~') << endl;
}
//---------------------------------------------------------------------------
// Error for missing end paranthesis
void CodeManagement::errorMissingEndParanthesis(Reference ref) {
    printError(ref, "error: expected \')\'");
    size_t pos = code.rfind("("sv, ref.begin);
    Reference ref2;
    ref2.begin = pos;
    printError(ref2, "note: to match this \'(\'");
}
//---------------------------------------------------------------------------
// Error for missing assignment operator
void CodeManagement::errorMissingAssignmentOperator(Reference ref) {
    printError2(ref, "error: expected \':=\'");
}
//---------------------------------------------------------------------------
// Error for a typo in an identifier
void CodeManagement::errorTypo(Reference ref) {
    printError2(ref, "error: typo in identifier");
}
//---------------------------------------------------------------------------
// Error for an unknown character
void CodeManagement::errorUnknownCharacter(Reference ref) {
    printError(ref, "error: unknown character");
}
//---------------------------------------------------------------------------
// Error for an invalid primary expression
void CodeManagement::errorInvalidPrimaryExpr(Reference ref) {
    printError(ref, "error: invalid primary expression");
}
//---------------------------------------------------------------------------
// Error for using an undeclared identifier
void CodeManagement::errorUndeclaredIdentifier(Reference ref) {
    printError2(ref, "error: undeclared identifier");
}
//---------------------------------------------------------------------------
// Error for redeclaring an identifier
void CodeManagement::errorRedeclaration(Reference ref) {
    printError2(ref, "error: redeclaration of identifier");
}
//---------------------------------------------------------------------------
// Error for assigning to a constant
void CodeManagement::errorAssigningToConstant(Reference ref) {
    printError2(ref, "error: trying to assign to a constant");
}
//---------------------------------------------------------------------------
// Error for using an uninitialized variable
void CodeManagement::errorUninitializedVariable(Reference ref) {
    printError2(ref, "error: trying to use an uninitialized variable");
}
//---------------------------------------------------------------------------
// Error for a wrong structure in the statements
void CodeManagement::errorAnalyzingStatements(Reference ref) {
    printError2(ref, "error: analyzing the statements failed; maybe missing endline?");
}
//---------------------------------------------------------------------------
// Error for a wrong structure in the declarations
void CodeManagement::errorDeclarations(Reference ref) {
    printError2(ref, "error: processing the declarations failed");
}
//---------------------------------------------------------------------------
// Error for missing keyword begin
void CodeManagement::errorMissingBegin(Reference ref) {
    printError(ref, "error: missing begin keyword");
}
//---------------------------------------------------------------------------
// Error for missing return statement
void CodeManagement::errorMissingReturn() {
    cerr << "error: missing return statement" << endl;
}
//---------------------------------------------------------------------------
// Error for extra endline
void CodeManagement::errorEndline(Reference ref) {
    printError(ref, "error: the statement before should not terminate with an endline separator");
}
//---------------------------------------------------------------------------
// Error for using the assignment operator in the constant declaration
void CodeManagement::errorBadAssignment(Reference ref) {
    printError2(ref, "error: expected \'=\'");
}
//---------------------------------------------------------------------------
// Error for not using a literal in the constant declaration
void CodeManagement::errorBadLiteral(Reference ref) {
    printError(ref, "error: expected literal after assignment");
}
//---------------------------------------------------------------------------
// Error for missing the dot at the end of the program
void CodeManagement::errorMissingDot() {
    cerr << "error: missing DOT symbol at the end of the program" << endl;
}
//---------------------------------------------------------------------------
// Error for using a bad identifier
void CodeManagement::errorBadIdentifier(Reference ref) {
    printError2(ref, "error : bad identifier");
}
//---------------------------------------------------------------------------
// Error for having a wrong structure in a declaration
void CodeManagement::errorWrongDeclaration(Reference ref) {
    printError2(ref, "error : wrong declaration");
}
//---------------------------------------------------------------------------
} // namespace pljit::codemanagement
//---------------------------------------------------------------------------
