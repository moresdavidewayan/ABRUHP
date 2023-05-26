#pragma once

#include "ast_node.hpp"

namespace ABRUHP {
class InstructionNode : public ASTNode {
public:
  virtual std::string toString() = 0;
  virtual std::string generate() = 0;
};
} // namespace ABRUHP