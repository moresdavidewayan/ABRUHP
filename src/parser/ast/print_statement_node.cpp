#include "print_statement_node.hpp"

#include <format>

namespace ABRUHP {
PrintStatementNode::PrintStatementNode(Token message)
    : message(message.getValue()) {}

std::string PrintStatementNode::toString() {
  return std::format("[PRINT: {}]", message);
}

std::string PrintStatementNode::generate() {
  return std::format("WRITE '{}'.", message);
}
} // namespace ABRUHP