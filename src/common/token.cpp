#include "token.hpp"

#include <format>

namespace ABRUHP {
std::string Token::toString() {
  switch (type) {
  case TokenType::TOKEN_IDENTIFIER:
    return std::format("[IDENTIFIER: {}]", value);
  default:
    break;
  }
  return "";
}
} // namespace ABRUHP

std::ostream &operator<<(std::ostream &os, ABRUHP::Token &tk) {
  os << tk.toString();
  return os;
}