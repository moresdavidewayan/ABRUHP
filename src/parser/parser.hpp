#pragma once

#include <vector>

#include "../common/common.hpp"
#include "ast/ast.hpp"

namespace ABRUHP {
class Parser {
  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;
  size_t current = 0, indentation_level = 0;
  std::unordered_map<std::string, std::string> types = {
      {"byte", "X"},  {"text_field", "C"}, {"int", "I"},
      {"float", "F"}, {"packed", "P"},     {"string", "STRING"}};
  

  Token advance();
  bool atEnd();
  Token getCurrent();
  Token peek();
  void consumeNewLine();
  std::unique_ptr<AssignmentStatementNode> handleAssignmentStatement();
  std::unique_ptr<BlockNode> handleBlock();
  std::unique_ptr<FunctionDefinitionStatementNode> handleFunctionDefinitionStatement();
  std::unique_ptr<InstructionNode> handleInstruction();
  std::unique_ptr<LineStatementNode> handleLineStatement();
  std::unique_ptr<PrintStatementNode> handlePrintStatement();
  std::unique_ptr<ProgramNode> handleProgram();
  std::unique_ptr<ProgramDeclarationNode> handleProgramDeclaration();
  std::unique_ptr<SkipStatementNode> handleSkipStatement();
  std::unique_ptr<StatementNode> handleStatement();
  std::unique_ptr<VariableDeclarationStatementNode> handleVariableDeclarationStatement();
  void unexpected_token(std::string expected);
  void unexpected_token(std::string expected, Token tk);

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP