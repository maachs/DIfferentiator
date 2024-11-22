#include "Dump.h"

void PrintInOrder(Node_t* node)
{
    if(!node) return;

    printf("(");

    PrintInOrder(node->left);

    if(node->type == OP)
    {
        if(node->value == ADD)
        {
            printf("+");
        }
        else if(node->value == SUB)
        {
            printf("-");
        }
        else if(node->value == DIV)
        {
            printf("/");
        }
        else if(node->value == MUL)
        {
            printf("*");
        }
    }
    else if(node->type == NUM)
    {
        printf("%d", node->value);
    }
    else if(node->type == VAR)
    {
        printf("x");
    }
    PrintInOrder(node->right);

    printf(")");

}

int GraphicDump(Node_t* node, const char** argv)
{
    assert(node);
    assert(argv);

    FILE* dump = fopen(argv[1], "w");

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
        if(node->value == ADD)
        {
            fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"+\"];\n", node);
        }
        else if(node->value == SUB)
        {
            fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"-\"];\n", node);
        }
        else if(node->value == DIV)
        {
            fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"/\"];\n", node);
        }
        else if(node->value == MUL)
        {
            fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"*\"];\n", node);
        }
        else if(node->value == POW)
        {
            fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"^\"];\n", node);
        }
    }

    if(node->type == NUM)
    {
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"%d\"];\n", node, node->value);
    }

    if(node->type == VAR)
    {
        fprintf(dump, "\"%p\" [shape = Mrecord, style = \"filled\", fillcolor = \"darkslateblue\","
            " label = \"x\"];\n", node);
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

void MySystem(const char* str, int number_dump)
{
    char command_dot[40] = "";

    sprintf(command_dot, str, number_dump);

    system(command_dot);

}
