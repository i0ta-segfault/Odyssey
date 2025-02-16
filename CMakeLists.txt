cmake_minimum_required(VERSION 3.10)
project(Odyssey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/lexer/lexer.cpp
    src/parser/parser.cpp
    src/token/token.cpp
    src/ast/ast.cpp
    src/evaluator/evaluator.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(odyssey ${SOURCES})