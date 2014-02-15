/**
 *
 * File to make image black and white
 *
 *
 * need to use round!!!!!!!!
 */


#include <stdio.h>
#include "pixel.h"
#include "image.h"
#include "openFile.h"
#include "saveFile.h"

int main(int argc, char** argv)
{

	image* img;
	int i;
	int j;
	int avg;


	if(argc != 3)
	{
		return 1;
	}

	printf("The image file is %s\n", argv[1]);
	img  = open(argv[1]);

	for(i = 0; i < img->width; i++)
	{
		for(j = 0; j < img->height; j++)
		{
		
			unsigned char r, g, b;
			r = img->pix[i][j].red;
			g = img->pix[i][j].green;
			b = img->pix[i][j].blue;
			
			avg = (r + b + g) / 3;
			
			img->pix[i][j].red = avg;
			img->pix[i][j].green = avg;
			img->pix[i][j].blue = avg;
		
		}


	}

	printf("Height: %d \nWidth: %d \n", img->height, img->width);

	printf("Saving to %s\n", argv[2]);
	save(img, argv[2]);

	return 0;

}
