#include "pixel.h"

#ifndef _IMAGE_H
#define _IMAGE_H
typedef struct image_s
{

	int height;
	int width;
	int pixelCount;
	pixel** pix;
	

} image;
#endif
