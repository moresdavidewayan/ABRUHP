#include "parser.hpp"

#include <format>

void unexpected_token(std::string expected, ABRUHP::Token tk) {
  logError(std::format("Unexpected token, expected: {}", expected), tk.getLine());
}

namespace ABRUHP {
Token Parser::advance() {
  current += 1;
  return getCurrent();
}

bool Parser::atEnd() { return current >= tokens.size(); }

Token Parser::getCurrent() { return tokens.at(current); }

std::unique_ptr<BlockNode> Parser::handleBlock() {
  indentation_level += 1;

  indentation_level -= 1;
  return nullptr;
}

std::unique_ptr<FunctionDefinitionStatementNode>
Parser::handleFunctionDefinitionStatement() {
  return nullptr;
}

std::unique_ptr<InstructionNode> Parser::handleInstruction() { return nullptr; }

std::unique_ptr<LineStatementNode> Parser::handleLineStatement() {
  return nullptr;
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
  Token next = advance();
  if (next == TokenType::TOKEN_RIGHT_PARENTHESIS)
    return std::make_unique<SkipStatementNode>();
  if (next != TokenType::TOKEN_INTEGER)
    unexpected_token("integer number or )", next);
  if (advance() != TokenType::TOKEN_RIGHT_PARENTHESIS)
    unexpected_token(")", getCurrent());
  return std::make_unique<SkipStatementNode>(next);
}

std::unique_ptr<StatementNode> Parser::handleStatement() { return nullptr; }

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  program = std::move(handleProgram());
}

std::unique_ptr<ProgramNode> Parser::parse() { return std::move(program); }
} // namespace ABRUHP