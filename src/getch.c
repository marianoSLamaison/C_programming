#include<stdio.h>
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
