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

  // Identifier
  TOKEN_IDENTIFIER,

  // Standard functions
  TOKEN_PRINT,
  TOKEN_SKIP,
  TOKEN_LINE,

  // Comment
  TOKEN_COMMENT,

  TOKEN_EOF,
};

class Token {
  TokenType type;
  std::string value;

public:
  Token(TokenType type);
  Token(TokenType type, std::string value);

  TokenType getType();
  std::string getValue();
  std::string toString();

  bool operator==(const TokenType type);
  bool operator==(Token tk);
};
} // namespace ABRUHP

std::ostream &operator<<(std::ostream &os, ABRUHP::Token &tk);