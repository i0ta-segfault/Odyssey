#include "odyssey.hpp"
#include <fstream>

int main(int argc, char** argv){

    if(argc != 2){
        std::cout << BOLD << RED << "Correct usage : ./odyssey file_name.ode" << RESET << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << BOLD << RED << "Error: Could not open file " << filePath << RESET << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string sourceCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::vector <Token> tokens = getTokens(sourceCode);

    if (tokens.empty()) {
        std::cout << "Tokens vector came back empty" << std::endl;
    }

    std::ofstream logFile("../logs/lexer_output.log");
    if (!logFile) {
        std::cerr << BOLD << RED << "Error: Could not create lexer_output.log" << RESET << std::endl;
        exit(EXIT_FAILURE);
    }

    logFile << "[" << std::endl;

    for (size_t i = 0; i < tokens.size(); i++) {
        logFile << "    {" << std::endl;
        logFile << "        \"line\": " << tokens[i].line_number << "," << std::endl;
        logFile << "        \"column\": " << tokens[i].column_number << "," << std::endl;
        logFile << "        \"type\": \"" << getTokenTypeName(tokens[i]) << "\"," << std::endl;
        logFile << "        \"literal\": \"" << tokens[i].literal << "\"" << std::endl;
        logFile << "    }";
        if (i != tokens.size() - 1) logFile << ",";
            logFile << std::endl;
    }

    logFile << "]" << std::endl;


    logFile.close();

    std::cout << "Lexer output written to lexer_output.log" << std::endl;

    return 0;
}