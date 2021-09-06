/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define KEYWORDS_COUNT 22 //

typedef enum {
  TK_NONE, TK_IDENT, TK_NUMBER, TK_DOUBLE, TK_STRING, TK_EOF, TK_CHAR, // String, Double Token

  KW_PROGRAM, KW_CONST, KW_TYPE, KW_VAR,
  KW_INTEGER, KW_CHAR, KW_DOUBLE, KW_STRING, // String, Double Keyword
  KW_ARRAY, KW_OF, 
  KW_FUNCTION, KW_PROCEDURE,
  KW_BEGIN, KW_END, KW_CALL,
  KW_IF, KW_THEN, KW_ELSE,
  KW_WHILE, KW_DO, KW_FOR, KW_TO,

  SB_SEMICOLON, SB_COLON, SB_PERIOD, SB_COMMA,
  SB_ASSIGN, SB_EQ, SB_NEQ, SB_LT, SB_LE, SB_GT, SB_GE,
  SB_PLUS, SB_MINUS, SB_TIMES, SB_SLASH,
  SB_LPAR, SB_RPAR,
  SB_ASSIGN_PLUS, SB_ASSIGN_SUBTRACT, SB_ASSIGN_TIMES, SB_ASSIGN_DIVIDE, // Assign Tokens
  SB_OPEN_BRACKET, SB_CLOSE_BRACKET, SB_MODULUS // Module Token
} TokenType;

typedef struct {
  char string[255];
  int lineNo, colNo;
  TokenType tokenType;
  int value;
  double d_value; // Double value
} Token;

TokenType checkKeyword(char *string);
Token* makeToken(TokenType tokenType, int lineNo, int colNo);
char *tokenToString(TokenType tokenType);


#endif
