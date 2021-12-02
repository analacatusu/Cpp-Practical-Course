#ifndef H_PLJIT_LEXER
#define H_PLJIT_LEXER
#include "pljit/codem/CodeManagement.hpp"
#include "pljit/lexer/Token.hpp"
#include <memory>
//---------------------------------------------------------------------------
namespace pljit::lexer {
//---------------------------------------------------------------------------
/// struct that represents the lexer -> tokenizing the code (MILESTONE 2)
struct Lexer {
    /// Constructors
    Lexer() = default;
    Lexer(const char* currentChar, shared_ptr<CodeManagement> codeM) : currentChar(currentChar), codeM(move(codeM)) {}
    /// Tokenize a literal (integer)
    Token literal();
    /// Tokenize an identifier
    Token identifier(size_t start);
    /// Tokenize a keyword
    Token keyword(size_t start, size_t length);
    /// Decide whether the current token is a keyword or an identifier
    Token identifierOrKeyword();
    /// Go to the next character in the code
    void increment();
    /// Return the next token in the code
    Token next();
    /// Return whether the current character is a whitespace
    static bool isWhitespace(char);
    /// Return whether the current character is a digit
    static bool isDigit(char);
    /// Return whether the current character is upper or lower letter
    static bool isAlpha(char);
    /// Return whether the current character is upper letter
    static bool isUpper(char);
    /// Return whether the current character is lower letter
    static bool isLower(char);

    private:
    /// Storage of the current character in the code
    const char* currentChar = "";
    /// Storage of the first character in the code
    const char* beginning = currentChar;
    /// Storage of the current position in the code
    size_t currentPos = 0;
    /// Storage of the code management unit
    shared_ptr<CodeManagement> codeM;
};
//---------------------------------------------------------------------------
} // namespace pljit::lexer
//---------------------------------------------------------------------------
#endif // H_PLJIT_LEXER
//---------------------------------------------------------------------------
