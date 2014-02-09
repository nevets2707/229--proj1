/**
 *
 * File for cropping
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "pixel.h"
#include "openFile.h"
#include "saveFile.h"

int main(int argc, char** argv)
{
	image* img;
	image* newImg;
	int i, j;
	int xpos = 0;
	int ypos = 0;

	if(argc < 7)
	{
		return 1;
	}
 
	img = open(argv[1]);
	newImg = (image*)malloc(sizeof(image));

	newImg->width = atoi(argv[3]);
	newImg->height = atoi(argv[4]);
	
	for(i = 0; i < newImg->width; i++)
	{
		newImg->pix[i] = (pixel*)malloc(newImg->height * sizeof(pixel));
	}

	for(i = atoi(argv[3]); i < newImg->width; i++)
	{
		for(j = atoi(argv[4]); j < newImg->height; j++)
		{
			newImg->pix[xpos][ypos].red = img->pix[i][j].red;
			newImg->pix[xpos][ypos].green = img->pix[i][j].green;
			newImg->pix[xpos][ypos].blue = img->pix[i][j].blue;
			newImg->pix[xpos][ypos].alpha = img->pix[i][j].alpha;
			ypos++;
		}
		xpos++;
	}

	save(newImg, argv[2]);

	return 0;
}
