#include <stdio.h>

int main(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	printf("Fahr\tCel\n");
	while( fahr <= upper ){
		celsius = (5.0/9.0) * (fahr - 32.0) ;
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	printf("Cel\tFahr\n");
	celsius = lower;
	upper = 120;
	step = 10;
	while( celsius <= upper ) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%3.0f\t%6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return 0;
}
