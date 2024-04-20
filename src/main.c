#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Link.h"
#include "Heap.h"
#include "Tree.h"
void Print(btree bt, stack S){
    struct FRECH temp;
    temp = *(struct FRECH*)Data(bt);
    printf("ch: %d, weight: %d\n", temp.ch, temp.fre);
    return;
}

void Store(btree bt, stack S){
    struct FRECH *temp;
    temp = (struct FRECH*)Data(bt);
    Push(S, temp);
    return;
}

struct FRECH frech;

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
    Frequency[0] = 1;
    Num++;
    /*Initial The structure Tag*/
    size_t t =  sizeof(frech);
    datatype FRECH_TYPE = {sizeof(frech), 0, NULL};
    datatype BTREENODE_TYPE = {sizeof(struct BTREE), 1, &t};
    cmpkey BTREENODE_KEY = {4, 0, 4};

    btree data = (btree)malloc(sizeof(struct BTREE)*Num);
    heap H = MakeNullHeap(data, 0, BTREENODE_KEY, BTREENODE_TYPE);

    btree bt;
    btree temp;
    btree sum;
    for(int i=0; i<128; i++){
	if(Frequency[i]!=0){
	    frech.ch = i;
	    frech.fre = Frequency[i];
	    bt = BtreeCreate(&frech, FRECH_TYPE, MakeNullBtree(FRECH_TYPE), MakeNullBtree(FRECH_TYPE));
	    Add(bt, H);
	}
    }
    while(H->n!=1){
	bt = (btree)malloc(sizeof(struct BTREE));
	temp = (btree)malloc(sizeof(struct BTREE));
	Move(H, bt, Root(H));
	Remove(H);
	Move(H, temp, Root(H));
	Remove(H);
	frech = *(struct FRECH*)Data(temp);
	frech.ch = -128;
	frech.fre = (*(struct FRECH*)Data(bt)).fre + (*(struct FRECH*)Data(temp)).fre;
	sum = BtreeCreate(&frech, FRECH_TYPE, bt, temp);
	Add(sum, H);
    }
    stack S = MakeNullStack(FRECH_TYPE);
    btree HaffTree = (btree)Root(H);
    PreOrder(HaffTree, S, Store);
    PreOrder(HaffTree, S, Print);
    stack T = MakeNullStack(FRECH_TYPE);
    while(!EmptyStack(S)){
	frech = *(struct FRECH*)Topelement(S);
	Push(T, &frech);
	Pop(S);
    }

    datatype CHAR_TYPE = {sizeof(char), 0, NULL};
    stack ST = MakeNullStack(CHAR_TYPE);

    typedef struct CODE{
	unsigned bits;
	char ch;
	char code[9];
    }code;

    datatype CODE_TYPE = {sizeof(code), 0, NULL};

    link L = MakeNullLink(CODE_TYPE);
    stack codebit = MakeNullStack(CHAR_TYPE);

    code codetemp;
    position p;
    char zero = '0';
    char one = '1';
    Push(codebit, &zero);
    printf("Load-----Ch:%d, weight: %d\n",frech.ch, frech.fre);
    Pop(T);
    printf("Push---0\n");
    frech = *(struct FRECH*)Topelement(T);
    while(!EmptyStack(T)){
	frech = *(struct FRECH*)Topelement(T);
	printf("Load-----Ch:%d, weight: %d\n",frech.ch, frech.fre);
	Pop(T);
	if(frech.ch == -128){
	printf("Push---0\n");

	    Push(codebit, &zero);
	} 
	else{
	    p = First(codebit);
	    codetemp.ch = frech.ch;
	    for(codetemp.bits=0; !IsEOL(codebit, p); codetemp.bits++){
		Push(ST, (char*)Retrieve(codebit, p));
		p = Next(codebit, p);
	    }
	    for(int k=0; k<codetemp.bits;k++){
		codetemp.code[k] = *(char*)Topelement(ST);
		Pop(ST);
	    }
	    codetemp.code[codetemp.bits] = '\0';
	    printf("Gathered a code!\n");
	    Insert(L, Next(L, End(L)), &codetemp);
		    
	    char top = *(char*)Topelement(codebit);
	    while(top == '1'){
		Pop(codebit);
		printf(" Pop---1\n");
		if(EmptyStack(codebit)) break;
		top = *(char*)Topelement(codebit);
	    }
	    if(top == '1') break;
	    Pop(codebit);
	    printf(" Pop---0\n");
	    Push(codebit, &one);
	    printf("Push---1\n");
	}
    }
    FILE *huff = fopen("./Test/Huffcode.txt", "w");
    if(!huff){
	printf("Failed to open th file!\n");
	return 0;
    } 
    p = First(L);
    char Line[50] = {'\0'};
    while(!IsEOL(L, p)){
	codetemp = *(code*)Retrieve(L, p);
	if(codetemp.ch=='\n')
	sprintf(Line, "%3d(%s):  %s\n", codetemp.ch, "\\n", codetemp.code);
	else if(codetemp.ch == '\0'){
	sprintf(Line, "%3d(%s):  %s\n", codetemp.ch, "\\0", codetemp.code);
	}
	else
	sprintf(Line, "%4d(%c):  %s\n", codetemp.ch, codetemp.ch, codetemp.code);
	fputs(Line, huff);
	p = Next(L, p);
    }
    fclose(huff);

    FILE *CF = fopen("./Test/CodedFile.txt", "w");
    if(!CF){
	printf("Failed to open the file!\n");
	return 1;
    }
    rewind(fp);
    while((ch =fgetc(fp)) != EOF){
	p = First(L);
	while(!IsEOL(L, p)){
	    if(ch == ((code*)Retrieve(L, p))->ch) break;
	    p = Next(L, p);
	}
	for(int k=0; k<((code*)Retrieve(L, p))->bits; k++){
	    fputc((((code*)Retrieve(L, p))->code)[k], CF);
	}
    }
    fclose(fp);
    fclose(CF);

    FILE *DF = fopen("./Test/DecodedFile.txt", "w");
    if(!DF){
	printf("Failed to open the file!\n");
	return 1;
    }

    CF = fopen("./Test/CodedFile.txt", "r");
    if(!CF){
	printf("Failed to open the file!\n");
	return 1;
    }

    char *Loca = Line;
    unsigned Remained = 0;
    unsigned fault = 0;
    unsigned up;
    ch = '\0';
    p = First(L);
    while(!IsEOL(L, p)){
	code ct = *(code*)Retrieve(L, p);
	printf("(%2d)ch: %3d, weight: %s\n", ct.bits, ct.ch, ct.code);
	p = Next(L, p);
    }
    while(ch!=EOF){
	if(Remained<25){
	    printf("Remained: %d\n", Remained);
	    printf("Let's ADD some!\n");
	    printf("%s\n", Line);
	    memcpy(Line, Loca, Remained);
	    Loca = Line+Remained;
	    for(;Remained<50;Remained++){
		ch = fgetc(CF);
		if(ch == EOF){
		    printf("Read EOF!\n");
		    break;
		}
		*(Loca++) = ch;
	    }
	    Loca = Line;
	    printf("%s\n", Line);
	    fault = 0;
	    printf("Now->Remianed: %d\n", Remained);
	}
	if(Remained==0) break;
	while(!fault && Remained){
	    p = First(L);
	    while(!IsEOL(L, p)){

		if(Remained < ((code*)Retrieve(L, p))->bits){
		    fault = 1;
		    p = Next(L, p);
		    continue;
		} 
		for(int k=0; k<Remained; k++){
		    printf("%c", Loca[k]);
		}
		printf("\n");
		printf("Compare(%d)--------->\n", ((code*)Retrieve(L, p))->bits);
		printf("Locate: ");
		for(unsigned k=0; k<((code*)Retrieve(L, p))->bits; k++){
		    printf("%c", Loca[k]);
		}
		printf("\n");
		printf("Source: ");
		for(unsigned k=0; k<((code*)Retrieve(L, p))->bits; k++){
		    printf("%c", (((code*)Retrieve(L, p))->code)[k]);
		}
		printf("\n");
		fault = memcmp(Loca, ((code*)Retrieve(L, p))->code, ((code*)Retrieve(L, p))->bits);
		printf("Result: %d\n", fault);
		//getchar();
		if(!fault) break;
		p = Next(L, p);
	    }
	    if(fault) continue;
	    Loca+=((code*)Retrieve(L, p))->bits;
	    Remained-=((code*)Retrieve(L, p))->bits;
	    ch = ((code*)Retrieve(L, p))->ch;
	    printf("Put: %c\n", ch);
	    fputc(ch, DF);
	    printf("Remained(%d)\n", Remained);
	    for(int k=0; k<Remained; k++){
		printf("%c", Loca[k]);
	    }
	    printf("\n");
	    printf("ch==EOF?%d\n", ch==EOF);
	    //getchar();
	}
    }
    fclose(DF);
    return 0;
}
