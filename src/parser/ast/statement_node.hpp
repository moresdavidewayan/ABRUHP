#pragma once

#include "ast.hpp"

namespace ABRUHP {
class StatementNode : public ASTNode {
public:
  virtual std::string toString() = 0;
  virtual std::string generate() = 0;
};
} // namespace ABRUHP