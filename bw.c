/**
 *
 * File to make image black and white
 *
 */


#include <stdio.h>
#include "pixel.h"
#include "image.h"


int bw(int argc, char** argv)
{
	if(argc < 1)
	{
		return 1;
	}

	image* img = openfile(argv[1]);

	int i;
	int j;

	for(i = 0; i < img->width; i++)
	{
		for(j = 0; j < img->height; j++)
		{
			int r, g, b;
			r = img[i][j]->red;
			g = img[i][j]->green;
			b = img[i][j]->blue;
			
			int avg = (r + b + g) / 3;
			
			img[i][j]->red = avg;
			img[i][j]->green = avg;
			img[i][j]->blue = avg;

		}


	}








	return 0;

}
