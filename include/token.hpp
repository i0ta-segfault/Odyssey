#pragma once

#include "types.hpp"

struct Token {
    TokenType type;
    int line_number;
    int column_number;
    std::string literal;
};

std::string getTokenTypeName(Token token);
bool isKeyword(std::string identifier);
bool isDataType(std::string identifier);
