#include <stdio.h>
#define MAXLINE 1000
#define TABSIZE 8
	
#define BAD_SINGLE_COMENT 0
#define BAD_PAIRING 1
#define ALL_GOOD 2
#define BAD_CHAR_CONST 3
#define BAD_STRING_CONST 4
#define ILEGAL_STATE 5
int getline(char line[], int maxline);
void copy(char to[], char from[]);
void detab(char s[], int size);
void entab(char s[], int size);
void fold(char s[], int size, int lineLengt);
void deComenter(char s[], int size);
void append(char s[], char extra[]);
void getTextBlock(char textBlock[]);
int errorChecker(char textBlock[], int row, int column);
void printErrorMessage(int errorCode);
int main(void){
	char line[MAXLINE];
	char textBlock[MAXLINE];
	getTextBlock(textBlock);
	printErrorMessage(errorChecker(textBlock, 0, 0));
//	deComenter(textBlock, MAXLINE);
//	printf("The de comented code looks like this \n%s\n", textBlock);
//	while(getline(line, MAXLINE) > 0){
//		detab(line, MAXLINE);
//		fold(line, MAXLINE, 8);
//		printf("The folder line looks like this \n%s\n", line); 
//	}
	return 0;
}

void printErrorMessage(int errorCode){
	if (errorCode==BAD_SINGLE_COMENT)
		printf("Error inclomplete single coment\n");
	else if(errorCode==BAD_PAIRING)
		printf("Error incomplete (, { or [ secuence\n");
	else if(errorCode==BAD_CHAR_CONST)
		printf("Error incorrect char constant");
	else if(errorCode==BAD_STRING_CONST)
		printf("Error incorrect string constant");
	else if(errorCode==ILEGAL_STATE)
		printf("Either a constant or a coment were never finished");
	else if(errorCode==ALL_GOOD)
		printf("There were no basic errors on the code");
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

void deComenter(char s[], int size){
#define MONO_LINE_COMENT 1
#define OUT_COMENT 0
#define MULTI_LINE_COMENT 2
#define IN_CONSTANT 3
	int state, c, i, cEndingStart,cEndingEnd, displacement;
	char holder[MAXLINE];
	state = OUT_COMENT;
	displacement = 0;
	for (i=0; (c=s[i]) != '\0'; ++i)
		if (state == OUT_COMENT){
			if (c == '/' && s[i+1]=='/') 
			{
				state = MONO_LINE_COMENT;
				++i;
			}
			else if(c == '/' && s[i+1]=='*') {
				cEndingStart = s[i+1];
				cEndingEnd = c;
				state = MULTI_LINE_COMENT;
				++i;//so in next iteration it will be ignored
			}else if(c=='"' || c=='\''){
				state = IN_CONSTANT;
				cEndingEnd = c;
				holder[displacement] = c;
				++displacement;
			}else {
				holder[displacement] = c;
				++displacement;
			}
		}else if(state == MONO_LINE_COMENT && c=='\n'){
			state = OUT_COMENT;
		}else if(state == MULTI_LINE_COMENT && c==cEndingStart && s[i+1]==cEndingEnd){
			state = OUT_COMENT;
			++i;
			cEndingStart = -1;
			cEndingEnd = -1;
		}else if(state == IN_CONSTANT){
			holder[displacement]=c;
			++displacement;
			if (c==cEndingEnd)
				state = OUT_COMENT;
		}
	holder[displacement] = '\0';
	copy(s, holder);
}

void append(char s[], char extra[]){
	int i, j, c;
	//to get i's position
	for (i=0;s[i] != '\0';++i);
	for (j=0;(c=extra[j]) != '\0';++j)
		s[i+j] = c;
	s[i+j] = '\0';
}

void getTextBlock(char textBlock[]){
	char line[MAXLINE];
	textBlock[0] = '\0';
	while(getline(line, MAXLINE)>0)
		append(textBlock, line);
}

int indexForChar(int c){
	if (c=='('||c==')')
		return 0;
	else if(c=='{'||c=='}')
		return 1;
	else if(c=='['||c==']')
		return 2;
	else 
		return -129;
}

int errorChecker(char t[], int row, int column){
#define GENERAL_CHECK 0
#define CHAR_CONST_CHECK 1
#define STRING_CONST_CHECK 2
#define MULTI_LINE_COMENT_CHECK 3
	int i, c, state, lengt;
	int paringCounter[3];
	for (i=0; i<3; ++i)
		paringCounter[i]=0;
	state = GENERAL_CHECK;
	for (i=0; (c=t[i])!='\0';++i)
		if(state == GENERAL_CHECK)
		{
			if(c=='\'')
			{
				lengt = 0;
				state=CHAR_CONST_CHECK;
			}
			else if(c=='"')
				state=STRING_CONST_CHECK;
			else if(c=='/')
			{
				if(t[i+1]=='*')
					state=MULTI_LINE_COMENT_CHECK;
				else if (t[i+1]!='/')
					return BAD_SINGLE_COMENT;
				else 
					++i;//so whe skip what was already checked 
			}else if(c=='{' || c=='(' || c=='[')
				++paringCounter[indexForChar(c)];
			else if(c=='}' || c==')' || c==']')
			{
				--paringCounter[indexForChar(c)];
				if (paringCounter[indexForChar(c)]<0)
					return BAD_PAIRING;
			}
		}else if(state == CHAR_CONST_CHECK){
			if (lengt > 2)
				return BAD_CHAR_CONST;
			if (c=='\'')
				state = GENERAL_CHECK;
			if (c=='\\'){
				if (t[i+1]==' ' || t[i+1]=='\t' || t[i+1]=='\n')
					return BAD_CHAR_CONST;
				else
					++i;//also to avoid the case wehre '\'' crashing 
			}
			++lengt;
		}else if(state == STRING_CONST_CHECK){
			if (c=='"')
				state = GENERAL_CHECK;
			if (c=='\\')
			{
				if (t[i+1]==' ' || t[i+1]=='\t' || t[i+1]=='\n')
					return BAD_STRING_CONST;
				else
					++i;
			}
			if (c=='\n')
				return BAD_STRING_CONST;
		}else if(state == MULTI_LINE_COMENT_CHECK){
			if(c=='*')
				if (t[i+1]=='/'){
					++i;
					state = GENERAL_CHECK;
				}
		}
	for(i=0; i<3; ++i)
		if (paringCounter[i]!=0)
			return BAD_PAIRING;
	if (state != GENERAL_CHECK)//this is the only state that woul signify a normal ending
		return ILEGAL_STATE;
	return ALL_GOOD;
}
