#pragma once

#include "statement_node.hpp"

namespace ABRUHP {
class PrintStatementNode : public StatementNode {
  std::string message;

public:
  PrintStatementNode(Token message);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP