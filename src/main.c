#include <stdio.h>
#include <limits.h>
#include "ejercicios.h"

#define MAXLINE 100
//Entrega N°4
void testStrindexFunctions(void);
void testAtof(void);
int main(void){
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
