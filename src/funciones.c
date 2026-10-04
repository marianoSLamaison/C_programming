#include<ctype.h>
#include<stdio.h>
#include"funciones.h"

int mystrncmp(char* s, char* t, int n){
	for(;n-- >0 && *s==*t; s++, t++)
		;
	if (*s=='\0' && *t!='\0')
		return 1;
	else if(*s!='\0' && *t=='\0')
		return -1;
	return *t-*s;
}

char* mystrncat(char* s, char* cp, int n){
	char* sstart;
	sstart = s;
	while(*s!='\0')
		s++;
	while(n-- > 0 && (*s++=*cp++)!='\0')
		;
	if(n==0)
		*s='\0';
	return sstart;
}

char* mystrncpy(char* s, char* cp, int n){
	char * sstart;
	sstart = s;
	while(n-- >0 &&  *cp!='\0')
		*s++=*cp++;
	*(--s)='\0';
	return sstart;
}

int mystrend(char* s, char* subs){
	char* subsstart, *sstart, *subsend;
	subsstart = subs;
	sstart=s;
	//whe ge to the end of both strings and compare them from there
	while(*s++!='\0')
		;
	s-=2;
	while(*subs++!='\0')
		;
	subs-=2;
	subsend = subs;
	printf("The end char is in the pos %li\n\n", subs - subsstart);
	while(s--!=sstart){
		if(*subs==*s)
			--subs;
		else 
			subs = subsend;
		if(subs<subsstart)
			return s-sstart;
	}
	return -1;

}

void mystrcat(char* base, char* added){
	//1. run till the end of the string
	while(*base!='\0')
		base++;
	//2. write the added in to it including it's end
	while((*base++=*added++)!='\0')
		;
}

int getfloat(float *pn){
	int c, sign, power;
	float fstnum,secnum;
	while(isspace(c=getch()))
		;
ANALISIS_OF_NUMBER:	
	if(!isdigit(c) && c!= EOF && c!= '+' && c!= '-' && c!='.'){
		ungetch(c); //I do not know what to do with that
		return 0;
	}
	sign=(c=='-')?-1:1;
	if(c=='+'||c=='-'){
		while(isspace(c=getch()))
			;
		if(!isdigit(c))
			goto ANALISIS_OF_NUMBER;
	}
	for(fstnum=0; isdigit(c); c=getch())
		fstnum=10 * fstnum+(c-'0');
	secnum=0;
	if(c=='.'){
		power=1;
		while(isdigit(c=getch())){
			secnum=10 * secnum + (c-'0');
			power*=10;
		}
		secnum/=power;//get the numbers afther the. at their rightfull value
	}
	*pn=sign*(fstnum+secnum);
	if(c!=EOF)
		ungetch(c);
	return c;
}

int getint(int *pn){
	int c, sign;
	while( isspace(c =getch()))
		;
ANALISIS_OF_NUMBER:
	if(!isdigit(c) && c!= EOF && c!= '+' && c!= '-'){
		ungetch(c); //I do not know what to do with that
		return 0;
	}
	sign = (c=='-')?-1:1;
	if(c=='+'||c=='-'){
		while(isspace(c=getch()))
				;
		if(!isdigit(c)){
			goto ANALISIS_OF_NUMBER;
		}
	}
			
	for (*pn=0; isdigit(c); c=getch())
		*pn=10* *pn+(c-'0');
	*pn*=sign;
	if(c!=EOF)
		ungetch(c);
	return c;
}
