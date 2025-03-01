#include "token.hpp"

std::string getTokenTypeName(Token token) {
    static const std::unordered_map<TokenType, std::string> tokenNames = {
        {TokenType::IDENTIFIER, "IDENTIFIER"},
        {TokenType::INVALID_IDENTIFIER, "INVALID_IDENTIFIER"},
        {TokenType::KEYWORDS, "KEYWORDS"},
        {TokenType::DATA_TYPE, "DATA_TYPE"},
        
        {TokenType::COLON, "COLON"},
        {TokenType::SEMICOLON, "SEMICOLON"},
        {TokenType::COMMA, "COMMA"},
        {TokenType::COMMENTS, "COMMENTS"},

        {TokenType::VALUE_LITERAL, "VALUE_LITERAL"},
        
        {TokenType::UNCLOSED_STRING_LITERAL, "UNCLOSED_STRING_LITERAL"},

        {TokenType::ASSIGNMENT_OPERATOR, "ASSIGNMENT_OPERATOR"},
        {TokenType::PLUS_OPERATOR, "PLUS_OPERATOR"},
        {TokenType::MINUS_OPERATOR, "MINUS_OPERATOR"},
        {TokenType::MODULUS_OPERATOR, "MODULUS_OPERATOR"},
        {TokenType::ASTERISK, "ASTERISK_OPERATOR"},  // * (Multiplication / Pointer dereference)
        {TokenType::FORWARD_SLASH, "FORWARD_SLASH"},  // /
        {TokenType::LESSER_THAN, "LESSER_THAN"},
        {TokenType::LESSER_EQUAL, "LESSER_EQUAL"},
        {TokenType::GREATER_THAN, "GREATER_THAN"},
        {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
        {TokenType::BANG, "BANG"},  // !
        {TokenType::CARET, "CARET (Exponentiation)"},  // ^
        {TokenType::EQUALITY_OPERATOR, "EQUALITY_OPERATOR"},
        {TokenType::NOT_EQUAL_OPERATOR, "NOT_EQUAL_OPERATOR"},
        {TokenType::INCREMENT_OPERATOR, "INCREMENT_OPERATOR"},
        {TokenType::DECREMENT_OPERATOR, "DECREMENT_OPERATOR"},

        {TokenType::SHORTHAND_ADDITION, "SHORTHAND_ADDITION"},
        {TokenType::SHORTHAND_SUBTRACTION, "SHORTHAND_SUBTRACTION"},
        {TokenType::SHORTHAND_MULTIPLICATION, "SHORTHAND_MULTIPLICATION"},
        {TokenType::SHORTHAND_DIVISION, "SHORTHAND_DIVISION"},
        {TokenType::SHORTHAND_MODULUS, "SHORTHAND_MODULUS"},
        {TokenType::SHORTHAND_EXPONENTIATION, "SHORTHAND_EXPONENTIATION"},
        {TokenType::SHORTHAND_BITWISE_AND, "SHORTHAND_BITWISE_AND"},
        {TokenType::SHORTHAND_BITWISE_OR, "SHORTHAND_BITWISE_OR"},
        {TokenType::SHORTHAND_BITWISE_XOR, "SHORTHAND_BITWISE_XOR"},

        {TokenType::CONCAT_PRINT, "CONCAT_PRINT"},  // <<
        {TokenType::DOT_OPERATOR, "DOT_OPERATOR"},

        {TokenType::LOGICAL_AND, "LOGICAL_AND"},  // &&
        {TokenType::LOGICAL_OR, "LOGICAL_OR"},  // ||

        {TokenType::AMPERSAND, "AMPERSAND"},  // &
        {TokenType::PIPE_OPERATOR, "PIPE_OPERATOR"},    // |
        {TokenType::BITWISE_XOR, "BITWISE_XOR"},  // ^^

        {TokenType::QUESTION_MARK, "QUESTION_MARK"},

        {TokenType::BACKSLASH, "BACKSLASH"},

        {TokenType::DOUBLE_QUOTE, "DOUBLE_QUOTE"},
        {TokenType::SINGLE_QUOTE, "SINGLE_QUOTE"},

        {TokenType::LEFT_PARENTHESIS, "LEFT_PARENTHESIS"},
        {TokenType::RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS"},
        {TokenType::LEFT_CURLY_BRACES, "LEFT_CURLY_BRACES"},
        {TokenType::RIGHT_CURLY_BRACES, "RIGHT_CURLY_BRACES"},
        {TokenType::LEFT_SQUARE_BRACKET, "LEFT_SQUARE_BRACKET"},
        {TokenType::RIGHT_SQUARE_BRACKET, "RIGHT_SQUARE_BRACKET"},

        {TokenType::UNKNOWN, "UNKNOWN"},
        {TokenType::ENDOFFILE, "ENDOFFILE"}
    };

    auto iterator = tokenNames.find(token.type);
    return (iterator != tokenNames.end()) ? iterator->second : "UNKNOWN_TOKEN";
}

bool isKeyword(std::string identifier){
    std::cout << "Identifier: '" << identifier << "' (length: " << identifier.length() << ")" << std::endl;
    static const std::unordered_set<std::string> keywords = {
        "if", "else", "while", "for", "return", "func", "let",
        "break", "continue",
        "struct", "enum",
        "true", "false"
    };

    bool chk =  keywords.find(identifier) != keywords.end();
    std::cout << chk << std::endl;
    if(chk) return true;
    else return false;
}

bool isDataType(std::string identifier){
    static const std::unordered_set<std::string> datatypes = {
        "i8", "i16", "i32", "i64", "f32", "f64", 
        "ui8", "ui16", "ui32", "ui64",
        "String", "char", "bool"
    };

    return datatypes.find(identifier) != datatypes.end();
}