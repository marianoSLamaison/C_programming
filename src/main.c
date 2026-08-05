#include <stdio.h>
#define MAXLINE 1000
#define TABSIZE 8
	
int getline(char line[], int maxline);
void copy(char to[], char from[]);
void detab(char s[], int size);
void entab(char s[], int size);
void fold(char s[], int size, int lineLengt);
int main(void){
	char line[MAXLINE];
	while(getline(line, MAXLINE) > 0){
		detab(line, MAXLINE);
		fold(line, MAXLINE, 8);
		printf("The folder line looks like this \n%s\n", line); 
	}
	return 0;
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

void detab(char s[], int size){
	int i, c, j, displacement, distanceToTab;
	char holder[size];
	displacement = 0;
	for (i=0; (c=s[i]) != '\0'; ++i)
	{
		//if whe reacha tab, whe fill with spaces up untill whe reach the tab stop 
		//or run out of space
		//i stops being trust worty as a reference afther the first tab so whe use 
		//displacement.
		if (c=='\t')
		{
			distanceToTab =  TABSIZE - (displacement % TABSIZE);
			for (j=0; 
			j+displacement < size - 1 && j <= distanceToTab; 
			++j)
				holder[j+displacement] = ' ';
			displacement = distanceToTab+displacement;
		}
		else if (c!='\n')
		{
			holder[displacement] = c;
			++displacement;
		}
		else
			holder[displacement] = '.';
	}
	holder[displacement+1] = '\0';
	copy(s, holder);

}
void entab(char s[], int size)
{
	int i,c, j, tabCount, displacement, tabDisplacement;
	char holder[size];
	displacement=0;
	for (i=0; (c=s[i])!='\0'; ++i)
		//if whe hit a blank whe start searching where it stops
		//then once whe know that, whe refill with the apropiate amount of tabs
		//and blanks
		if (c==' ')
		{
			for (j=i; s[j]==' ' && s[j]!='\0'; ++j);
			j = j-i;
			tabCount = ((j+i) / TABSIZE);
			tabDisplacement = i / TABSIZE;
			if (tabCount - tabDisplacement == 0)
				c = (i + j) - 
					tabCount * TABSIZE - (displacement%TABSIZE);
			else
				c = (i + j) - 
					tabCount * TABSIZE; 
			tabCount = tabCount - tabDisplacement;
			i = i + j - 1;//to avoid entering multiple times
			printf("c is <%d>,tabCount is <%d>, tabDisplacement=<%d>\n",
					c,tabCount, tabDisplacement);
			for (j=0; j<tabCount; ++j)
				holder[displacement+j] = '\t';
			for (j=0; j<c; ++j)
				holder[displacement+tabCount+j] = ' ';
			displacement = c+tabCount+displacement;
		}else{
			holder[displacement] = c;
			++displacement;
		}
	holder[displacement]='\0';
	copy(s,holder);
}

void fold(char s[], int size, int lineLengt){
	int lastBlank, c, i, displacement;
	displacement=0;
	lastBlank = -1;
	char obj[MAXLINE];
	//detab(s,size);
	for (i=0; (c=s[i])!='\0'; ++i)
	{
		if (c==' '&&lastBlank!=-1)
			lastBlank = i;
		if (i%lineLengt==0)
		{
			if (lastBlank!=-1)
			{
				obj[lastBlank] = '\n';
				lastBlank = -1;
			}else{
				obj[displacement] = '\n';
				++displacement;
			}
		}
		obj[displacement] = s[i];
		++displacement;
	}
	obj[displacement] = '\0';
	copy(s,obj);
}
