#pragma once

#include "ast_node.hpp"

namespace ABRUHP {
class ProgramDeclarationNode : public ASTNode {
  Token type;
  std::string name;

public:
  ProgramDeclarationNode(Token type, Token name);

  virtual std::string toString();
};
} // namespace ABRUHP