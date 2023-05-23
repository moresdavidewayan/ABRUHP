#pragma once

#include <vector>

#include "../common/token.hpp"
#include "ast/ast.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;

  std::unique_ptr<ProgramNode> handleProgram();

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP