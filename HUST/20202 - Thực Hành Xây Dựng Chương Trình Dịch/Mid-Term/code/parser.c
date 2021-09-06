/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "semantics.h"
#include "error.h"
#include "debug.h"

Token *currentToken;
Token *lookAhead;

extern Type* intType;
extern Type* charType;
extern Type* doubleType; // Not use
extern Type* stringType; // Not use
extern SymTab* symtab;

void scan(void) {
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) {
  if (lookAhead->tokenType == tokenType)
    scan();
  else 
    missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

void compileProgram(void) {
  Object* program;

  eat(KW_PROGRAM);
  eat(TK_IDENT);
  program = createProgramObject(currentToken->string);
  enterBlock(program->progAttrs->scope);
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_PERIOD);
  exitBlock();
}

void compileBlock(void) {
  Object* constObj;

  if (lookAhead->tokenType == KW_CONST) {
    eat(KW_CONST);
    do {
      eat(TK_IDENT);
      checkFreshIdent(currentToken->string);
      constObj = createConstantObject(currentToken->string);
      eat(SB_EQ);
      constObj->constAttrs->value = compileConstant();
      declareObject(constObj);
      eat(SB_SEMICOLON);
    } while (lookAhead->tokenType == TK_IDENT);
    compileBlock2();
  }
  else compileBlock2();
}

void compileBlock2(void) {
  Object* typeObj;

  if (lookAhead->tokenType == KW_TYPE) {
    eat(KW_TYPE);
    do {
      eat(TK_IDENT);
      checkFreshIdent(currentToken->string);
      typeObj = createTypeObject(currentToken->string);
      eat(SB_EQ);
      typeObj->typeAttrs->actualType = compileType();
      declareObject(typeObj);
      eat(SB_SEMICOLON);
    } while (lookAhead->tokenType == TK_IDENT);
    compileBlock3();
  } 
  else compileBlock3();
}

