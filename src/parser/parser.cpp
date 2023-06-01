#include "parser.hpp"

#include <format>

void unexpected_token(std::string expected, ABRUHP::Token tk) {
  logError(std::format("Unexpected token, expected: {}", expected),
           tk.getLine());
}

namespace ABRUHP {
Token Parser::advance() {
  current += 1;
  return getCurrent();
}

bool Parser::atEnd() { return current >= tokens.size(); }

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
    while (advance() == TokenType::TOKEN_INDENTATION)
      count_indentations += 1;
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
  return nullptr;
}

std::unique_ptr<InstructionNode> Parser::handleInstruction() { return nullptr; }

std::unique_ptr<LineStatementNode> Parser::handleLineStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(", getCurrent());
  Token lines = advance();
  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS)
    return std::make_unique<LineStatementNode>();
  if (lines != TokenType::TOKEN_INTEGER)
    unexpected_token("integer number or )", lines);
  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")", getCurrent());
  return std::make_unique<LineStatementNode>(lines);
}

std::unique_ptr<PrintStatementNode> Parser::handlePrintStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(", getCurrent());
  Token message = advance();
  if (message != TokenType::TOKEN_STRING)
    unexpected_token("\"", message);
  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")", getCurrent());
  return std::make_unique<PrintStatementNode>(message);
}

std::unique_ptr<ProgramNode> Parser::handleProgram() {
  std::unique_ptr<ProgramDeclarationNode> declaration;

  while (!atEnd() && (getCurrent() == TokenType::TOKEN_COMMENT ||
                      getCurrent() == TokenType::TOKEN_NEW_LINE ||
                      getCurrent() == TokenType::TOKEN_INDENTATION))
    advance();
  if (atEnd())
    unexpected_token("program declaration", getCurrent());
  if (getCurrent() != TokenType::TOKEN_PROGRAM_TYPE)
    unexpected_token("program declaration", getCurrent());
  declaration = handleProgramDeclaration();

  return std::make_unique<ProgramNode>(std::move(declaration));
}

std::unique_ptr<ProgramDeclarationNode> Parser::handleProgramDeclaration() {
  Token programType = advance();
  if (programType != TokenType::TOKEN_REPORT)
    unexpected_token("report", programType);
  if (advance() != TokenType::TOKEN_NAME)
    unexpected_token("name", getCurrent());
  if (advance() != TokenType::TOKEN_STRING)
    unexpected_token("string", getCurrent());
  return std::make_unique<ProgramDeclarationNode>(programType, getCurrent());
}

std::unique_ptr<SkipStatementNode> Parser::handleSkipStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
    unexpected_token("(", getCurrent());
  Token lines = advance();
  if (lines == TokenType::TOKEN_RIGHT_PARENTHESIS)
    return std::make_unique<SkipStatementNode>();
  if (lines != TokenType::TOKEN_INTEGER)
    unexpected_token("integer number or )", lines);
  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")", getCurrent());
  return std::make_unique<SkipStatementNode>(lines);
}

std::unique_ptr<StatementNode> Parser::handleStatement() { return nullptr; }

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  program = std::move(handleProgram());
}

std::unique_ptr<ProgramNode> Parser::parse() { return std::move(program); }
} // namespace ABRUHP