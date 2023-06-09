#pragma once

#include "instruction_node.hpp"

namespace ABRUHP {
class StatementNode : public InstructionNode {
public:
  virtual std::string toString() = 0;
  virtual std::string generate() = 0;
};
} // namespace ABRUHP