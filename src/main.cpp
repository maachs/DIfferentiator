#include "Differentiator.h"

int main(const int argc, const char** argv)
{
    Token_t token = {};
    struct stat buffer = {};

    if(argc != 4)
    {
        printf("usage: argv[0] <%s>\n", argv[0]);

        return -1;
    }

    int count_phrase = 0;

    FILE* tex_file = fopen(argv[3], "w");

    if(tex_file == NULL)
    {
        printf("cannot open file: %s\n", argv[3]);

        return -1;
    }

    stat(argv[1], &buffer);

    ReadExpression(&token, argv, buffer.st_size);

    Node_t* root = GetGrammar(&token);

    BeginTexDump(root, tex_file);

    PrintInOrder(root);
    printf("\n");
    //root = SimplifyExpTree(root, argv);

    //GraphicDump(root, argv);

    Node_t* diff = DiffExpression(root, diff, tex_file, &count_phrase);
    PrintInOrder(diff);
    diff = SimplifyExpTree(diff, argv);
    TexDump(root, diff, tex_file, &count_phrase);
    //PrintInOrder(root);
    printf("\n");
    PrintInOrder(diff);
    printf("\n");

    TexEnd(tex_file);
    fclose(tex_file);
    //printf("-----------\n");
    //PrintInOrder(diff);
    GraphicDump(diff, argv);

    TreeDtor(root);
    TreeDtor(diff);
    TokenDtor(&token);
}
