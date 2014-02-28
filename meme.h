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
	font* fonts; /* maybe */
} meme;

#endif

