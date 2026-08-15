#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#define MAXLINE 1000
int binsearch(int x, int v[], int n);
void escape(char s[], char t[]);
int atoi(char s[]);
void shellsort(int v[], int n);
void reverse(char s[]);
void expand(char s1[], char s2[]);
void itoa(int n, char s[]);
void itob(int n, char s[], int base);
void itoap(int n, char s[], int min);
int trim(char s[]);
int main(void){
	int numbers[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//	printf("La posicion en numbers de el numero %d es <%d>\n", 
//			7, binsearch(7, numbers, 14));
//	printf("La posicion en numbers de el numero %d es <%d>\n",
//			17, binsearch(17, numbers, 14));
	char text[] = "alelu maniqueni \n adjfew \t adaslok",
	     text2[MAXLINE],
	     text3[] = "Test a-z 1-9\na-b-c -a-e a-e- a-z1-9 ";
	int number = INT_MAX * (-1) - 1; 
	printf("The un edited text looke like this <%s>\n", text);
	escape(text2, text);
	printf("The edited text looks like this <%s>\n", text2);
	printf("This chain should get expanded <%s>\n", text3);
	expand(text3, text2);
	printf("This is the cahin expanded<%s>\n", text2); 
	printf("El numero negatio mas grande <%d>\n", number);
	itoa(number, text2);
	printf("Puede convertirse al string <%s>\n", text2);
	itob(number, text2, 16);
	printf("El numero se escribe como <%s>\n", text2);
	itoap(-3, text2, 7);
	printf("The numer -3 padded  by 7 looks like this <%s>\n",  text2);
	return 0;
}
int trim(char s[]){
	int n;
	for (n=strlen(s)-1; n>=0; --n)
		if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
			break;
	s[n+1]='\0';
	return n;

void itoap(int n, char s[], int min){
	int i;
	itoa(n, s);
	reverse(s);
	for (i=0; s[i]!='\0'; ++i)
		;
	while (i-1 < min)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}
void itob(int n, char s[], int base){

	int i, sign;
	unsigned num = (unsigned)n;

	sign = (n<0)?-1:1;
	if (n & (~0>>1) != 0)
		n *= -1;
	num = (unsigned) n;
	i = 0;
	do{
		s[i++] = num%base + '0';
	}while((num/=base) > 0);
	if(sign<0)
		s[i++] = '-';
	s[i]='\0';
	reverse(s);
}
//the text example had a problem were if you inserted it the biggest posible negative
//integer it did not gave back what it should, that is bacause the magnitud of negative 
//integers is greater than that of positive ones. To fix that whe jut treated it as an unsigned
//value in order to be able to take that last digit into account
void itoa(int n, char s[]){
	int i, sign;
	unsigned num;

	sign = (n<0)?-1:1;
	if (n & (~0>>1) != 0)
		n *= -1;
	num = (unsigned) n;
	i = 0;
	do{
		s[i++] = num%10 + '0';
	}while((num/=10) > 0);
	if(sign<0)
		s[i++] = '-';
	s[i]='\0';
	reverse(s);
}

int expandir(char s[], char chstart, char chend, int pos){
	int sign, j;
	sign = chend>chstart? 1: -1;
	for (j=1; j<( (chend-chstart) * sign); ++j)
		s[j+pos-1] = chstart+j*sign;//load all on order
	return (chend-chstart-1)*sign;
}

void expand(char s1[], char s2[]){
	int c, i, delta, post, ante;
	for (delta=0, i=0; (c=s1[i]) != '\0'; ++i)
		if (c == '-'){
			post = s1[i+1];
			ante = s1[i-1];
			if ( ( (isalpha(ante) && isalpha(post)) || 
					(isdigit(ante) && isdigit(post)) ) && 
					( (post - ante > 1) || (ante - post > 1) ) ) {
				delta += expandir(s2, ante, post, delta);
			}
			else
				s2[delta++]=c;
		}else 
			s2[delta++]=c;
	s2[delta] = s1[i];
}

void reverse(char s[]){
	int c, i, j;
	for ( i=0, j = strlen(s) - 1; i<j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

//sorts into increasing order
//NOTE: The standard does have a generic sort function, but it does not
//especify an algorithm so for reliability's sake you may prefer to still
//make your own sorting functions like this one. 
//NOTE2: Base on a read, this algorigm although not as fast as quick sort, 
//it is more reliably fast than it AKA this one does not get too far away in any direction
//from it's average time while quick sort have some edge cases were it fumbles hard.
void shellsort(int v[], int n){
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i=gap; i<n; i++)
			for(j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap){
				temp = v[j];
				v[j]=v[j+gap];
				v[j+gap]=temp;
			}
}

int atoi(char s[]){
	int i, n, sign;
	for(i=0; isspace(s[i]); i++)
		;

	sign = (s[i]=='-')? -1: 1;
	if(s[i]=='+' || s[i]=='-')
		i++;
	for(n=0; isdigit(s[i]); i++)
		n=10*n+(s[i]-'0');
	return sign * n;
}


void escape(char s[], char t[]){
	int i, c, delta;
	delta = 0;
	for (i=0; (c=t[i]) != '\0'; ++i){
		switch(c){
			case '\n':
				s[delta] = '\\';
				s[delta+1] = 'n';
				delta += 2;
				break;
			case '\t':
				s[delta] = '\\';
				s[delta+1] = 't';
				delta += 2;
				break;
			default:
				s[delta] = c;
				++delta;
				break;
		}
	}
	s[delta] = c;
}

int binsearch(int x, int v[], int n){
	int low, high, mid;
	
	low = 0;
	high = n-1;
	while( low < mid ){
		mid = (low + high) / 2;
		if(x < v[mid])
			high = mid + 1;
		else
			low = mid ;
	}
	if (x == v[mid])
		return mid;
	else
		return -1;
}
