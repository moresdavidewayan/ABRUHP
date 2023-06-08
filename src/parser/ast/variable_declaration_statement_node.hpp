#pragma once

#include "statement_node.hpp"

namespace ABRUHP {
class VariableDeclarationStatementNode : StatementNode {
  TokenType type;
  std::string name;

public:
  VariableDeclarationStatementNode(Token type, Token name);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP