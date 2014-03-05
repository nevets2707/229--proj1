#include "font.h"

#ifndef __MEME_H_
#define __MEME_H_

typedef struct meme_s
{
	char* name;
	char* file;
	pos** loc;
	font** fonts; /* maybe */
} meme;

typedef struct pos_s
{
	char* name;
	int x;
	int y;
} pos;

meme** readMemeFile(char* file);

int readActFile(char* file, meme** memes);

#endif

