#include <fstream>
#include <iostream>

#include "common/common.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

void printUsage();

int main(int argc, char *argv[]) {
  std::string source;

  if (argc == 2) {
    std::string path = argv[1];
    source = readFile(path);
  } else if (argc == 1) {
    std::string path;
    std::cout << "File path: ";
    std::cin >> path;
    source = readFile(path);
  } else
    printUsage();

  ABRUHP::Lexer lexer(source);
  std::vector<ABRUHP::Token> tokens = lexer.getTokens();
  for (ABRUHP::Token token : tokens) {
    std::cout << token << std::endl;
  }

  ABRUHP::Parser parser(tokens);
  std::unique_ptr<ABRUHP::ASTNode> program = parser.parse();
  std::cout << program->toString() << std::endl;

  return EXIT_SUCCESS;
}

void printUsage() {
  std::cout << "Usage: ABRUHP [path/to/file.abruhp]" << std::endl;
  exit(EXIT_FAILURE);
}