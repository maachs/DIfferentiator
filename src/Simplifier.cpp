#include "Simplifier.h"

Node_t* SimplifyExpTree(Node_t* node, const char** argv)
{
    assert(node);

    if(node->left == NULL && node->right == NULL) return node;

    node->left = SimplifyExpTree(node->left, argv);
    node->right = SimplifyExpTree(node->right, argv);

    if(node->type == OP)
    {
        if(node->left->type == NUM && node->right->type == NUM)
        {
            if(node->value.op == ADD)
            {
                node->type = NUM;
                node->value.num = node->left->value.num + node->right->value.num;

                DtorSimplyNodes(node);
            }
            else if(node->value.op == SUB)
            {
                node->type = NUM;
                node->value.num = node->left->value.num - node->right->value.num;

                DtorSimplyNodes(node);
            }
            else if(node->value.op == POW)
            {
                node->type = NUM;
                node->value.num = pow(node->left->value.num, node->right->value.num);

                DtorSimplyNodes(node);
            }
            else if(node->value.op == MUL)
            {
                node->type = NUM;
                node->value.num = node->left->value.num * node->right->value.num;

                DtorSimplyNodes(node);
            }
            else if(node->value.op == DIV)
            {
                node->type = NUM;
                node->value.num = node->left->value.num / node->right->value.num;

                DtorSimplyNodes(node);
            }
            else if(node->value.op == POW)
            {
                node->type = NUM;
                node->value.num = pow(node->left->value.num, node->right->value.num);

                DtorSimplyNodes(node);
            }
        }
        else if(node->left->type == VAR && node->right->type == NUM)
        {
            if(node->value.op == MUL && CompareNum(node->right->value.num, 0))
            {
                node->type = NUM;
                node->value.num = 0;

                DtorSimplyNodes(node);
            }
            if(node->value.op == MUL && CompareNum(node->right->value.num, 1))
            {
                node->type = VAR;
                node->value.var_num = X;

                DtorSimplyNodes(node);
            }
        }
        else if(node->right->type == VAR && node->left->type == NUM)
        {
            if(node->value.op == MUL && CompareNum(node->left->value.num, 0))
            {
                node->type = NUM;
                node->value.num = 0;

                DtorSimplyNodes(node);
            }
            if(node->value.op == MUL && CompareNum(node->left->value.num, 1))
            {
                node->type = VAR;
                node->value.var_num = X;

                DtorSimplyNodes(node);
            }
        }
        else if(node->left->type == NUM && CompareNum(node->left->value.num, 1) && node->value.op == MUL && node->right->type == OP)
        {
            TreeDtor(node->left);
            node = Copy(node->right);
        }
        else if(node->right->type == NUM && CompareNum(node->right->value.num, 1) && (node->value.op == MUL || node->value.op == DIV) && node->left->type == OP)
        {
            TreeDtor(node->right);
            node = Copy(node->left);
        }
        else if(node->left->type == NUM && CompareNum(node->left->value.num, 0) && node->value.op == ADD)
        {
            TreeDtor(node->left);
            node = Copy(node->right);
        }
        else if(node->right->type == NUM && CompareNum(node->right->value.num, 0) && node->value.op == ADD)
        {
            TreeDtor(node->right);
            node = Copy(node->left);
        }
        else if(node->left->type == NUM && CompareNum(node->left->value.num, 0) && node->type == OP && node->value.op == MUL)
        {
            node->type = NUM;
            node->value.num = 0;
            DtorSimplyNodes(node);
        }
        else if(node->right->type == NUM && CompareNum(node->right->value.num, 0) && node->type == OP && node->value.op == MUL)
        {
            node->type = NUM;
            node->value.num = 0;
            DtorSimplyNodes(node);
        }
        else if(node->value.op == POW && node->right->type == NUM && CompareNum(node->right->value.num, 0))
        {
            node->type = NUM;
            node->value.num = 1;
            DtorSimplyNodes(node);
        }
        else if(node->value.op == POW && node->right->type == NUM && CompareNum(node->right->value.num, 1))
        {
            TreeDtor(node->right);
            node = Copy(node->left);
        }
        else if((node->value.op == LOG || node->value.op == LN) && node->left->type == NUM && CompareNum(node->left->value.num, 1))
        {
            node->type = NUM;
            node->value.num = 0;

            DtorSimplyNodes(node);
        }

    }

    return node;
}

int CompareNum(double val_1, double val_2)
{
    if(fabs(val_1 - val_2) < EPS) return 1;

    return 0;
}

void DtorSimplyNodes(Node_t* node)
{
    assert(node);

    TreeDtor(node->left);
    TreeDtor(node->right);

    node->left = NULL;
    node->right = NULL;
}
