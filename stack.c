#include<stdlib.h>
#include"stack.h"

void initIstack(istack *s)
{
	s->top = NULL;
	s->size= 0;
}


void istackPush(istack *s, number *a)
{
    if(a == NULL)return;
	inode *tmp;
	tmp = (inode*)(malloc(sizeof(inode)));
	tmp->a = a;
	tmp->i = s->top;
	s->top = tmp;
	s->size++;
}

number* istackPop(istack*s)
{

	inode *tmp;
	number *r;
	tmp = s->top;
	r = tmp->a;
	s->top = tmp->i;
	free(tmp);
	s->size--;
	return r;
}

number* istackTop(istack s)
{
	inode *tmp;
	tmp = s.top;
	return tmp->a;
}

int istackEmpty(istack s)
{
	if(s.size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void initCstack(ostack *s){

	s->top = NULL;
	s->size = 0;
}

void cstackPush(ostack *s, char a)
{

	cnode *tmp;
	tmp = (cnode*)(malloc(sizeof(cnode)));
	tmp->a = a;
	tmp->i = s->top;
	s->top = tmp;
	s->size = s->size+1;

}

char cstackPop(ostack *s)
{
	char ch;
	cnode *tmp;
	tmp = s->top;
	ch = tmp->a;
	s->top = tmp->i;
	free(tmp);
	s->size--;
	return ch;
}

char cstackTop(ostack s)
{
	char r;
	cnode *tmp;
	tmp = s.top;
	r = tmp->a;
	return r;
}


int cstackEmpty(ostack s)
{
	if(s.size == 0)
	{
		return 1;
	}
	else{
		return 0;
	}
}

