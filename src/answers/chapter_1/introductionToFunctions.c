#include <stdio.h>

#define TOP 300
#define BOT 0
#define STEP 20

int power(int m, int n);
float farhToCel(float farhVal);
float celToFarh(float celVal);

int main(void){
//	int i;
//	for (i=0; i<10; ++i)
//		printf("%d %d %d\n", i, power(2,i), power(-3,i));
	float i;

	for(i=BOT; i<TOP; i+= STEP)
		printf("fahr = %3.0f, cel = %5.1f\n", i, farhToCel(i));
	for(i=BOT; i<TOP; i+= STEP)
		printf("cel = %3.0f, farh = %5.1f\n", i, celToFarh(i)); 
	return 0;
}

int power(int base, int n){
	int p;
	for (p=1; n>0; --i)
		p = p * base;
	return p;
}

float farhToCel(float farhVal){
	return (5.0 / 9.0) * (farhVal - 32.0);
}

float celToFarh(float celVal){
	return (9.0/5.0) * celVal + 32.0;
}
