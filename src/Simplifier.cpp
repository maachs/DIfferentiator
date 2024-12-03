#include "Simplifier.h"

Node_t* Simplifier(Node_t* node)
{
    assert(node);

    if(node->left == NULL && node->right == NULL) return node;

    node->left = Simplifier(node->left);
    node->right = Simplifier(node->right);

    if(node->type == OP)
    {
        if(node->left->type == NUM && node->right->type == NUM)
        {
            if(node->value.op == ADD)
            {
                node->type = NUM;
                node->value.num = node->left->value.num + node->right->value.num;

                DtorSimplyNode(node);
            }
            else if(node->value.op == SUB)
            {
                node->type = NUM;
                node->value.num = node->left->value.num - node->right->value.num;

                DtorSimplyNode(node);
            }
            else if(node->value.op == POW)
            {
                node->type = NUM;
                node->value.num = pow(node->left->value.num, node->right->value.num);

                DtorSimplyNode(node);
            }
            else if(node->value.op == MUL)
            {
                node->type = NUM;
                node->value.num = node->left->value.num * node->right->value.num;

                DtorSimplyNode(node);
            }
            else if(node->value.op == DIV)
            {
                node->type = NUM;
                node->value.num = node->left->value.num / node->right->value.num;

                DtorSimplyNode(node);
            }
            else if(node->value.op == POW)
            {
                node->type = NUM;
                node->value.num = pow(node->left->value.num, node->right->value.num);

                DtorSimplyNode(node);
            }
        }
        else if(node->left->type == VAR && node->right->type == NUM)
        {
            if(node->value.op == MUL && CompareNum(node->right->value.num, 0))
            {
                node->type = NUM;
                node->value.num = 0;

                DtorSimplyNode(node);
            }
            if(node->value.op == MUL && CompareNum(node->right->value.num, 1))
            {
                node->type = VAR;
                node->value.var_num = X;

                DtorSimplyNode(node);
            }
        }
        else if(node->right->type == VAR && node->left->type == NUM)
        {
            if(node->value.op == MUL && CompareNum(node->left->value.num, 0))
            {
                node->type = NUM;
                node->value.num = 0;

                DtorSimplyNode(node);
            }
            if(node->value.op == MUL && CompareNum(node->left->value.num, 1))
            {
                node->type = VAR;
                node->value.var_num = X;

                DtorSimplyNode(node);
            }
        }
        else if(node->left->type == NUM && CompareNum(node->left->value.num, 1) && node->value.op == MUL && node->right->type == OP)
        {
            node = node->right;

            DtorSimplyNode(node->left);
        }
        else if(node->right->type == NUM && CompareNum(node->right->value.num, 1) && (node->value.op == MUL || node->value.op == DIV) && node->left->type == OP)
        {
            node = node->left;

            DtorSimplyNode(node->left);
        }
        else if(node->left->type == NUM && CompareNum(node->left->value.num, 0) && node->value.op == ADD)
        {
            node = node->right;

            DtorSimplyNode(node->left);
        }
        else if(node->right->type == NUM && CompareNum(node->right->value.num, 0) && node->value.op == ADD)
        {
            node = node->left;

            DtorSimplyNode(node->right);
        }

    }

    return node;
}

int CompareNum(double val_1, double val_2)
{
    if(fabs(val_1 - val_2) < EPS) return 1;

    return 0;
}

void DtorSimplyNode(Node_t* node)
{
    assert(node);

    Dtor(node->left);
    Dtor(node->right);

    node->left = NULL;
    node->right = NULL;
}
