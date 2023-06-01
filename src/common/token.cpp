#include "token.hpp"

#include <format>

namespace ABRUHP {
Token::Token(TokenType type, size_t line) : type(type), line(line) {}

Token::Token(TokenType type, std::string value, size_t line)
    : type(type), value(value), line(line) {}

size_t Token::getLine() { return line; }

TokenType Token::getType() { return type; }

std::string Token::getValue() { return value; }

std::string Token::toString() {
  switch (type) {
  case TokenType::TOKEN_PROGRAM_TYPE:
    return "[PROGRAM]";
  case TokenType::TOKEN_NEW_LINE:
    return "[NEW LINE]";
  case TokenType::TOKEN_INDENTATION:
    return "[INDENTATION]";
  case TokenType::TOKEN_REPORT:
    return "[REPORT]";
  case TokenType::TOKEN_NAME:
    return "[NAME]";
  case TokenType::TOKEN_STRING:
    return std::format("[STRING: {}]", value);
  case TokenType::TOKEN_INTEGER:
    return std::format("[INTEGER: {}]", value);
  case TokenType::TOKEN_LEFT_PARENTHESIS:
    return "[LEFT PARENTHESIS]";
  case TokenType::TOKEN_RIGHT_PARENTHESIS:
    return "[RIGHT PARENTHESIS]";
  case TokenType::TOKEN_COLON:
    return "[COLON]";
  case TokenType::TOKEN_IDENTIFIER:
    return std::format("[IDENTIFIER: {}]", value);
  case TokenType::TOKEN_PRINT:
    return "[PRINT]";
  case TokenType::TOKEN_SKIP:
    return "[SKIP]";
  case TokenType::TOKEN_LINE:
    return "[LINE]";
  case TokenType::TOKEN_COMMENT:
    return std::format("[COMMENT: {}]", value);
  case TokenType::TOKEN_EOF:
    return "[END OF FILE]";
  default:
    break;
  }
  return "";
}

bool Token::operator==(const TokenType type) { return this->getType() == type; }

bool Token::operator==(Token tk) {
  return this->getType() == tk.getType() &&
         this->getValue().compare(tk.getValue());
}

bool Token::operator!=(const TokenType type) { return !this->operator==(type); }

bool Token::operator!=(Token tk) { return !this->operator==(tk); }
} // namespace ABRUHP

std::ostream &operator<<(std::ostream &os, ABRUHP::Token &tk) {
  return os << tk.toString();
}