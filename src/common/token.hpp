#pragma once

#include <string>

namespace ABRUHP
{
    enum class TokenType
    {
        // Basic types
        TOKEN_STRING,

        // Standard functions
        TOKEN_PRINT,

        // Special tokens
        TOKEN_NEW_LINE,
        TOKEN_TAB,
        TOKEN_EOF
    };

    class Token
    {
        TokenType type;
        std::string value;

    public:
        Token(TokenType type);
        Token(TokenType type, std::string value);
    };
}