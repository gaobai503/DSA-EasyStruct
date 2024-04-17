#pragma once
#ifndef LINK_H
#define LINK_H
#define MAX_POINTER
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

typedef struct DATATYPE datatype;
typedef struct NODE node;
typedef struct LINK link;
typedef node *position;

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

#endif // !LINK_H
