#include "assignment_statement_node.hpp"

#include <format>

namespace ABRUHP {
AssignmentStatementNode::AssignmentStatementNode(Token variable_name,
                                                 Token value)
    : variable_name(variable_name.getValue()), value(value) {}

std::string AssignmentStatementNode::toString() {
  return std::format("[NAME: {}, VALUE: {}]", variable_name, value.toString());
}
std::string AssignmentStatementNode::generate() {
  return std::format("{} = {}.", variable_name, value.getValue());
}
} // namespace ABRUHP