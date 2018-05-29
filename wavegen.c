#include <stdio.h>
#include <math.h>

/*
  ------------------------------------------------------------------------------
  main
*/

int main(int argc, char *argv[])
{
	int i;
	float x = 0;
	int y = 0;

	for (i = 0; i < 500; ++i) {
		y = x * 250;
		x = x + 0.0031;
		printf("i=%d x=%f y=%d\n", i, x, y);
	}
}
