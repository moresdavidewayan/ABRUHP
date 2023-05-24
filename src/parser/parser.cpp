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
    logError("Unexpected EOF, expected: program declaration");
  if (getCurrent() == TokenType::TOKEN_PROGRAM_TYPE)
    declaration = handleProgramDeclaration();
  else
    logError("Unexpected token, expected: program declaration");

  return std::make_unique<ProgramNode>(handleProgramDeclaration());
}

std::unique_ptr<ProgramDeclarationNode> Parser::handleProgramDeclaration() {
  if (advance() != TokenType::TOKEN_REPORT)
    logError("Unexpected token, expected: report");
  if (advance() != TokenType::TOKEN_NAME)
    logError("Unexpected token, expected: name");
  if (advance() != TokenType::TOKEN_STRING)
    logError("Unexpected token, expected: string");
  return std::make_unique<ProgramDeclarationNode>(TokenType::TOKEN_REPORT,
                                                  getCurrent().getValue());
}

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {}

std::unique_ptr<ProgramNode> Parser::parse() {
  return std::move(handleProgram());
}
} // namespace ABRUHP