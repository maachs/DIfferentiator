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
                Node_t* dl_mul = DIFF_(node->left);
                Node_t* dr_mul = DIFF_(node->right);

                Node_t* copy_left_mul  = Copy(node->left);
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
                return MUL_(Copy(node), DIFF_(MUL_(LN_(node->left), Copy(node->right))));
            }
            case SIN:
            {
                return MUL_(NUM_(1), MUL_(COS_(Copy(node->right)), DIFF_(node->right)));
            }
            case COS:
            {
                return MUL_(NUM_(-1), MUL_(SIN_(Copy(node->right)), DIFF_(node->right)));
            }
            case TG:
            {
                return MUL_(DIV_(NUM_(1), POW_(COS_(Copy(node->right)), 2)), DIFF_(node->right));
            }
            case CTG:
            {
                return MUL_(DIV_(NUM_(-1), POW_(SIN_(Copy(node->right)), 2)), DIFF_(node->right));
            }
            case LOG:
            {
                return MUL_(DIV_(NUM_(1), MUL_(LN_(node->left), Copy(node->right))), DIFF_(node->right));
            }
            case LN:
            {
                return MUL_(DIV_(NUM_(1), Copy(node->right)), DIFF_(node->right));
            }
            case SH:
            {
                return MUL_(CH_(Copy(node->right)), DIFF_(node->right));
            }
            case CH:
            {
                return MUL_(SH_(Copy(node->right)), DIFF_(node->right));
            }
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
