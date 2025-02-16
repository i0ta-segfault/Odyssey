#include "lexer.hpp"

Lexer::Lexer(std::string sourceCode){
    this->sourceCode = sourceCode;
    lineNumber = 1;
    columnNumber = 1;
    characterRead = 0;
    nextCharacter = 0;
    currentPosition = 0;
    currentLine = "";
    readChar();
}

void Lexer::reportError(const std::string& message) {
    std::cerr << BOLD << RED << "Error at [Line " << lineNumber << ", Col " << columnNumber << "]: " << RESET << message << std::endl;
    std::cerr << "  " << BOLD << PURPLE << currentLine << RESET << std::endl;
    std::cerr << "  ";
    for (int i = 1; i < columnNumber; i++) {
        std::cerr << " ";
    }
    std::cerr << BOLD << RED << "^" << std::endl;
    exit(EXIT_FAILURE);
}

void Lexer::readChar(){
    if(currentPosition >= sourceCode.length()){
        characterRead = 0;
        nextCharacter = 0;
        return;
    }
    else{
        characterRead = sourceCode[currentPosition];
        currentPosition += 1;
        nextCharacter = (currentPosition < sourceCode.length()) ? sourceCode[currentPosition] : '\0';
        if(characterRead == '\n'){
            lineNumber++;
            columnNumber = 1;

            size_t lineStart = currentPosition;
            while (lineStart > 0 && sourceCode[lineStart - 1] != '\n') {
                lineStart--;
            }
            size_t lineEnd = currentPosition;
            while (lineEnd < sourceCode.size() && sourceCode[lineEnd] != '\n') {
                lineEnd++;
            }
            currentLine = sourceCode.substr(lineStart, lineEnd - lineStart);

        } else {
            columnNumber++;
        }
    }
}

