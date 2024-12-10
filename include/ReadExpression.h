#ifndef READ_EQUATION_
#define READ_EQUATION_

#include "Globals.h"

int ReadExpression(Token_t* token, const char** argv, int size);
int FillNodes     (Token_t* token, char* expression, int size);
int GetFunction   (Token_t* token, char* expression);
int GetOperation  (Token_t* token, char* expression);

Node_t* GetGrammar (Token_t* token);
Node_t* GetEquation(Token_t* token);
Node_t* GetNumber  (Token_t* token);
Node_t* GetT(Token_t* token);
Node_t* GetP(Token_t* token);
Node_t* GetVariable(Token_t* token);
Node_t* GetD(Token_t* token);

#define NEW_FUNC_(var, delta)             \
    token->str[token->count].type = OP;      \
    token->str[token->count].value.op = var; \
    token->str[token->count].left = NULL;    \
    token->str[token->count].right = NULL;   \
    token->count++ ;                         \
    token->point += delta;

#endif
