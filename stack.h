#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include "number.h"

typedef struct inode{

	struct inode* i;
	number *a;
}inode;


typedef struct istack{

	inode* top;
	int size;

}istack;



typedef struct cnode{

	struct cnode* i;
	char a;

}cnode;

typedef struct ostack{

	cnode *top;
	int size;

}ostack;

void initIstack(istack *s);
void istackPush(istack *s, number *a);
number* istackPop(istack *s);
number* istackTop(istack s);
int istackEmpty(istack s);
void initCstack(ostack *s);
void cstackPush(ostack *s,char a);
char cstackPop(ostack *s);
char cstackTop(ostack s);
int cstackEmpty(ostack s);







#endif // STACK_H_INCLUDED
