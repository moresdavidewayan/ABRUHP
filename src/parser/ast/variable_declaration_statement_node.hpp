#pragma once

#include <unordered_map>

#include "statement_node.hpp"

namespace ABRUHP {
class VariableDeclarationStatementNode : public StatementNode {
  std::string abruhp_type, abap_type, name;

public:
  VariableDeclarationStatementNode(Token abruhp_type, std::string abap_type,
                                   Token name);

  virtual std::string toString();
  virtual std::string generate();
};
} // namespace ABRUHP