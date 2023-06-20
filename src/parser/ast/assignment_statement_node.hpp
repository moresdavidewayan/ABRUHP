#pragma once

#include "ast_node.hpp"

namespace ABRUHP{
    class AssignmentStatementNode : public ASTNode{
        std::string variable_name;
        Token value;

        public:
        AssignmentStatementNode(Token variable_name, Token value);

        virtual std::string toString();
        virtual std::string generate();
    };
}