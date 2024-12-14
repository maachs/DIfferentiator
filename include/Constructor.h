#ifndef CONSTRUCTOR_
#define CONSTRUCTOR_

#include "Globals.h"

int     TreeDtor (Node_t* node);
int     TokenDtor(Token_t* token);
Node_t* MakeNode (int type, NodeValue value, Node_t* left, Node_t* right);

#endif
