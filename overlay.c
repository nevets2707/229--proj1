/**
 *
 * File for overlaying
 *
 */

#include <stdio.h> 
#include "image.h"
#include "openFile.h"
#include "saveFile.h"

int main(int argc, char** argv)
{

	image* img1;
	image* img2;
	image* img3;
	int i, j;
	unsigned char r, g, b, a;
	int x = atoi(argv[4]);
	int y = atoi(argv[5]);


	if(argc != 6)
	{
		printf("Invalid arguments\n");
		return 1;
	}

	img1 = open(argv[1]);
	img2 = open(argv[2]);
	
	if(img1->width > img2->width)
		i = img1->width;
	else
		i = img2->width;

	if(img1->height > img2->height)
		j = img1->height;
	else
		j = img2->height;

	img3 = newImg(img1->width, img1->height);

	printf("a\n");

	for(i = 0; i < img3->width; i++)
	{
		for(j = 0; j < img3->height; j++)
		{
			if((i < x && j < y) || (i >= img2->width || j >= img2->height))
			{
				img3->pix[i][j].red = img1->pix[i][j].red;
				img3->pix[i][j].green = img1->pix[i][j].green;
				img3->pix[i][j].blue = img1->pix[i][j].blue;
				img3->pix[i][j].alpha = img1->pix[i][j].alpha;
			}
			else
			{
				if(img2->pix[i][j].alpha == 255)
				{
					img3->pix[i][j].red = img2->pix[i][j].red;
					img3->pix[i][j].green = img2->pix[i][j].green;
					img3->pix[i][j].blue = img2->pix[i][j].blue;
					img3->pix[i][j].alpha = img2->pix[i][j].alpha;
				}
				
			 	r = (img2->pix[i][j].alpha * img2->pix[i][j].red + img1->pix[i][j].alpha * (255 - img2->pix[i][j].alpha) * img1->pix[i][j].red / 255) / 255;
				
				g = (img2->pix[i][j].alpha * img2->pix[i][j].green + img1->pix[i][j].alpha * (255 - img2->pix[i][j].alpha) * img1->pix[i][j].green / 255) / 255; 
				b = (img2->pix[i][j].alpha * img2->pix[i][j].blue + img1->pix[i][j].alpha * (255 - img2->pix[i][j].alpha) * img1->pix[i][j].blue / 255) / 255; 

				a = img2->pix[i][j].alpha + img1->pix[i][j].alpha * (255 - img2->pix[i][j].alpha) / 255;

				img3->pix[i][j].red = r;
				img3->pix[i][j].green = g;
				img3->pix[i][j].blue = b;
				img3->pix[i][j].alpha = a;
			}

		}
	}

	save(img3, argv[3]);

	return 0;
}
