#include "ReadExpression.h"
#include "Constructor.h"

int ReadExpression(Read* read, const char** argv, int size)
{
    FILE* file_ptr = fopen(argv[1], "rb");

    read->str = (char*) calloc(size, sizeof(char));

    if(file_ptr == NULL)
    {
        printf("cannot open file\n");

        return -1;
    }

    fread(read->str, sizeof(char), size, file_ptr);

    return 0;
}

Node_t* GetG(Read* read)
{
    Node_t* val = GetE(read);

    if(read->str[read->point] != '$')
    {
        printf("expected $\n");
        exit(0);
    }

    return val;
}

Node_t* GetE(Read* read)
{
    Node_t* val = GetT(read);

    while(read->str[read->point] == '+' || read->str[read->point] == '-')
    {
        int op = read->str[read->point];

        read->point++;

        Node_t* val_1 = GetT(read);

        if(op == '+')
        {
            NodeValue node_add = {};
            node_add.op = ADD;

            val = MakeNode(OP, node_add, val, val_1);
        }
        if(op == '-')
        {
            NodeValue node_sub = {};
            node_sub.op = SUB;

            val = MakeNode(OP, node_sub, val, val_1);
        }
    }

    return val;
}

Node_t* GetT(Read* read)
{
    Node_t* val = GetD(read);

    while(read->str[read->point] == '*' || read->str[read->point] == '/')
    {
        int op = read->str[read->point];

        read->point++;

        Node_t* val_1 = GetD(read);

        if(op == '*')
        {
            NodeValue node_mul = {};
            node_mul.op = MUL;

            val = MakeNode(OP, node_mul, val, val_1);
        }
        if(op == '/')
        {
            NodeValue node_div = {};
            node_div.op = DIV;

            val = MakeNode(OP, node_div, val,val_1);
        }
    }

    return val;
}

Node_t* GetD(Read* read)
{
    Node_t* val = GetP(read);

    while(read->str[read->point] == '^')
    {
        int op = read->str[read->point];

        read->point++;

        Node_t* val_1 = GetP(read);

        if(op == '^')
        {
            NodeValue node_pow = {};
            node_pow.op = POW;

            val = MakeNode(OP, node_pow, val, val_1);
        }
    }

    return val;
}

Node_t* GetP(Read* read)
{
    if(read->str[read->point] == '(')
    {
        read->point++;

        Node_t* val = GetE(read);

        if(read->str[read->point] != ')')
        {
            printf("cannot find close brackets\n");

            exit(0);
        }

        read->point++;

        return val;
    }
    else if(read->str[read->point] == 'x')
    {
        return GetV(read);
    }
    else
    {
        return GetN(read);
    }
}

Node_t* GetN(Read* read)
{
    double val = 0;
    int old_p = read->point;

    while('0' <= read->str[read->point] && read->str[read->point] <= '9')
    {
        val = val * 10 + read->str[read->point] - '0';

        read->point++;
    }

    if(read->point == old_p)
    {
        printf("GetN error: old_p = p\n");

        exit(0);
    }
    NodeValue node_num = {};
    node_num.num = val;



    return MakeNode(NUM, node_num, NULL, NULL);
}

Node_t* GetV(Read* read)
{
    if(read->str[read->point] == 'x')
    {
        NodeValue node_var = {};
        node_var.var_num = X;

        read->point++;

        return MakeNode(VAR, node_var, NULL, NULL);
    }
    else
    {
        return NULL;
    }
}
