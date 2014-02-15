/**
 *
 *  Program to open binary folders
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "pixel.h"
#include "image.h"
#include "openFile.h"

image* open(char* file)

{
	FILE* infile;
	char* newFile;
	image* temp;
	int i, j;
	printf("openfile: %s\n", file);


	temp = (image*)malloc(sizeof(image));
	infile = fopen(file, "rb");

	while(infile == 0)
	{
		printf("Invalid file. Please enter a new file.\n>");
		scanf("%s", newFile);
		infile = fopen(newFile, "rb");
	}
		
	if(!feof(infile))
	{
		/* fread(pointer, size, count, file); */
		fread(&(temp->width), sizeof(int), 1, infile);
		printf("width : %d\n", temp->width);
		fread(&(temp->height), sizeof(int), 1, infile);
		printf("height : %d\n", temp->height);	
		temp->pix = (pixel**)malloc(temp->width * sizeof(pixel*));

		for(i = 0; i < temp->width; i++)
		{
			temp->pix[i] = (pixel*)malloc(temp->height * sizeof(pixel));
		}
	

		for(i = 0; i < temp->width; i++)
		{
		
			for(j = 0; j < temp->height; j++)
			{						
				fread(&(temp->pix[i][j].red), sizeof(char), 1, infile);
				fread(&(temp->pix[i][j].green), sizeof(char), 1, infile);
				fread(&(temp->pix[i][j].blue), sizeof(char), 1, infile);
				fread(&(temp->pix[i][j].alpha), sizeof(char), 1, infile);
			}
		}
	}
	printf("pixel [%d][%d] has\nred=%d\ngreen=%d\nblue=%d\nalpha=%d\n", 0,0,temp->pix[0][0].red, temp->pix[0][0].green, temp->pix[0][0].blue, temp->pix[0][0].alpha);


	return temp;

}  
