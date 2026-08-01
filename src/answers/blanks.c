#include <stdio.h>

int main(void)
{
//	int c, nl;
//	nl = 0;
//	while((c=getchar()) != EOF)
//		if (c=='\n')
//			++nl;
//	printf("%d\n", nl);
//	int counter, ch; 
//	counter = 0;
	//as a note getchar() blocks the program until an input is detected
	//so it does catch everything basically
//	while( (ch = getchar()) != EOF){
//		if (ch == '\n')
//			++counter;
//		if (ch == ' ')
//			++counter;
//		if (ch == '\t')
//			++counter;
//	}
//	printf("Non visible characters counted = %d", counter);
//	int c, continous_blanks;
//	continous_blanks = 0;
//	while ((c=getchar()) != EOF){
			//Look I love to stick to "Use only what the book has shown you"
			//To solve excersices, but the book itself incentivices you to 
			//experiment, I do not believe the expected audience will not have
			//found && and || yet,
			//and this will look horrible if I don't use && and || so
			//I'll be using those here
		//if it is a blank and it is the first of them all just write a normal blank
//		if ((c==' ' || c== '\n' || c=='\t') && continous_blanks == 0)
//		{
//			putchar(' ');
//			++continous_blanks;
//		}
//		if ( c!=' ' && c!='\n' && c!='\t' )
//		{
//			putchar(c);
//			continous_blanks = 0;
//		}
//	}
	int c;
	while((c=getchar()) != EOF)
	{
		if (c == '\t')
		{
			putchar('\\');
			putchar('t');
		}
		if (c == '\b')//Note. The back space simply physically deletes a char
			      //so this one I cannot test
		{
			putchar('\\');
			putchar('b');
		}
		if (c == '\\')
		{
			putchar('\\');
			putchar('\\');
		}
		if (c != '\t' && c != '\b' && c != '\\')
			putchar(c);
	}
	return 0;
}
