#include "line_statement_node.hpp"

#include <format>
#include <sstream>

namespace ABRUHP {
    LineStatementNode::LineStatementNode() : lines(1) {}

    LineStatementNode::LineStatementNode(Token lines) {
        std::stringstream stream(lines.getValue());
        stream >> this->lines;
    }

    std::string LineStatementNode::toString() {
        return std::format("[LINES: {}]", std::to_string(lines));
    }

    std::string LineStatementNode::generate() {
        return std::format("LINE {}.", lines);
    }
}