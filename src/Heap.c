#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Link.h"
#include "Heap.h"
#include "Tree.h"
int counter = 0;

heap MakeNullHeap(void *data, int flag, cmpkey key, datatype type){
    heap H = (heap)malloc(sizeof(struct HEAP));
    if(!H) return NULL;
    H->data = data;
    H->n = 0;
    H->flag = flag;
    H->key = key;
    H->type = type;
    return H;
}

int Compare(heap H, void *src, void *des){

    src = ((char **)src)[H->key.keyoffset];
    des = ((char **)des)[H->key.keyoffset];
    if(H->key.pokeyoffset>=0){
	src = (char *)src+H->key.pokeyoffset;
	des = (char *)des+H->key.pokeyoffset;
    }

    int flag = memcmp(src, des, H->key.keysize);
    return flag;
}

int Move(heap H, void *des, void *src){
    memcpy(des, src, H->type.size);
    unsigned pointers = H->type.pointer_count;
    size_t *size = H->type.pointer_size;
    void **strdata = (void**)src;
    for(int i=0; i<pointers; i++){
	void *temp = malloc(sizeof(size[i]));
	if(!temp) return 1;
	memcpy(temp, strdata[i], size[i]);
	((void**)des)[i] = temp;
    }
    return 0;
}

int Add(void *data, heap H){
    size_t size = H->type.size;
    H->n++;
    Move(H, Node(H, H->n), data);
    void *temp = Node(H, H->n);
    unsigned i = H->n / 2;
    void *bt = Node(H, i);
    void *alt = malloc(size);
    while(i!=0){
	if(Compare(H, bt, temp)>0){
	    memcpy(alt, temp, size);
	    memcpy(temp, bt, size);
	    memcpy(bt, alt, size); 
	}
	i = i / 2;
	temp = bt;
	bt = Node(H, i);
    }
    free(alt);
    return 0;
}

int Remove(heap H){
    size_t size = H->type.size;
    if(!H->n){
	return 1;
    }
    unsigned i = 1;
    void *bt = Node(H, 1);
    void *temp = Node(H, H->n);
    void *alt = malloc(size);
    memcpy(bt, temp, size);
    memset(temp, 0, size);
    H->n--;
    while(2*i<=H->n){
	i = 2*i;
	temp = Node(H, i);
	if(Compare(H, bt, temp)>0){
	    memcpy(alt, temp, size);
	    memcpy(temp, bt, size);
	    memcpy(bt, alt, size); 
	    bt = temp;
	}
	else if(i+1<=H->n){
	    i++;
	    temp = Node(H, i);
	    if(Compare(H, bt, temp)>0){
		memcpy(alt, temp, size);
		memcpy(temp, bt, size);
		memcpy(bt, alt, size); 
		bt = temp;
	    }
	    else break;
	}
	else break;
    }
    return 0;
}

void *Root(heap H){
    return Node(H, 1);
}

void *Node(heap H, unsigned p){
    if(p > (H->n+1) || !p) return NULL;
    void *temp = (char *)(H->data) + H->type.size*(p-1);
    return temp;
}
