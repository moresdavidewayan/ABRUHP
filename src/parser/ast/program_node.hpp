#pragma once

#include "ast_node.hpp"
#include "program_declaration_node.hpp"

namespace ABRUHP {
class ProgramNode : public ASTNode {
  std::unique_ptr<ProgramDeclarationNode> declaration;

public:
  ProgramNode(std::unique_ptr<ProgramDeclarationNode> declaration);

  virtual std::string toString();
};
} // namespace ABRUHP