#include "parser.hpp"

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

std::unique_ptr<FunctionDefinitionStatementNode> Parser::handleFunctionDefinitionStatement() {
  return nullptr;
}

std::unique_ptr<InstructionNode> Parser::handleInstruction() {
  return nullptr;
}

std::unique_ptr<LineStatementNode> Parser::handleLineStatement() {
  return nullptr;
}

std::unique_ptr<PrintStatementNode> Parser::handlePrintStatement() {
  return nullptr;
}

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

std::unique_ptr<SkipStatementNode> Parser::handleSkipStatement() {
  if (advance() != TokenType::TOKEN_LEFT_PARENTHESIS)
  logError("Unexpected token, expected: (", getCurrent().getLine());
  Token next = advance();
  if (next == TokenType::TOKEN_RIGHT_PARENTHESIS) return std::make_unique<SkipStatementNode>();
  if (next != TokenType::TOKEN_INTEGER)
  logError("Unexpected token, integer number or ) expected", next.getLine());
  return std::make_unique<SkipStatementNode>(next);
}

std::unique_ptr<StatementNode> Parser::handleStatement() { return nullptr; }

Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
  program = std::move(handleProgram());
}

std::unique_ptr<ProgramNode> Parser::parse() { return std::move(program); }
} // namespace ABRUHP