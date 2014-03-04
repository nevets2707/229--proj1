#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "letter.h"
#include "font.h"

font* openFont(char* file)
{
	int i;
	int count, line;
	char c;
	char* temp;
	char* temp2;
	font* newFont;
	FILE* in = fopen(file, "r");

	if(in == 0)
	{
		printf("Couldn't open the font file\n");
		return;
	}

	newFont = (font*)malloc(sizeof(font));
	newFont->list = (letter*)malloc(0);
	temp = (char*)malloc(128 * sizeof(char));

	newFont->charCount = 0;

	c = getc(in);
	count = 0;
	line = 0;

	while(c != EOF)
	{
		count = 0;
		while(c != '\n' && c != EOF)
		{
			temp[count] = c;
			count++;
			c = getc(in);
		}
		if(c == '\n')
		{
			c = getc(in);
		}
		temp[count] = 0;

		temp2 = temp;
		if(strcmp(temp2, "NAME") == 0)
		{
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->name = (char*)malloc(strlen(temp2) + 1 * sizeof(char));
			newFont->name = temp2;
			printf("%s\n", newFont->name);
		}
		else if(strcmp(temp2, "IMAGE") == 0)
		{
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->fileLocation = (char*)malloc(strlen(temp2) + 1 * sizeof(char));
			newFont->fileLocation = temp2;
		
		}
		else if(strcmp(temp2, "CHARACTER") == 0) /*Account for wildcard char */
		{
			/* realloc memory for the list of letters and adds data from the line */
			newFont->list = (letter*)realloc(newFont->list, sizeof(newFont->list) + sizeof(letter));
			
			newFont->list[line].value = temp2[9];
			
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->list[line].x = atoi(temp2);
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->list[line].y = atoi(temp2);
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->list[line].w = atoi(temp2);
			temp2 = temp2 + strlen(temp2) + 1;
			newFont->list[line].h = atoi(temp2);

			line++;
		}

		newFont->charCount = line;
	}
	return newFont;
}

