#include "Differentiator.h"

int main(const int argc, const char** argv)
{
    if(argc != 2)
    {
        printf("argc error\n");

        return -1;
    }

    Node_t* root = MakeNode(OP, DIV, MakeNode(OP, ADD, MakeNode(OP, POW, MakeNode(VAR, 1, NULL, NULL), MakeNode(NUM, 2, NULL, NULL)), MakeNode(NUM, 3, NULL, NULL)),
                                     MakeNode(OP, SUB, MakeNode(NUM, 1000, NULL, NULL), MakeNode(NUM, 7, NULL, NULL)));

    Node_t* diff = Diff(root, argv);

    PrintInOrder(root);

    printf("\n");

    PrintInOrder(diff);

    GraphicDump(diff, argv);

    Dtor(root);

}
