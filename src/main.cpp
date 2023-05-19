#include <fstream>
#include <iostream>

#include "common/log.hpp"
#include "common/utils.hpp"
#include "lexer/lexer.hpp"

void printUsage();

int main(int argc, char *argv[]) {
  std::string source;

  if (argc == 2) {
    std::string path = argv[1];
    source = readFile(path);
  } else if (argc == 1) {
    std::string path;
    std::cout << "Dammi il percorso:";
    std::cin >> path;
    source = readFile(path);
  } else
    printUsage();

  ABRUHP::Lexer lexer(source);
  for (ABRUHP::Token token : lexer.getTokens()) {
    std::cout << token << std::endl;
  }

  return EXIT_SUCCESS;
}

void printUsage() {
  std::cout << "Usage: ABRUHP [path/to/file.abruhp]" << std::endl;
  exit(EXIT_FAILURE);
}