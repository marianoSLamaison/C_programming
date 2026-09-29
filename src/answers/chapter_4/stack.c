#include<stdio.h>
#include "calc.h"

#define MAXVAL 100

int sp=0;//stack pointer
double val[MAXVAL];//the stack of values

void push(double f){
	if(sp<MAXVAL)
		val[sp++]=f;
	else
		printf("Error: stack full, can't push %g\n", f);
}

double pop(void){
	if(sp>0)
		return val[--sp];
	else{
		printf("Error: stack empty\n");
		return 0.0;
	}
}

int isStackEmpty(void){
	return sp==0;
}


