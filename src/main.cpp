#include "Differentiator.h"

int main(const int argc, const char** argv)
{
    Read read = {};
    struct stat buffer = {};

    if(argc != 3)
    {
        printf("argc error\n");

        return -1;
    }

    stat(argv[1], &buffer);

    ReadExpression(&read, argv, buffer.st_size);

    Node_t* root = GetG(&read);

    GraphicDump(root, argv);

    Node_t* diff = Diff(root, diff, argv);

    root = Simplifier(root);
    diff = Simplifier(diff);

    PrintInOrder(root);
    printf("\n");
    PrintInOrder(diff);
    printf("\n");

    GraphicDump(diff, argv);

    Dtor(root);
    //Dtor(diff);
}
