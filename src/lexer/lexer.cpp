#include "lexer.hpp"

#include <cctype>

#include "../common/log.hpp"

namespace ABRUHP {
void Lexer::addToken(TokenType type) { tokens.push_back(Token(type)); }

void Lexer::addToken(TokenType type, std::string value) {
  tokens.push_back(Token(type, value));
}

char Lexer::advance() {
  char result = getCurrent();
  current += 1;
  return result;
}

void Lexer::analyze() {
  char c = getCurrent();
  while (!atEnd()) {
    switch (c) {
    case '\n':
      addToken(TokenType::TOKEN_NEW_LINE);
      break;
    case '\t':
      addToken(TokenType::TOKEN_INDENTATION);
      break;
    case '(':
      addToken(TokenType::TOKEN_LEFT_PARENTHESIS);
      break;
    case ')':
      addToken(TokenType::TOKEN_RIGHT_PARENTHESIS);
      break;
    case ':':
      addToken(TokenType::TOKEN_COLON);
      break;
    case '#':
      handleComment();
      break;
    // Ignore
    case ' ':
    case '\r':
      break;
    default:
      if (isAlpha(c))
        handleIdentifier();
      else if (isNumeric(c))
        handleNumber();
      else
        logError("Unexpected character.");
    }
    c = advance();
  }
  addToken(TokenType::TOKEN_EOF);
}

bool Lexer::atEnd() { return current >= source.length(); }

char Lexer::getCurrent() { return source.at(current); }

void Lexer::handleComment() {
  std::string comment;
  while (peek() != '\n') comment.push_back(advance());
  addToken(TokenType::TOKEN_COMMENT, comment);
}

void Lexer::handleIdentifier() {
  std::string identifier;
  identifier.push_back(advance());
  while (isAlphaNumeric(peek()))
    identifier.push_back(advance());
  if (keywords.contains(identifier))
    return addToken(keywords.at(identifier));
  return addToken(TokenType::TOKEN_IDENTIFIER, identifier);
}

void Lexer::handleNumber() {
  std::string number;
  number.push_back(advance());
  while (isNumeric(peek()))
    number.push_back(advance());
  addToken(TokenType::TOKEN_INTEGER, number);
}

bool Lexer::isAlpha(char control) { return isalpha(control); }

bool Lexer::isAlphaNumeric(char control) {
  return isAlpha(control) && isNumeric(control);
}

bool Lexer::isNumeric(char control) { return isdigit(control); }

char Lexer::peek() {
  if (current >= source.length() - 2)
    logError("EOF");
  return source.at(current + 1);
}

Lexer::Lexer(std::string source) : source(source) { analyze(); }

std::vector<Token> Lexer::getTokens() { return tokens; }
} // namespace ABRUHP