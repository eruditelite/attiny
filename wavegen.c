/*******************************************************************************
 *
 * wavegen.c
 *
 ******************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

enum wave_shape {unknown, triangle, sawtooth, sine};

/*
  ------------------------------------------------------------------------------
  wave_shape_name
*/

static char *
wave_shape_name(enum wave_shape shape)
{
	switch (shape) {
	case unknown:
		return "unknown";
		break;
	case triangle:
		return "triangle";
		break;
	case sawtooth:
		return "sawtooth";
		break;
	case sine:
		return "sine";
		break;
	default:
		break;
	}

	return "INVALID SHAPE";
}

/*
  ------------------------------------------------------------------------------
  triangle_wave
*/

static void
triangle_wave(unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y = 0;
	double y_delta;
	int up = 1;

	y_delta = ((((double)top - (double)bottom) * 2) / (double)intervals);
	printf("y_delta is %f\n", y_delta);
	printf("__flash const uint8_t wave[] = {\n\t");

	for (;;) {
		printf("0x%02x", (bottom + (unsigned)y));

		if (++i == intervals) {
			printf("\n};\n");
			break;
		}

		if (0 == (i % 8))
			printf(",\n\t");
		else
			printf(", ");

		if (i < (intervals / 2))
			y += y_delta;
		else
			y -= y_delta;

		if ((double)bottom > y)
			y = (double)bottom;

		if ((double)top < y)
			y = (double)top;
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  sawtooth_wave
*/

static void
sawtooth_wave(unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y = 0;
	double y_delta;
	int up = 1;

	y_delta = (((double)top - (double)bottom) / (double)intervals);
	printf("y_delta is %f\n", y_delta);
	printf("__flash const uint8_t wave[] = {\n\t");

	for (;;) {
		printf("0x%02x", (bottom + (unsigned)y));

		if (++i == intervals) {
			printf("\n};\n");
			break;
		}

		if (0 == (i % 8))
			printf(",\n\t");
		else
			printf(", ");

		y += y_delta;

		if ((double)bottom > y)
			y = (double)bottom;

		if ((double)top < y)
			y = (double)top;
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  sine_wave
*/

static void
sine_wave(unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y;
	int up = 1;

	printf("__flash const uint8_t wave[] = {\n\t");

	for (;;) {
		y = ((sin(((double)i / (double)intervals) * 2 * M_PI)
		      + 1.) / 2.) * (double)(top - bottom);

		printf("0x%02x", (bottom + (unsigned)y));

		if (++i == intervals) {
			printf("\n};\n");
			break;
		}

		if (0 == (i % 8))
			printf(",\n\t");
		else
			printf(", ");
	}

	return;
}

/*
  ------------------------------------------------------------------------------
  usage
*/

static void
usage(int exit_code)
{
	printf("wavegen -h || -l value -h value -i value -w name\n"
	       "    -h : Display this wonderful help screen\n"
	       "    -b : low value [0...255] [default is 0]\n"
	       "    -t : high value [0...255] [default is 255]\n"
	       "    -i : number of intervals\n"
	       "    -w : triangle|sine\n");

	exit(exit_code);
}

/*
  ------------------------------------------------------------------------------
  main
*/

int main(int argc, char *argv[])
{
	unsigned bottom = 0;
	unsigned top = 255;
	unsigned intervals;
	enum wave_shape shape = unknown;
	int c;

	while (-1 != (c = getopt(argc, argv, "b:t:i:w:h")))
		switch (c) {
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		case 'b':
			bottom = (unsigned)strtoul(optarg, NULL, 0);
			break;
		case 't':
			top = (unsigned)strtoul(optarg, NULL, 0);
			break;
		case 'i':
			intervals = (unsigned)strtoul(optarg, NULL, 0);
			break;
		case 'w':
			if (0 == strncmp("triangle", optarg,
					 sizeof("triangle"))) {
				shape = triangle;
			} else if (0 == strncmp("sawtooth", optarg,
						sizeof("sawtooth"))) {
				shape = sawtooth;
			} else if (0 == strncmp("sine", optarg,
					   sizeof("sine"))) {
				shape = sine;
			} else {
				fprintf(stderr, "Unknown Shape!!!\n");
				usage(EXIT_FAILURE);
			}
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}

	printf("bottom=%u top=%u intervals=%u shape=%s\n",
	       bottom, top, intervals, wave_shape_name(shape));

	switch (shape) {
	case triangle:
		triangle_wave(bottom, top, intervals);
		break;
	case sawtooth:
		sawtooth_wave(bottom, top, intervals);
		break;
	case sine:
		sine_wave(bottom, top, intervals);
		break;
	default:
		fprintf(stderr, "INVALID SHAPE");
		return EXIT_FAILURE;
		break;
	}

	return EXIT_SUCCESS;
}
