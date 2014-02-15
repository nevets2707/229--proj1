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
	image* img2;
	int i, j;
	int xpos = 0;
	int ypos = 0;
	int x = atoi(argv[3]);
	int y = atoi(argv[4]);
	int w = atoi(argv[5]);
	int h = atoi(argv[6]);


	if(argc != 7)
	{
		return 1;
	}

 
	img = open(argv[1]);
	img2 = newImg(w, h);

	printf("Start at (%s,%s)\n", argv[3], argv[4]);
	
	for(j = 0; j < img2->height; j++)
	{
		for(i = 0; i < img2->width; i++)
			{
			img2->pix[i][j].red = img->pix[i + x][j + y].red;
			img2->pix[i][j].green = img->pix[i + x][j + y].green;
			img2->pix[i][j].blue = img->pix[i + x][j + y].blue;
			img2->pix[i][j].alpha = img->pix[i + x][j + y].alpha;
		
	/*		printf("(%d,%d)to(%d,%d) ", i , j,xpos, ypos);
			ypos++; */
		}
	/*	xpos++;
		ypos = 0; */
	}

/*	printf("End at (%d,%d)\n", i, j);
	printf("d\n");
*/
	save(img2, argv[2]);

	return 0;
}
