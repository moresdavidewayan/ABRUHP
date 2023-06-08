#include <iostream>

#include "common/common.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

void usage();

int main(int argc, char *argv[]) {
  std::string source;

  if (argc != 2) usage();

  source = readFile(argv[1]);

  ABRUHP::Lexer lexer(source);
  std::vector<ABRUHP::Token> tokens = lexer.getTokens();

  ABRUHP::Parser parser(tokens);
  std::unique_ptr<ABRUHP::ASTNode> program = parser.parse();
  std::cout << program->toString() << std::endl;

  std::cout << program->generate() << std::endl;

  return EXIT_SUCCESS;
}

void usage() {
  std::cerr << "Usage: abruhp path/to/file.abruhp" << std::endl;
  exit(EXIT_FAILURE);
}