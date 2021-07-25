#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED
#define PLUS 1
#define MINUS -1
typedef struct node {
	int num;
	struct node *next, *prev;
}node;
typedef struct number {
	int sign, dec;
	node *head, *tail;
}number;
void init(number *a);
void appendRight(number *a, char ch);
void print(number a,char *output);
void appendleft(number *a, int no);
int length(number a);
//void removea(number *a, int pos);
void rounded(number *n);
void removeZeros(number *a);
#endif // NUMBER_H_INCLUDED
