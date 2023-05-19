#pragma once

#include <vector>

#include "../common/token.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;

public:
  Parser(std::vector<Token> tokens);
};
} // namespace ABRUHP