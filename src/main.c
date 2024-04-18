#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
#include "Tree.h"
typedef struct{
    char *a;
    char *b;
    int i;
}foo;
void Print(btree bt, stack S){
    printf("-----%d\n", *(int*)Data(bt));
    return;
}

int main(){
    FILE *fp = fopen("./Test/test.txt", "r");
    if(!fp){
	printf("failed open the file!\n");
	return 0;
    }
    //char ch;
    //while((ch = fgetc(fp)) != EOF){
    //    printf("%c->", ch);
    //}
    char *a  = (char *)malloc(3);
    char *b  = (char *)malloc(3);
    memcpy(a, "ab", 3);
    memcpy(b, "ef", 3);

    foo loo = {a, b, 1};

    size_t *pointer_size = (size_t*)malloc(sizeof(size_t)*2);
    pointer_size[0] = 3;
    pointer_size[1] = 3;
    datatype type = {sizeof(loo), 2, pointer_size};
    datatype INT_TYPE = {sizeof(int), 0, NULL};
    int r = 1;
    int s = 2;
    int t = 3;
    int z = 0;
    btree l = BtreeCreate(&s, INT_TYPE, MakeNullBtree(INT_TYPE),  MakeNullBtree(INT_TYPE));
    btree R = BtreeCreate(&t, INT_TYPE, MakeNullBtree(INT_TYPE),  MakeNullBtree(INT_TYPE));
    btree n = BtreeCreate(&r, INT_TYPE, l, R);
    int dataset[13] = {1,2,3,0,0,4,0,0,5,6,0,0,0};
    stack S = MakeNullStack(INT_TYPE);

    btree bt = PreCreBtree(dataset, 13, INT_TYPE);

    LevelOrder(bt, S, Print);
    printf("IsComTree: %d\n", IsComTree(n));
    printf("Tree Width: %d\n", BtreeWidth(n));
    
    //printf("----%d----\n", *(int*)Data(bt));
    //printf("%d\n", BtreeWidth(n));
    //PreOrderRec(n, S, Print);



    queue Q = MakeNullQueue(type);

    for(int i=1; i<=10; i++){
	loo.i = i;
	loo.a[0]+=1;
	EnQueue(Q, &loo);
    }
    foo data;
    while(!EmptyQueue(Q)){
	data = *(foo*)Front(Q);
	printf("%d: %s %s\n", data.i, data.a, data.b);
	DeQueue(Q);
    }
    fclose(fp);
    return 0;

    /* Calculate the f */

    /* Make Haffman Tree */

    /* Process the file */

    /* Read Processed file*/

    /* Decode the file */

}
