#include "ReadExpression.h"
#include "Constructor.h"

int ReadExpression(Token_t* token, const char** argv, int size)
{
    FILE* file_ptr = fopen(argv[1], "rb");

    token->str =       (Node_t*) calloc(size, sizeof(Node_t));
    char* expression = (char*)   calloc(size, sizeof(char));

    if(file_ptr == NULL)
    {
        printf("cannot open file\n");
        return -1;
    }
    if(token->str == NULL || expression == NULL)
    {
        printf("calloc error\n");
        return -1;
    }

    fread(expression, sizeof(char), size, file_ptr);

    FillNodes(token, expression, size);

    token->point = 0;

    return 0;
}

int FillNodes(Token_t* token, char* expression, int size)
{
    assert(token);
    assert(expression);

    while(token->point < size)
    {
        while(expression[token->point] == ' ')
        {
            token->point++;
        }
        if(isdigit(expression[token->point]))
        {
            double val_num = 0;
            int count = 0;

            sscanf(&expression[token->point], "%lg%n", &val_num, &count);
            token->point += count;

            token->str[token->count].type = NUM;
            token->str[token->count].value.num = val_num;
            token->str[token->count].left = NULL;
            token->str[token->count].right = NULL;

            token->count++;
        }
        if(expression[token->point] == 'x')
        {
            token->str[token->count].type = VAR;
            token->str[token->count].value.var_num = X;
            token->str[token->count].left = NULL;
            token->str[token->count].right = NULL;

            token->count++;
            token->point++;
        }
        if(expression[token->point] == '(')
        {
            NEW_FUNC_(OPEN_BRACKETS , 1);
        }
        if(expression[token->point] == ')')
        {
            NEW_FUNC_(CLOSE_BRACKETS, 1);
        }
        FillOperation(token, expression);
        FillFunction(token, expression);

        if(expression[token->point] == '$')
        {
            NEW_FUNC_(END_OF_EXPRESSION, 1);
            return 0;
        }
    }
    return 0;
}

int FillFunction(Token_t* token, char* expression)
{
    if(expression[token->point] == 's' && expression[token->point + 1] == 'i' && expression[token->point + 2] == 'n')
    {
        NEW_FUNC_(SIN, 3);
    }
    else if(expression[token->point] == 'c' && expression[token->point + 1] == 'o' && expression[token->point + 2] == 's')
    {
        NEW_FUNC_(COS, 3);
    }
    else if(expression[token->point] == 't' && expression[token->point + 1] == 'g')
    {
        NEW_FUNC_(TG, 2);
    }
    else if(expression[token->point] == 'c' && expression[token->point + 1] == 't' && expression[token->point + 2] == 'g')
    {
        NEW_FUNC_(CTG, 3);
    }
    else if(expression[token->point] == 'a' && expression[token->point + 1] == 'r' && expression[token->point + 2] == 'c')
    {
        if(expression[token->point + 3] == 's' && expression[token->point + 4] == 'i' && expression[token->point + 5] == 'n')
        {
            NEW_FUNC_(ARCSIN, 6);
        }
        else if(expression[token->point + 3] == 'c' && expression[token->point + 4] == 'o' && expression[token->point + 5] == 's')
        {
            NEW_FUNC_(ARCCOS, 6);
        }
        else if(expression[token->point + 3] == 't' && expression[token->point + 4] == 'g')
        {
            NEW_FUNC_(ARCTG, 5);
        }
        else if(expression[token->point + 3] == 'c' && expression[token->point + 4] == 't' && expression[token->point + 5] == 'g')
        {
            NEW_FUNC_(ARCCTG, 6);
        }
        else if(expression[token->point + 3] == 't' && expression[token->point + 4] == 'h')
        {
            NEW_FUNC_(ARCTH, 5);
        }
        else if(expression[token->point + 3] == 's' && expression[token->point + 4] == 'h')
        {
            NEW_FUNC_(ARCSH, 5);
        }
        else if(expression[token->point + 3] == 'c' && expression[token->point + 4] == 'h')
        {
            NEW_FUNC_(ARCCH, 5);
        }
        else if(expression[token->point + 3] == 'c' && expression[token->point + 4] == 't' && expression[token->point + 5] == 'h')
        {
            NEW_FUNC_(ARCCTH, 6);
        }
    }
    else if(expression[token->point] == 'l' && expression[token->point + 1] == 'o' && expression[token->point + 2] == 'g')
    {
        NEW_FUNC_(LOG, 3);
    }
    else if(expression[token->point] == 'l' && expression[token->point + 1] == 'n')
    {
        NEW_FUNC_(LN, 2);
    }
    else if(expression[token->point] == 's' && expression[token->point + 1] == 'h')
    {
        NEW_FUNC_(SH, 2);
    }
    else if(expression[token->point] == 'c' && expression[token->point + 1] == 'h')
    {
        NEW_FUNC_(CH, 2);
    }
    else if(expression[token->point] == 't' && expression[token->point + 1] == 'h')
    {
        NEW_FUNC_(TH, 2);
    }
    else if(expression[token->point] == 'c' && expression[token->point + 1] == 't' && expression[token->point + 2] == 'h')
    {
        NEW_FUNC_(CTH, 3);
    }
    return 0;
}

