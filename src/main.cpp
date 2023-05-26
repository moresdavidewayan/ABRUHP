#include <fstream>
#include <iostream>

#include "common/common.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

int main(int argc, char *argv[]) {
  std::string source;

  std::string path;
  std::cout << "File path: ";
  std::cin >> path;
  source = readFile(path);

  ABRUHP::Lexer lexer(source);
  std::vector<ABRUHP::Token> tokens = lexer.getTokens();

  ABRUHP::Parser parser(tokens);
  std::unique_ptr<ABRUHP::ASTNode> program = parser.parse();
  std::cout << program->toString() << std::endl;

  std::cout << program->generate() << std::endl;

  return EXIT_SUCCESS;
}