#ifndef READ_EQUATION_
#define READ_EQUATION_

#include "Globals.h"

int ReadExpression(Token_t* token, const char** argv, int size);
int FillNodes     (Token_t* token, char* expression, int size);
int FillFunction  (Token_t* token, char* expression);
int FillOperation (Token_t* token, char* expression);

Node_t* GetGrammar (Token_t* token);
Node_t* GetEquation(Token_t* token);
Node_t* GetNumber  (Token_t* token);
Node_t* GetMulDiv  (Token_t* token);
Node_t* GetBrackets(Token_t* token);
Node_t* GetVariable(Token_t* token);
Node_t* GetDeg     (Token_t* token);
Node_t* GetFunc    (Token_t* token);

#define NEW_FUNC_(var, delta)             \
    token->str[token->count].type = OP;      \
    token->str[token->count].value.op = var; \
    token->str[token->count].left = NULL;    \
    token->str[token->count].right = NULL;   \
    token->count++ ;                         \
    token->point += delta;

#define COMP_FUNC(var)                          \
    token->str[token->point].value.op == var    \

#define MAKE_NODE_IF(var)                                             \
    if(op == var)                                                     \
    {                                                                 \
        val = MakeNode(OP, NodeValue {.op = var},                     \
              MakeNode(NUM, NodeValue{.num = 0}, NULL, NULL), val_1); \
    }                                                                 \
    else

#endif
