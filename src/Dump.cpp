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
           printf("cannot defined operator in order dump: %d\n", node->value.op);
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
            printf("cannot defined operator in graphic dump: %d\n", node->value.op);
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

int BeginTexDump(Node_t* node, FILE* tex_file)
{
    assert(node);

    fprintf(tex_file, "\\documentclass[a4paper,12pt]{article}\n\\usepackage{cmap}\n\\usepackage[T2A]{fontenc}\n\\usepackage[utf8]{inputenc}\n"
        "\\usepackage[english,russian]{babel}\n\\usepackage{graphicx}\n\\graphicspath{{noiseimages/}}\n"
        "\\usepackage{enumitem}\n\\date{}\n\n\n\\newtheorem{task}{Задача}\n\\begin{document}\n\\begin{titlepage}\n"
        "\\begin{center}\n\t\\textsc{MOSKOW INSTITUTE OF PHYSICS AND TECHNOLOGY}\n\t\\vspace{2ex}\n\n"
        "\\end{center}\n\\vspace{10ex}\n\\begin{center}\n\t\\vspace{24ex}\n"
        "\n\t\\vspace{2ex}\n\t\\textbf{\\Large{Differentiator}}\n\t\\vspace{34ex}\n"
        "\t\\begin{flushright}\n\t\\noindent\n\tDone by:\n\t\\textit{Vanin Maxim}\n\t\\end{flushright}\n\t\\vfill\n\tDolgoprudny, 2024\n"
        "\\end{center}\n\\end{titlepage}\n\\newpage\n");

    return 0;
}

int TexDump(Node_t* node, Node_t* diff, FILE* tex_file, int* count_phrase)
{
    assert(node);
    assert(tex_file);

    fprintf(tex_file, "\\section%s\n\\begin{center}\n\t$$", phrase[*count_phrase]);

    fprintf(tex_file, "(");
    DrawTexNode(node, tex_file);
    fprintf(tex_file, ")\' = ");

    DrawTexNode(diff, tex_file);

    *count_phrase++;

    fprintf(tex_file, "$$\n\\end{center}\n");

    //TreeDtor(diff);

    return 0;
}

int DrawTexNode(Node_t* node, FILE* tex_file)
{
    assert(tex_file);

    if(!node)
    {
        fprintf(tex_file, "\n");
        return 0;
    }

    if(node->type == NUM)
    {
        fprintf(tex_file, " %lg ", node->value.num);
    }
    else if(node->type == VAR)
    {
        fprintf(tex_file, " x ");
    }
    else if(node->type == OP)
    {
        if(node->value.op == DIV)
        {
            DrawTexOperation(node, tex_file);

            if(node->left->type == OP)
            {
                fprintf(tex_file, "{");
                DrawTexNode(node->left, tex_file);
                fprintf(tex_file, "}");
            }
            else
            {
                DrawTexNode(node->left, tex_file);
            }

            if(node->right->type == OP)
            {
                fprintf(tex_file, "{");
                DrawTexNode(node->right, tex_file);
                fprintf(tex_file, "}");
            }
            else
            {
                DrawTexNode(node->right , tex_file);
            }
        }
        else if(node->value.op == MUL)
        {
            if(node->left->type == OP && (node->left->value.op == ADD || node->left->value.op == SUB))
            {
                fprintf(tex_file, "(");
                DrawTexNode(node->left, tex_file);
                fprintf(tex_file, ")");
            }
            else
            {
                DrawTexNode(node->left, tex_file);
            }
            DrawTexOperation(node, tex_file);
            if(node->right->type == OP && (node->right->value.op == ADD || node->right->value.op == SUB))
            {
                fprintf(tex_file, "(");
                DrawTexNode(node->right, tex_file);
                fprintf(tex_file, ")");
            }
            else
            {
                DrawTexNode(node->right , tex_file);
            }
        }
        else if(node->value.op == SIN || node->value.op == COS || node->value.op == TG)
        {
            DrawTexOperation(node, tex_file);

            fprintf(tex_file, "(");

            DrawTexNode(node->right, tex_file);

            fprintf(tex_file, ")");
        }
        else if(node->value.op == POW && node->left->type == OP && (node->left->value.op == SIN || node->left->value.op == COS))
        {
            DrawTexOperation(node->left, tex_file);

            DrawTexOperation(node, tex_file);

            fprintf(tex_file, "{");
            DrawTexNode(node->right, tex_file);
            fprintf(tex_file, "}");

            fprintf(tex_file, "(");

            DrawTexNode(node->left->right, tex_file);

            fprintf(tex_file, ")");
        }
        else if(node->value.op == LN)
        {
            DrawTexOperation(node->right, tex_file);

            fprintf(tex_file, "(");
            DrawTexNode(node->right, tex_file);
            fprintf(tex_file, ")");
        }
        else if(node->value.op == POW && node->left->type == OP)
        {
            fprintf(tex_file, "(");
            DrawTexNode(node->left, tex_file);
            fprintf(tex_file, ")");

            DrawTexOperation(node, tex_file);

            if(node->right->type == OP)
            {
                fprintf(tex_file, "(");
                DrawTexNode(node->right, tex_file);
                fprintf(tex_file, ")");
            }
            else
            {
                DrawTexNode(node->right, tex_file);
            }
        }
        else
        {
            DrawTexNode(node->left, tex_file);

            DrawTexOperation(node, tex_file);

            DrawTexNode(node->right, tex_file);
        }
    }
    else
    {
        printf("cannot defined op in tex dump %d\n", node->value.op);
    }


    return 0;
}

int DrawTexOperation(Node_t* node, FILE* tex_file)
{
    assert(node);
    assert(tex_file);

    switch(node->value.op)
    {
        case ADD: DRAW_TEX_OP("+"); break;

        case SUB: DRAW_TEX_OP("-"); break;

        case MUL: DRAW_TEX_OP("\\cdot"); break;

        case DIV: DRAW_TEX_OP("\\frac"); break;;

        case SIN: DRAW_TEX_OP("\\sin"); break;

        case COS: DRAW_TEX_OP("\\cos"); break;

        case POW: DRAW_TEX_OP("^"); break;

        case LN: DRAW_TEX_OP("ln"); break;
        /*case TG: DRAW_GRAPHIC_OP(TG, "tg"); break;

        case POW: DRAW_TEX_OP("^"); break;

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

        case ARCCTH: DRAW_GRAPHIC_OP(ARCCTH, "arccth"); break;*/

        default:
            printf("cannot defined operator in tex switch: %d\n", node->value.op);
            return -1;
    }
    return 0;
}

int TexEnd(FILE* tex_file)
{
    assert(tex_file);

    fprintf(tex_file, "\n\\end{document}\n");

    return 0;
}