void compileBlock3(void) {
  Object* varObj;

  if (lookAhead->tokenType == KW_VAR) {
    eat(KW_VAR);
    do {
      eat(TK_IDENT);
      checkFreshIdent(currentToken->string);
      varObj = createVariableObject(currentToken->string);
      eat(SB_COLON);
      varObj->varAttrs->type = compileType();
      declareObject(varObj);
      eat(SB_SEMICOLON);
    } while (lookAhead->tokenType == TK_IDENT);
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

void compileSubDecls(void) {
  while ((lookAhead->tokenType == KW_FUNCTION) || (lookAhead->tokenType == KW_PROCEDURE)) {
    if (lookAhead->tokenType == KW_FUNCTION)
      compileFuncDecl();
    else compileProcDecl();
  }
}

void compileFuncDecl(void) {
  Object* funcObj;

  eat(KW_FUNCTION);
  eat(TK_IDENT);
  checkFreshIdent(currentToken->string);
  funcObj = createFunctionObject(currentToken->string);
  declareObject(funcObj);

  enterBlock(funcObj->funcAttrs->scope);
  compileParams();
  eat(SB_COLON);
  funcObj->funcAttrs->returnType = compileBasicType();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  exitBlock();
}

void compileProcDecl(void) {
  Object* procObj;

  eat(KW_PROCEDURE);
  eat(TK_IDENT);
  checkFreshIdent(currentToken->string);
  procObj = createProcedureObject(currentToken->string);
  declareObject(procObj);

  enterBlock(procObj->procAttrs->scope);
  compileParams();
  eat(SB_SEMICOLON);
  compileBlock();
  eat(SB_SEMICOLON);
  exitBlock();
}

ConstantValue* compileUnsignedConstant(void) {
  ConstantValue* constValue;
  Object* obj;

  switch (lookAhead->tokenType) {
  case TK_NUMBER:
    eat(TK_NUMBER);
    constValue = makeIntConstant(currentToken->value);
    break;
  case TK_DOUBLE: //
    eat(TK_DOUBLE);
    constValue = makeDoubleConstant(currentToken->d_value);
    break;
  case TK_STRING: //
    eat(TK_STRING);
    constValue = makeStringConstant(currentToken->string);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    obj = checkDeclaredConstant(currentToken->string);
    constValue = duplicateConstantValue(obj->constAttrs->value);
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    constValue = makeCharConstant(currentToken->string[0]);
    break;
  default:
    error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
  return constValue;
}

ConstantValue* compileConstant(void) {
  ConstantValue* constValue;

  switch (lookAhead->tokenType) {
  case SB_PLUS:
    eat(SB_PLUS);
    constValue = compileConstant2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    constValue = compileConstant2();
    if (constValue->type == TP_INT)
      constValue->intValue = - constValue->intValue;
    else if (constValue->type == TP_DOUBLE)
      constValue->doubleValue = - constValue->doubleValue;
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    constValue = makeCharConstant(currentToken->string[0]);
    break;
  case TK_STRING: //
    eat(TK_STRING);
    constValue = makeStringConstant(currentToken->string);
    break;
  default:
    constValue = compileConstant2();
    break;
  }
  return constValue;
}

ConstantValue* compileConstant2(void) {
  ConstantValue* constValue;
  Object* obj;

  switch (lookAhead->tokenType) {
  case TK_NUMBER:
    eat(TK_NUMBER);
    constValue = makeIntConstant(currentToken->value);
    break;
  case TK_DOUBLE: //
    eat(TK_DOUBLE);
    constValue = makeDoubleConstant(currentToken->d_value);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    obj = checkDeclaredConstant(currentToken->string);
    if (obj->constAttrs->value->type == TP_INT || obj->constAttrs->value->type == TP_DOUBLE)
      constValue = duplicateConstantValue(obj->constAttrs->value);
    else
      error(ERR_UNDECLARED_INT_CONSTANT, currentToken->lineNo, currentToken->colNo);
    break;
  default:
    error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
  return constValue;
}

Type* compileType(void) {
  Type* type;
  Type* elementType;
  int arraySize;
  Object* obj;

  switch (lookAhead->tokenType) {
  case KW_INTEGER:
    eat(KW_INTEGER);
    type =  makeIntType();
    break;
  case KW_DOUBLE: //
    eat(KW_DOUBLE); 
    type = makeDoubleType();
    break;
  case KW_STRING: //
    eat(KW_STRING);
    type = makeStringType();
    break;
  case KW_CHAR:
    eat(KW_CHAR);
    type = makeCharType();
    break;
  case KW_ARRAY:
    eat(KW_ARRAY);
    eat(SB_OPEN_BRACKET);
    eat(TK_NUMBER);
    arraySize = currentToken->value;
    eat(SB_CLOSE_BRACKET);
    eat(KW_OF);
    elementType = compileType();
    type = makeArrayType(arraySize, elementType);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    obj = checkDeclaredType(currentToken->string);
    type = duplicateType(obj->typeAttrs->actualType);
    break;
  default:
    error(ERR_INVALID_TYPE, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
  return type;
}

Type* compileBasicType(void) {
  Type* type;

  switch (lookAhead->tokenType) {
  case KW_INTEGER: 
    eat(KW_INTEGER); 
    type = makeIntType();
    break;
  case KW_DOUBLE: //
    eat(KW_DOUBLE);
    type = makeDoubleType(); 
    break;
  case KW_STRING: //
    eat(KW_STRING);
    type = makeStringType();
    break;
  case KW_CHAR: 
    eat(KW_CHAR); 
    type = makeCharType();
    break;
  default:
    error(ERR_INVALID_BASICTYPE, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
  return type;
}

void compileParams(void) {
  if (lookAhead->tokenType == SB_LPAR) {
    eat(SB_LPAR);
    compileParam();
    while (lookAhead->tokenType == SB_SEMICOLON) {
      eat(SB_SEMICOLON);
      compileParam();
    }
    eat(SB_RPAR);
  }
}

void compileParam(void) {
  Object* param;
  Type* type;
  enum ParamKind paramKind;

  switch (lookAhead->tokenType) {
  case TK_IDENT:
    paramKind = PARAM_VALUE;
    break;
  case KW_VAR:
    eat(KW_VAR);
    paramKind = PARAM_REFERENCE;
    break;
  default:
    error(ERR_INVALID_PARAMETER, lookAhead->lineNo, lookAhead->colNo);
    break;
  }

  eat(TK_IDENT);
  checkFreshIdent(currentToken->string);
  param = createParameterObject(currentToken->string, paramKind, symtab->currentScope->owner);
  eat(SB_COLON);
  type = compileBasicType();
  param->paramAttrs->type = type;
  declareObject(param);
}

void compileStatements(void) {
  compileStatement();
  while (lookAhead->tokenType == SB_SEMICOLON) {
    eat(SB_SEMICOLON);
    compileStatement();
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
  case KW_DO: // Do While
    compileDoWhileSt();
    break;
    // EmptySt needs to check FOLLOW tokens
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
    // Error occurs
  default:
    error(ERR_INVALID_STATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

Type* compileLValue(void) {
  Object* var;
  Type* varType;

  switch (lookAhead->tokenType) {
    case TK_NUMBER:
    case TK_DOUBLE: //
    case TK_STRING: //
    case TK_CHAR:
      error(ERR_ASSIGN_VALUE_LITERAL, lookAhead->lineNo, lookAhead->colNo);
    case TK_IDENT:
    default:
      eat(TK_IDENT);
      break;
  }

  var = checkDeclaredLValueIdent(currentToken->string);
  if (var->kind == OBJ_VARIABLE) {
    if(var->varAttrs->type->typeClass == TP_ARRAY) {
      varType = compileIndexes(var->varAttrs->type);
    } else {
      varType = var->varAttrs->type;
    }
  }
  else if(var->kind == OBJ_FUNCTION) 
    varType = var->funcAttrs->returnType;
  else if(var->kind == OBJ_PARAMETER)
    varType = var->paramAttrs->type;

  return varType;
}

void compileAssignSt(void) { // Multiple Assign
  Type *L[10], *R[10];
  int m = 0, n = 0;
  
  /* Compile Left */
  L[m++] = compileLValue();
  while(lookAhead->tokenType == SB_COMMA) {
    eat(SB_COMMA);
    L[m++] = compileLValue();
  }

  /* Compile Assign Token */
  if (m == 1) {
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
      default:
        eat(SB_ASSIGN);
        break;
    }
  }
  else
    eat(SB_ASSIGN);
  
  /* Compile Right */
  R[n++] = compileExpression();
  while (lookAhead->tokenType == SB_COMMA) {
    eat(SB_COMMA);
    R[n++] = compileExpression();
  }

  /* Check Assign */
  if (m < n)
    error(ERR_VALUE_UNPACK1, currentToken->lineNo, currentToken->colNo);
  else if (m > n)
    error(ERR_VALUE_UNPACK2, currentToken->lineNo, currentToken->colNo);
  else { // CHECK TYPE CONSISTENCY
    for (int i = 0; i < m; ++i) {
      if ((L[i]->typeClass == TP_INT) && (R[i]->typeClass == TP_DOUBLE)) // Không cho phép ép kiểu từ int -> double
        error(ERR_CONVERT_DOUBLE_INT, currentToken->lineNo, currentToken->colNo);
      else if ((L[i]->typeClass == TP_DOUBLE) && (R[i]->typeClass == TP_INT)) continue; // Cho phép ép kiểu từ double -> int
      else checkTypeEquality(L[i], R[i]);
    }
  }
}

void compileCallSt(void) {
  Object* proc;
  eat(KW_CALL);
  eat(TK_IDENT);
  proc = checkDeclaredProcedure(currentToken->string);
  compileArguments(proc->procAttrs->paramList);
}

void compileGroupSt(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileIfSt(void) {
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE) 
    compileElseSt();
}

void compileElseSt(void) {
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void) {
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
}

void compileDoWhileSt(void) { // Do While
  eat(KW_DO);
  compileStatement();
  eat(KW_WHILE);
  compileCondition();
}

void compileForSt(void) {
  Object *var = NULL;

  eat(KW_FOR);
  eat(TK_IDENT);
  var = checkDeclaredVariable(currentToken->string);
  checkIntType(var->varAttrs->type);
  eat(SB_ASSIGN);
  checkIntType(compileExpression());
  eat(KW_TO);
  checkIntType(compileExpression());
  eat(KW_DO);
  compileStatement();
}

void compileArgument(Object* param) {
  if(param->paramAttrs->kind == PARAM_REFERENCE) {
    if(lookAhead->tokenType == TK_IDENT)
      checkDeclaredLValueIdent(lookAhead->string);
    else
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
  checkTypeEquality(compileExpression(), param->paramAttrs->type);
}

void compileArguments(ObjectNode* paramList) {
  if(paramList != NULL && lookAhead->tokenType != SB_LPAR)
    error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo); 

  switch (lookAhead->tokenType) {
  case SB_LPAR:
    eat(SB_LPAR);
    if(paramList != NULL)
      compileArgument(paramList->object);
    else
      error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo); 

    while (lookAhead->tokenType == SB_COMMA) {
      eat(SB_COMMA);
      paramList = paramList->next; // next object in paramList
      if(paramList != NULL) // still have param
        compileArgument(paramList->object);
      else
        error(ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    }
    eat(SB_RPAR);
    break;
    // Check FOLLOW set 
  case SB_TIMES:
  case SB_SLASH:
  case SB_PLUS:
  case SB_MINUS:
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_CLOSE_BRACKET:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default:
    error(ERR_INVALID_ARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileCondition(void) {
  Type *LExpression = NULL;
  LExpression = compileExpression();

  switch (lookAhead->tokenType) {
  case SB_EQ:
    eat(SB_EQ);
    break;
  case SB_NEQ:
    eat(SB_NEQ);
    break;
  case SB_LE:
    eat(SB_LE);
    break;
  case SB_LT:
    eat(SB_LT);
    break;
  case SB_GE:
    eat(SB_GE);
    break;
  case SB_GT:
    eat(SB_GT);
    break;
  default:
    error(ERR_INVALID_COMPARATOR, lookAhead->lineNo, lookAhead->colNo);
  }
  checkTypeEquality(LExpression, compileExpression());
}

Type* compileExpression(void) { //
  Type* type;
  
  switch (lookAhead->tokenType) {
  case SB_PLUS:
    eat(SB_PLUS);
    type = compileExpression2();
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    type = compileExpression2();
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    break;
  default:
    type = compileExpression2();
  }
  return type;
}

Type* compileExpression2(void) {
  Type* type, *resultType;

  type = compileTerm();
  resultType = compileExpression3(type);
  checkTypeEquality(type, resultType);
  return resultType;
}

Type* compileExpression3(Type* argType1) { //
  Type* type;
  Type* resultType;

  switch (lookAhead->tokenType) {
  case SB_PLUS:
    eat(SB_PLUS);
    type = compileTerm();
    checkTypeEquality(type, argType1);
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    resultType = compileExpression3(type);
    checkTypeEquality(resultType, argType1);
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    type = compileTerm();
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    resultType = compileExpression3(type);
    checkTypeEquality(resultType, argType1);
    break;
    // check the FOLLOW set
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_CLOSE_BRACKET:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    resultType = argType1;
    break;
  default:
    error(ERR_INVALID_EXPRESSION, lookAhead->lineNo, lookAhead->colNo);
  }
  return resultType;
}

Type* compileTerm(void) {
  Type *type, *resultType;

  type = compileFactor();
  resultType = compileTerm2(type);
  checkTypeEquality(type, resultType);
  return resultType;
}

Type* compileTerm2(Type* argType1) { //
  Type* type;
  Type* resultType;

  switch (lookAhead->tokenType) {
  case SB_TIMES:
    eat(SB_TIMES);
    type = compileFactor();
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    resultType = compileTerm2(type);
    checkTypeEquality(type, resultType);
    break;
  case SB_SLASH:
    eat(SB_SLASH);
    type = compileFactor();
    if ((type->typeClass != TP_INT) && (type->typeClass != TP_DOUBLE))
      error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
    resultType = compileTerm2(type);
    checkTypeEquality(type, resultType);
    break;
  case SB_MODULUS:
    eat(SB_MODULUS);
    type = compileFactor();
    if (type->typeClass != TP_INT)
      error(ERR_INVALID_MODUL_OPERATOR, currentToken->lineNo, currentToken->colNo);
    resultType = compileTerm2(type);
    if (resultType->typeClass != TP_INT)
      error(ERR_INVALID_MODUL_OPERATOR, currentToken->lineNo, currentToken->colNo);
    break;
    // check the FOLLOW set
  case SB_PLUS:
  case SB_MINUS:
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_CLOSE_BRACKET:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    resultType = argType1;
    break;
  default:
    error(ERR_INVALID_TERM, lookAhead->lineNo, lookAhead->colNo);
  }
  return resultType;
}

Type* compileFactor(void) {
  Object* obj;
  Type* type;

  switch (lookAhead->tokenType) {
  case TK_NUMBER:
    eat(TK_NUMBER);
    type = makeIntType();
    break;
  case TK_DOUBLE: //
    eat(TK_DOUBLE);
    type = makeDoubleType();
    break;
  case TK_STRING: //
    eat(TK_STRING);
    type = makeStringType();
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    type = makeCharType();
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    // check if the identifier is declared
    obj = checkDeclaredIdent(currentToken->string);
    switch (obj->kind) {
    case OBJ_CONSTANT:
      type = makeIntType();
      type->typeClass = obj->constAttrs->value->type;
      break;
    case OBJ_VARIABLE:
      if(obj->varAttrs->type->typeClass == TP_ARRAY) {
        type = compileIndexes(obj->varAttrs->type);
      } else {
        type = obj->varAttrs->type;
      }
      break;
    case OBJ_PARAMETER:
      type = obj->paramAttrs->type;
      break;
    case OBJ_FUNCTION:
      type = obj->funcAttrs->returnType;
      compileArguments(obj->funcAttrs->paramList);
      break;
    default: 
      error(ERR_INVALID_FACTOR,currentToken->lineNo, currentToken->colNo);
      break;
    }
    break;
  case SB_LPAR:
    eat(SB_LPAR);
    type = compileExpression();
    eat(SB_RPAR);
    break;
  default:
    error(ERR_INVALID_FACTOR, lookAhead->lineNo, lookAhead->colNo);
  }
  return type;
}

Type* compileIndexes(Type* arrayType) {
  Type *indexType = NULL, *elementType = NULL;
  while (lookAhead->tokenType == SB_OPEN_BRACKET) {
    eat(SB_OPEN_BRACKET);
    checkArrayType(arrayType); // check if current type is TP_Array
    indexType = compileExpression();
    checkIntType(indexType);
    eat(SB_CLOSE_BRACKET);
    arrayType = arrayType->elementType;
  }
  elementType = arrayType;
  return elementType;
}

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;
  currentToken = NULL;
  lookAhead = getValidToken();

  initSymTab();
  compileProgram();
  printObject(symtab->program, 0);
  cleanSymTab();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}