#pragma once

#include "statement_node.hpp"

namespace ABRUHP{
    class AssignmentStatementNode : public StatementNode{
        std::string variable_name;
        Token value;

        public:
        AssignmentStatementNode(Token variable_name, Token value);

        virtual std::string toString();
        virtual std::string generate();
    };
}