#include "font.h"

#ifndef __MEME_H_
#define __MEME_H_

typedef struct meme_s
{
	char* name;
	char* file;
	int topW;
	int topH;
	int botW;
	int botH;
	font** fonts; /* maybe */
} meme;

meme** readMemeFile(char* file);

int readActFile(char* file, meme** memes);

#endif

