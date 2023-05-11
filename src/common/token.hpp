#pragma once

namespace ABRUHP
{
    enum class TokenType
    {
        TOKEN_EOF
    };

    class Token
    {
        TokenType type;

    public:
        Token(TokenType type);
    };
}