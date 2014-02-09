/**
 *
 *
 *
 * colorshifter
 *
 *
 */

#include <stdio.h>
#include "pixel.h"
#include "image.h"
#include "openFile.h"

int main(int argc, char** argv)
{
	image* img;

	if(argc < 1)
	{
		return 1;
	}
	printf("WAT");	
	img = open(argv[1]);

	printf("%d\n", img->height);

	return 0;
}