int FillOperation(Token_t* token, char* expression)
{
    if(expression[token->point] == '+')
    {
        NEW_FUNC_(ADD, 1);
    }
    else if(expression[token->point] == '-')
    {
        NEW_FUNC_(SUB, 1);
    }
    else if(expression[token->point] == '*')
    {
        NEW_FUNC_(MUL, 1);
    }
    else if(expression[token->point] == '/')
    {
        NEW_FUNC_(DIV, 1);
    }
    else if(expression[token->point] == '^')
    {
        NEW_FUNC_(POW, 1);
    }

    return 0;
}

Node_t* GetGrammar(Token_t* token)
{
    Node_t* val = GetEquation(token);

    if(token->str[token->point].value.op != END_OF_EXPRESSION)
    {
        printf("error: expected $\n");
        exit(0);
    }

    return val;
}

Node_t* GetEquation(Token_t* token)
{
    Node_t* val = GetMulDiv(token);

    while(token->str[token->point].value.op == ADD || token->str[token->point].value.op == SUB)
    {
        int op = token->str[token->point].value.op;

        token->point++;

        Node_t* val_1 = GetMulDiv(token);

        if(op == ADD)
        {
            val = MakeNode(OP, NodeValue{.op = ADD}, val, val_1);
        }
        if(op == SUB)
        {
            val = MakeNode(OP, NodeValue{.op = SUB}, val, val_1);
        }
    }

    return val;
}

Node_t* GetMulDiv(Token_t* token)
{
    Node_t* val = GetDeg(token);

    while(token->str[token->point].value.op == MUL || token->str[token->point].value.op == DIV)
    {
        int op = token->str[token->point].value.op;

        token->point++;

        Node_t* val_1 = GetDeg(token);

        if(op == MUL)
        {
            val = MakeNode(OP, NodeValue{.op = MUL}, val, val_1);
        }
        if(op == DIV)
        {
            val = MakeNode(OP, NodeValue{.op = DIV}, val, val_1);
        }
    }

    return val;
}

Node_t* GetDeg(Token_t* token)
{
    Node_t* val = GetBrackets(token);

    while(token->str[token->point].value.op == POW)
    {
        int op_pow = token->str[token->point].value.op;

        token->point++;

        Node_t* val_1 = GetBrackets(token);

        if(op_pow == POW)
        {
            val = MakeNode(OP, NodeValue{.op = POW}, val, val_1);
        }
    }
    return val;
}

Node_t* GetFunc(Token_t* token)
{
    Node_t* val = NULL;
    int oper = 0;

    if(COMP_FUNC(SIN)   || COMP_FUNC(COS)    || COMP_FUNC(TG)   || COMP_FUNC(CTG)    || COMP_FUNC(ARCSIN) || COMP_FUNC(ARCCOS) ||
       COMP_FUNC(ARCTG) || COMP_FUNC(ARCCTG) || COMP_FUNC(SH)   || COMP_FUNC(CH)     || COMP_FUNC(TH)     || COMP_FUNC(CTH) ||
       COMP_FUNC(ARCSH) || COMP_FUNC(ARCCH)  || COMP_FUNC(ARCTH)|| COMP_FUNC(ARCCTH) || COMP_FUNC(LOG)    || COMP_FUNC(LN))
    {
        oper = token->str[token->point].value.op;

        token->point++;

        Node_t* val_1 = GetBrackets(token);

        if(oper == LOG)
        {
            Node_t* val_2 = GetBrackets(token);

            val = MakeNode(OP, NodeValue{.op = LOG}, val_1, val_2);
        }
        else
        {
            val = MakeNode(OP, NodeValue{.op = oper}, MakeNode(NUM, NodeValue{.num = 0}, NULL, NULL), val_1);
        }
    }
    return val;
}

Node_t* GetBrackets(Token_t* token)
{
    if(token->str[token->point].value.op == OPEN_BRACKETS)
    {
        token->point++;

        Node_t* val = GetEquation(token);

        if(token->str[token->point].value.op != CLOSE_BRACKETS)
        {
            printf("cannot find close brackets\n");
            exit(0);
        }

        token->point++;

        return val;
    }
    else if(token->str[token->point].type == OP)
    {
        return GetFunc(token);
    }
    else if(token->str[token->point].type == VAR)
    {
        return GetVariable(token);
    }
    else
    {
        return GetNumber(token);
    }
}

Node_t* GetNumber(Token_t* token)
{
    double val = 0;

    int old_p = token->point;

    if(token->str[token->point].type == NUM)
    {
        val = token->str[token->point].value.num;
        token->point++;
    }

    if(token->point == old_p)
    {
        printf("GetN error: old_p = p\n");

        exit(0);
    }

    return MakeNode(NUM, NodeValue{.num = val}, NULL, NULL);
}

Node_t* GetVariable(Token_t* token)
{
    if(token->str[token->point].value.var_num == X)
    {
        token->point++;

        return MakeNode(VAR, NodeValue{.var_num = X}, NULL, NULL);
    }
    else
    {
        return NULL;
    }
}
