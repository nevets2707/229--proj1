#include <stdio.h>
#include "pixel.h"
#include "image.h"
#include <stdio.h>
#include "openFile.h"
#include "saveFile.h"
#include "image.h"
#include "pixel.h"

int main(int argc, char** argv)
{
	
	image* img = open(argv[1]);
	save(img, argv[2]);

	return 0;
}
