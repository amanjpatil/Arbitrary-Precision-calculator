#ifndef INFIX_H_INCLUDED
#define INFIX_H_INCLUDED
typedef struct token{
	int type;
	number *num;
	char op;
}token;
token getnext(char *expr, int *reset);
number *infix(char *input);
void modify(char *expr);
int readline(char *expr, int len);
#endif // INFIX_H_INCLUDED
