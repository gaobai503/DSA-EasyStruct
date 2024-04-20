#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
#include "Heap.h"
#include "Tree.h"
void Print(btree bt, stack S){
    printf("---%d---\n", *(int*)Data(bt));
    return;
}

struct FRECH{
    char ch;
    unsigned fre;
}frech;


int main(){
    FILE *fp = fopen("./Test/test.txt", "r");
    if(!fp){
	printf("failed open the file!\n");
	return 0;
    }
    char ch;
    unsigned Num = 0;
    unsigned Frequency[128] = {0};
    rewind(fp);
    while((ch = fgetc(fp))!=EOF){
	if(!Frequency[(int)ch]++) Num++;
    }
    /*Initial The structure Tag*/
    size_t t =  sizeof(frech);
    datatype FRECH_TYPE = {sizeof(frech), 0, NULL};
    datatype BTREENODE_TYPE = {sizeof(struct BTREE), 1, &t};
    cmpkey BTREENODE_KEY = {4, 0, 4};

    /*Initial The Heap*/
    btree data = (btree)malloc(sizeof(struct BTREE)*Num);
    heap H = MakeNullHeap(data, 0, BTREENODE_KEY, BTREENODE_TYPE);
    //for(int i=1; i<=Num; i++){
    //    printf("i: %2d-->%p\n", i, Node(H, i));
    //}
    //getchar();

    btree bt;
    for(int i=0; i<128; i++){
	if(Frequency[i]!=0){
	    frech.ch = i;
	    frech.fre = Frequency[i];
	    bt = BtreeCreate(&frech, FRECH_TYPE, MakeNullBtree(FRECH_TYPE), MakeNullBtree(FRECH_TYPE));
	    frech = *(struct FRECH*)Data(bt);
	    printf("INPUT---ch: %d, weight: %d\n", frech.ch, frech.fre);
	    Add(bt, H);
	    if(counter<28){
		printf("H->n: %d\n", H->n);
		for(int i=1; i<=H->n; i++){
		    bt = (btree)Node(H, i);
		    printf("I: %d\n", i);
		    printf("(%d)%p\n",(bt!=NULL), bt);
		    if(bt!=NULL){
			frech = *(struct FRECH*)Data(bt);
			printf(" OUTPUT---ch: %d, weight: %d\n", frech.ch, frech.fre);
		    }
		    else{
			printf(" NULL!\n");
		    }
		}
	    }
	    printf("-----------------------------\n");
	    getchar();
	}
    }
    
    fclose(fp);
    return 0;

    /* Calculate the f */

    /* Make Haffman Tree */

    /* Process the file */

    /* Read Processed file*/

    /* Decode the file */

}
