#ifndef READ_EQUATION_
#define READ_EQUATION_

#include "Globals.h"

int ReadExpression(Read* read, const char** argv, int size);

Node_t* GetG(Read* read);
Node_t* GetE(Read* read);
Node_t* GetN(Read* read);
Node_t* GetT(Read* read);
Node_t* GetP(Read* read);
Node_t* GetV(Read* read);
Node_t* GetD(Read* read);

#endif
