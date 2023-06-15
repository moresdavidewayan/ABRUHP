#include "parser.hpp"

#include <format>

namespace ABRUHP {
Token Parser::advance() {
  current += 1;
  return getCurrent();
}

bool Parser::atEnd() { return current >= tokens.size() - 1; }

Token Parser::getCurrent() { return tokens.at(current); }

Token Parser::peek() {
  if (current >= tokens.size() - 1)
    logError("EOF");

  return tokens.at(current + 1);
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

  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(");

  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")");

  if (advance() != TokenType::TOKEN_COLON)
    unexpected_token(":");

  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");
  advance();

  return std::make_unique<FunctionDefinitionStatementNode>(
      name, std::move(handleBlock()));
}

std::unique_ptr<InstructionNode> Parser::handleInstruction() {
  return std::move(handleStatement());
}

std::unique_ptr<LineStatementNode> Parser::handleLineStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(");

  Token lines = advance();

  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS) {
    if (advance() != TokenType::TOKEN_NEW_LINE)
      unexpected_token("new line");

    advance();
    return std::make_unique<LineStatementNode>();
  }

  if (lines != TokenType::TOKEN_INTEGER)
    unexpected_token("integer number or )", lines);

  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")");

  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");

  advance();

  return std::make_unique<LineStatementNode>(lines);
}

std::unique_ptr<PrintStatementNode> Parser::handlePrintStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(");

  Token message = advance();

  if (message != TokenType::TOKEN_STRING)
    unexpected_token("\"", message);

  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")");

  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");

  advance();

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

  if (getCurrent() != TokenType::TOKEN_PROGRAM_TYPE)
    unexpected_token("program declaration");

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

  if (programType != TokenType::TOKEN_REPORT)
    unexpected_token("report", programType);

  if (advance() != TokenType::TOKEN_NAME)
    unexpected_token("name");

  Token name = advance();

  if (name != TokenType::TOKEN_STRING)
    unexpected_token("string");

  if (advance() != TokenType::TOKEN_NEW_LINE &&
      getCurrent() != TokenType::TOKEN_EOF)
    unexpected_token("new line");

  return std::make_unique<ProgramDeclarationNode>(programType, name);
}

std::unique_ptr<SkipStatementNode> Parser::handleSkipStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(");

  Token lines = advance();

  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS) {
    if (advance() != TokenType::TOKEN_NEW_LINE)
      unexpected_token("new line");

    advance();

    return std::make_unique<SkipStatementNode>();
  }

  if (lines != TokenType::TOKEN_INTEGER)
    unexpected_token("integer number or )", lines);

  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")");

  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");

  advance();

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

  if (name != TokenType::TOKEN_IDENTIFIER)
    unexpected_token("identifier");

  if (advance() != TokenType::TOKEN_NEW_LINE)
    unexpected_token("new line");

  advance();

  return std::make_unique<VariableDeclarationStatementNode>(type, types.at(type.getValue()), name);
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