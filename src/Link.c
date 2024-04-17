#include <string.h>
#include <stdlib.h>
#include "Link.h"

link MakeNullLink(datatype type){
    position p = (position)malloc(sizeof(struct NODE));
    link Emp = {NULL, type};
    if(!p){
	return Emp;
    }
    p->data = NULL;
    p->next = NULL;
    link L = {p, type};
    return L;
}

int Insert(link L, position p, void *data){
    position q = NULL;
    q = (position)malloc(sizeof(struct NODE));
    q->data = malloc(sizeof(void *));
    if(!q){
	return 1;
    }
    q->next = p->next;
    q->data = memcpy(q->data, data, L.type.size);
    unsigned pointers = L.type.pointer_count;
    size_t *size = L.type.pointer_size;
    void **strdata = (void **)data;
    for(int i=0; i<pointers; i++){
	void *temp = malloc(sizeof(size[i]));
	memcpy(temp, strdata[i], size[i]);
	((void**)q->data)[i] = temp;
    }
    p->next = q;
    return 0;
}

int Delete(link L, position p){
    if(IsEOL(L, p)) 
	/* 不是合理的逻辑位置(EOL)*/
	return -1;
    position q = p->next;
    p->next = p->next->next;
    unsigned pointers = L.type.pointer_count;
    void **pointer = (void **)(q->data);
    for(unsigned i=0; i<pointers; i++){
	free(*pointer);
	*pointer = NULL;
	pointer++;
    }
    free(q);
    return 0;
}

int IsEOL(link L, position p){
    if(!p->next) return 1;
    return 0;
}

int EmptyLink(link L){
    if(L.addr->next){
	return 0;
    } 
    return 1;
}

int FreeLink(link L){
    while(!EmptyLink(L)){
	Delete(L, L.addr);
    }
    return 0;
}

void *Retrieve(link L, position p){
    if(!IsEOL(L, p)) return p->next->data;
    /* 非法位置 */
    return NULL;
}

position Next(link L, position p){
    if(!p) return L.addr;
    return p->next;
    /* if(p == EOL) return NULL;*/
}

position Previous(link L, position p){
    position q = First(L);
    if(p == q) 
	/* 无前趋元素 */
	return NULL;
    while(!IsEOL(L, q)){
	if(Next(L, q) == p){
	    return q;
	}
	q = Next(L, q);
    }
    /* 到达了EOL */
    return NULL;
}

position First(link L){
    return L.addr;
}
position End(link L){
    position p = L.addr;
    if(!p->next)
    {
	/*Empty link*/
	return NULL;
    }
    while(p->next->next) p=p->next;
    return p;
}
