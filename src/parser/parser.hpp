#pragma once

#include <vector>

#include "../common/common.hpp"
#include "ast/program_node.hpp"
#include "ast/program_declaration_node.hpp"
#include "ast/statement_node.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;
  size_t current = 0;

  Token advance();
  bool atEnd();
  Token getCurrent();
  std::unique_ptr<ProgramNode> handleProgram();
  std::unique_ptr<ProgramDeclarationNode> handleProgramDeclaration();
  std::unique_ptr<StatementNode> handleStatement();

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP