#ifndef DUMP_
#define DUMP_

#include "Globals.h"
#include "Constructor.h"

static const char* phrase[] = { "{Let's diff:}",
                               };

int  GraphicDump         (Node_t* node, const char** argv);
int  DrawNode            (Node_t* node, FILE* dump);
int  DrawOperation       (Node_t* node, FILE* dump);

void MySystem            (const char* str, int number_dump);

void PrintInOrderOperator(Node_t* node);
void PrintInOrder        (Node_t* node);

int TexEnd               (FILE* tex_file);
int BeginTexDump         (Node_t* node, FILE* tex_file);
int DrawTexNode          (Node_t* node, FILE* tex_file);
int DrawTexOperation     (Node_t* node, FILE* tex_file);
int TexDump              (Node_t* node, Node_t* diff, FILE* tex_file, int* count_phrase);

#define DRAW_GRAPHIC_OP(var, operator)                                                                                                                                                                                \
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","                      \
        " label = \"{ %s | addr = %p | { left = %p | right = %p}}\"];\n", node, operator, node, node->left, node->right);

#define DRAW_TEX_OP(operator)\
        fprintf(tex_file, "%s", operator)

#endif
