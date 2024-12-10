#ifndef SIMPLIFIER_
#define SIMPLIFIER_

#include "Globals.h"
#include "Constructor.h"
#include "Dump.h"
#include "Diff.h"

const double EPS = 0.01;

Node_t* SimplifyExpTree(Node_t* node, const char** argv);
void    DtorSimplyNodes(Node_t* node);
int     CompareNum    (double val_1, double val_2);

#endif
