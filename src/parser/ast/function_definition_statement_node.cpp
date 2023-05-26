#include "function_definition_statement_node.hpp"

#include <format>

namespace ABRUHP {
    FunctionDefinitionStatementNode::FunctionDefinitionStatementNode(Token name, std::unique_ptr<BlockNode> body) : name(name.getValue()), body(std::move(body)) {}

    std::string FunctionDefinitionStatementNode::toString() {
        return std::format("[FUNCTION: {}, BODY: {}]", name, body->toString());
    }

    std::string FunctionDefinitionStatementNode::generate() {
        return std::format("FORM {}.\n{}\nENDFORM.", name, body->generate());
    }
}