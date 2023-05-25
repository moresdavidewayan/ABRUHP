#include "skip_statement_node.hpp"

#include <format>

namespace ABRUHP {
SkipStatementNode::SkipStatementNode() : lines(1) {}

SkipStatementNode::SkipStatementNode(size_t lines) : lines(lines) {}

std::string SkipStatementNode::toString() {
  return std::format("(SKIP: {})", std::to_string(lines));
}

std::string SkipStatementNode::generate() {
  return std::format("SKIP {}.", lines);
}
} // namespace ABRUHP