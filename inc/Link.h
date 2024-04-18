#pragma once
#ifndef LINK_H
#define LINK_H
#define MAX_POINTER
#include <stdio.h>
struct DATATYPE{
    size_t size;
    unsigned pointer_count;
    size_t *pointer_size;
};

struct NODE{
    void* data;
    struct NODE *next;
};

struct LINK{
    struct NODE *addr;
    struct DATATYPE type;
};

struct QUEUE{
    struct NODE *front;
    struct NODE *rear;
    struct DATATYPE type;
};

typedef struct DATATYPE datatype;
typedef struct NODE node;
typedef struct LINK link;
typedef link stack;
typedef node *position;
typedef struct QUEUE *queue;

link MakeNullLink(datatype type);

int Insert(link L, position p, void *data);
int Delete(link L, position p);
int IsEOL(link L, position p);
int EmptyLink(link L);
int FreeLink(link L);

void *Retrieve(link L, position p);

position Next(link L, position p);
position Previous(link L, position);
position First(link L);
position End(link L);

stack MakeNullStack(datatype type);

int Pop(stack S);
int Push(stack S, void *data);
int EmptyStack(stack S);
int FreeStack(stack S);
void *Topelement(stack S);

queue MakeNullQueue(datatype type);

int EnQueue(queue Q, void *data);
int DeQueue(queue Q);
int EmptyQueue(queue Q);
int FreeQueue(queue Q);
void *Front(queue Q);

#endif // !LINK_H
