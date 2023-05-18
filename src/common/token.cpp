#include "token.hpp"

#include <format>

namespace ABRUHP
{
    Token::Token(TokenType type) : type(type) {}
    Token::Token(TokenType type, std::string value) : type(type), value(value) {}

    std::string Token::toString()
    {
        switch (type)
        {
        default:
            break;
        }
    }
}

std::ostream &operator<<(std::ostream &os, ABRUHP::Token &tk)
{
    os << tk.toString();
    return os;
}