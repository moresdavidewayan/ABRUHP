#include "lexer.hpp"

#include <cctype>
#include <format>

#include "../common/log.hpp"

namespace ABRUHP {
std::unordered_map<std::string, TokenType> keywords = {
    {"type", TokenType::TOKEN_PROGRAM_TYPE},
    {"report", TokenType::TOKEN_REPORT},
    {"name", TokenType::TOKEN_NAME},
    {"print", TokenType::TOKEN_PRINT},
    {"skip", TokenType::TOKEN_SKIP},
    {"line", TokenType::TOKEN_LINE}};

Token::Token(TokenType type) : type(type) {}
Token::Token(TokenType type, std::string value) : type(type), value(value) {}
void Lexer::addToken(TokenType type) { tokens.push_back(Token(type)); }

void Lexer::addToken(TokenType type, std::string value) {
  tokens.push_back(Token(type, value));
}

char Lexer::advance() {
  current += 1;
  return !atEnd() ? getCurrent() : '\0';
}

void Lexer::analyze() {
  char c = getCurrent();
  while (!atEnd()) {
    switch (c) {
    case '"':
      handleString();
      break;
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
    case ' ':
    case '\r':
      break;
    default:
      if (isAlpha(c))
        handleIdentifier();
      else if (isNumeric(c))
        handleNumber();
      else
        logError(std::format("Unexpected character.{}", getCurrent()));
    }
    c = advance();
  }
  addToken(TokenType::TOKEN_EOF);
}

bool Lexer::atEnd() { return current >= source.length(); }

char Lexer::getCurrent() { return source.at(current); }

void Lexer::handleComment() {
  std::string comment;
  while (peek() != '\n')
    comment.push_back(advance());
  addToken(TokenType::TOKEN_COMMENT, comment);
}

void Lexer::handleIdentifier() {
  std::string identifier;
  identifier.push_back(getCurrent());
  while (isAlphaNumeric(peek()))
    identifier.push_back(advance());
  if (keywords.contains(identifier))
    return addToken(keywords.at(identifier));
  return addToken(TokenType::TOKEN_IDENTIFIER, identifier);
}

void Lexer::handleNumber() {
  std::string number;
  number.push_back(getCurrent());
  while (isNumeric(peek()))
    number.push_back(advance());
  addToken(TokenType::TOKEN_INTEGER, number);
}

void Lexer::handleString() {
  std::string value;
  while (peek() != '"')
    value.push_back(advance());
  advance();
  addToken(TokenType::TOKEN_STRING, value);
}

bool Lexer::isAlpha(char control) {
  return (control >= 'a' && control <= 'z') ||
         (control >= 'A' && control <= 'Z');
}

bool Lexer::isAlphaNumeric(char control) {
  return isAlpha(control) || isNumeric(control);
}

bool Lexer::isNumeric(char control) { return isdigit(control); }

char Lexer::peek() {
  if (current >= source.length() - 1)
    logError("EOF");
  return source.at(current + 1);
}

Lexer::Lexer(std::string source) : source(source) { analyze(); }

std::vector<Token> Lexer::getTokens() { return tokens; }
} // namespace ABRUHP