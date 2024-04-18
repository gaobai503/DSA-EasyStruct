#pragma once
#ifndef TREE_H
#define TREE_H
#include "Link.h"

typedef struct DATATYPE datatype;
typedef struct NODE node;
typedef struct LINK link;
typedef link stack;
typedef node *position;
typedef struct QUEUE *queue;

struct BTREE{
    struct BTREE *lchild;
    struct BTREE *rchild;
    void *data;
    datatype type;
};

typedef struct BTREE *btree;

struct TagBtree{
    btree bt;
    int flag;
};

int EmptyBtree(btree bt);
int IsComTree(btree bt);

unsigned BtreeWidth(btree bt);

void *Data(btree bt);

btree MakeNullBtree(datatype type);
btree BtreeCreate(void *data, datatype type, btree lchild, btree rchild);
btree PreCreBtree(void *dataset, unsigned n, datatype type);
btree Lchild(btree bt);
btree Rchild(btree bt);

void PreOrder(btree bt, stack S, void visit(btree, stack));
void PreOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void InOrder(btree bt, stack S, void (*visit)(btree, stack));
void InOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void PostOrder(btree bt, stack S, void (*visit)(btree, stack));
void PostOrderRec(btree bt, stack S, void (*visit)(btree, stack));
void LevelOrder(btree bt, stack S, void (*visit)(btree, stack));

#endif //!TREE_H
