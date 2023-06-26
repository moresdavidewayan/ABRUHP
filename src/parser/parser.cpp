#include "parser.hpp"

#include <format>

namespace ABRUHP {
Token Parser::advance() {
  current += 1;
  return getCurrent();
}

bool Parser::atEnd() { return current >= tokens.size() - 1; }

void Parser::check(Token value, TokenType expected, std::string message) {
  if (value != expected)
    unexpected_token(message);
}

void Parser::check(Token value, TokenType expected, std::string message,
                   Token tk) {
  if (value != expected)
    unexpected_token(message, tk);
}

void Parser::consumeNewLine() {
  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");

  advance();
}

Token Parser::getCurrent() { return tokens.at(current); }

std::unique_ptr<AssignmentStatementNode> Parser::handleAssignmentStatement() {
  Token variableName = getCurrent();

  check(advance(), TokenType::TOKEN_ASSIGN, "=");

  Token value = advance();

  check(value, TokenType::TOKEN_INTEGER, "value");
  consumeNewLine();

  return std::make_unique<AssignmentStatementNode>(variableName, value);
}

std::unique_ptr<BlockNode> Parser::handleBlock() {
  indentation_level += 1;

  std::vector<std::unique_ptr<InstructionNode>> instructions;

  while (!atEnd()) {
    size_t count_indentations = 0;

    while (getCurrent() == TokenType::TOKEN_INDENTATION) {
      count_indentations += 1;
      advance();
    }

    if (peek() == TokenType::TOKEN_NEW_LINE ||
        peek() == TokenType::TOKEN_COMMENT)
      continue;

    if (count_indentations < indentation_level)
      break;

    instructions.push_back(handleInstruction());
  }

  indentation_level -= 1;
  return std::make_unique<BlockNode>(std::move(instructions));
}

std::unique_ptr<FunctionDefinitionStatementNode>
Parser::handleFunctionDefinitionStatement() {
  Token name = getCurrent();
  std::unique_ptr<FunctionDefinitionStatementNode> return_value;

  check(advance(), TokenType::TOKEN_LEFT_PARENTHESIS, "(");
  check(advance(), TokenType::TOKEN_RIGHT_PARENTHESIS, ")");
  check(advance(), TokenType::TOKEN_COLON, ":");
  consumeNewLine();

  scope_level.push_back(name.getValue());

  return_value = std::make_unique<FunctionDefinitionStatementNode>(
      name, std::move(handleBlock()));

  scope_level.pop_back();

  return return_value;
}

std::unique_ptr<InstructionNode> Parser::handleInstruction() {
  return std::move(handleStatement());
}

std::unique_ptr<LineStatementNode> Parser::handleLineStatement() {
  check(advance(), TokenType::TOKEN_LEFT_PARENTHESIS, "(");

  Token lines = advance();

  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS) {
    check(advance(), TokenType::TOKEN_NEW_LINE, "new line");
    advance();
    return std::make_unique<LineStatementNode>();
  }

  check(lines, TokenType::TOKEN_INTEGER, "integer number or )", lines);
  check(advance(), TokenType::TOKEN_RIGHT_PARENTHESIS, ")");
  consumeNewLine();

  return std::make_unique<LineStatementNode>(lines);
}

std::unique_ptr<PrintStatementNode> Parser::handlePrintStatement() {
  check(advance(), TokenType::TOKEN_LEFT_PARENTHESIS, "(");

  Token message = advance();

  check(message, TokenType::TOKEN_STRING, "\"", message);
  check(advance(), TokenType::TOKEN_RIGHT_PARENTHESIS, ")");
  consumeNewLine();

  return std::make_unique<PrintStatementNode>(message);
}

