#pragma once

#include <vector>

#include "ast_node.hpp"
#include "program_declaration_node.hpp"
#include "statement_node.hpp"

namespace ABRUHP {
class ProgramNode : public ASTNode {
  std::unique_ptr<ProgramDeclarationNode> declaration;
  std::vector<std::unique_ptr<StatementNode>> statements;

public:
  ProgramNode(std::unique_ptr<ProgramDeclarationNode> declaration,
              std::vector<std::unique_ptr<StatementNode>> statements);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP