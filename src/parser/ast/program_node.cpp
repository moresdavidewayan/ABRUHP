#include "program_node.hpp"

namespace ABRUHP {
ProgramNode::ProgramNode(std::unique_ptr<ProgramDeclarationNode> declaration)
    : declaration(std::move(declaration)) {}

std::string ProgramNode::toString() { return declaration->toString(); }
} // namespace ABRUHP