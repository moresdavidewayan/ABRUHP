#include "ast_node.hpp"

namespace ABRUHP {}

std::ostream &operator<<(std::ostream os, ABRUHP::ASTNode *ast) {
  return os << ast->toString();
}