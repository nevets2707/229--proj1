#include <stdio.h>
#include <stdlib.h>
#include "font.h"


int main(int argc, char** argv)
{

	FILE* in = fopen("memes.mem", "r");
	char c;
	int i;
	char* buffer;
	font* f;
/*
	f = openFont("impact.fsf");
	printf("%s\n", f->name);
*/	
	char* a = (char*)malloc(5);
	a[0] = 'a';
	a[1] = 'b';
	a[2] = 0;
	char* c = "abcd";
	char* b = c;
	printf("%s\n", b);
	b[1] = 'c';
	printf("%s\n", b);
	printf("%s\n", c);
	
	
	 
/*
	buffer = malloc(128 * sizeof(char));
	c = getc(in);
	while(c != EOF)
	{
		i = 0;
		while(c != '\n' && c != EOF)
		{
			buffer[i] = c;
			i++;
			printf("%c ", c);
			c = getc(in);
		}
		if(c == '\n')
		{
			c = getc(in);
		}
		 buffer[i] = 0;
		printf("\nBuffer is %s\n", buffer);

	}
*/
	return 0;
}
