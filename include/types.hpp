#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#define RED "\033[31m"
#define PURPLE "\033[35m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

enum class TokenType {
    IDENTIFIER,
    INVALID_IDENTIFIER,

    KEYWORDS,   // let, while, for, func, ...
    DATA_TYPE,

    COLON,
    SEMICOLON,
    COMMA,

    // the lexer won't scan these and store as tokens, it's only here to indicate such a token exists
    COMMENTS,   // rn they'll be single line so no multi line stuff like /**/

    VALUE_LITERAL,  // makes sense to be generic because odyssey should be able to support a bunch of types

    ASSIGNMENT_OPERATOR, // =
    PLUS_OPERATOR,   // +
    MINUS_OPERATOR,   // -
    MODULUS_OPERATOR,   // %
    ASTERISK,   // *   this could be multiplication or derefence operator for pointers
    FORWARD_SLASH,   // /
    LESSER_THAN,   // <
    LESSER_EQUAL,   // <=
    GREATER_THAN,   // >
    GREATER_EQUAL,   // >=
    BANG,   // !
    CARET, // ^   this is for exponentiation not bitwise xor
    EQUALITY_OPERATOR,   // ==
    NOT_EQUAL_OPERATOR,   // !=
    INCREMENT_OPERATOR,   // ++
    DECREMENT_OPERATOR,   // --

    SHORTHAND_ADDITION,    // +=
    SHORTHAND_SUBTRACTION,    // -=
    SHORTHAND_MULTIPLICATION,    // *=
    SHORTHAND_DIVISION,    // /=
    SHORTHAND_MODULUS,    // %=
    SHORTHAND_EXPONENTIATION,  // ^=
    SHORTHAND_BITWISE_AND,  // &=
    SHORTHAND_BITWISE_OR,  // |=
    SHORTHAND_BITWISE_XOR,  // ^^=

    CONCAT_PRINT,  // <<    inspiration from cpp's insertion operator
    DOT_OPERATOR,

    LOGICAL_AND,   // &&
    LOGICAL_OR,    // ||

    AMPERSAND,   // &
    PIPE_OPERATOR,   // |
    BITWISE_XOR,   // ^^

    QUESTION_MARK,   // ?
    BACKSLASH,

    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    UNCLOSED_STRING_LITERAL,  // this is to indicate to the parser that an unclosed string/char was encountered,
    // the lexer won't deal with it, the parser will because this is mainly a syntactical issue
        
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_CURLY_BRACES,
    RIGHT_CURLY_BRACES,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,

    UNKNOWN,
    ENDOFFILE,

    ENUM_TOKEN_TYPE_COUNT
};