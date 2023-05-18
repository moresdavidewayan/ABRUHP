#pragma once

#include <string>
#include <vector>

#include "../common/token.hpp"

namespace ABRUHP
{
    class Lexer
    {
        std::string source;
        std::vector<Token> tokens;
        size_t current = 0;

        void addToken(TokenType type);
        void addToken(TokenType type, std::string value);
        char advance();
        void analyze();
        bool atEnd();
        char getCurrent();

    public:
        Lexer(std::string source);

        std::vector<Token> getTokens();

    };

}
