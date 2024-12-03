#ifndef SIMPLIFIER_
#define SIMPLIFIER_

#include "Globals.h"
#include "Constructor.h"
#include "Dump.h"

const double EPS = 0.01;

Node_t* Simplifier    (Node_t* node);
void    DtorSimplyNode(Node_t* node);
int     CompareNum    (double val_1, double val_2);

#endif
