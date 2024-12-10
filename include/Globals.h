#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <sys\stat.h>
#include <ctype.h>

const int MAX_OP_LEN = 5;

union NodeValue
{
    double num;
    int    var_num;
    int    op;
};

struct Node_t
{
    int       type;
    NodeValue value;
    Node_t*   left;
    Node_t*   right;
};

struct Token_t
{
    Node_t* str;
    int     point;
    int     count;
};

enum Operation
{
    ADD     = 1,
    SUB     = 2,
    DIV     = 3,
    MUL     = 4,
    POW     = 5,
    SIN     = 6,
    COS     = 7,
    TG      = 8,
    CTG     = 9,
    LOG     = 10,
    EXP     = 11,
    EXP_F   = 12,
    SH      = 13,
    CH      = 14,
    TH      = 15,
    CTH     = 16,
    ARCSIN  = 17,
    ARCCOS  = 18,
    ARCTG   = 19,
    ARCCTG  = 20,
    LN      = 21,
    ARCSH   = 22,
    ARCCH   = 23,
    ARCTH   = 24,
    ARCCTH  = 25
};

enum Lexis
{
    END_OF_EXPRESSION = 97,
    OPEN_BRACKETS     = 98,
    CLOSE_BRACKETS    = 99
};

enum Type
{
    OP  = 1,
    NUM = 2,
    VAR = 3
};

enum Arg
{
    X = 1
};

#define NUM_(number)                                           \
    MakeNode(NUM, NodeValue{.num = number}, NULL, NULL)

#define ADD_(left, right)                                      \
    MakeNode(OP, NodeValue{.op = ADD}, left, right)

#define SUB_(left, right)                               \
    MakeNode(OP, NodeValue{.op = SUB}, left, right)

#define MUL_(left, right)                               \
    MakeNode(OP, NodeValue{.op = MUL}, left, right)

#define DIV_(left, right)                                \
    MakeNode(OP, NodeValue{.op = DIV}, left, right)

#define POW_(left, number)                                                     \
    MakeNode(OP, NodeValue{.op = POW}, left, MakeNode(NUM, NodeValue{.num = number}, NULL, NULL))

#define DIFF_(node)         \
    DiffExpression(node, diff, argv)


#endif
