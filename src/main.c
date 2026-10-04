#include <stdio.h>
#include <ctype.h>
#include "funciones.h"
#define LIST_LENGT 256

///////////Tests
void testgetint(void);
void testgetfloat(void);
void teststrcat(void);
void teststrend(void);
void testnstringfunctions(void);

int main(void){
	testnstringfunctions();
	return 0;
}
void testnstringfunctions(void){
	char basestr[LIST_LENGT] = "I will write something here",
	     comparable[]="I wilL dfg",
	     extra[]="I love pandas",
	     copia[LIST_LENGT];
	printf("Testing strn functions implementations\n");
	mystrncpy(copia, basestr, 3);
	printf("Copiamos \n%s\n", copia);
	mystrncpy(copia, basestr, 89);
	printf("Ahora copiamos \n%s\n", copia);
	printf("De los string \n%s\n\n%s\nel mayor segun los primeros 5 caracteres es\n%s\n", 
			basestr, comparable, mystrncmp(basestr, comparable, 5)>0 ? 
			basestr: comparable);
	mystrncat(basestr, extra, 5);
	printf("Asi se ve base con los 5 caracteres extra pegados %s", basestr);
}
void teststrend(void){
	char basestr[]= "hello this can you find the last instance of can in this string?";
	char pattern[]= "can";
	int patternPos;
	printf("Testing strend function\n");
	printf("The test string is \n%s\nAnd the pattenr to search is \n%s\n", basestr, pattern);
	patternPos = mystrend(basestr, pattern);
	printf("The positions of the start of the pattern is %i\n", patternPos);
}
void teststrcat(void){
	char basestr[LIST_LENGT] = "hello, my name is ",name[] = "julian";
	printf("Testing strcat function\n");
	printf("The base string is \n%s\nAnd the added one is\n%s\n", 
			basestr, name);
	mystrcat(basestr, name);
	printf("%s\n", basestr);
}
void testgetfloat(void){
#define ARRAYSIZE 10
	float numbers[ARRAYSIZE]={};
	int i;
	i=0;
	while(getfloat(&numbers[i++])!=EOF && i<ARRAYSIZE)
		;
	printf("\nThe array inserted is\n");
	putchar('{');
	for (i=0; i<ARRAYSIZE; i++)
		printf(" %.4f%c", numbers[i], (i==ARRAYSIZE-1)?' ': ',');
	putchar('}');
	putchar('\n');
#undef ARRAYSIZE
}

void testgetint(void){
#define ARRAYSIZE 10
	int numbers[ARRAYSIZE]={0,0},i;
	i=0;
	while(getint(&numbers[i++])!=EOF && i<ARRAYSIZE)
		;
	printf("\nThe array inserted is\n");
	putchar('{');
	for (i=0; i<ARRAYSIZE; i++)
		printf(" %i%c", numbers[i], (i==ARRAYSIZE-1)?' ': ',');
	putchar('}');
	putchar('\n');
#undef ARRAYSIZE
}

