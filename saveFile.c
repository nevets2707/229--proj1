
#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"
#include "image.h"
#include "saveFile.h"


int save(image* img, char* file)
{

	int i, j;
	FILE* out = fopen(file, "wb");

	fwrite(&(img->width), sizeof(int), 1, out);
	fwrite(&(img->height), sizeof(int), 1, out);

	for(i = 0; i < img->width; i++)
	{
		for(j = 0; j < img->height; j++)
		{
			fwrite(&(img->pix[i][j].red), sizeof(char), 1, out);
			fwrite(&(img->pix[i][j].green), sizeof(char), 1, out);
			fwrite(&(img->pix[i][j].blue), sizeof(char), 1, out);
			fwrite(&(img->pix[i][j].alpha), sizeof(char), 1, out);
		}
	}

	fclose(out);

	return 0;


}





