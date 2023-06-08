#pragma once

#include "statement_node.hpp"

namespace ABRUHP {
    class LineStatementNode : public StatementNode {
        size_t lines;

        public:
        LineStatementNode();
        LineStatementNode(Token lines);

        virtual std::string toString();
        virtual std::string generate();
    };
}