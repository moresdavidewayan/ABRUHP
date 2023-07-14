#pragma once

#include <vector>

#include "../common/common.hpp"
#include "ast/ast.hpp"

namespace ABRUHP {
class Parser {
  typedef std::string variable_name;
  typedef std::string variable_type;
  typedef std::string scope;
  typedef std::unordered_map<variable_name, variable_type> variable_info;

  std::vector<Token> tokens;
  std::unique_ptr<ProgramNode> program;
  size_t current = 0, indentation_level = 0;
  std::vector<std::string> scope_level = {"global"};
  std::unordered_map<variable_type, std::string> types = {
      {"byte", "X"},  {"text_field", "C"}, {"int", "I"},
      {"float", "F"}, {"packed", "P"},     {"string", "STRING"}};

  std::unordered_map<scope, std::vector<variable_info>> variables = {
      {"global", {}}};

  Token advance();
  bool atEnd();
  void check(Token value, TokenType expected, std::string message);
  void check(Token value, TokenType expected, std::string message, Token tk);
  void consumeNewLine();
  Token getCurrent();
  std::unique_ptr<AssignmentStatementNode> handleAssignmentStatement();
  std::unique_ptr<BlockNode> handleBlock();
  std::unique_ptr<FunctionDefinitionStatementNode>
  handleFunctionDefinitionStatement();
  std::unique_ptr<InstructionNode> handleInstruction();
  std::unique_ptr<LineStatementNode> handleLineStatement();
  std::unique_ptr<PrintStatementNode> handlePrintStatement();
  std::unique_ptr<ProgramNode> handleProgram();
  std::unique_ptr<ProgramDeclarationNode> handleProgramDeclaration();
  std::unique_ptr<SkipStatementNode> handleSkipStatement();
  std::unique_ptr<StatementNode> handleStatement();
  std::unique_ptr<VariableDeclarationStatementNode>
  handleVariableDeclarationStatement();
  Token peek();
  void unexpected_token(std::string expected);
  void unexpected_token(std::string expected, Token tk);

public:
  Parser(std::vector<Token> tokens);

  std::unique_ptr<ProgramNode> parse();
};
} // namespace ABRUHP