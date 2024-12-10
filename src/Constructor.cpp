#include "Constructor.h"

int TreeDtor(Node_t* node)
{
    if(!node)
    {
        return 0;
    }

    TreeDtor(node->left);
    TreeDtor(node->right);

    free(node);

    node = NULL;

    return 0;

}

Node_t* MakeNode(int type, NodeValue value, Node_t* left, Node_t* right)
{
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));

    if(node == NULL)
    {
        printf("calloc error");

        return NULL;
    }

    node->type = type;

    node->value = value;

    node->left = left;
    node->right = right;

    return node;
}

