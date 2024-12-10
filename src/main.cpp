#include "Differentiator.h"

int main(const int argc, const char** argv)
{
    Token_t token = {};
    struct stat buffer = {};

    if(argc != 3)
    {
        printf("usage: argv[0] <%s>\n", argv[0]);

        return -1;
    }

    stat(argv[1], &buffer);

    ReadExpression(&token, argv, buffer.st_size); // read from stdin

    Node_t* root = GetGrammar(&token);

    root = SimplifyExpTree(root, argv);

    //GraphicDump(root, argv);

    //Node_t* diff = DiffExpression(root, diff, argv);
    //PrintInOrder(diff);
    //diff = SimplifyExpTree(diff, argv);

    PrintInOrder(root);
    printf("\n");
    //PrintInOrder(diff);
    printf("\n");

    //GraphicDump(diff, argv);
    TreeDtor(root);
    //TreeDtor(diff);
}
