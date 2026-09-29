#include <stdio.h>
#include <ctype.h>

void rreverse(char s[], int i){
	static int maxi=0;
	char c;
	if(s[i]=='\0')//base case
		return;
	else{
		c=s[maxi++];
		rreverse(s, i+1);
		s[maxi-i-1] = c;
		maxi=(i==0)?0:maxi;
	}
}

void ritoa(int num, char s[], int i){
	static int maxi=0;
	if (num!=0){
		maxi++;
		if (i==0 && num<0){
			num*=-1;
			i=1;
			s[0]='-';
			maxi+=2;
		}
		ritoa(num/10, s, i+1);
		s[maxi-i-1]=num%10+'0';
		maxi=(i==0||(i==1&&s[0]=='-'))?0:maxi;
	}
	else
		if(s[0]=='-')
			s[maxi-1]='\0';
		else
			s[maxi]='\0';
}

//A confusion ocurred and I though that itoa converted strings to integers. 
//it is the other way around witch makes these way easier
/*
int ritoa(char s[], int i){
	char c;
	static double power;
	static int sign;
	power = 0;
	
	if (s[i]=='\0'){
		power = 0.1;
		return 0;
	}else if(s[i]=='-'){
		sign = -1;
		i++;
	}else if (s[i]=='+'){
		sign = 1;
		i++;
	}else
		sign=1;

	power*=10;
	//too many checks? Maybe, but I wanna go further and I cannot think on another
	//alternative to fix the sign problem. Alternatives would entail
	//- to add a seond function, but the work says that I must make these
	//function the recursive one. 
	//- to pourposefully force users to insert a 1 value on the first call
	//so I do not hav to do the checks, and can just do these in the base case
	//having a secondary array in withc I go storing values too, so I can
	//invert them with a second static var
	return (c-'0')*power*(i==0?sign:1) + ritoa(s,++i);
}*/

int strindexr(char s[], char t[]){
	int i, j, k, patternSize;
	//sacamos la longitud del string
	for(patternSize=0; t[patternSize]!='\0'; ++patternSize);
	--patternSize;
	for(i=0; s[i]!='\0'; ++i);
	--i;//point to the non NULL end
	for(; i>=0; --i){
		for(j=patternSize, k=i; k>=0 && j>= 0 && s[k]==t[j]; --j, --k);
		if(j<0)
			return i;
	}
	return -1;	
}

/*normal version of strindex*/
int strindex(char s[], char t[]){
	int i, j, k;
	for (i=0; s[i]!='\0'; i++) {
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++);
		if (k>0 && t[k]=='\0')
			return i;
	}
	return -1;
}

static double atopow(char s[], int i){
	int  val;
	double ret, base;
	//whe ignore the number's sign it is not our problem here
	//whe just get a magnitude
	base = (s[i] == '-') ? 0.1 : 10;
	if (s[i]=='+' || s[i]=='-')
		i++;

	for(val=0; isdigit(s[i]); i++)
		val=10.0*val+(s[i]-'0');
	for (ret=1; val>0; val--)
		ret*=base;

	return ret;
}

double atof(char s[]){
	double val, power;
	int i, sign;
	//take out all the trailing spaces
	for(i=0; isspace(s[i]); i++);
	//take the number's sign
	sign = (s[i] == '-') ? -1: 1;
	if (s[i]=='+' || s[i]=='-')
		i++;

	for(val=0.0; isdigit(s[i]); i++)
		val=10.0*val+(s[i]-'0');
	if(s[i]=='.')
		i++;
	for(power=1.0; isdigit(s[i]); i++){
		val=10.0*val+(s[i]-'0');
		power*=0.1;
	}
	//if it's sientific notation whe do extra job
	if (s[i]=='e' || s[i]=='E'){
		//the name is weird in these case but escentially. 
		//for our pourposes, these variable ougth to grow if
		//the result of these atoi is negative
		i++;
		power *= atopow(s, i);
	}

	if (power>0)
		return sign * val * power;
	return 0;
}

int atoi(char s[]){
	return (int) atof(s);
}

int getlineC(char s[], int lim){
	int c, i;
	for(i=0; (i<lim-1)&& ( (c=getchar()) != EOF) && (c!='\n'); ++i)
		s[i]=c;
	if (c=='\n') {
		s[i]=c;
		++i;
	}
	s[i]='\0';
	if (c==EOF)
		return -1;
	return i;
}
