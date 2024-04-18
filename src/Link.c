#include <string.h>
#include <stdlib.h>
#include "Link.h"

link MakeNullLink(datatype type){
    position p = (position)malloc(sizeof(struct NODE));
    link Emp = {NULL, type};
    if(p == NULL){
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
    if(q == NULL){
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
    if(p->next==NULL) return 1;
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
    if(p->next == NULL)
    {
	/*Empty link*/
	return NULL;
    }
    while(p->next->next != NULL) p=p->next;
    return p;
}

stack MakeNullStack(datatype type){
    position p = (position)malloc(sizeof(struct NODE));
    stack Emp = {NULL, type};
    if(p == NULL){
	return Emp;
    }
    p->data = NULL;
    p->next = NULL;
    stack S = {p, type};
    return S;
}

int Pop(stack S){
    if(EmptyStack(S)) return 1;
    return Delete(S, First(S));;
}

int Push(stack S, void *data){
    return Insert(S, First(S), data);
}

int EmptyStack(stack S){
    if(End(S) == NULL) return 1;
    return 0;
}

int FreeStack(stack S){
    while(!EmptyStack(S)){
	Pop(S);
    }
    return 0;
}

void *Topelement(stack S){
    return Retrieve(S, First(S));
}

queue MakeNullQueue(datatype type){
    position N = (position)malloc(sizeof(node));
    N->data = NULL;
    N->next = NULL;
    queue Q = (queue)malloc(sizeof(struct QUEUE));
    Q->front = N;
    Q->rear = NULL;
    Q->type = type;
    return Q;
}

int EnQueue(queue Q, void *data){
    if(!Q) return -1;
    link L = {Q->front, Q->type};
    if(!Q->rear){
	Insert(L, First(L), data);
	Q->rear = Q->front;
	return 0;
    }
    Insert(L, Next(L, Q->rear), data);
    Q->rear = Next(L, Q->rear);
    return 0;
}

int DeQueue(queue Q){
    if(!Q) return -1;
    if(EmptyQueue(Q)) return 1;
    link L = {Q->front, Q->type};
    Delete(L, First(L));
    if(Q->rear == Q->front){
	Q->rear = NULL;
	return 0;
    }
    Q->rear = End(L);
    return 0;
}

int EmptyQueue(queue Q){
    if(!Q->rear) return 1;
    return 0;
}

void *Front(queue Q){
    if(!Q) return NULL;
    link L = {Q->front, Q->type};
    return Retrieve(L, First(L));
}

int FreeQueue(queue Q){
    if(!Q) return -1;
    while(!EmptyQueue(Q)){
	DeQueue(Q);
    }
    return 0;
}
