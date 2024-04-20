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

    printf("Compare: %d --- %d\n", ((unsigned*)src)[0], ((unsigned*)des)[0]);
    int flag = memcmp(src, des, H->key.keysize);
    printf("Return: (%d)\n", flag);
    return flag;
}

int Move(heap H, void *des, void *src){
    //if(counter == 12){
    //    printf("des: %p\nsrc: %p\n", des, src);
    //}
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
    if(!H->n){
	Move(H, H->data, data);
	H->n++;
	return 0;
    }
    unsigned i = 1;
    void *show;
    void *bt = Node(H, i);
    void *temp = data;
    for(int j=1; j<=H->n; j++){
	if(Node(H,j)!=NULL){
	    show = Data((btree)Node(H, j));
	    printf("Node(%d)---ch: %d, weight: %d\n", j,((char*)show)[0], ((unsigned*)show)[1]);
	}
	else{
	    printf("NULL when j == %d\n", j);
	    break;
	}
    }
    void *alt = malloc(size);
    while(bt != NULL){
	if(Compare(H, bt, temp)>0){
	    memcpy(alt, temp, size);
	    memcpy(temp, bt, size);
	    memcpy(bt, alt, size);
	}
	printf("--------->\n");
	show = Data((btree)bt);
	printf("bt---ch: %d, weight: %d\n",((char*)show)[0], ((unsigned*)show)[1]);
	show = Data((btree)temp);
	printf("temp---ch: %d, weight: %d\n",((char*)show)[0], ((unsigned*)show)[1]);
	if(2*i+1>H->n) break;
	i = Compare(H, Node(H, 2*i), Node(H, 2*i+1))?2*i:2*i+1;
	printf("Choose I: %d\n",i);
	//getchar();
	bt = Node(H, i);
	show = Data((btree)bt);
	printf("bt---ch: %d, weight: %d\n",((char*)show)[0], ((unsigned*)show)[1]);
	show = Data((btree)temp);
	printf("temp---ch: %d, weight: %d\n",((char*)show)[0], ((unsigned*)show)[1]);
    }
    free(alt);
    if(!bt) return -1;
    bt = Node(H, 2*i);
    if(2*i <= H->n) bt = Node(H, 2*i+1);
    //if(counter == 5)
    //{
//	printf("N: %d, I:%d\n", H->n, i);
	//printf("bt: %p\ntemp: %p\n", bt, temp);
    //}
    Move(H, bt, temp);
    //printf("HEllO!\n");
    H->n++;
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
    void *alt = bt;
    memcpy(bt, temp, size);
    memset(temp, 0, size);
    memcpy(temp, bt, size);
    H->n--;
    while(bt != NULL && (2*i+1)<=H->n){
	temp = Node(H, i);
	i = Compare(H, Node(H, 2*i), Node(H, 2*i+1))?2*i:2*i+1;
	bt = Node(H, i);
	if(Compare(H, bt, temp)>0){
	    memcpy(alt, temp, size);
	    memcpy(temp, bt, size);
	    memcpy(bt, alt, size);
	}
    }
    if(!bt) return -1;
    if(2*i>H->n) return 0;
    temp = Node(H, i);
    bt = Node(H, 2*i);
    if(Compare(H, bt, temp)>0){
	memcpy(alt, temp, size);
	memcpy(temp, bt, size);
	memcpy(bt, alt, size);
    }
    return 0;
}

void *Root(heap H){
    return Node(H, 1);
}

void *Node(heap H, unsigned p){
    //if(p > (H->n+2) || !p) return NULL;
    void *temp = (char *)(H->data) + H->type.size*(p-1);
    return temp;
}
