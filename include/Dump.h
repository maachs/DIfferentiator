#ifndef DUMP_
#define DUMP_

#include "Globals.h"

int  GraphicDump  (Node_t* node, const char** argv);
void PrintInOrder (Node_t* node);
int  DrawNode     (Node_t* node, FILE* dump);
int  DrawOperation(Node_t* node, FILE* dump);
void MySystem     (const char* str, int number_dump);

#endif
