#include "pljit/lexer/Lexer.hpp"
//---------------------------------------------------------------------------
namespace pljit::lexer {
//---------------------------------------------------------------------------
// Function to determine wheter a char is whitespace
bool Lexer::isWhitespace(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\n':
            return true;
        default:
            return false;
    }
}
//---------------------------------------------------------------------------
// Function to determine whether a char is a digit
bool Lexer::isDigit(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': return true;
        default: return false;
    }
}
//---------------------------------------------------------------------------
// Function to determine whether a char is a letter
bool Lexer::isAlpha(char c) {
    if (isUpper(c) || isLower(c)) {
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
// Function to determine whether a char is a lower letter
bool Lexer::isLower(char c) {
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return true;
        default:
            return false;
    }
}
//---------------------------------------------------------------------------
// Function to determine whether a char is a lower letter
bool Lexer::isUpper(char c) {
    switch (c) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            return true;
        default:
            return false;
    }
}
//---------------------------------------------------------------------------
// Function to tokenize a literal
Token Lexer::literal() {
    size_t start = currentPos;
    while (isDigit(*currentChar)) {
        increment();
    }
    size_t length = currentPos - start;
    return Token(Token::TokenType::Literal, Reference(start, length));
}
//---------------------------------------------------------------------------
// Function to tokenize an identifier
Token Lexer::identifier(size_t start) {
    while (isAlpha(*currentChar)) {
        increment();
    }

    size_t length = currentPos - start;

    return Token(Token::TokenType::Identifier, Reference(start, length));
}
//---------------------------------------------------------------------------
// Function to tokenize a keyword
Token Lexer::keyword(size_t start, size_t length) {
    string_view word = codeM->getCharacters(start, length);
    if (word == "RETURN") {
        return Token(Token::TokenType::ReturnKeyword, Reference(start, length));
    } else if (word == "END") {
        return Token(Token::TokenType::EndKeyword, Reference(start, length));
    } else if (word == "BEGIN") {
        return Token(Token::TokenType::BeginKeyword, Reference(start, length));
    } else if (word == "PARAM") {
        return Token(Token::TokenType::ParamKeyword, Reference(start, length));
    } else if (word == "VAR") {
        return Token(Token::TokenType::VarKeyword, Reference(start, length));
    } else if (word == "CONST") {
        return Token(Token::TokenType::ConstKeyword, Reference(start, length));
    } else {
        codeM->errorTypo(Reference(start, length));
        return Token(Token::TokenType::Unexpected, Reference(start, length));
    }
}
//---------------------------------------------------------------------------
// Function to decide whether to tokenize a keyword or an identifier
Token Lexer::identifierOrKeyword() {
    size_t start = currentPos;

    while (isUpper(*currentChar)) {
        increment();
    }
    if (isLower(*currentChar)) {
        return identifier(start);
    } else {
        return keyword(start, currentPos - start);
    }
}
//---------------------------------------------------------------------------
// Function to increment through the code
void Lexer::increment() {
    currentChar++;
    currentPos++;
}
//---------------------------------------------------------------------------
// Function to return the next token in the code
Token Lexer::next() {
    if (currentChar != beginning && (*(currentChar - 1) == '.')) {
        return Token();
    }

    while (isWhitespace(*currentChar)) {
        increment();
    }

    if (isDigit(*currentChar)) {
        return literal();
    }

    if (isLower(*currentChar)) {
        return identifier(currentPos);
    }

    if (isAlpha(*currentChar)) {
        return identifierOrKeyword();
    }

    switch (*currentChar) {
        case ',': {
            increment();
            return Token(Token::TokenType::CommaSeparator, Reference(currentPos - 1));
        }
        case ';': {
            increment();
            return Token(Token::TokenType::EndLineSeparator, Reference(currentPos - 1));
        }
        case '.': {
            increment();
            return Token(Token::TokenType::Dot, Reference(currentPos - 1));
        }
        case '*': {
            increment();
            return Token(Token::TokenType::MulOperator, Reference(currentPos - 1));
        }
        case '/': {
            increment();
            return Token(Token::TokenType::DivOperator, Reference(currentPos - 1));
        }
        case '(': {
            increment();
            return Token(Token::TokenType::LeftParanthesis, Reference(currentPos - 1));
        }
        case ')': {
            increment();
            return Token(Token::TokenType::RightParanthesis, Reference(currentPos - 1));
        }
        case ':': {
            if (*(currentChar + 1) == '=') {
                increment();
                increment();
                return Token(Token::TokenType::AssignmentOperator, Reference(currentPos - 2, 2));
            } else {
                codeM->errorUnknownCharacter(Reference(currentPos));
                return Token(Token::TokenType::Unexpected, Reference());
            }
        }
        case '=': {
            increment();
            return Token(Token::TokenType::AssignmentOperatorDecl, Reference(currentPos - 1));
        }
        case '+': {
            increment();
            char c = *(currentChar);

            if (c == ' ') {
                return Token(Token::TokenType::BinaryPlusOperator, Reference(currentPos - 1));
            } else {
                return Token(Token::TokenType::UnaryPlusOperator, Reference(currentPos - 1));
            }
        }
        case '-': {
            increment();
            char c = *(currentChar);

            if (c == ' ') {
                return Token(Token::TokenType::BinaryMinusOperator, Reference(currentPos - 1));
            } else {
                return Token(Token::TokenType::UnaryMinusOperator, Reference(currentPos - 1));
            }
        }
        default: {
            codeM->errorUnknownCharacter(Reference(currentPos));
            return Token(Token::TokenType::Unexpected, Reference());
        }
    }
}
//---------------------------------------------------------------------------
} // namespace pljit::lexer
//---------------------------------------------------------------------------
