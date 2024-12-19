#ifndef DERIVATIVE_
#define DERIVATIVE_

#include "Globals.h"
#include "Constructor.h"
#include "Dump.h"

Node_t* DiffExpression(Node_t* node, Node_t* diff, FILE* tex_file, int* count_phrase);
Node_t* Copy(Node_t* node);

#endif

