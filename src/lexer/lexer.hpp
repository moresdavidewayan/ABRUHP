#pragma once

#include <string>
#include <vector>

#include "../common/common.hpp"

namespace ABRUHP {
class Lexer {
  std::string source;
  std::vector<Token> tokens;
  size_t current = 0, line = 1;

  void addToken(TokenType type);
  void addToken(TokenType type, std::string value);
  char advance();
  void analyze();
  bool atEnd();
  char getCurrent();
  void handleComment();
  void handleIdentifier();
  void handleNumber();
  void handleString();
  bool isAlpha(char control);
  bool isAlphaNumeric(char control);
  bool isNumeric(char control);
  char peek();

public:
  Lexer(std::string source);

  std::vector<Token> getTokens();
};

} // namespace ABRUHP
