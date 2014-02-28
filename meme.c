#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openFile.h"
#include "saveFile.h"
#include "crop.h"
#include "overlay.h"
#include "font.h"
#include "meme.h"

int main(int argc, char** argv)
{
	int i;
	if(argc != 3)
	{
		printf("Invalid number of arguments. Please try agian\n");
		return 1;
	}


	i = readMemeFile(argv[2]);
	if(i == 1)
	{
		return 1;
	}
	i = readActFile(argv[3]);
	if(i == 1)
	{
		return 1;
	}

	return 0;
}

int readMemeFile(char* file)
{
	void (*method)(void* data);
	FILE* in = fopen(file, "r");
	char* buffer = (char*)malloc(128 * sizeof(char));
	char* buffer2;
	char c;
	int wordCount = 1;
	int i = 0;
	int length;
	meme* memes;
	font* fonts;


	if(open == 0){
		printf("Invalid file %s\n", file);
		return 1;
	}

	/* Gets the next line of the file */
	while(c = getc(in) != '\n')
	{
		buffer[i] = c;
		i++;
	}
	buffer[i] = 0;
	
	i = 0;

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

	buffer2 = buffer;
	
	if(strcmp("MEMES", buffer2) == 0)
	{
		/* make array of memes maybe */
		memes = (meme*)malloc(wordCount - 1 * sizeof(meme));
		for(i = 0; i < wordCount - 1; i++)
		{
			length = strlen(buffer2);
			buffer2 = buffer2 + length + 1;
			memes[i].name = buffer2; /* ??? */
		}
	}
	else if(strcmp("FONTS", buffer2) == 0)
	{
		/* make array of fonts maybe */
		fonts = (font*)malloc(wordCount - 1 * sizeof(font));
		for(i = 0; i < wordCount - 1; i++)
		{
			length = strlen(buffer2);
			buffer2 = buffer2 + length + 1;
			fonts[i] = openFont(buffer2);
		}
	}
	/* check if meme data */
	/* else return 1 */
}

int readActFile(char* file)
{

}
