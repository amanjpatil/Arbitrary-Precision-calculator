#include<stdio.h>
#include"number.h"
#include"function.h"
#include"infix.h"
int main(int argc, char *argv[]) {

	number *r;
	char expr[2048];
	while(readline(expr, 2048)){


		modify(expr);
		r = infix(expr);
		if(r != NULL){

            char output[2001];
            print(*r,output);

		}
		else{

            fprintf(stderr, "Error in expression\n");
	}
	}

	return 0;

}
