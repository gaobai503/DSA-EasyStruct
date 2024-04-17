#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
typedef struct{
    char *a;
    char *b;
    int i;
}foo;
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
