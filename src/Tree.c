#include <string.h>
#include <stdlib.h>
#include "Link.h"
#include "Tree.h"

int EmptyBtree(btree bt){
    if(!bt){
	return -1;
    }
    if((bt->data)!=NULL)
    {
	return 0;
    }
    return 1;
}

int IsComTree(btree bt){
    if(!bt){
	return -1;
    }
    struct TagBtree temp = {bt, 0};
    datatype type = {sizeof(struct TagBtree), 0, NULL};
    queue Q = MakeNullQueue(type);
    EnQueue(Q, &temp);
    while(!EmptyBtree(((struct TagBtree*)Front(Q))->bt) && !EmptyQueue(Q)){
	temp.bt = Lchild(((struct TagBtree*)Front(Q))->bt);
	EnQueue(Q, &temp);
	temp.bt = Rchild(((struct TagBtree*)Front(Q))->bt);
	EnQueue(Q, &temp);
	DeQueue(Q);
    }
    while(!EmptyQueue(Q)){
	if(!EmptyBtree(((struct TagBtree*)Front(Q))->bt)) return 0;
	DeQueue(Q);
    }
    return 1;
}

unsigned BtreeWidth(btree bt){
    struct TagBtree temp = {bt, 1};
    datatype type = {sizeof(struct TagBtree), 0, NULL};
    unsigned record_height = 1;
    unsigned counter = 0;
    unsigned width = 0;
    queue Q = MakeNullQueue(type);
    EnQueue(Q, &temp);
    while(!EmptyQueue(Q)){
	if(!EmptyBtree(((struct TagBtree*)Front(Q))->bt)){
	    temp.bt = Lchild(((struct TagBtree*)Front(Q))->bt);
	    temp.flag = ((struct TagBtree*)Front(Q))->flag+1;
	    EnQueue(Q, &temp);
	    temp.bt = Rchild(((struct TagBtree*)Front(Q))->bt);
	    temp.flag = ((struct TagBtree*)Front(Q))->flag+1;
	    EnQueue(Q, &temp);
	    if(((struct TagBtree*)Front(Q))->flag!=record_height){
		record_height = ((struct TagBtree*)Front(Q))->flag;
		if(counter > width) width = counter;
		counter = 0;
	    }
	    counter++;
	}
	DeQueue(Q);
    }
    return width>counter?width:counter;
}

void *Data(btree bt){
    if(!bt){
	return NULL;
    }
    return bt->data;
}

btree MakeNullBtree(datatype type){
    btree bt = (struct BTREE*)malloc(sizeof(struct BTREE));
    if(!bt){
	return NULL;
    }
    bt->data = NULL;
    bt->lchild = NULL;
    bt->rchild = NULL;
    bt->type = type;
    return bt;
}

btree BtreeCreate(void *data, datatype type, btree lchild, btree rchild){
    btree bt = (btree)malloc(sizeof(struct BTREE));
    if(!bt){
	return NULL;
    }
    bt->data = data;
    unsigned pointers = type.pointer_count;
    size_t *size = type.pointer_size;
    void **strdata = (void **)data;
    for(int i=0; i<pointers; i++){
	void *temp = malloc(sizeof(size[i]));
	memcpy(temp, strdata[i], size[i]);
	((void**)bt->data)[i] = temp;
    }
    bt->lchild = lchild;
    bt->rchild = rchild;
    bt->type = type;
    return bt;
}

