#include<stdio.h>
#include<ctype.h>
#include "calc.h"
#include "ejercicios.h"
#define MAXLINE 1000
static char inputedLine[MAXLINE];//global so it lasts all the execution
static int newLine = 1;
int getop(char s[]){
	int i, c;
	
	static int j;
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
