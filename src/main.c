#include <stdio.h>
#include <ctype.h>
int getch(void);
void ungetch(int);
int getint(int *pn);
int getfloat(float *pn);
///////////Tests
void testgetint(void);
void testgetfloat(void);


int main(void){
	testgetfloat();
	return 0;
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