btree PreCreBtree(void *dataset, unsigned n, datatype type){
    datatype TagBtree = {sizeof(struct TagBtree), 0, NULL};
    stack S = MakeNullStack(TagBtree);

    struct TagBtree bt = {MakeNullBtree(type), 0};
    struct TagBtree temp = {MakeNullBtree(type), 0};

    void *Emp = malloc(type.size);
    memset(Emp, 0, type.size);

    for(int i=0; i<n; i++){
	if(!memcmp(dataset, Emp, type.size)){
	    bt = *(struct TagBtree*)Topelement(S);
	    Pop(S);
	    if(!bt.flag){
		bt.flag=1;
		Push(S, &bt);
	    }
	    else{
		while(!EmptyStack(S) && ((struct TagBtree*)Topelement(S))->flag){
		    temp = *(struct TagBtree*)Topelement(S);
		    Pop(S);
		    temp.bt->rchild = bt.bt;
		    bt = temp;
		}
		if(!EmptyStack(S)){
		    temp = *(struct TagBtree*)Topelement(S);
		    Pop(S);
		    temp.bt->lchild = bt.bt;
		    temp.flag = 1;
		    Push(S, &temp);
		}
	    }
	}
	else{
	    bt.bt = BtreeCreate(dataset, type, MakeNullBtree(type), MakeNullBtree(type));
	    bt.flag = 0;
	    Push(S, &bt);
	}
	if(EmptyStack(S) && (i!=n-1)){
	    return MakeNullBtree(type);
	}
	dataset = (char*)dataset+type.size;
    }
    return bt.bt;
}

btree Lchild(btree bt){
    if(!bt){
	return NULL;
    }
    return bt->lchild;
}

btree Rchild(btree bt){
    if(!bt){
	return NULL;
    }
    return bt->rchild;
}

void PreOrder(btree bt, stack S, void visit(btree, stack)){
    if(!bt){
	return;
    }
    datatype type = {sizeof(struct TagBtree), 0, NULL};
    stack Stemp = MakeNullStack(type);
    visit(bt, S);
    struct TagBtree temp = {bt, 0};
    Push(Stemp, &temp);
    while(!EmptyStack(Stemp)){
	if(!((struct TagBtree*)Topelement(Stemp))->flag){
	    temp = *(struct TagBtree*)Topelement(Stemp);
	    Pop(Stemp);
	    temp.flag = 1;
	    Push(Stemp, &temp);
	    if(!EmptyBtree(Lchild(((struct TagBtree*)Topelement(Stemp))->bt))){
		visit(Lchild(((struct TagBtree*)Topelement(Stemp))->bt), S);
		temp.bt = Lchild(((struct TagBtree*)Topelement(Stemp))->bt);
		temp.flag = 0;
		Push(Stemp, &temp);
	    }
	}
	else if(!EmptyBtree(Rchild(((struct TagBtree*)Topelement(Stemp))->bt))){
	    visit(Rchild(((struct TagBtree*)Topelement(Stemp))->bt), S);
	    temp.bt = Rchild(((struct TagBtree*)Topelement(Stemp))->bt);
	    temp.flag = 0;
	    Pop(Stemp);
	    Push(Stemp, &temp);
	}
	else {
	    Pop(Stemp);
	}
    }
}

void PreOrderRec(btree bt, stack S, void (*visit)(btree, stack)){
    if(!EmptyBtree(bt)){
	visit(bt, S);
	PreOrderRec(Lchild(bt), S, visit);
	PreOrderRec(Rchild(bt), S, visit);
    }
}

void InOrder(btree bt, stack S, void (*visit)(btree, stack)){
    if(!bt){
	return;
    }
    datatype type = {sizeof(struct TagBtree), 0, NULL};
    stack Stemp = MakeNullStack(type);
    struct TagBtree temp = {bt, 0};
    Push(Stemp, &temp);
    while(!EmptyStack(Stemp)){
	if(!((struct TagBtree*)Topelement(Stemp))->flag){
	    if(!EmptyBtree(Lchild(((struct TagBtree*)Topelement(Stemp))->bt))){

		/**/
		temp = *(struct TagBtree*)Topelement(Stemp);
		Pop(Stemp);
		temp.flag = 1;
		Push(Stemp, &temp);

		/**/
		temp.bt = Lchild(((struct TagBtree*)Topelement(Stemp))->bt);
		temp.flag = 0;
		Push(Stemp, &temp);

	    }
	    else{
		visit(((struct TagBtree*)Topelement(Stemp))->bt, S);
		if(!EmptyBtree(Rchild(((struct TagBtree*)Topelement(Stemp))->bt))){
		    temp.bt = Rchild(((struct TagBtree*)Topelement(Stemp))->bt);
		    temp.flag = 0;
		    Pop(Stemp);
		    Push(Stemp, &temp);
		}
		else Pop(Stemp);
	    }
	}
	else{
	    visit(((struct TagBtree*)Topelement(Stemp))->bt, S);
	    if(!EmptyBtree(Rchild(((struct TagBtree*)Topelement(Stemp))->bt))){
		temp.bt = Rchild(((struct TagBtree*)Topelement(Stemp))->bt);
		temp.flag = 0;
		Pop(Stemp);
		Push(Stemp, &temp);
	    }
	    else Pop(Stemp);
	}
    }

}

