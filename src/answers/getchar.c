#include <stdio.h>

int main(void)
{
	//Reading chars with getchar()
	//En windows EOF tipicamente es Ctrl+z
	//En linux es Ctrl+d
//	printf("El valor de getCharEs %d", getchar() != EOF);
//	printf("El valor de EOF es = %d", EOF);
	long nc;
	nc=0;
//	while(getchar() != EOF)
//		++nc;
//	NOTE: getchar() also takes in the "\n" char so take that into account if you notice
//	the counter being bigger than expected
	for(nc=0; getchar() != EOF; nc = ++nc)
		;
	printf("%ld\n", nc);
	return 0;
}
