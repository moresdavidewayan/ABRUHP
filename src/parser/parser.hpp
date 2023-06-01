#pragma once

#include <vector>

#include "../common/common.hpp"
#include "ast/ast.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;
  size_t current = 0, indentation_level = 0;

  Token advance();
  bool atEnd();
  Token getCurrent();
  Token peek();
  std::unique_ptr<BlockNode> handleBlock();
  std::unique_ptr<FunctionDefinitionStatementNode> handleFunctionDefinitionStatement();
  std::unique_ptr<InstructionNode> handleInstruction();
  std::unique_ptr<LineStatementNode> handleLineStatement();
  std::unique_ptr<PrintStatementNode> handlePrintStatement();
  std::unique_ptr<ProgramNode> handleProgram();
  std::unique_ptr<ProgramDeclarationNode> handleProgramDeclaration();
  std::unique_ptr<SkipStatementNode> handleSkipStatement();
  std::unique_ptr<StatementNode> handleStatement();

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP