#include "skip_statement_node.hpp"

#include <format>
#include <sstream>

namespace ABRUHP {
SkipStatementNode::SkipStatementNode() : lines(1) {}

SkipStatementNode::SkipStatementNode(Token lines) {
  std::stringstream stream(lines.getValue());
  stream >> this->lines;
}

std::string SkipStatementNode::toString() {
  return std::format("(SKIP: {})", std::to_string(lines));
}

std::string SkipStatementNode::generate() {
  return std::format("SKIP {}.", lines);
}
} // namespace ABRUHP