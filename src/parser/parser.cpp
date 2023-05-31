#include "parser.hpp"

namespace ABRUHP {
Token Parser::advance() {
  current += 1;
  return getCurrent();
}

bool Parser::atEnd() { return current >= tokens.size(); }

Token Parser::getCurrent() { return tokens.at(current); }

std::unique_ptr<ProgramNode> Parser::handleProgram() {
  std::unique_ptr<ProgramDeclarationNode> declaration;

  while (!atEnd() && (getCurrent() == TokenType::TOKEN_COMMENT ||
                      getCurrent() == TokenType::TOKEN_NEW_LINE ||
                      getCurrent() == TokenType::TOKEN_INDENTATION))
    advance();
  if (atEnd())
    logError("Unexpected EOF, expected: program declaration",
             getCurrent().getLine());
  if (getCurrent() != TokenType::TOKEN_PROGRAM_TYPE)
    logError("Unexpected token, expected: program declaration",
             getCurrent().getLine());
  declaration = handleProgramDeclaration();

  return std::make_unique<ProgramNode>(std::move(declaration));
}

std::unique_ptr<ProgramDeclarationNode> Parser::handleProgramDeclaration() {
  Token programType = advance();
  if (programType != TokenType::TOKEN_REPORT)
    logError("Unexpected token, expected: report", programType.getLine());
  if (advance() != TokenType::TOKEN_NAME)
    logError("Unexpected token, expected: name", getCurrent().getLine());
  if (advance() != TokenType::TOKEN_STRING)
    logError("Unexpected token, expected: string", getCurrent().getLine());
  return std::make_unique<ProgramDeclarationNode>(programType, getCurrent());
}

std::unique_ptr<StatementNode> Parser::handleStatement() { return nullptr; }

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  program = std::move(handleProgram());
}

std::unique_ptr<ProgramNode> Parser::parse() { return std::move(program); }
} // namespace ABRUHP