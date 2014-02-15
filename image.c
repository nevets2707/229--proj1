/** 
 *
 * File to create a new
 * image
 *
 *
 */

#include <stdlib.h>
#include "image.h"
#include "pixel.h"


image* newImg(int w, int h)
{

	int i;
	image* img = (image*)malloc(sizeof(image));

	img->width = w;
	img->height = h;

	img->pix = (pixel**)malloc(img->width * sizeof(pixel*));

	for(i = 0; i < img->width; i++)
	{
		img->pix[i] = (pixel*)malloc(img->height * sizeof(pixel));
	}

	return img;
}







