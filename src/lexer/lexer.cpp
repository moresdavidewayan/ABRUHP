#include "lexer.hpp"

namespace ABRUHP
{
    void Lexer::addToken(TokenType type)
    {
        tokens.push_back(Token(type));
    }

    void Lexer::addToken(TokenType type, std::string value)
    {
        tokens.push_back(Token(type, value));
    }

    char Lexer::advance() {
        char result = getCurrent();
        current += 1;
        return result;
    }

    void Lexer::analyze()
    {
        while (!atEnd())
        {
            switch (getCurrent())
            {
            default:
                throw "Unexpected character";
            }
            advance();
        }
        addToken(TokenType::TOKEN_EOF);
    }

    bool Lexer::atEnd()
    {
        return current >= source.length();
    }

    char Lexer::getCurrent()
    {
        return source.at(current);
    }
    Lexer::Lexer(std::string source) : source(source)
    {
        analyze();
    }

    std::vector<Token> Lexer::getTokens()
    {
        return tokens;
    }
}