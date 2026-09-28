#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "ejercicios.h"
#include <math.h>

#define MAXLINE 100
#define MAXOP 100
#define NUMBER '0'
#define PRINTTOP 'P'
#define DUPLICATETOP 'D'
#define SWAPTOP 'S'
#define CLEARSTACK 'C'
#define SIN 's'
#define EXP 'e'
#define POW 'p'
#define READVAR 'R'
#define WRITEVAR 'W'
//#define VARCOUNT 27 //whe have 27 in total, one more for the special one
		    //Not felling like diferentiating between cases
#define LASVARINDEX 26
#define SPECIALVAR '_'
#define VARSIMBOLINDX 1
//Entrega N°4
int getop(char[]);
void push(double);
double pop(void);
int isStackEmpty(void);

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
#include<ctype.h>
int getch(void);
void ungetch(int);

char inputedLine[MAXLINE];//global so it lasts all the execution
int newLine = 1;
int j;

int getop(char s[]){
	int i, c;
	
	if(newLine){
		c = getlineC(inputedLine, MAXLINE);
		j=0;
		newLine=0;
		if (c==EOF)
			return c;
	}
		
	while((s[0]=c=inputedLine[j++]) == ' ' || c=='\t')
		;
	s[1]='\0';
	if(!isdigit(c) && c!='.' && c!='-'){
		if (c==READVAR || c==WRITEVAR){
			s[1]=inputedLine[j++];
			s[2]='\0';
		}else if(c=='\n')
			newLine=1;
		return c;
	}
	else if(c=='-' && !isdigit(s[1]=c=inputedLine[j++])){
		j--;
		s[1]='\0';
		return '-';
	}

	i= (s[1] == '\0') ? 0: 1;
	if(isdigit(c))
		while(isdigit(s[++i]=c=inputedLine[j++]))
			;
	if(c=='.')
		while(isdigit(s[++i]=c=inputedLine[j++]))
			;
	s[i]='\0';
	if(c!=EOF)
		j--;
	return NUMBER;
}

/*
int getop(char s[]){
	//So they tello us that some body is using
	//get line and bascially that trew off getch an 
	//ungetch so Whe ought to replace thes
	int i, c;
	while((s[0]=c=getch()) == ' ' || c=='\t')
		;
	s[1]='\0';
	if(!isdigit(c) && c!='.' && c!='-'){
		//so whe added the new commands to work with variables
		//READ takes out the value of a variable
		//Write stores it on it
		//you have 26 variables for every key and
		//an extra one for the empty space that is the
		//one for the last printed value
		if (c==READVAR || c==WRITEVAR){
			s[1]=getch();
			s[2]='\0';
		}
			//whe ougth to ignore UTF-8 because whe aint even using wchars
		return c;
	}
	else if(c=='-' && !isdigit(s[1]=c=getch())){
		ungetch(c);
		s[1]='\0';
		return '-';
	}

	i= s[1] == '\0' ? 0: 1;
	if(isdigit(c))
		while(isdigit(s[++i]=c=getch()))
			;
	if(c=='.')
		while(isdigit(s[++i]=c=getch()))
			;
	s[i]='\0';
	if(c!=EOF)
		ungetch(c);
	return NUMBER;
}
*/


#define BUFSIZE 100
int buf[BUFSIZE];
int bufp=0;
int getch(void){
	return (bufp>0) ? buf[--bufp]:getchar();
}
void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch: too many arguments\n");
	else
		buf[bufp++]=c;
}
void ungetchs(int s[])
{//does the same as ungetch but with strings
	int i;
	for ( i=0; s[i]!='\0' && i<1; i++)
		if(bufp<BUFSIZE)
			buf[bufp++]=s[i];
		else
			printf("The buffer is full");
	//stores the end of the string
	buf[(bufp>=BUFSIZE)?bufp++:BUFSIZE-1]='\0';
}
