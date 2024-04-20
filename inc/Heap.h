#pragma once
#ifndef HEAP_H
#define HEAP_H
#include "Link.h"
extern int counter;

struct FRECH{
    char ch;
    unsigned fre;
};

struct CMPKEY{
    size_t pokeyoffset;
    size_t keyoffset;
    size_t keysize;
};

struct HEAP{
    void *data;
    unsigned n;
    struct DATATYPE type;
    struct CMPKEY key;
    int flag;
};


typedef struct HEAP *heap;

typedef struct DATATYPE datatype;
typedef struct CMPKEY cmpkey;

heap MakeNullHeap(void *data, int flag, cmpkey key, datatype type);

int Compare(heap H, void *src, void *des);
int Move(heap H, void *des, void *src);

int Add(void *data, heap H);
int Remove(heap H);
void *Root(heap H);
void *Node(heap H, unsigned p);

#endif //!HEAP_H
