#include <stdio.h>
#define MAXLINE 1000
//returns the length of the line recieved
int getline(char line[], int maxline);
void copy(char to[], char from[]);
void myPutLine(char s[]);
void cutTrailing(char s[]);
void reverse(char s[]);
int main(void){
	/*
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)
		if (max == MAXLINE-1)

			printf("The line recieved had a length equal or greater than <%d>\n and it was <%s>\n", MAXLINE-1, longest);
		else 
			printf("The line recieved had a length of <%d> and was <%s>", max, longest);
			*/
	/*
	char line[MAXLINE];
	int len;
	while((len = getline(line, MAXLINE))>0)
		if (len > 80){
			myPutLine(line);
			printf("That line was longer than 80 characters\n");
		}
		*/
	/*
	char line[MAXLINE];
	while (getline(line, MAXLINE) > 0){
		cutTrailing(line);
		printf("That line without trailing spaces is <%s>\n", line);
	}
	*/

	char line[MAXLINE];
	while (getline(line, MAXLINE) > 0){
		reverse(line);
		cutTrailing(line);
		printf("That line reversed is <%s>\n", line);
	}
	return 0;
}

void cutTrailing(char s[]){
#define IN 1
#define OUT 0
	int i, state, c, j;
	i = j = 0;
	state = OUT;
	char holder[MAXLINE];
	while((c = s[i]) != '\0'){
		if (state == OUT && c!=' ' && c!='\t' && c!='\n')
			state = IN;
		if(state == IN){
			holder[j] = s[i];
			++j;
		}
		++i;
	}
	if (j != 0)
		holder[j-1] = '\0';
	else
		holder[j] = '\0';
	copy(s, holder);
}

int stringSize(char s[]){
	int i;
	i=0;
	while (s[i] != '\0')
		++i;
	return i;
}

void reverse(char s[]){
	int i, end;
	char hold[MAXLINE];
	i=0;
	end = stringSize(s) - 1;
	while(s[i] != '\0'){
		hold[end - i] = s[i];
		++i;
	}
	hold[++i] = '\0';
	copy(s, hold);
}

void myPutLine(char s[]){
	int i;
	i=0;
	while(s[i] != '\0'){
		putchar(s[i]);
		i++;
	}
}

int getline(char s[], int lim){
	int c, i;
	for(i=0; i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
		s[i]=c;
	if (c=='\n') {
		s[i]=c;
		++i;
	}
	s[i]='\0';
	return i;
}

void copy(char to[], char from[]){
	int i;
	i=0;
	while((to[i]=from[i]) != '\0')
		++i;
}
