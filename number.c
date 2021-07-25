#include <stdio.h>
#include <stdlib.h>
#include "number.h"
void init(number *a) {
	a->head = a->tail = NULL;
	a->dec = 0;
	a->sign = PLUS;
}
void appendRight(number *a, char ch) {
	if(ch < '0' || ch > '9')
		return;
	node *tmp = (node *)malloc(sizeof(node));
	if(tmp == NULL)
		return;
	tmp->num = ch - '0';
	tmp->next = NULL;
	if((a->head == NULL) && (a->tail == NULL)) {
		tmp->prev = NULL;
		a->head = tmp;
		a->tail = tmp;
		return;
	}
	tmp->prev = a->tail;
	a->tail->next = tmp;
	a->tail = tmp;
	return;
}
int length(number c) {
	node *p;
       	p = c.head;
	int count = 0;
	while(p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}
void appendleft(number *c, int no) {
	if(no < 0 || no > 9)
		return;
	node *tmp = (node *)malloc(sizeof(node));
	if(!tmp)
		return;
	tmp->num = no;
	tmp->prev = NULL;
	if((c->head == NULL) && (c->tail == NULL)){
		tmp->next = NULL;
		c->head = c->tail = tmp;
		return;
	}
	tmp->next = c->head;
	c->head->prev = tmp;
	c->head = tmp;
	return;
}
void removeZeros(number *a) {
	node *p = a->head;
	int i, len = length(*a);
	for(i = 0; i < len - a->dec -1; i++) {
		if(p->num == 0) {
			a->head = p->next;
			p->next = NULL;
			a->head->prev = NULL;
			free(p);
			p = a->head;
		}else {
			break;
		}
	}
	p = a->tail;
	int decimal = a->dec;
	for(i = 0; i < decimal - 1; i++) {
		if(p->num == 0) {
			a->tail = p->prev;
			p->prev = NULL;
			a->tail->next = NULL;
			free(p);
			p = a->tail;
			a->dec--;

		}else {
			break;
		}
	}
	return;
}

void rounded(number *n){

    int s = n->dec;
    if(s > 30){

        int d = s-30;
        while(d--){

            n->tail = n->tail->prev;
            n->dec--;
        }

        n->tail->next = NULL;

    }


}
void print(number c, char * output) {


    int i=0;
	node *p;
	int pos = 0;
	removeZeros(&c);
	p = c.head;
	if(c.sign == MINUS) {

		output[i++] = '-';
		printf("-");
		c.sign = PLUS;
	}
	rounded(&c);
	while(p != NULL ) {
		pos++;
		if(pos == (length(c) - c.dec + 1)){

            output[i++] = '.';
            printf(".");
		}

		printf("%d", p->num);
		output[i++] = '0'+p->num;
		p = p->next;
	}
	output[i++] = '\0';
	printf("\n");

}
