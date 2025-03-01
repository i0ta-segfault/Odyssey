#pragma once

#include "token.hpp"
#include <vector>
#include <deque>

struct Lexer{
    std::string sourceCode;
    
    // for error reporting
    std::string currentLine;
    int lineNumber;
    int columnNumber;
    //------------------
    
    char characterRead;
    char nextCharacter;

    int currentPosition;

    Lexer(std::string sourceCode);
    void reportError(const std::string& message);

    Token getNextToken(std::deque<Token>& tokensBuffer);

    void readChar();

};

std::vector<Token> getTokens(std::string sourceCode);