void InOrderRec(btree bt, stack S, void (*visit)(btree, stack)){
    if(!EmptyBtree(bt)){
	InOrderRec(Lchild(bt), S, visit);
	visit(bt, S);
	InOrderRec(Rchild(bt), S, visit);
    }
}

void PostOrder(btree bt, stack S, void (*visit)(btree, stack)){
    if(!bt){
	return;
    }
    struct TagBtree temp = {bt, 0};
    datatype type = {sizeof(struct TagBtree), 0, NULL};
    stack Stemp = MakeNullStack(type);
    Push(Stemp, &temp);
    while(!EmptyStack(Stemp)){
	if((((struct TagBtree*)Topelement(Stemp))->flag)<1){
	    temp = *(struct TagBtree*)Topelement(Stemp);
	    Pop(Stemp);
	    temp.flag = 1;
	    Push(Stemp, &temp);

	    if(!EmptyBtree(Lchild(((struct TagBtree*)Topelement(Stemp))->bt))){
		temp.bt = Lchild(((struct TagBtree*)Topelement(Stemp))->bt);
		temp.flag = 0;
		Push(Stemp, &temp);
	    }
	}
	else if((((struct TagBtree*)Topelement(Stemp))->flag)<2){

	    temp = *(struct TagBtree*)Topelement(Stemp);
	    Pop(Stemp);
	    temp.flag = 2;
	    Push(Stemp, &temp);

	    if(!EmptyBtree(Rchild(((struct TagBtree*)Topelement(Stemp))->bt))){
		temp.bt = Rchild(((struct TagBtree*)Topelement(Stemp))->bt);
		temp.flag = 0;
		Push(Stemp, &temp);
	    }
	}
	else{
	    visit(((struct TagBtree*)Topelement(Stemp))->bt, S);
	    Pop(Stemp);
	}
    }
}

void PostOrderRec(btree bt, stack S, void (*visit)(btree, stack)){
    if(!EmptyBtree(bt)){
	PostOrderRec(Lchild(bt), S, visit);
	PostOrderRec(Rchild(bt), S, visit);
	visit(bt, S);
    }
}

void LevelOrder(btree bt, stack S, void (*visit)(btree, stack)){
    if(!bt){
	return;
    }

    datatype type = {sizeof(struct TagBtree), 0, NULL};
    queue Q = MakeNullQueue(type);

    struct TagBtree Tagtree = {bt, 0};
    struct TagBtree temp;

    temp.flag = 0;

    EnQueue(Q, &Tagtree);

    while(!EmptyQueue(Q)){
	Tagtree = *(struct TagBtree*)Front(Q);

	visit(Tagtree.bt, S);
	DeQueue(Q);

	if(!EmptyBtree(Lchild(Tagtree.bt))){
	    temp.bt = Lchild(Tagtree.bt);
	    EnQueue(Q, &temp);
	}
	if(!EmptyBtree(Rchild(Tagtree.bt))){
	    temp.bt = Rchild(Tagtree.bt);
	    EnQueue(Q, &temp);
	}
    }
    return;
}
