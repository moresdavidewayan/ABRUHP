#include "variable_declaration_statement_node.hpp"

#include <format>

namespace ABRUHP {
VariableDeclarationStatementNode::VariableDeclarationStatementNode(Token type,
                                                                   Token name)
    : type(type.getValue()), name(type.getValue()) {}

std::string VariableDeclarationStatementNode::toString() {
    return std::format("[VARIABLE DECLARATION: type {}, name {}]", type, name);
}

std::string VariableDeclarationStatementNode::generate() {
    return std::format("DATA: {} TYPE {}.", name, type);
}
} // namespace ABRUHP