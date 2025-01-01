#include "Diff.h"

Node_t* DiffExpression(Node_t* node, Node_t* diff, FILE* tex_file, int* count_phrase)
{
    assert(tex_file);
    assert(count_phrase);

    //GraphicDump(node, argv);
    //TexDump(node, diff, tex_file, count_phrase);
    if(node->type == NUM)
    {
        Node_t* diff_num = NUM_(0);

        TexDump(node, diff_num, tex_file, count_phrase);
        return diff_num;
    }

    if(node->type == VAR)
    {
        Node_t* diff_var = NUM_(1);

        TexDump(node, diff_var, tex_file, count_phrase);
        return diff_var;
    }

    if(node->type == OP)
    {
        switch(node->value.op)
        {
            case ADD:
            {
                Node_t* diff_add = ADD_(DIFF_(node->left), DIFF_(node->right));

                TexDump(node, diff_add, tex_file, count_phrase);
                return diff_add;
            }
            case SUB:
            {
                Node_t* diff_sub = SUB_(DIFF_(node->left), DIFF_(node->right));

                TexDump(node, diff_sub, tex_file, count_phrase);
                return diff_sub;
            }
            case MUL:
            {
                Node_t* dl_mul = DIFF_(node->left);
                Node_t* dr_mul = DIFF_(node->right);

                Node_t* copy_left_mul  = Copy(node->left);
                Node_t* copy_right_mul = Copy(node->right);

                Node_t* diff_mul = ADD_(MUL_(dl_mul, copy_right_mul), MUL_(dr_mul, copy_left_mul));

                TexDump(node, diff_mul, tex_file, count_phrase);
                return diff_mul;
            }
            case DIV:
            {
                Node_t* dl_div = DIFF_(node->left);
                Node_t* dr_div = DIFF_(node->right);

                Node_t* copy_left_div  = Copy(node->left);
                Node_t* copy_right_div = Copy(node->right);

                Node_t* diff_div = DIV_(SUB_(MUL_(dl_div, copy_right_div), MUL_(dr_div, copy_left_div)), POW_(copy_right_div, 2));

                TexDump(node, diff_div, tex_file, count_phrase);
                return diff_div;
            }
            case POW:
            {
                Node_t* diff_pow = MUL_(Copy(node), DIFF_(MUL_(LN_(node->left), Copy(node->right))));

                TexDump(node, diff_pow, tex_file, count_phrase);
                return diff_pow;
            }
            case SIN:
            {
                Node_t* diff_sin = MUL_(NUM_(1), MUL_(COS_(Copy(node->right)), DIFF_(node->right)));

                TexDump(node, diff_sin, tex_file, count_phrase);
                return diff_sin;
            }
            case COS:
            {
                Node_t* diff_cos = MUL_(NUM_(-1), MUL_(SIN_(Copy(node->right)), DIFF_(node->right)));

                TexDump(node, diff_cos, tex_file, count_phrase);
                return diff_cos;
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
                Node_t* diff_ln = MUL_(DIV_(NUM_(1), Copy(node->right)), DIFF_(node->right));

                TexDump(node, diff_ln, tex_file, count_phrase);
                return diff_ln;
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
