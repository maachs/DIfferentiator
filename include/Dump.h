#ifndef DUMP_
#define DUMP_

#include "Globals.h"

int  GraphicDump         (Node_t* node, const char** argv);
void PrintInOrder        (Node_t* node);
int  DrawNode            (Node_t* node, FILE* dump);
int  DrawOperation       (Node_t* node, FILE* dump);
void MySystem            (const char* str, int number_dump);
void PrintInOrderOperator(Node_t* node);

#define DRAW_GRAPHIC_OP(var, operator)                                                                                                                                                                                \
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","                      \
        " label = \"{ %s | addr = %p | { left = %p | right = %p}}\"];\n", node, operator, node, node->left, node->right);

#endif
