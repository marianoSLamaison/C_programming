#include <stdio.h>

#define IN 1 //whe are inside a word
#define OUT 0 //whe are outside a word

int main(void){
//	int c, nl, nw, nc, state;
//	
//	state = OUT;
//	nl = nw = nc = 0;
//	while((c=getchar()) != EOF){
//		++nc;
//		if (c == '\n')
//			++nl;
//		if (c == ' ' || c == '\n' || c == '\t')
//			state = OUT;
//		else if( state == OUT ){
//			state = IN;
//			++nw;
//		}
//	}
//	printf("%d %d %d\n", nl, nw, nc);
	int state,c;
	state = OUT;
	while ((c=getchar()) != EOF){
		if (c != ' ' && c != '\n' && c != '\t')
			putchar(c);
		if (c == ' ' || c == '\n' || c == '\t')
			putchar('\n');
	}
	return 0;
}
/*
 * In answer to the theory question. I will test it with pure blank, new line lines. Lines that
 * alternate between some of the especial characters too
 */
