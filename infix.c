#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"stack.h"
#include "function.h"
#include"infix.h"
#define OPERAND	100
#define OPERATOR 200
#define END	300
#define ERR 400
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };
token getnext(char *expr, int *reset) {
	static int i = 0;
	number *a = (number *)malloc(sizeof(number));
	init(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;
	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						appendRight(a, currchar);
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default: // anything else
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case DOT:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						appendRight(a, currchar);
						a->dec++;
						nextstate = DOT;
						currstate = nextstate;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						i++;
						currstate = nextstate;
						break;

					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;

			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERATOR;
						t.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;
						//i++;
						return t;
						break;
					case '+': case '-': case '*': case '/': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;

					case '.':
						nextstate = DOT;
						t.type = OPERATOR;
						t.op = expr[i -1];
						currstate = nextstate;
						i++;
						return t;
						break;

					default: // anything else
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						//no = currchar - '0';
						appendRight(a, currchar);
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(' : case ')' :
					case 'S': case 'C' : case 'T':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					case '.':
						nextstate = DOT;
						i++;
						break;

					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int precedece(char o) {
	switch(o) {
		case 'S':
		case 'C':
		case 'T':
			return -1;
			break;
		case ')' :
			return 0;
			break;
		case '+' :
		case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '(' :
			return 3;
			break;
		default :
			return 4;
			break;
	}
	return 5;
}
number *infix(char *input){

	istack s1;
	ostack s2;
	initIstack(&s1);
	initCstack(&s2);
	number *a,*b,*z;
	a = (number*)malloc(sizeof(number));
	b = (number*)malloc(sizeof(number));
	z = (number*)malloc(sizeof(number));
	init(a);
	init(b);
	init(z);
	char currOp,prevOp;
	int reset = 1;
	int cntCb = 0;
	int cntOb = 0;

	while(1)
	{
		token t;
		t = getnext(input,&reset);
		if(t.type == OPERAND)
		{

			istackPush(&s1,t.num);
			//printNumber(*(t.num));
			continue;
		}
		else if(t.type == OPERATOR)
		{
			if(t.op == ')'){

				cntCb++;
			}
			else if(t.op == '('){

				cntOb++;
			}
			if(cntOb < cntCb){
				return NULL;
			}
			if(t.op == '('){
				cstackPush(&s2,t.op);
				continue;

			}
			 currOp = t.op;

			while(!cstackEmpty(s2)  && precedece(cstackTop(s2))>= precedece(currOp)){


				 prevOp = cstackPop(&s2);
				 if(prevOp == '('){

                    cstackPush(&s2,prevOp);
                    break;

                }
				if(!istackEmpty(s1)){

					a = istackPop(&s1);
				}
				else {
					fprintf(stderr, "Less operands\n");
					return NULL;
				}
				if(!istackEmpty(s1)){

					b = istackPop(&s1);

				}
				else{
					fprintf(stderr,"Less operands\n");
					return NULL;
				}
				if(prevOp == '/' || prevOp == '%' ){

					if(isZero(a)){
						fprintf(stderr,"Mathematical error\n");
						return NULL;
					}
				}
				switch(prevOp){

					case '+':

						z = add(a,b);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;
					case '-':
						z = sub(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '*':
						z = multiply(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '/':
						z = divide(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;


					default :
						return NULL;


				}
			}
			if(currOp == ')'){

				if(cstackTop(s2) == '('){

					char tmp = cstackPop(&s2);
				}
			}
			else{
				cstackPush(&s2,currOp);
			}
		}
		else if(t.type == ERR){

			fprintf(stderr,"Error in expression\n");
			return NULL;
		}
		else if(t.type == END){


			if(cntOb == cntCb){

				while(!cstackEmpty(s2)){

					if(!istackEmpty(s1)){

						a = istackPop(&s1);
					}
					else{
						fprintf(stderr,"Less operands\n");
						return NULL;
					}
					if(!istackEmpty(s1)){

						b = istackPop(&s1);
					}
					else{

						fprintf(stderr,"Less operands\n");
						return NULL;
					}
					char ch ;
					ch = cstackPop(&s2);
					switch(ch){

					case '+':
						z = add(a,b);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;
					case '-':
						z = sub(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);

						break;

					case '*':
						z = multiply(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;

					case '/':
						z = divide(b,a);
						if(z == NULL) return NULL;
						istackPush(&s1,z);
						break;
					default :
						return NULL;

					}

				}
				if(!istackEmpty(s1)){

						z = istackPop(&s1);
						if(istackEmpty(s1)){


							return z;

						}
						else {

							fprintf(stderr,"Less operators\n");
							return NULL;
						}
					}
					else {

						fprintf(stderr,"Less operands\n");
						return NULL;
					}
			}
			else{

                printf("count\n");
				fprintf(stderr,"Error in expression\n");
				return NULL;

			}

		}
	}

}



void modify(char *expr) {
	int i;
	for(i = 0; i < strlen(expr); i++) {
		if(expr[i] == '(') {
			int j = 1;
			while(1) {
				if(expr[i + j] == ' ') {
					j++;
				}
				else {
					break;
				}
			}
			if((expr[i + j] == '-') || (expr[i + j] == '+')) {
				int temp = strlen(expr);
				while(temp >= i + j) {
					expr[temp + 1] = expr[temp];
					temp--;
				}
				expr[i + j] = '0';
			}
		}
	}
}


int readline(char *expr, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			expr[i++] = '\0';
			return i - 1;
		}
		else
			expr[i++] = ch;
	}
	expr[len - 1] = '\0';
	return len - 1;
}
