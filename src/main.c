#include <stdio.h>
#define LENGTS_SIZE 15 //every thing under 3 goes grouped, 
		       //every thing avove 13 also goes grouped
#define IN 1
#define OUT 0
int main(void)
{
//	int c, i, nwhite, nother;
//	int ndigit[10];
//
//	nwhite = nother = 0;
//	for (i=0; i<10; ++i)
//		ndigit[i] = 0;
//	while((c=getchar()) != EOF)
//		if(c >= '0' && c <= '9')
//			++ndigit[c-'0'];
//		else if(c==' ' || c== '\n' || c=='\t')
//			++nwhite;
//		else
//			++nother;
//	printf("digits =");
//	for (i=0; i<10; ++i)
//		printf(" %d", ndigit[i]);
//	printf(", white space = %d, other = %d\n", nwhite, nother);
	int lengths[LENGTS_SIZE];
	int i, j , c, state, currentWordSize, mostRefs;
	state = OUT;
	currentWordSize = mostRefs = 0;
	for (i=0;i<LENGTS_SIZE; ++i)
		lengths[i]=0;
	while ((c=getchar()) != EOF){
		if (c==' ' || c=='\n' || c=='\t'){
			if (state==IN)
				if (currentWordSize<=3)
					++lengths[0];
				else if (currentWordSize>=LENGTS_SIZE)
					++lengths[LENGTS_SIZE-1];
				else
					++lengths[currentWordSize-3];
			state = OUT;
			currentWordSize = 0;
		}
		else {
			state = IN;
			++currentWordSize;
		}
	}
	for (i=0; i<LENGTS_SIZE; ++i)
		if (lengths[i] > mostRefs)
			mostRefs = lengths[i];
#define PADDING "|      |"
#define LONGSEP "+------+"
#define EMPTYCELL "|   |"
#define CELL "|888|"
#define SEP "+---+"
	printf(LONGSEP);
	for (i=0; i<LENGTS_SIZE; ++i)
		printf(SEP);
	putchar('\n');
	for (j=mostRefs; j>=0; --j)
	{
		printf(PADDING);
		for (i=0; i<LENGTS_SIZE; ++i)
			if(lengths[i] - j >= 0)
				printf(CELL);
			else
				printf(EMPTYCELL);
		putchar('\n');
	}
	printf(LONGSEP);
	for (i=0; i<LENGTS_SIZE; ++i)
		printf(SEP);
	printf("\n|legend|");
	printf("|3> |");
	for (i=3; i<LENGTS_SIZE+1; ++i)
		printf("|%3d|",i);
	printf("|15<|\n");
	return 0;
}
