#include "parser.hpp"

namespace ABRUHP {
    std::unique_ptr<ProgramNode> Parser::handleProgram() {
        return std::make_unique<ProgramNode>(handleProgramDeclaration());
    }

    std::unique_ptr<ProgramDeclarationNode> Parser::handleProgramDeclaration() {
        return nullptr;
    }

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

std::unique_ptr<ProgramNode> Parser::parse() {
    return std::move(handleProgram());
}
} // namespace ABRUHP