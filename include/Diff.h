#ifndef DERIVATIVE_
#define DERIVATIVE_

#include "Globals.h"
#include "Constructor.h"
#include "Dump.h"

Node_t* Diff(Node_t* node, Node_t* diff, const char** argv);
Node_t* Copy(Node_t* node);

#endif

