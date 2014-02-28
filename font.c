#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "letter.h"
#include "font.h"

font openFont(char* file)
{
	int i;
	int line, count;
	char c;
	char* temp;
	font* newFont;
	FILE* in = fopen(file, "r");

	if(in == 0)
	{
		printf("Couldn't open the font file\n");
		return;
	}

	newFont = (font*)malloc(sizeof(font));
	temp = (char*)malloc(128 * sizeof(char));

	newFont->charCount = 0;

	c = getc(in);
	count = 0;
	line = 0;
	while(c != EOF)
	{
		while(c != '\n' && c != EOF)
		{
			temp[count] = c;
			count++;
			c = getc(in);
		}
		temp[count] = 0;
		if(line == 0)
		{
			newFont->name = (char*)malloc(strlen(temp) * sizeof(char));
			for(i = 5; temp[i] != 0; i++)
			{
				newFont->name[i-5] = temp[i];
			}
			line++;
		}
		if(line == 1)
		{
			/*set file location */
			line++;
		}

		newFont->charCount++;
	}

	/*redo the loop focusing on adding lines >=2 as letters */

}

letter createLetter(font* newFont, char* input)
{

}
