#include "font.h"
#include "crop.h"

#ifndef __MEME_H_
#define __MEME_H_

typedef struct pos_s pos;

typedef struct meme_s
{
	char* name;
	char* file;
	pos** loc;
	font** fonts; /* maybe */
} meme;

struct pos_s
{
	char* name;
	int x;
	int y;
};

meme** readMemeFile(char* file);
int readActFile(char* file, meme** memes);
image* textImg(char* in, meme* m, font* f);
void addText(image* toChange, image* toAdd);

#endif

