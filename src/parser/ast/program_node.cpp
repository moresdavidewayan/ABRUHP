#include "program_node.hpp"

#include <format>

namespace ABRUHP {
ProgramNode::ProgramNode(std::unique_ptr<ProgramDeclarationNode> declaration,
                         std::vector<std::unique_ptr<StatementNode>> statements)
    : declaration(std::move(declaration)), statements(std::move(statements)) {}

std::string ProgramNode::toString() {
  std::string result;

  result += declaration->toString();

  for (size_t index = 0; index < statements.size(); index += 1) {
    result += statements.at(index)->toString();
  }

  return result;
}

std::string ProgramNode::generate() {
  std::string result;

  result += std::format("{}\n", declaration->generate());

  for (size_t index = 0; index < statements.size(); index += 1) {
    result += statements.at(index)->generate();
  }

  return result;
}
} // namespace ABRUHP