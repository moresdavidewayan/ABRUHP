#pragma once

#include <memory>
#include <vector>

#include "ast_node.hpp"
#include "instruction_node.hpp"

namespace ABRUHP {
class BlockNode : public ASTNode {
  std::vector<std::unique_ptr<InstructionNode>> instructions;

public:
  BlockNode(std::vector<std::unique_ptr<InstructionNode>> instructions);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP