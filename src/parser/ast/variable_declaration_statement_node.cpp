#include "variable_declaration_statement_node.hpp"

#include <format>

namespace ABRUHP {
VariableDeclarationStatementNode::VariableDeclarationStatementNode(
    Token abruhp_type, std::string abap_type, Token name)
    : abruhp_type(abruhp_type.getValue()), abap_type(abap_type),
      name(name.getValue()) {}

std::string VariableDeclarationStatementNode::toString() {
  return std::format("[VARIABLE DECLARATION: type {}, name {}]", abruhp_type,
                     name);
}

std::string VariableDeclarationStatementNode::generate() {
  return std::format("DATA: {} TYPE {}.", name, abap_type);
}
} // namespace ABRUHP