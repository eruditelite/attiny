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
triangle_wave(FILE *output, unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y = 0;
	double y_delta;
	unsigned char *temp;
	int ti = 0;

	temp = malloc(intervals + 3);
	temp[ti++] = (unsigned char)(intervals & 0xff);
	temp[ti++] = (unsigned char)((intervals & 0xff00) >> 8);
	temp[ti++] = 2;

	y_delta = ((((double)top - (double)bottom) * 2) / (double)intervals);

	for (;;) {
		temp[ti++] = (unsigned char)(bottom + (unsigned)y);

		if (++i == intervals)
			break;

		if (i < (intervals / 2))
			y += y_delta;
		else
			y -= y_delta;

		if ((double)bottom > y)
			y = (double)bottom;

		if ((double)top < y)
			y = (double)top;
	}

	fwrite(temp, sizeof(unsigned char), ti, output);

	return;
}

/*
  ------------------------------------------------------------------------------
  sawtooth_wave
*/

static void
sawtooth_wave(FILE *output, unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y = 0;
	double y_delta;
	unsigned char *temp;
	int ti = 0;

	temp = malloc(intervals + 3);
	temp[ti++] = (unsigned char)(intervals & 0xff);
	temp[ti++] = (unsigned char)((intervals & 0xff00) >> 8);
	temp[ti++] = 2;

	y_delta = (((double)top - (double)bottom) / (double)intervals);

	for (;;) {
		temp[ti++] = (unsigned char)(bottom + (unsigned)y);

		if (++i == intervals)
			break;

		y += y_delta;

		if ((double)bottom > y)
			y = (double)bottom;

		if ((double)top < y)
			y = (double)top;
	}

	fwrite(temp, sizeof(unsigned char), ti, output);

	return;
}

/*
  ------------------------------------------------------------------------------
  sine_wave
*/

static void
sine_wave(FILE *output, unsigned bottom, unsigned top, unsigned intervals)
{
	int i = 0;
	double y;

	unsigned char *temp;
	int ti = 0;

	temp = malloc(intervals + 3);
	temp[ti++] = (unsigned char)(intervals & 0xff);
	temp[ti++] = (unsigned char)((intervals & 0xff00) >> 8);
	temp[ti++] = 2;

	for (;;) {
		y = ((sin(((double)i / (double)intervals) * 2 * M_PI)
		      + 1.) / 2.) * (double)(top - bottom);

		temp[ti++] = (unsigned char)(bottom + (unsigned)y);

		if (++i == intervals)
			break;
	}

	fwrite(temp, sizeof(unsigned char), ti, output);

	return;
}

/*
  ------------------------------------------------------------------------------
  usage
*/

static void
usage(int exit_code)
{
	printf("wavegen -h || -l value -h value -i value -w name -o output\n"
	       "    -h : Display this wonderful help screen\n"
	       "    -b : low value [0...255] [default is 0]\n"
	       "    -t : high value [0...255] [default is 255]\n"
	       "    -i : number of intervals\n"
	       "    -w : triangle|sawtooth|sine\n"
	       "    -o : output file [default is wave.bin\n");

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
	char output_name[FILENAME_MAX] = "eeprom.bin";
	FILE *output;
	int c;

	while (-1 != (c = getopt(argc, argv, "b:t:i:w:o:h")))
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
		case 'o':
			strncpy(output_name, optarg, FILENAME_MAX);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}

	printf("bottom=%u top=%u intervals=%u shape=%s output=%s\n",
	       bottom, top, intervals, wave_shape_name(shape), output_name);
	output = fopen(output_name, "wb");

	switch (shape) {
	case triangle:
		triangle_wave(output, bottom, top, intervals);
		break;
	case sawtooth:
		sawtooth_wave(output, bottom, top, intervals);
		break;
	case sine:
		sine_wave(output, bottom, top, intervals);
		break;
	default:
		fprintf(stderr, "INVALID SHAPE");
		return EXIT_FAILURE;
		break;
	}

	fclose(output);

	return EXIT_SUCCESS;
}
