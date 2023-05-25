#pragma once

#include <memory>
#include <ostream>
#include <string>

#include "../../common/common.hpp"

namespace ABRUHP {
class ASTNode {
public:
  virtual std::string toString() = 0;
  virtual std::string generate() = 0;
};
} // namespace ABRUHP

std::ostream &operator<<(std::ostream os, ABRUHP::ASTNode *ast);