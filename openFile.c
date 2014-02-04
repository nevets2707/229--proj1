/**
 *
 *  Program to open binary folders
 *
 */

#include <stdio.h>
#include "pixel.h"
#include "image.h"

image* open(char* argv)
{

	FILE* infile = fopen(argv[1], "rb");
	
	if(infile == 0)
	{
		printf("File failed to open\n");
		return 1;
	}

	image* temp = (image*)malloc(sizeof(image));

	while(!feof(infile))
	{
		
	}

}  
