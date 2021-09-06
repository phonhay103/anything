/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  assert("Parsing a Program ....");
  eat(KW_PROGRAM);
  eat(TK_IDENT);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  assert("Program parsed!");
}

void compileBlock(void) {
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    compileConstDecl();
    compileConstDecls();
    compileBlock2();
  } 
  else compileBlock2();
  assert("Block parsed!");
}

void compileBlock2(void) {
  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    compileTypeDecl();
    compileTypeDecls();
    compileBlock3();
  } 
  else compileBlock3();
}

void compileBlock3(void) {
  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    compileVarDecl();
    compileVarDecls();
    compileBlock4();
  } 
  else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileConstDecls(void) {
  // FIRST(ConstDecls) = {TK_IDENT, ε}
  // FOLLOW(ConstDecls) = {KW_TYPE, KW_VAR, KW_FUNCTION, KW_PROCEDURE, ε, $}
  if(lookAhead->tokenType == TK_IDENT) {
    compileConstDecl();
    compileConstDecls();
  }
}

void compileConstDecl(void) {
  // FIRST(ConstDecl) = {TK_IDENT}
  if (lookAhead->tokenType == TK_IDENT) {
    eat(TK_IDENT);
    eat(SB_EQ);
    compileConstant();
    eat(SB_SEMICOLON);
  }
  // Error occurs
  else {
    error(ERR_INVALIDCONSTDECL, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileTypeDecls(void) {
  // FIRST(TypeDecls) = {TK_IDENT, ε}
  // FOLLOW(TypeDecls) = {KW_VAR, KW_FUNCTION, KW_PROCEDURE, ε, $}
  if(lookAhead->tokenType == TK_IDENT) {
    compileTypeDecl();
    compileTypeDecls();
  }
}

void compileTypeDecl(void) {
  // FIRST(TypeDecl) = {TK_IDENT}
  if (lookAhead->tokenType == TK_IDENT) {
    eat(TK_IDENT);
    eat(SB_EQ);
    compileType();
    eat(SB_SEMICOLON);
  }
  // Error occurs
  else {
    error(ERR_INVALIDTYPEDECL, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileVarDecls(void) {
  // FIRST(VarDecls) = {TK_IDENT, ε}
  // FOLLOW(VarDecls) = {KW_FUNCTION, KW_PROCEDURE, ε, $}
  if(lookAhead->tokenType == TK_IDENT) {
    compileVarDecl();
    compileVarDecls();
  }
}

void compileVarDecl(void) {
  // FIRST(VarDecl) = {TK_IDENT}
  if (lookAhead->tokenType == TK_IDENT) {
    eat(TK_IDENT);
    eat(SB_COLON);
    compileType();
    eat(SB_SEMICOLON);
  }
  // Error occurs
  else {
    error(ERR_INVALIDVARDECL, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileSubDecls(void) {
  assert("Parsing subtoutines ....");
  switch (lookAhead->tokenType) {
  // FIRST(SubDecls) = {KW_FUNTION, KW_PROCEDURE, ε}
  case KW_FUNCTION:
    compileFuncDecl();
    compileSubDecls();
    break;
  case KW_PROCEDURE:
    compileProcDecl();
    compileSubDecls();
    break;
  // FOLLOW(SubDecls) = {KW_BEGIN, $}
  case KW_BEGIN:
    break;
  // Error occurs
  default:
    error(ERR_INVALIDSUBDECL, lookAhead->lineNo, lookAhead->colNo);
  }
  assert("Subtoutines parsed ....");
}

void compileFuncDecl(void) {
  assert("Parsing a function ....");
  // FIRST(FuncDecl) = {KW_FUNCTION}
  eat(KW_FUNCTION);
  eat(TK_IDENT);
  compileParams();
  eat(SB_COLON);
  compileBasicType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Function parsed ....");
}

void compileProcDecl(void) {
  assert("Parsing a procedure ....");
  // FIRST(ProcDecl) = {KW_PROCEDURE}
  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  assert("Procedure parsed ....");
}

void compileUnsignedConstant(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(UnsignedConstant) = {TK_NUMBER, TK_IDENT, TK_CHAR, TK_FLOAT}
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_FLOAT: // !(3)
    eat(TK_FLOAT);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  // Error occurs
  default:
    error(ERR_INVALIDCHARCONSTANT, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileConstant(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(Constant) = {SB_PLUS, SB_MINUX, TK_CHAR, TK_NUMBER, TK_IDENT, TK_FLOAT}
  case SB_PLUS:
    eat(SB_PLUS);
    compileConstant2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileConstant2();
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  case TK_NUMBER:
  case TK_FLOAT: // !(3)
  case TK_IDENT:
    compileConstant2();
    break;
  // Error occurs
  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileConstant2(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(Constant2) = {TK_IDENT, TK_NUMBER, TK_FLOAT}
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_FLOAT: // !(3)
    eat(TK_FLOAT);
    break;
  // Error occurs
  default:
    error(ERR_INVALIDCONSTANT, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileType(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(Type) = {KW_INTEGER, KW_CHAR, TK_IDENT, KW_ARRAY, KW_FLOAT}
  case KW_INTEGER:
    eat(KW_INTEGER);
    break;
  case KW_CHAR:
    eat(KW_CHAR);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    break;
  case KW_FLOAT: // !(3)
    eat(KW_FLOAT);
    break;
  case KW_ARRAY:
    eat(KW_ARRAY);
    eat(SB_OPEN_BRACKET); // !(3)
    eat(TK_NUMBER);
    eat(SB_CLOSE_BRACKET); // !(3)
    eat(KW_OF);
    compileType();
    break;
  // Error occurs
  default:
    error(ERR_INVALIDTYPE, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileBasicType(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(BasicType) = {KW_INTEGER, KW_CHAR, KW_FLOAT}
  case KW_INTEGER:
    eat(KW_INTEGER);
    break;
  case KW_CHAR:
    eat(KW_CHAR);
    break;
  case KW_FLOAT: // !(3)
    eat(KW_FLOAT);
    break;
  // Error occurs
  default:
    error(ERR_INVALIDBASICTYPE, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileParams(void) {
  switch (lookAhead->tokenType)
  {
  // FIRST(Params) = {SB_LPAR, ε}
  case SB_LPAR: // (a:INTEGER; b:CHAR)
    eat(SB_LPAR);
    compileParam();
    compileParams2();
    eat(SB_RPAR);
    break;
  // FOLLOW(params) = {SB_COLON, SB_SEMICOLON, $}
  case SB_COLON:
  case SB_SEMICOLON:
    break;
  // Error occurs
  default:
    error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileParams2(void) {
  switch (lookAhead->tokenType) {
    // FIRST(Params2) = {SB_SEMICOLON, ε}
    case SB_SEMICOLON:
      eat(SB_SEMICOLON);
      compileParam();
      compileParams2();
      break;
    // FOLLOW(Params2) = {SB_RPAR, $}
    case SB_RPAR:
      break;
    // Error occurs
    default:
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileParam(void) {
  // FIRST(Param) = {TK_IDENT, KW_VAR}
  switch (lookAhead->tokenType) {
  case KW_VAR:
    eat(KW_VAR);
  case TK_IDENT:
    eat(TK_IDENT);
    eat(SB_COLON);
    compileBasicType();
    break;
  // Error occurs
    default:
      error(ERR_INVALIDPARAM, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileStatements(void) {
  compileStatement();
  compileStatements2();
}

void compileStatements2(void) {
  switch (lookAhead->tokenType) {
  // FIRST(Statements2) = {SB_SEMICOLON, ε}
  case SB_SEMICOLON:
    eat(SB_SEMICOLON);
    compileStatement();
    compileStatements2();
    break;
  // FOLLOW(Statements2) = {KW_END, $}
  case KW_END:
    break;
  // Error occurs
  default:
    // error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
    eat(SB_SEMICOLON);
  }
}

void compileStatement(void) {
  switch (lookAhead->tokenType) {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALIDSTATEMENT, lookAhead->lineNo, lookAhead->colNo);
  }
}


// TODO: Add assign_plus, assign_subtract, assign_times, assign_divide to AssignSt
void compileAssignSt(void) { // !(3)
  assert("Parsing an assign statement ....");
  // AssignSb ::= SB_ASSIGN|SB_ASSIGN_PLUS|SB_ASSIGN_SUBTRACT|SB_ASSIGN_TIMES|SB_ASSIGN_DIVIDE
  // AssignSt ::= Variable AssignSb Expession
  // AssignSt ::= FunctionIdent AssignSb Expression
  // Variable ::= VariableIdent Indexes
  // Indexes ::= SB_OPEN_BRACKET Expression SB_CLOSE_BRACKET Indexes|ε

  // FIRST(AssignSt) = {TK_IDENT}
  eat(TK_IDENT);
  if(lookAhead->tokenType == SB_OPEN_BRACKET) {
    compileIndexes();
  }
  switch(lookAhead->tokenType) {
    case SB_ASSIGN:
      eat(SB_ASSIGN);
      break;
    case SB_ASSIGN_PLUS:
      eat(SB_ASSIGN_PLUS);
      break;
    case SB_ASSIGN_SUBTRACT:
      eat(SB_ASSIGN_SUBTRACT);
      break;
    case SB_ASSIGN_TIMES:
      eat(SB_ASSIGN_TIMES);
      break;
    case SB_ASSIGN_DIVIDE:
      eat(SB_ASSIGN_DIVIDE);
      break;
    // Error occurs
    default:
      error(ERR_INVALIDASSIGNST, lookAhead->lineNo, lookAhead->colNo);
  }
  compileExpression();
  assert("Assign statement parsed ....");
}

void compileCallSt(void) {
  assert("Parsing a call statement ....");
  // FIRST(CallSt) = {KW_CALl}
  eat(KW_CALL);
  eat(TK_IDENT);
  compileArguments();
  assert("Call statement parsed ....");
}

void compileGroupSt(void) {
  assert("Parsing a group statement ....");
  // FIRST(GroupSt) = {KW_BEGIN}
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
  assert("Group statement parsed ....");
}

void compileIfSt(void) {
  assert("Parsing an if statement ....");
  // FIRST(IfSt) = {KW_IF}
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE)
    compileElseSt();
  assert("If statement parsed ....");
}

void compileElseSt(void) {
  // FIRST(ElseSt) = {KW_ELSE}
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  assert("Parsing a while statement ....");
  // FIRST(WhileSt) = {KW_WHILE}
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
  assert("While statement pased ....");
}

void compileForSt(void) { 
  assert("Parsing a for statement ....");
  // FIRST(ForSt) = {KW_FOR}
  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatement();
  assert("For statement parsed ....");
}

void compileArguments(void) { // !(3)
  switch (lookAhead->tokenType) {
    // FIRST(Arguments) = {SB_LPAR, ε}
    case SB_LPAR:
      eat(SB_LPAR);
      compileExpression();
      compileArguments2();
      eat(SB_RPAR);
      break;
    // FOLLOW(Arguments) same as FOLLOW(Term2)
    case SB_PLUS:
    case SB_MINUS:
    case KW_TO:
    case KW_DO:
    case SB_RPAR:
    case SB_CLOSE_BRACKET: // !(3)
    case SB_COMMA:
    case SB_EQ:
    case SB_NEQ:
    case SB_LE:
    case SB_LT:
    case SB_GE:
    case SB_GT:
    case KW_THEN:
    case SB_SEMICOLON:
    case KW_END:
    case KW_ELSE:
      break;
  // Error
    default:
      error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileArguments2(void) {
  // FIRST(Arguments2) = {SB_COMMA, ε}
  switch (lookAhead->tokenType) {
  case SB_COMMA:
    eat(SB_COMMA);
    compileExpression();
    compileArguments2();
    break;
  // FOLLOW(Arguments2) = {SB_RPAR, $}
  case SB_RPAR:
    break;
  // Error
  default:
    error(ERR_INVALIDARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileCondition(void) {
  compileExpression();
  compileCondition2();
}

void compileCondition2(void) {
  switch (lookAhead->tokenType) {
  // FIRST(Condition2) = {SB_EQ, SB_NEQ, SB_LE, SB_LT, SB_GE, SB_GT}
  case SB_EQ:
    eat(SB_EQ);
    compileExpression();
    break;
  case SB_NEQ:
    eat(SB_NEQ);
    compileExpression();
    break;
  case SB_LE:
    eat(SB_LE);
    compileExpression();
    break;
  case SB_LT:
    eat(SB_LT);
    compileExpression();
    break;
  case SB_GE:
    eat(SB_GE);
    compileExpression();
    break;
  case SB_GT:
    eat(SB_GT);
    compileExpression();
    break;
  // Error
  default:
    error(ERR_INVALIDCOMPARATOR, lookAhead->lineNo, lookAhead->colNo);
  }
}

// !(4)
void compileExpression(void) {
  assert("Parsing an expression");
  // FIRST(Expression) = {SB_PLUS, SB_MINUS}
  switch (lookAhead->tokenType) {
  case SB_PLUS:
    eat(SB_PLUS);
    compileExpression2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileExpression2();
    break;
  default:
    compileExpression2();
    break;
  }
  assert("Expression parsed");
}

void compileExpression2(void) {
  compileTerm();
  compileExpression3();
}

void compileExpression3(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(Expression3) = {SB_PLUS, SB_MINUS, ε}
  case SB_PLUS:
    eat(SB_PLUS);
    compileTerm();
    compileExpression3();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileTerm();
    compileExpression3();
    break;
  // FOLLOW(Expression)
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_CLOSE_BRACKET: // !(3)
  // FIRST(Arguments2)
  case SB_COMMA:
  // FIRST(Condition2)
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  // FOLLOW(Condition)
  case KW_THEN:
  // FOLLOW(Statement)
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
  // Error occurs
  default:
    error(ERR_INVALIDEXPRESSION, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileTerm(void) {
  compileFactor();
  compileTerm2();
}

void compileTerm2(void) { // !(3) !(4)
  switch (lookAhead->tokenType) {
  // FIRST(Term2) = {SB_TIMES, SB_SLASH, SB_MODULUS, ε}
  case SB_TIMES:
    eat(SB_TIMES);
    compileFactor();
    compileTerm2();
    break;
  case SB_SLASH:
    eat(SB_SLASH);
    compileFactor();
    compileTerm2();
    break;
  case SB_MODULUS: // !(4)
    eat(SB_MODULUS);
    compileFactor();
    compileTerm2();
    break;
  // FIRST(Expression3)
  case SB_PLUS:
  case SB_MINUS:
  // FOLLOW(Expression)
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_CLOSE_BRACKET: // !(3)
  // FIRST(Arguments2)
  case SB_COMMA:
  // FIRST(Condition2)
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  // FOLLOW(Condition)
  case KW_THEN:
  // FOLLOW(Statement)
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
  // Error
  default:
    error(ERR_INVALIDTERM, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileFactor(void) { // !(3)
  switch (lookAhead->tokenType) {
  // FIRST(Factor) = {TK_NUMBER, TK_IDENT, TK_CHAR, SB_LPAR, TK_FLOAT}
  case TK_NUMBER:
  case TK_FLOAT: // !(3)
  case TK_CHAR:
    compileUnsignedConstant();
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    switch (lookAhead->tokenType) {
    // FIRST(Indexes) = {SB_OPEN_BRACKET}
    case SB_OPEN_BRACKET: // !(3)
      compileIndexes();
      break;
    // FIRST(Arguments) = {SB_LPAR, ε}
    case SB_LPAR:
      compileArguments();
      break;
    default:
      break;
    }
    break;
  case SB_LPAR:
    eat(SB_LPAR);
    compileExpression();
    eat(SB_RPAR);
    break;
  // Error
  default:
    error(ERR_INVALIDFACTOR, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileIndexes(void) { // !(3)
  // FIRST(Indexes) = {SB_OPEN_BRACKET, ε}
  if (lookAhead->tokenType == SB_OPEN_BRACKET) {
    eat(SB_OPEN_BRACKET);
    compileExpression();
    eat(SB_CLOSE_BRACKET);
    compileIndexes();
  }
  // FOLLOW(Indexes) = {$}
  // Error
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;
}