Token Lexer::getNextToken(std::vector<Token>& tokensBuffer){
    if (!tokensBuffer.empty()) {
        Token token = tokensBuffer.back();
        tokensBuffer.pop_back();
        return token;
    }
    Token token;
    token.line_number = lineNumber;
    token.column_number = columnNumber;
    
    //skip whitespace  -  could have been a function, but eh
    while(characterRead == ' ' || characterRead == '\n' || characterRead == '\t' || characterRead == '\r')
        readChar();

    if (nextCharacter == 0){
        token.type = TokenType::ENDOFFILE;
        token.literal = "";
        return token;
    }

    if (characterRead == '/'){
        if(nextCharacter == '/'){
            // read the comment
            readChar();  // move to second / of //
            readChar();  // move to the actual comment that is character after //
            while (characterRead != '\n' && characterRead != 0) {
                token.literal += characterRead;
                readChar();
            }
            token.type = TokenType::COMMENTS;
            return token;
        }
        else if(nextCharacter == '='){
            readChar();
            readChar();
            token.type = TokenType::SHORTHAND_DIVISION;
            token.literal = "/=";
            return token;
        }
        token.type = TokenType::FORWARD_SLASH;
        token.literal = "/";
        readChar();
        return token;
    }

    if (characterRead == '='){
        if(nextCharacter == '='){
            readChar();
            readChar();
            token.type = TokenType::EQUALITY_OPERATOR;
            token.literal = "==";
            return token;
        }
        readChar();
        token.type = TokenType::ASSIGNMENT_OPERATOR;
        token.literal = "=";
        return token;
    }

    if (characterRead == '!'){
        if(nextCharacter == '='){
            token.type = TokenType::NOT_EQUAL_OPERATOR;
            token.literal = "!=";
            readChar();
            readChar();
            return token;
        } else{
            token.literal = "!";
            token.type = TokenType::BANG;
            readChar();
            return token;
        }
    }
    
    if (characterRead == '+'){
        if(nextCharacter == '+'){
            token.type = TokenType::INCREMENT_OPERATOR;
            token.literal = "++";
            readChar();
            readChar();
            return token;
        } else if(nextCharacter == '='){
            token.type = TokenType::SHORTHAND_ADDITION;
            token.literal = "+=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::PLUS_OPERATOR;
            token.literal = "+";
            readChar();
            return token;
        }
    }

    if (characterRead == '-'){
        if(nextCharacter == '-'){
            token.type = TokenType::DECREMENT_OPERATOR;
            token.literal = "--";
            readChar();
            readChar();
            return token;
        } else if(nextCharacter == '='){
            token.type = TokenType::SHORTHAND_SUBTRACTION;
            token.literal = "-=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::MINUS_OPERATOR;
            token.literal = "-";
            readChar();
            return token;
        }
    }

    if (characterRead == '%'){
        if(nextCharacter == '='){
            token.type = TokenType::SHORTHAND_MODULUS;
            token.literal = "%=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::MODULUS_OPERATOR;
            token.literal = "%";
            readChar();
            return token;
        }
    }

    if (characterRead == '*'){
        if(nextCharacter == '='){
            token.type = TokenType::SHORTHAND_MULTIPLICATION;
            token.literal = "*=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::ASTERISK;
            token.literal = "*";
            readChar();
            return token;
        }
    }

    if (characterRead == '<'){
        if(nextCharacter == '='){
            token.type = TokenType::LESSER_EQUAL;
            token.literal = "<=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::LESSER_THAN;
            token.literal = "<";
            readChar();
            return token;
        }
    }

    if (characterRead == '>'){
        if(nextCharacter == '='){
            token.type = TokenType::GREATER_EQUAL;
            token.literal = ">=";
            readChar();
            readChar();
            return token;
        } else{
            token.type = TokenType::GREATER_THAN;
            token.literal = ">";
            readChar();
            return token;
        }
    }
    
    if (characterRead == '^'){
        if(nextCharacter == '='){
            token.type = TokenType::SHORTHAND_EXPONENTIATION;
            token.literal = "^=";
            readChar();
            readChar();
            return token;
        } else if(nextCharacter == '^'){ // could be ^^ or ^^=
            readChar();
            if(nextCharacter == '='){
                readChar();
                readChar();
                token.type = TokenType::SHORTHAND_BITWISE_XOR;
                token.literal = "^^=";
                return token;
            }
            readChar();
            token.type = TokenType::BITWISE_XOR;
            token.literal = "^^";
            return token;
        } else{
            token.type = TokenType::CARET;
            token.literal = "^";
            readChar();
            return token;
        }
    }
    
    if (characterRead == '&'){
        if(nextCharacter == '&'){
            readChar();
            readChar();
            token.type = TokenType::LOGICAL_AND;
            token.literal = "&&";
            return token;
        } else if(nextCharacter == '='){
            readChar();
            readChar();
            token.type = TokenType::SHORTHAND_BITWISE_AND;
            token.literal = "&=";
            return token;
        }
        readChar();
        token.type = TokenType::AMPERSAND;
        token.literal = "&";
        return token;
    }
    
    if (characterRead == '|'){
        if(nextCharacter == '|'){
            readChar();
            readChar();
            token.type = TokenType::LOGICAL_OR;
            token.literal = "||";
            return token;
        } else if(nextCharacter == '='){
            readChar();
            readChar();
            token.type = TokenType::SHORTHAND_BITWISE_OR;
            token.literal = "|=";
            return token;
        }
        readChar();
        token.type = TokenType::PIPE_OPERATOR;
        token.literal = "|";
        return token;
    }

    if (characterRead == '('){
        token.type = TokenType::LEFT_PARENTHESIS;
        token.literal = "(";
        readChar();
        return token;
    }
    
    if (characterRead == ')'){
        token.type = TokenType::RIGHT_PARENTHESIS;
        token.literal = ")";
        readChar();
        return token;
    }

    
    if (characterRead == '{'){
        token.type = TokenType::LEFT_CURLY_BRACES;
        token.literal = "{";
        readChar();
        return token;
    }

    
    if (characterRead == '}'){
        token.type = TokenType::RIGHT_CURLY_BRACES;
        token.literal = "}";
        readChar();
        return token;
    }

    
    if (characterRead == '['){
        token.type = TokenType::LEFT_SQUARE_BRACKET;
        token.literal = "[";
        readChar();
        return token;
    }

    
    if (characterRead == ']'){
        token.type = TokenType::RIGHT_SQUARE_BRACKET;
        token.literal = "]";
        readChar();
        return token;
    }

    if (characterRead == '?'){
        token.type = TokenType::QUESTION_MARK;
        token.literal = "?";
        readChar();
        return token;
    }

    if (characterRead == '\''){
        token.type = TokenType::SINGLE_QUOTE;
        token.literal = "'";
        readChar();

        Token value;
        value.type = TokenType::VALUE_LITERAL;
        value.line_number = lineNumber;
        value.column_number = columnNumber;
        while (characterRead != '\'' && characterRead != '\n' && characterRead != 0) {
            value.literal += characterRead;
            readChar();
        }
        tokensBuffer.push_back(value);
        if (characterRead == '\'') {
            Token closingQuote;
            closingQuote.type = TokenType::SINGLE_QUOTE;
            closingQuote.literal = "'";
            closingQuote.line_number = lineNumber;
            closingQuote.column_number = columnNumber;
            tokensBuffer.push_back(closingQuote);
            readChar();
        } else {
            Token unclosedliteral;
            unclosedliteral.type = TokenType::UNCLOSED_STRING_LITERAL;
            unclosedliteral.literal = "";
            unclosedliteral.line_number = lineNumber;
            unclosedliteral.column_number = columnNumber;
            tokensBuffer.push_back(unclosedliteral);
            readChar();
        }

        return token;
    }

    if (characterRead == '"'){
        token.type = TokenType::DOUBLE_QUOTE;
        token.literal = "\"";
        readChar();

        Token value;
        value.type = TokenType::VALUE_LITERAL;
        value.line_number = lineNumber;
        value.column_number = columnNumber;
        while (characterRead != '"' && characterRead != '\n' && characterRead != 0) {
            value.literal += characterRead;
            readChar();
        }
        tokensBuffer.push_back(value);
        if (characterRead == '"') {
            Token closingQuote;
            closingQuote.type = TokenType::DOUBLE_QUOTE;
            closingQuote.literal = "\"";
            closingQuote.line_number = lineNumber;
            closingQuote.column_number = columnNumber;
            tokensBuffer.push_back(closingQuote);
            readChar();
        } else {
            Token unclosedliteral;
            unclosedliteral.type = TokenType::UNCLOSED_STRING_LITERAL;
            unclosedliteral.literal = "";
            unclosedliteral.line_number = lineNumber;
            unclosedliteral.column_number = columnNumber;
            tokensBuffer.push_back(unclosedliteral);
            readChar();
        }

        return token;
    }

    token.type = TokenType::UNKNOWN;
    token.literal = "=====UNKNOWN TOKEN====";
    reportError("Unknown symbol encountered.");
    return token;
}

std::vector<Token> getTokens(std::string sourceCode){
    std::vector<Token> tokens;
    Lexer lexer(sourceCode);
    std::vector<Token> tokensBuffer;   // this is for instances when i wanna return more than one token really
    while(true){
        Token token = lexer.getNextToken(tokensBuffer);
        tokens.push_back(token);
        if (token.type == TokenType::ENDOFFILE) {
            break;
        }
    }
    return tokens;
}