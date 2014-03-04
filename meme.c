#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openFile.h"
#include "saveFile.h"
#include "crop.h"
#include "overlay.h"
#include "font.h"
#include "meme.h"
#include "image.h"

int main(int argc, char** argv)
{
	int i;
	meme** memes;

	if(argc != 3)
	{
		printf("Invalid number of arguments. Please try agian\n");
		return 1;
	}


	memes = readMemeFile(argv[1]);
	if(memes == 0)
	{
		return 0;
	}
	i = readActFile(argv[2], memes);
	if(i == 1)
	{
		return 1;
	}

	return 0;
}

meme** readMemeFile(char* file)
{
	FILE* in = fopen(file, "r");
	char* buffer = (char*)malloc(128 * sizeof(char));
	char* buffer2;
	char c;
	int wordCount = 1;
	int i = 0;
	int j;
	int size, length, charPos;
	meme** memes;
	font** fonts;


	if(in == 0){
		printf("Invalid file %s\n", file);
		return memes;
	}
	printf("File to open is %s\n", file);

	c = getc(in);
	while(c != EOF){

		/* Cleans buffer */
		for(i = 0; i < 128; i++)
		{
			buffer[i] = 0;
		}
		/* Gets the next line of the file */
		i = 0;
		while(c != '\n' && c != EOF)
		{	
			buffer[i] = c;
			i++;
			c = getc(in);
		}
		if(c == '\n')
		{
			c = getc(in);
		}
		buffer[i] = 0;
		i = 0;
		printf("Line is %s\n", buffer);

		/* POSSIBLE ERROR: next line shorter than prev line =>
		 * extra chars on the line that arn't supposed to be there */
		if(strlen(buffer) == 0)
		{
			continue;
		}
		
		wordCount = 0;
		/* Breaks the line into each word */
		while(buffer[i] != 0)
		{
			if(buffer[i] == ' ' || buffer[i] == ':')
			{
				buffer[i] = 0;
				wordCount++;
			}
			i++;
		}
			
		charPos = 0;
		buffer2 = &(buffer[charPos]);
		
		if(strcmp("MEMES", buffer2) == 0)
		{
			/* make array of memes maybe */
			memes = (meme**)malloc(wordCount * sizeof(meme*));
			size = wordCount;
			for(i = 0; i < size; i++)
			{
				memes[i] = (meme*)malloc(sizeof(meme));
				length = strlen(buffer2);
				charPos += length + 1;
				buffer2 = &(buffer[charPos]);
				memes[i]->name = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
				strcpy(memes[i]->name, buffer2);
			}
		}
		else if(strcmp("FONTS", buffer2) == 0)
		{
			/* make array of fonts maybe */
			fonts = (font**)malloc(wordCount * sizeof(font*));
			for(i = 0; i < wordCount - 1; i++)
			{
				fonts[i] = malloc(sizeof(font));
				length = strlen(buffer2);
				charPos +=  length + 1;
				buffer2 = &(buffer[charPos]);
				fonts[i] = openFont(buffer2);
			}
		}
		/* check if meme data */
		/* else return 1 */
		else
		{
			for(i = 0; i <= size; i++)
			{
				if(i == size)
				{
					printf("File Error \n");
					memes = 0;
					return memes;
				}
	
				if(strcmp(memes[i]->name, buffer2) == 0)
				{
					length = strlen(buffer2);
					charPos +=  length + 1;
					buffer2 = &(buffer[charPos]);
					if(strcmp("FILE", buffer2) == 0)
					{
						length = strlen(buffer2);
						charPos +=  length + 1;
						buffer2 = &(buffer[charPos]);
						memes[i]->file = (char*)malloc((strlen(buffer2) - 1) * sizeof(char));
						strcpy(memes[i]->file, buffer2);
					}
					else if(strcmp("TOP", buffer2) == 0)
					{
						length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);
						memes[i]->topW = atoi(buffer2);
						
						length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);
						memes[i]->topH = atoi(buffer2);
					}
					else if(strcmp("BOTTOM", buffer2) == 0)
					{
						length = strlen(buffer2);					
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);
						memes[i]->botW = atoi(buffer2);
	
						length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);
						memes[i]->botH = atoi(buffer2);
					}
					else
					{
						printf("File error 2\n");
						memes = 0;
						return memes;
					}
					break;
				}
			}
		}
	}
	for(i = 0; i < size; i++)
	{
		memes[i]->fonts = fonts; /* definitely gonna be a problem */
	}
	return memes;
}
int readActFile(char* file, meme** memes)
{
	char* out;
	int memeNum, fontNum;
	char* top;
	char* bot;

	char* buffer = (char*)malloc(128 * sizeof(char));
	char* buffer2;
	int i;
	int charPos;
	char c;
	FILE* in = fopen(file, "r");

	if(in == 0)
	{
		printf("Couldn't open file at %s", file);
		return 1;
	}
	
	c = getc(in);
	while(c != EOF)
	{
		i = 0;
		while(c != '\n' && c != EOF)
		{
			buffer[i] = c;
			i++;
			c = getc(in);
		}
		buffer[i] = 0;
		if(c == '\n')
		{
			c = getc(in);
		}
		if(strlen(buffer) == 0)
		{
			continue;
		}
		i = 0;
		while(buffer[i] != 0)
		{
			if(buffer[i] == ':')
			{
				buffer[i] = 0;
			}
			i++;
		}

		charPos = 0;
		buffer2 = &(buffer[charPos]);
	
		if(strcmp(buffer2, "OUTFILE") == 0)
		{

		}
		else if(strcmp(buffer2, "MEME") == 0)
		{

		}
		else if(strcmp(buffer2, "FONT") == 0)
		{

		}
		else if(strcmp(buffer2, "TOP") == 0)
		{

		}
		else if(strcmp(buffer2, "BOTTOM") == 0)
		{

		}
		else
		{
			printf("%s is not a valid command\n", buffer2);
			return 1;
		}
	}

}

image* textImg(char* in, meme m)
{
	image* text;
	int i;
	char c;

	text = newImg(0,0);

	for(i = 0; i < strlen(in); i++)
	{	
		
	}
}
