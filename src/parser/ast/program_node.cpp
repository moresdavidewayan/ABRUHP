#include "program_node.hpp"

namespace ABRUHP {
ProgramNode::ProgramNode(std::unique_ptr<ProgramDeclarationNode> declaration)
    : declaration(std::move(declaration)) {}

std::string ProgramNode::toString() { return declaration->toString(); }

std::string ProgramNode::generate() {
    std::string result;

    result += declaration->generate();

    return result;
}
} // namespace ABRUHP