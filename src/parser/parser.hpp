#pragma once

#include <vector>

#include "../common/token.hpp"
#include "ast/ast.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;
  size_t current = 0;

  std::unique_ptr<ProgramNode> handleProgram();
  std::unique_ptr<ProgramDeclarationNode> handleProgramDeclaration();

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP