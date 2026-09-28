#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "ejercicios.h"
#include <math.h>
#include "calc.h"

#define MAXLINE 100
#define MAXOP 100
#define PRINTTOP 'P'
#define DUPLICATETOP 'D'
#define SWAPTOP 'S'
#define CLEARSTACK 'C'
#define SIN 's'
#define EXP 'e'
#define POW 'p'
//#define VARCOUNT 27 //whe have 27 in total, one more for the special one
		    //Not felling like diferentiating between cases
#define LASVARINDEX 26
#define SPECIALVAR '_'
#define VARSIMBOLINDX 1
//Entrega N°4

void testStrindexFunctions(void);
void testAtof(void);

double variables[LASVARINDEX+1];

//reverse polish notation calculator
int main(void){
	int type, operationsMade;
	double op2, helper;
	char s[MAXOP];
	operationsMade=0;
	while((type = getop(s)) != EOF) {
		if (type=='\n' && operationsMade && !isStackEmpty()){
			op2 = pop();
			printf("\tResult = %.8g\n", op2);
			push(op2);
			variables[LASVARINDEX]=op2;
			operationsMade = 0;
			continue;
		}else if(type!='\n')
			operationsMade=1;
		else
			continue;
		if(type<0)
			type*=-1;
		switch(type){
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2=pop();
				push(pop()-op2);
				break;
			case '/':
				op2=pop();
				if(op2!=0.0)
					push(pop()/op2);
				else
					printf("Error: zero division\n");
				break;
			case '%':
				op2=pop();
				if(op2!=0.0)
					push((int)pop()%(int)op2);
				break;//the reminder of 0 division is the same number
		//	case '\n'://I did these because otherwise P would be useless
		//		printf("\t%.8g\n", pop());
		//		break;
			case PRINTTOP:
				//if(isStackEmpty())
				//	break;
				//printf("\tCurrent top of stack %.8g\n", op2=pop());
				//push(op2);
				if (isStackEmpty())
					printf("\tThe stack is currently empty\n");
				break;
			case DUPLICATETOP:
				if(isStackEmpty()){
					pop();
					break;
				}
				op2=pop();
				push(op2);
				push(op2);
				break;
			case SWAPTOP:
				if (isStackEmpty()){
					pop();
					break;
				}
				op2=pop();
				helper=pop();
				push(op2);
				push(helper);
				break;
			case CLEARSTACK:
				while(!isStackEmpty())
					pop();
				break;
			case SIN:
				if (isStackEmpty()){
					pop();
					break;
				}
				push(sin(pop()));
				break;
			case POW:
				if (isStackEmpty()){
					pop();
					break;
				}
				op2=pop();
				if(isStackEmpty()){
					pop();
					break;
				}
				helper=pop();
				push(pow(helper, op2));
				break;
			case EXP:
				if (isStackEmpty()){
					pop();
					break;
				}
				push(exp(pop()));
				break;
			case READVAR:
				if (s[VARSIMBOLINDX]==SPECIALVAR)
					op2=variables[LASVARINDEX];
				else
					op2=variables[toupper(s[VARSIMBOLINDX])-'A'];
				push(op2);
				break;
			case WRITEVAR:
				if(isStackEmpty()){
					pop();
					break;
				}
				op2=pop();
				if(s[VARSIMBOLINDX]==SPECIALVAR)
					variables[LASVARINDEX]=op2;
				else
					variables[toupper(s[VARSIMBOLINDX])-'A']=op2;
				break;
			default:
				printf("Error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}



void testAtof(void){
	double sum, atof(char []);
	char line[MAXLINE];
	int getlineC(char line[], int max);
	sum = 0;
	while(getlineC(line, MAXLINE) > 0)
		printf("\t%g\n", sum += atof(line));
}

void testStrindexFunctions(void){
	char stringPrueba[] = "hola como estan Aqui solo hay nombres para escribir como quieras";
	char stringPatron[] = "como";
	int indiceEncontrado;
	printf("El estring ingrsado era\n%s\n", stringPrueba);
	printf("El string patron es \n%s\n", stringPatron);
	indiceEncontrado = strindex(stringPrueba, stringPatron);
	printf("El string patron segun strindex estaba en %d\n", indiceEncontrado);
	indiceEncontrado = strindexr(stringPrueba, stringPatron);
	printf("El string patron segun strindexr estaba en %d\n", indiceEncontrado);
}


