#include "block_node.hpp"

#include <format>

namespace ABRUHP {
BlockNode::BlockNode(std::vector<std::unique_ptr<InstructionNode>> instructions)
    : instructions(std::move(instructions)) {}

std::string BlockNode::toString() {
  std::string result = "[BLOCK: ";
  for (size_t index = 0; index < instructions.size(); index += 1)
    result += std::format("{}{}", instructions.at(index)->toString(),
                          index == instructions.size() - 1 ? "" : ",\n");
  result += "]";
  return result;
}

std::string BlockNode::generate() {
  std::string result;
  for (size_t index = 0; index < instructions.size(); index += 1)
    result += std::format("{}\n", instructions.at(index)->generate());
  return result;
}
} // namespace ABRUHP