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
	int size, size2, length, charPos;
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
				memes[i]->locCount = 0;
				memes[i]->loc = (pos**)malloc(memes[i]->locCount);
			}
		}
		else if(strcmp("FONTS", buffer2) == 0)
		{
			/* make array of fonts maybe */
			fonts = (font**)malloc(wordCount * sizeof(font*));
			for(i = 0; i < wordCount; i++)
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
					else
					{
						j = memes[i]->locCount;
						memes[i]->locCount++;
						memes[i]->loc = (pos**)realloc(memes[i]->loc, memes[i]->locCount * sizeof(pos*));
						
				/*		length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);
				*/		
						memes[i]->loc[j] = (pos*)malloc(sizeof(pos));
						memes[i]->loc[j]->name = (char*)malloc(strlen(buffer2) * sizeof(char));
						strcpy(memes[i]->loc[j]->name, buffer2);
						
						length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);

						memes[i]->loc[j]->x = atoi(buffer2);

						length = strlen(buffer2);
						charPos += length + 1;
						buffer2 = &(buffer[charPos]);

						memes[i]->loc[j]->y = atoi(buffer2);
					}
					break;
				}
			}
		}
	}
	for(i = 0; i < size; i++)
	{
		size2 = sizeof(fonts) / sizeof(font*);
		memes[i]->fonts = (font**)malloc(sizeof(fonts));
		/* memes[i]->fonts = fonts;  definitely gonna be a problem */
		/* I think I'm only making a shallow copy so I only get the 
		 * font array not the values too */
		for(j = 0; j < size2; j++)
		{
			memes[i]->fonts[j] = fonts[j];
		}
	}
	return memes;
}
int readActFile(char* file, meme** memes)
{
	char* out;
	int memeNum, fontNum, textNum;
	char* top;
	char* bot;
	image** textLines;
	image* m;

	char* buffer = (char*)malloc(128 * sizeof(char));
	char* buffer2;
	int i, x, y;
	int length, size;
	int charPos;
	char c;
	FILE* in = fopen(file, "r");
	textLines = (image**)malloc(sizeof(image*));
	textNum = 0;

	if(in == 0)
	{
		printf("Couldn't open file at %s\n", file);
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
		printf("Line is %s\n", buffer);
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
	

		memeNum = 0;
		fontNum = 0;
		if(strcmp(buffer2, "OUTFILE") == 0)
		{
			length = strlen(buffer2);
			charPos += length + 1;
			buffer2 = &(buffer[charPos]);

			out = (char*)malloc(strlen(buffer2) * sizeof(char));
			strcpy(out, buffer2);
		}
		else if(strcmp(buffer2, "MEME") == 0)
		{
			length = strlen(buffer2);
			charPos += length + 1;
			buffer2 = &(buffer[charPos]);

			size = sizeof(memes) / sizeof(meme*); /* Does this work */
			for(memeNum; memeNum <= size; memeNum++)
			{
				if(memeNum == size)
				{
					printf("Couldn't find meme: %s\n", buffer2);
					return 1;
				}
				if(strcmp(memes[memeNum]->name, buffer2) == 0)
				{
					m = open(memes[memeNum]->file);
					break;
				}
			}
		}
		else if(strcmp(buffer2, "FONT") == 0)
		{
			length = strlen(buffer2);
			charPos += length + 1;
			buffer2 = &(buffer[charPos]);

			size = sizeof(memes[memeNum]->fonts) / sizeof(font*);
			for(fontNum; fontNum <= size; fontNum++)
			{
				if(fontNum == size)
				{
					printf("Couldn't find font: %s\n", buffer2);
					return 1;
				}
				if(strcmp(memes[memeNum]->fonts[fontNum]->name, buffer2) == 0)
				{
					break;
				}	
			}
		}	
		else
		{
			size = memes[memeNum]->locCount;
			for(i = 0; i <= size; i++)
			{
				if(i == size)
				{
					printf("%s is not a valid command\n", buffer2);
					return 1;
				}
				if(strcmp(memes[memeNum]->loc[i]->name, buffer2) == 0)
				{
					length = strlen(buffer2);
					charPos += length + 1;
					buffer2 = &(buffer[charPos]);

					textLines = realloc(textLines, sizeof(textLines) + sizeof(image*));
					/* make new image with textImg() */
					textLines[textNum] = (image*)malloc(sizeof(image));
					textLines[textNum] = textImg(buffer2, memes[memeNum], memes[memeNum]->fonts[fontNum]);	
					if(textLines[textNum] == 0)
					{
						return 1;
					}
					x = memes[memeNum]->loc[i]->x - (textLines[textNum]->width / 2);
					y = memes[memeNum]->loc[i]->y - (textLines[textNum]->height / 2);
					m = overlay(m, textLines[textNum], x, y);
					break;
				}
			}
		}
	}

	/* Overlay all of the textLines to the image file, out
	 * find the position by x - (textLines->width / 2) and 
	 * y - (textLines->height / 2) (probably) */
	
	save(m, out);
	
}

image* textImg(char* in, meme* m, font* f)
{
	image* text;
	image* nextLetter;
	int i, j;
	char c;

	text = newImg(1,40);

	for(i = 0; i < strlen(in); i++)
	{	
		for(j = 0; j <= f->charCount; j++)
		{
			if(j == f->charCount)
			{
				printf("Cannot use char: %c\n", in[i]);
				text = 0;
				return text;
			}
		
			if(in[i] == f->list[j]->value)
			{
				nextLetter = crop(f->fileLocation, f->list[j]->x, f->list[j]->y, f->list[j]->w, f->list[j]->h);	
				/* add to text image */
				addText(text, nextLetter);			
				break;
			}
		}
	}
	return text;
}

void addText(image* toChange, image* toAdd)
{
	int i, x, y;
	int x2, y2;
	x = toChange->width;
	y = toChange->height;
	
	toChange->width += toAdd->width;
/*	toChange->height += toAdd->height; */

/*	toChange->pix = (pixel**)realloc(toChange->pix, toChange->height); */
	
	for(i = 0; i < toChange->height; i++)
	{
		toChange->pix[i] = (pixel*)realloc(toChange->pix[i], toChange->width);
	}

	x2 = 0;
	y2 = 0;
	for(x; x < toChange->width; x++)
	{
		y2 = 0;
		for(y; y < toChange->height; y++)
		{
			toChange->pix[x][y].red = toAdd->pix[x2][y2].red;
			toChange->pix[x][y].green = toAdd->pix[x2][y2].green;
			toChange->pix[x][y].blue = toAdd->pix[x2][y2].blue;
			toChange->pix[x][y].alpha = toAdd->pix[x2][y2].alpha;
			y2++;
		}
		x2++;
	}
	return;
}
