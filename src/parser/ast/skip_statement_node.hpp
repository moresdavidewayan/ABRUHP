#pragma once

#include "statement_node.hpp"

namespace ABRUHP {
class SkipStatementNode : public StatementNode {
  size_t lines;

public:
  SkipStatementNode();
  SkipStatementNode(size_t lines);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP