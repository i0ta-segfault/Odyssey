#include "odyssey.hpp"

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
    std::cout << std::string(50, '-') << std::endl;
    for (size_t i = 0; i < tokens.size(); i++) {
        // if (tokens[i].literal.empty()) {
        //     std::printf("Token %zu has an empty literal\n", i);
        //     continue;
        // }
        std::printf("Token Type: %-30s | Literal: %-20s | Line: %d   Column: %d\n",
            getTokenTypeName(tokens[i]).c_str(),  // Convert std::string to C-style string
            tokens[i].literal.c_str(),           // Convert std::string to C-style string
            tokens[i].line_number,
            tokens[i].column_number);
    }
    std::cout << std::string(50, '-') << std::endl;

    return 0;
}