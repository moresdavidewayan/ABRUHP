#pragma once

#include <ostream>
#include <string>
#include <unordered_map>

namespace ABRUHP {
enum class TokenType {
  TOKEN_PROGRAM_TYPE,

  // Format tokens
  TOKEN_NEW_LINE,
  TOKEN_INDENTATION,

  // Report specific tokens
  TOKEN_REPORT,
  TOKEN_NAME,

  // Basic types
  TOKEN_STRING,
  TOKEN_INTEGER,

  // ()
  TOKEN_LEFT_PARENTHESIS,
  TOKEN_RIGHT_PARENTHESIS,

  // :
  TOKEN_COLON,

  // =
  TOKEN_ASSIGN,

  // Identifier
  TOKEN_IDENTIFIER,

  // Standard functions
  TOKEN_PRINT,
  TOKEN_SKIP,
  TOKEN_ULINE,

  // Comment
  TOKEN_COMMENT,

  TOKEN_EOF,
};

class Token {
  TokenType type;
  std::string value;
  size_t line;

public:
  Token(TokenType type, size_t line);
  Token(TokenType type, std::string value, size_t line);

  size_t getLine();
  TokenType getType();
  std::string getValue();
  std::string toString();

  bool operator==(const TokenType type);
  bool operator==(Token tk);
  bool operator!=(const TokenType type);
  bool operator!=(Token tk);
};
} // namespace ABRUHP

std::ostream &operator<<(std::ostream &os, ABRUHP::Token &tk);