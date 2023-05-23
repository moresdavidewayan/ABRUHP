#include "parser.hpp"

namespace ABRUHP {
Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

std::unique_ptr<ProgramNode> Parser::parse() {
    return std::move(handleProgram());
}
} // namespace ABRUHP