std::unique_ptr<ProgramNode> Parser::handleProgram() {
  std::unique_ptr<ProgramDeclarationNode> declaration;
  std::vector<std::unique_ptr<StatementNode>> statements;

  while (!atEnd() && (getCurrent() == TokenType::TOKEN_COMMENT ||
                      getCurrent() == TokenType::TOKEN_NEW_LINE ||
                      getCurrent() == TokenType::TOKEN_INDENTATION))
    advance();

  if (atEnd())
    unexpected_token("program declaration");

  check(getCurrent(), TokenType::TOKEN_PROGRAM_TYPE, "program declaration");

  declaration = handleProgramDeclaration();

  while (!atEnd()) {
    if (getCurrent() == TokenType::TOKEN_COMMENT ||
        getCurrent() == TokenType::TOKEN_NEW_LINE) {
      advance();
      continue;
    }
    statements.push_back(std::move(handleStatement()));
  }

  return std::make_unique<ProgramNode>(std::move(declaration),
                                       std::move(statements));
}

std::unique_ptr<ProgramDeclarationNode> Parser::handleProgramDeclaration() {
  Token programType = advance();

  check(programType, TokenType::TOKEN_REPORT, "report", programType);
  check(advance(), TokenType::TOKEN_NAME, "name");

  Token name = advance();

  check(name, TokenType::TOKEN_STRING, "string");

  if (advance() != TokenType::TOKEN_NEW_LINE &&
      getCurrent() != TokenType::TOKEN_EOF)
    unexpected_token("new line");

  return std::make_unique<ProgramDeclarationNode>(programType, name);
}

std::unique_ptr<SkipStatementNode> Parser::handleSkipStatement() {
  check(advance(), TokenType::TOKEN_LEFT_PARENTHESIS, "(");

  Token lines = advance();

  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS) {
    check(advance(), TokenType::TOKEN_NEW_LINE, "new line");

    advance();

    return std::make_unique<SkipStatementNode>();
  }

  check(lines, TokenType::TOKEN_INTEGER, "integer number or )", lines);
  check(advance(), TokenType::TOKEN_LEFT_PARENTHESIS, ")");
  consumeNewLine();

  return std::make_unique<SkipStatementNode>(lines);
}

std::unique_ptr<StatementNode> Parser::handleStatement() {
  std::unique_ptr<StatementNode> statement = nullptr;

  Token next = getCurrent();
  if (next.getType() == TokenType::TOKEN_IDENTIFIER &&
      types.contains(next.getValue()))
    return std::move(handleVariableDeclarationStatement());
  switch (next.getType()) {
  case TokenType::TOKEN_IDENTIFIER:
    if (peek() == TokenType::TOKEN_ASSIGN)
      statement = std::move(handleAssignmentStatement());
    else
      statement = std::move(handleFunctionDefinitionStatement());
    break;
  case TokenType::TOKEN_ULINE:
    statement = std::move(handleLineStatement());
    break;
  case TokenType::TOKEN_PRINT:
    statement = std::move(handlePrintStatement());
    break;
  case TokenType::TOKEN_SKIP:
    statement = std::move(handleSkipStatement());
    break;
  default:
    unexpected_token("statement", next);
  }

  return statement;
}

std::unique_ptr<VariableDeclarationStatementNode>
Parser::handleVariableDeclarationStatement() {
  Token type = getCurrent();
  Token name = advance();

  check(name, TokenType::TOKEN_IDENTIFIER, "identifier");

  consumeNewLine();

  std::string current_scope = scope_level.at(scope_level.size() - 1);

  if (!variables.contains(current_scope))
  variables.at(current_scope) = std::vector<variable_info>();
  variables[current_scope].push_back({name.getValue(), type.getValue()});

  return std::make_unique<VariableDeclarationStatementNode>(
      type, types.at(type.getValue()), name);
}

Token Parser::peek() {
  if (current >= tokens.size() - 1)
    logError("EOF");

  return tokens.at(current + 1);
}

void Parser::unexpected_token(std::string expected) {
  unexpected_token(expected, getCurrent());
}

void Parser::unexpected_token(std::string expected, ABRUHP::Token tk) {
  logError(std::format("Unexpected token, expected: {}", expected),
           tk.getLine());
}

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  program = std::move(handleProgram());
}

std::unique_ptr<ProgramNode> Parser::parse() { return std::move(program); }
} // namespace ABRUHP