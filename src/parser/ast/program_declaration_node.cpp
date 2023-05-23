#include "program_declaration_node.hpp"

#include <format>

namespace ABRUHP {
ProgramDeclarationNode::ProgramDeclarationNode(Token type, Token name)
    : type(type.getType()), name(name.getValue()) {}

    std::string ProgramDeclarationNode::toString() {
        return std::format("(PROGRAM {} NAME {})", type.toString(), name);
    }
} // namespace ABRUHP