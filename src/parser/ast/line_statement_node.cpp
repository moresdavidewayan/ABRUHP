#include "line_statement_node.hpp"

#include <format>

namespace ABRUHP {
    LineStatementNode::LineStatementNode() : lines(1) {}

    LineStatementNode::LineStatementNode(size_t lines) : lines(lines) {}

    std::string LineStatementNode::toString() {
        return std::format("[LINES: {}]", std::to_string(lines));
    }

    std::string LineStatementNode::generate() {
        return std::format("LINE {}.", lines);
    }
}