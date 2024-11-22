#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node_t
{
    int     type;
    int     value;
    Node_t* left;
    Node_t* right;
    Node_t* parent;
};

enum Operation
{
    ADD   = 1,
    SUB   = 2,
    DIV   = 3,
    MUL   = 4,
    POW   = 5,
    SIN   = 6,
    COS   = 7,
    TG    = 8,
    CTG   = 9,
    LOG   = 10,
    EXP   = 11,
    EXP_F = 12
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

#endif
