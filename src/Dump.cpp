#include "Dump.h"

void PrintInOrder(Node_t* node)
{
    if(!node) return;

    printf("(");

    PrintInOrder(node->left);

    if(node->type == OP)
    {
        PrintInOrderOperator(node);
    }
    else if(node->type == NUM)
    {
        printf("%lg", node->value.num);
    }
    else if(node->type == VAR)
    {
        printf("x");
    }
    PrintInOrder(node->right);

    printf(")");
}

void PrintInOrderOperator(Node_t* node)
{
    assert(node);

    switch(node->value.op)
    {
        case ADD: printf("+"); break;

        case SUB: printf("-"); break;

        case MUL: printf("*"); break;

        case DIV: printf("/"); break;

        case POW: printf("^"); break;

        case SIN: printf("sin"); break;

        case COS: printf("cos"); break;

        case TG: printf("tg"); break;

        case CTG: printf("ctg"); break;

        case LN: printf("ln"); break;

        case LOG: printf("log"); break;

        case EXP: printf("e"); break;

        case SH: printf("sh"); break;

        case CH: printf("ch"); break;

        case ARCSIN: printf("arcsin"); break;

        case ARCTG: printf("arcsin"); break;

        case ARCCTG: printf("arcctg"); break;

        case ARCSH: printf("arcsh"); break;

        case ARCCH: printf("arcch"); break;

        case ARCTH: printf("arcth"); break;

        case ARCCTH: printf("arccth"); break;

        default:
           printf("cannot defined operator: %d\n", node->value.op);
    }
}

int GraphicDump(Node_t* node, const char** argv)
{
    assert(node);
    assert(argv);

    FILE* dump = fopen(argv[2], "w");

    fprintf(dump, "digraph G\n{\n rankdir = UD\nbgcolor = \"aquamarine3\"\n");

    DrawNode(node, dump);

    fprintf(dump, "}\n");

    fclose(dump);

    //static int count = 0;

    //MySystem("dot Dump.dot -Tpng -o Dump%03d.png", count);

    system("dot Dump.dot -Tpng -o Dump.png");

    //count++;

    return 0;
}

int DrawNode(Node_t* node, FILE* dump)
{
    assert(dump);

    if(node->type == OP)
    {
        DrawOperation(node, dump);
    }

    if(node->type == NUM)
    {
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"olivedrab2\","
            " label = \"{ %lg | addr = %p | { left = %p | right = %p}}\"];\n", node, node->value.num, node, node->left, node->right);
    }

    if(node->type == VAR)
    {
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"firebrick1\","
            " label = \"{ x | addr = %p | { left = %p | right = %p}}\"];\n", node, node, node->left, node->right);
    }

    if(node->left != NULL)
    {
        DrawNode(node->left, dump);

        fprintf(dump, "\"%p\"->\"%p\"\n", node, node->left);
    }
    if(node->right != NULL)
    {
        DrawNode(node->right, dump);

        fprintf(dump, "\"%p\"->\"%p\"\n", node, node->right);
    }

    return 0;
}

int DrawOperation(Node_t* node, FILE* dump)
{
    assert(node);
    assert(dump);

    switch(node->value.op)
    {
        case ADD: DRAW_GRAPHIC_OP(ADD, "+"); break;

        case SUB: DRAW_GRAPHIC_OP(SUB, "-"); break;

        case MUL: DRAW_GRAPHIC_OP(MUL, "*"); break;

        case DIV: DRAW_GRAPHIC_OP(DIV, "/"); break;;

        case SIN: DRAW_GRAPHIC_OP(SIN, "sin"); break;

        case COS: DRAW_GRAPHIC_OP(COS, "cos"); break;

        case TG: DRAW_GRAPHIC_OP(TG, "tg"); break;

        case POW: DRAW_GRAPHIC_OP(POW, "^"); break;

        case LN: DRAW_GRAPHIC_OP(LN, "ln"); break;

        case LOG: DRAW_GRAPHIC_OP(LOG, "log"); break;

        case EXP: DRAW_GRAPHIC_OP(EXP, "e"); break;

        case SH: DRAW_GRAPHIC_OP(SH, "sh"); break;

        case CH: DRAW_GRAPHIC_OP(CH, "ch"); break;

        case TH: DRAW_GRAPHIC_OP(TH, "th"); break;

        case CTH: DRAW_GRAPHIC_OP(CTH, "cth"); break;

        case ARCSIN: DRAW_GRAPHIC_OP(ARCSIN, "arcsin"); break;

        case ARCCOS: DRAW_GRAPHIC_OP(ARCCOS, "arccos"); break;

        case ARCTG: DRAW_GRAPHIC_OP(ARCTG, "arctg"); break;

        case ARCCTG: DRAW_GRAPHIC_OP(ARCCTG, "arcctg"); break;

        case ARCSH: DRAW_GRAPHIC_OP(ARCSH, "arcsh"); break;

        case ARCCH: DRAW_GRAPHIC_OP(ARCCH, "arcch"); break;

        case ARCTH: DRAW_GRAPHIC_OP(ARCTH, "arcth"); break;

        case ARCCTH: DRAW_GRAPHIC_OP(ARCCTH, "arccth"); break;

        default:
            printf("cannot defined operator: %d\n", node->value.op);
            return -1;
    }

    return 0;
}

void MySystem(const char* str, int number_dump)
{
    char command_dot[40] = "";

    sprintf(command_dot, str, number_dump);

    system(command_dot);

}

int TexDump(Node_t* node, const char** argv)
{
    assert(node);
    assert(argv);

    FILE* tex_file = fopen(argv[3], "w");

    if(tex_file == NULL)
    {
        printf("cannot open file: %s\n", argv[3]);

        return -1;
    }

    return 0;
}
