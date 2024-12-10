#include "Diff.h"

Node_t* DiffExpression(Node_t* node, Node_t* diff, const char** argv)
{
    assert(argv);

    //GraphicDump(node, argv);

    if(node->type == NUM)
    {
        //NUM_(0 ,12);

        return NUM_(0);
    }

    if(node->type == VAR)
    {
        return NUM_(1);
    }

    if(node->type == OP)
    {
        switch(node->value.op)
        {
            case ADD:
            {
                return ADD_(DIFF_(node->left), DIFF_(node->right));
            }
            case SUB:
            {
                return SUB_(DIFF_(node->left), DIFF_(node->right));
            }
            case MUL:
            {
                Node_t* dl_mul = DIFF_(node->left); // TODO DIFF_(left)
                Node_t* dr_mul = DIFF_(node->right);

                Node_t* copy_left_mul  = Copy(node->left); // TODO COPY(left)
                Node_t* copy_right_mul = Copy(node->right);

                return ADD_(MUL_(dl_mul, copy_right_mul), MUL_(dr_mul, copy_left_mul));
            }
            case DIV:
            {
                Node_t* dl_div = DIFF_(node->left);
                Node_t* dr_div = DIFF_(node->right);

                Node_t* copy_left_div  = Copy(node->left);
                Node_t* copy_right_div = Copy(node->right);

                return DIV_(SUB_(MUL_(dl_div, copy_right_div), MUL_(dr_div, copy_left_div)), POW_(copy_right_div, 2));
            }
            case POW:
            {
                return MUL_(Copy(node->right), POW_(Copy(node->left), node->right->value.num - 1));
            }
            /*case SIN:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, 1, NULL, NULL, diff),
                                         MakeNode(OP, MUL, MakeNode(OP, COS, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, node->left->parent), NULL, diff),
                                                           Diff(node->left, diff, argv), diff), diff);
            }
            case COS:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, -1, NULL, NULL, diff),
                                         MakeNode(OP, MUL, MakeNode(OP, SIN, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, node->left->parent), NULL, diff),
                                                           Diff(node->left, diff, argv), diff), diff);
            }
            case TG:
            {
                return MakeNode(OP, DIV, MakeNode(OP, MUL, MakeNode(NUM, 1, NULL, NULL, diff), Diff(node->left, diff, argv), diff),
                                         MakeNode(OP, POW, MakeNode(OP, COS, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, diff), NULL, diff),
                                                           MakeNode(NUM, 2, NULL, NULL, diff), diff), diff);
            }
            case CTG:
            {
                return MakeNode(OP, DIV, MakeNode(OP, MUL, MakeNode(NUM, -1, NULL, NULL, diff), Diff(node->left, diff, argv), diff),
                                         MakeNode(OP, POW, MakeNode(OP, SIN, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, diff), NULL, diff),
                                                           MakeNode(NUM, 2, NULL, NULL, diff), diff), diff);
            }
            case LOG:
            {
                return MakeNode(OP, DIV, Diff(node->right, diff, argv),
                                         MakeNode(OP, MUL, MakeNode(OP, LOG, MakeNode(OP, EXP, NULL, NULL, diff), node->left, diff),
                                                           MakeNode(node->right->type, node->right->value, node->left, node->right, diff), diff), diff);
            }
            case EXP_F:
            {
                return MakeNode(OP, MUL, MakeNode(OP, LOG, MakeNode(OP, EXP, NULL, NULL, diff), node->left, diff),
                                         MakeNode(OP, MUL, MakeNode(node->type, node->value, node->left, node->right, diff),
                                                           Diff(node->right, diff, argv), diff), diff);
            }
            case SH:
            {
                return MakeNode(OP, MUL, MakeNode(OP, CH, node->left, NULL, diff),
                                         Diff(node->left, diff, argv), diff);
            }
            case CH:
            {
                return MakeNode(OP, MUL, MakeNode(OP, SH, node->left, NULL, diff),
                                         Diff(node->left, diff, argv), diff);
            }
            case TH:
            {
                return MakeNode(OP, DIV, MakeNode(OP, MUL, MakeNode(NUM, 1, NULL, NULL, diff), Diff(node->left, diff, argv), diff),
                                         MakeNode(OP, POW, MakeNode(OP, CH, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, diff), NULL, diff),
                                                           MakeNode(NUM, 2, NULL, NULL, diff), diff), diff);
            }
            case CTH:
            {
                return MakeNode(OP, DIV, MakeNode(OP, MUL, MakeNode(NUM, -1, NULL, NULL, diff), Diff(node->left, diff, argv), diff),
                                         MakeNode(OP, POW, MakeNode(OP, SH, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right, diff), NULL, diff),
                                                           MakeNode(NUM, 2, NULL, NULL, diff), diff), diff);
            }*/
            default:
                printf("cannot defined operation %c\n", node->value.op);
                return NULL;
        }
    }

    return NULL;
}

Node_t* Copy(Node_t* node)
{
    if(node == NULL) return NULL;

    return MakeNode(node->type, node->value, Copy(node->left), Copy(node->right));
}
