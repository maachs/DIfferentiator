#include "Diff.h"

Node_t* Diff(Node_t* node, const char** argv)
{
    assert(node);

    GraphicDump(node, argv);

    if(node->type == NUM) return MakeNode(NUM, 0, NULL, NULL);

    if(node->type == VAR) return MakeNode(NUM, 1, NULL, NULL);

    if(node->type == OP)
    {
        switch(node->value)
        {
            case ADD:

                return MakeNode(OP, ADD, Diff(node->left, argv), Diff(node->right, argv));

            case SUB:

                return MakeNode(OP, DIV, Diff(node->left, argv), Diff(node->right, argv));

            case MUL:
            {
                Node_t* dl_mul = Diff(node->left, argv);
                Node_t* dr_mul = Diff(node->right, argv);

                Node_t* copy_left_mul  = MakeNode(node->left->type,  node->left->value,  node->left->left,  node->left->right);
                Node_t* copy_right_mul = MakeNode(node->right->type, node->right->value, node->right->left, node->right->right);

                return MakeNode(OP, ADD, MakeNode(OP, MUL, dl_mul, copy_right_mul),
                                         MakeNode(OP, MUL, copy_left_mul, dr_mul));
            }
            case DIV:
            {
                Node_t* dl_div = Diff(node->left, argv);
                Node_t* dr_div = Diff(node->right, argv);

                Node_t* copy_left_div  = MakeNode(node->left->type,  node->left->value,  node->left->left,  node->left->right);
                Node_t* copy_right_div = MakeNode(node->right->type, node->right->value, node->right->left, node->right->right);

                return MakeNode(OP, DIV, MakeNode(OP, SUB, MakeNode(OP, MUL, dl_div, copy_right_div), MakeNode(OP, MUL, copy_left_div, dr_div)),
                                         MakeNode(OP, POW, copy_right_div, MakeNode(NUM, 2, NULL, NULL)));
            }
            case POW:
            {
                return MakeNode(OP, MUL,
                       MakeNode(NUM, node->right->value, NULL, NULL),
                       MakeNode(OP, POW, MakeNode(VAR, 1, NULL, NULL), MakeNode(NUM, node->right->value - 1, NULL, NULL)));
            }
            case SIN:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, 1, NULL, NULL),
                                         MakeNode(OP, COS, Diff(node->left),
                                                           MakeNode(OP, COS, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right), NULL)));
            }
            case COS:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, -1, NULL, NULL),
                                         MakeNode(OP, MUL, Diff(node->left),
                                                           MakeNode(OP, SIN, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right), NULL)));
            }
            case TG:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, 1, NULL, NULL),
                                         MakeNode(OP, POW, MakeNode(OP, COS, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right)),
                                                           MakeNode(NUM, 2, NULL, NULL)));
            }
            case CTG:
            {
                return MakeNode(OP, MUL, MakeNode(NUM, -1, NULL, NULL),
                                         MakeNode(OP, POW, MakeNode(OP, SIN, MakeNode(node->left->type, node->left->value, node->left->left, node->left->right)),
                                                           MakeNode(NUM, 2, NULL, NULL)));
            }
            case LOG:
            {
                return MakeNode(OP, DIV, Diff(node->right),
                                         MakeNode(OP, MUL, MakeNode(OP, LOG, MakeNode(OP, EXP, NULL, NULL), node->left)
                                                           MakeNode(node->right->type, node->right->value, node->left, node->right)));
            }
            case EXP_F:
            {
                return MakeNode(OP, MUL, MakeNode(OP, LOG, MakeNode(OP, EXP, NULL, NULL), node->left),
                                         MakeNode(OP, MUL, MakeNode(node->type, node->value, node->left, node->right),
                                                           Diff(node->right)));
            }
            default:
                return NULL;
        }
    }

    return NULL;
}

