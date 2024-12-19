#include "Diff.h"

Node_t* DiffExpression(Node_t* node, Node_t* diff, FILE* tex_file, int* count_phrase)
{
    assert(tex_file);
    assert(count_phrase);

    //GraphicDump(node, argv);
    //TexDump(node, diff, tex_file, count_phrase);
    if(node->type == NUM)
    {
        //TexDump(node, NUM_(0), tex_file, count_phrase);
        return NUM_(0);
    }

    if(node->type == VAR)
    {
        //TexDump(node, NUM_(1), tex_file, count_phrase);
        return NUM_(1);
    }

    if(node->type == OP)
    {
        switch(node->value.op)
        {
            case ADD:
            {
                //TexDump(node, ADD_(DIFF_(node->left), DIFF_(node->right)), tex_file, count_phrase);
                return ADD_(DIFF_(node->left), DIFF_(node->right));
            }
            case SUB:
            {
                //TexDump(node, SUB_(DIFF_(node->left), DIFF_(node->right)), tex_file, count_phrase);
                return SUB_(DIFF_(node->left), DIFF_(node->right));
            }
            case MUL:
            {
                Node_t* dl_mul = DIFF_(node->left);
                Node_t* dr_mul = DIFF_(node->right);

                Node_t* copy_left_mul  = Copy(node->left);
                Node_t* copy_right_mul = Copy(node->right);

                //TexDump(node, ADD_(MUL_(dl_mul, copy_right_mul), MUL_(dr_mul, copy_left_mul)), tex_file, count_phrase);

                return ADD_(MUL_(dl_mul, copy_right_mul), MUL_(dr_mul, copy_left_mul));
            }
            case DIV:
            {
                Node_t* dl_div = DIFF_(node->left);
                Node_t* dr_div = DIFF_(node->right);

                Node_t* copy_left_div  = Copy(node->left);
                Node_t* copy_right_div = Copy(node->right);

                //TexDump(node, DIV_(SUB_(MUL_(dl_div, copy_right_div), MUL_(dr_div, copy_left_div)), POW_(copy_right_div, 2)), tex_file, count_phrase);

                return DIV_(SUB_(MUL_(dl_div, copy_right_div), MUL_(dr_div, copy_left_div)), POW_(copy_right_div, 2));
            }
            case POW:
            {
                //TexDump(node, MUL_(Copy(node), DIFF_(MUL_(LN_(node->left), Copy(node->right)))), tex_file, count_phrase);

                return MUL_(Copy(node), DIFF_(MUL_(LN_(node->left), Copy(node->right))));
            }
            case SIN:
            {
                //TexDump(node, MUL_(NUM_(1), MUL_(COS_(Copy(node->right)), DIFF_(node->right))), tex_file, count_phrase);

                return MUL_(NUM_(1), MUL_(COS_(Copy(node->right)), DIFF_(node->right)));
            }
            case COS:
            {
                //TexDump(node, MUL_(NUM_(-1), MUL_(SIN_(Copy(node->right)), DIFF_(node->right))), tex_file, count_phrase);

                return MUL_(NUM_(-1), MUL_(SIN_(Copy(node->right)), DIFF_(node->right)));
            }
            case TG:
            {
                //TexDump(node, MUL_(DIV_(NUM_(1), POW_(COS_(Copy(node->right)), 2)), DIFF_(node->right)), tex_file, count_phrase);

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
                //TexDump(node, MUL_(DIV_(NUM_(1), Copy(node->right)), DIFF_(node->right)), tex_file, count_phrase);

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
            case TH:
            {
                return MUL_(DIV_(NUM_(1), POW_(CH_(node->right), 2)), DIFF_(node->right));
            }
            case CTH:
            {
                return MUL_(DIV_(NUM_(1), POW_(SH_(node->right), 2)), DIFF_(node->right));
            }
            case ARCSIN:
            {
                return MUL_(DIV_(NUM_(1), POW_(SUB_(NUM_(1), POW_(Copy(node->right), 2)), 0.5)), DIFF_(node->right));
            }
            case ARCCOS:
            {
                return MUL_(DIV_(NUM_(-1), POW_(SUB_(NUM_(1), POW_(Copy(node->right), 2)), 0.5)), DIFF_(node->right));
            }
            case ARCTG:
            {
                return MUL_(DIV_(NUM_(1), ADD_(NUM_(1), POW_(Copy(node->right), 2))), DIFF_(node->right));
            }
            case ARCCTG:
            {
                return MUL_(DIV_(NUM_(-1), ADD_(NUM_(1), POW_(Copy(node->right), 2))), DIFF_(node->right));
            }
            case ARCSH:
            {
                return MUL_(DIV_(NUM_(1), POW_(ADD_(POW_(Copy(node->right), 2), NUM_(1)), 0.5)), DIFF_(node->right));
            }
            case ARCCH:
            {
                return MUL_(DIV_(NUM_(1), POW_(SUB_(POW_(Copy(node->right), 2), NUM_(1)), 0.5)), DIFF_(node->right));
            }
            case ARCTH:
            {
                return MUL_(DIV_(NUM_(1), SUB_(NUM_(1), POW_(Copy(node->right), 2))), DIFF_(node->right));
            }
            case ARCCTH:
            {
                return MUL_(DIV_(NUM_(1), SUB_(NUM_(1), POW_(Copy(node->right), 2))), DIFF_(node->right));
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
