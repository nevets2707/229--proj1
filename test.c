#include <stdio.h>
#include "pixel.h"
#include "image.h"

int main(void)
{

	pixel a;
	a.red = 1;
	int b;
	FILE* in;
	in  = ("insanity.simp", "rb");
	

	/*printf("%d\n", b);
		printf("%d\n", sizeof(long int));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(int*));
	printf("%d\n", a.red);
	*/

	printf("%d\n", sizeof(int));

		
	return 0;
}
