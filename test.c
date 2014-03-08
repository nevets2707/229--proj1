#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "font.h"
#include "crop.h"
#include "image.h"
#include "openFile.h"
#include "saveFile.h"

int main(int argc, char** argv)
{
	
	font* f = malloc(sizeof(font));
	image* i = malloc(sizeof(image));

	f = openFont("impact.fsf");
	i = textImg("LOLOLOL", f); 

	save(i, "test.simp");

	return 0;
}

image* addText(image* toChange, image* toAdd)
{
	int i, x, y;
	int x2, y2, oldWidth;
	oldWidth = toChange->width;
	y = toChange->height;
	
	toChange->width += toAdd->width;
/*	toChange->height += toAdd->height; */

/*	toChange->pix = (pixel**)realloc(toChange->pix, toChange->height); */
	
	for(i = 0; i < toChange->height; i++)
	{
		toChange->pix[i] = (pixel*)realloc(toChange->pix[i], toChange->width * sizeof(pixel));
	}

	x2 = 0;
	y2 = 0;
	for(y = 0; y < toChange->height; y++)
	{
		x2 = 0;
		for(x = oldWidth; x < toChange->width; x++)
		{
			toChange->pix[y][x].red = toAdd->pix[y2][x2].red;
			toChange->pix[y][x].green = toAdd->pix[y2][x2].green;
			toChange->pix[y][x].blue = toAdd->pix[y2][x2].blue;
			toChange->pix[y][x].alpha = toAdd->pix[y2][x2].alpha;
			x2++;
		}
		y2++;
	}
	return toChange;
}

image* textImg(char* in, font* f)
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
				save(nextLetter, "test2.simp");
				/* add to text image */
				text = addText(text, nextLetter);			
				break;
			}
		}
	}
	return text;
}
