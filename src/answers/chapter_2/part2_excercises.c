#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#define MAXLINE 1000
void limit_checker(void);
int htoi(char number[]);
int getline(char line[], int maxline);
void squeeze(char s1[], char s2[]);
int any(char s1[], char s2[]);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
unsigned bitcount(unsigned x);
void lower(char s[]);
int main(void){
//	char line[MAXLINE], line2[MAXLINE];
	//getline(line, MAXLINE);
	//printf("La linea insertada fue \n<%s>\n", line);
//	getline(line, MAXLINE);
//	getline(line2, MAXLINE);
//	printf("Las lineas insertadas fueron\nBase: %sCaracteres a eliminar: %s", line, line2); 
//	squeeze(line, line2);
//	printf("La nueva linea con caracteres eliminados es %s", line);
//	printf("La posicion del primer caracter de la segunda es %d", any(line, "z"));
//	printf("El digito ingresado es <%s> el numero que se obtiene es <%0x>", line, htoi(line));
	unsigned x, y;
	int p, n;
	char line[] = "Hola ESTO Esta CApitalizado AlEatOriAMente",
	     line2[]= "Hola ESTO Esta CApitalizado AlEatOriAMente";
	x = 0x94;
	y = 0xFF;
	n = 2;
	p = 1;
	printf("Los numeros insertados son <x = %0x, p = %0x, n = %0x, y = %0x>\n", x, p, n, y); 
	printf("El numero x seteado es <%0x>\n", setbits(x, p, n, y));
	printf("El numero de x invertido segun p y n es <%0x>\n", invert(x, p, n));
	printf("El numero de x rotado a derecha segun 3 es <%0x>\n", rightrot(x, 3u));
	printf("El numero de bits en 1 de x es igual a <%0x>", bitcount(x));
	lower(line2);
	printf("La linea \n<%s>\n des-capitalizada es igual a \n<%s>\n",line, line2);  
	return 0;
}
void lower(char s[]){
	int i;
	char c;
	for (i=0; (c=s[i])!='\0'; ++i){
		s[i]=(c>='A' && c<='Z')?c-'A' + 'a':c;
	}
}

unsigned bitcount(unsigned x){
	unsigned b;
	//this works since every number followed only by 0s gets turned every 0 before into 1
	//in base 2, also on top of that the & operator will there fore made an and 
	//between a 0 and a 1 i nthe position of the right most 1 turning it 0
	//for the other numbers posterior to it, they are unscated by the change since the
	//-1 will only affect up until the very first 1
	//This therefore, does the same job as shifthing with an if but faster since it will 
	//affect directly the non 0 ones.
	for (b=0; x!=0; x&=(x-1))
		++b;
	return b;
}
unsigned rightrot(unsigned x, int n){
	const int integer_size = CHAR_BIT * sizeof(x) - 1;
	return (x>>n) | ~(~0u>>n) & (x<<(integer_size-n));
}

unsigned invert(unsigned x, int p, int n){
	return x ^ (~(~0 << n) << p);
}

unsigned setbits(unsigned x, int p, int n, unsigned y){
	return (x & ~(~(~0 << n) << p)) | ((y & ~(~0 << n)) << p);
}

unsigned getbits(unsigned x, int p, int n){
	return (x >> (p+1-n)) & ~(~0 << n);
}

int any(char s1[], char s2[]){
	int i, j, match;
	match = 0;
	for(i=0; s1[i]!='\0' && !match; ++i)
		for (j=0; s2[j]!='\0'&& !match; ++j)
			match = (s1[i] == s2[j]);
	if(match)
		return i-1;
	return -1;
}

void squeeze(char s1[], char s2[]){
	int i, j, k,match;
	match = 0;
	for(k=i=0; s1[i]!='\0'; ++i){
		for(j=0;s2[j]!='\0' && !match;++j)
			match = (s1[i] == s2[j]);
		if (!match)
			s1[k++] = s1[i];
		else
			match=0;
	}
	s1[k]='\0';
}

int getline(char s[], int lim){
	int c, i;
	for(i=0; (i<lim-1) * ( (c=getchar()) != EOF) * (c!='\n'); ++i)
		s[i]=c;
	if (c=='\n') {
		s[i]=c;
		++i;
	}
	s[i]='\0';
	return i;
}

int htoi(char s[]){
	const int LAST_CONTROL_INDEX = 2;
	const int BASE = 16;
	int i=0, c, ret, power, number_start=0;
	while((c=s[i]) != '\0' && c != '\n')
		++i;
	--i;
	ret = 0;
	power = 1;
	if (s[0] == '0')
		number_start = LAST_CONTROL_INDEX;
	while(i>=number_start){
		c= s[i];
		if (isalpha(c)){
			if (isupper(c))
				ret = (c-'A' + 10)*power+ret;
			else
				ret = (c-'a' + 10)*power+ret;
		}
		else
			ret = (s[i]-'0')*power + ret;
		power = BASE*power;
		--i;
	}
	return ret;
}

void limit_checker(void){

	long limit_long, old_long;
	int limit_int, old_int;
	signed char limit_char, old_char;
	printf("Los limites de long, int, char signados son son:\n"
			"<Long, <%ld> <%ld>>\n<Int, <%d> <%d>>\n<Char, <%d> <%d>>\n", 
			LONG_MAX, LONG_MIN, INT_MAX, INT_MIN, SCHAR_MAX, SCHAR_MIN);
	//I just dicovered that on my machine, long and int are the same length
	printf("Los limites de long, int, char no signados son son:\n"
			"<Long, <%lu>>\n<Int, <%u>>\n<Char, <%d>>\n", 
			ULONG_MAX, UINT_MAX, UCHAR_MAX);
	limit_long = 1;
	old_long = 0;
	while (limit_long > old_long){
		old_long = limit_long;
		++limit_long;
	}
	old_int = 0;
	limit_int = 1;
	while (limit_int > old_int){
		old_int = limit_int;
		++limit_int;
	}
	old_char = 0;
	limit_char = 1;
	while (limit_char > old_char){
		old_char = limit_char;
		++limit_char;
	}
	printf("Segun lo calculado los limites son:\n"
			"<Long, <%ld> <%ld>>\n"
			"<Int, <%d> <%d>>\n"
			"<Char, <%d> <%d>>\n", 
			old_long, -old_long - 1, 
			old_int, -old_int -1, 
			old_char, -old_char - 1);
	printf("Segun lo calculado los limites de unsigned son:\n"
			"<Long, <%lu>>\n"
			"<Int, <%u>>\n"
			"<Char, <%u>>\n",
			old_long * 2 + 1,
			old_int * 2 + 1,
			old_char * 2 + 1);

}
