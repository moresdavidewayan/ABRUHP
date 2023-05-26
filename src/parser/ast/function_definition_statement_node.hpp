#pragma once

#include "block_node.hpp"
#include "statement_node.hpp"

namespace ABRUHP {
class FunctionDefinitionStatementNode : public StatementNode {
  std::string name;
  std::unique_ptr<BlockNode> body;

public:
  FunctionDefinitionStatementNode(Token name, std::unique_ptr<BlockNode> body);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP