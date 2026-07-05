#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "imp.h"

int main(int argc, char* argv[]) {
	if (argc < 4) {
		fprintf(stderr, "usage: %s <type> <input_file> <output_file>\n", argv[0]);
		fprintf(stderr, "\navailable image processing types:\n");
		fprintf(stderr, "  t : apply black and white filter\n");
		fprintf(stderr, "  a : invert image colors\n");
		fprintf(stderr, "  s : apply sepia tone\n");
		fprintf(stderr, "  * : apply grayscale (default for unknown types)\n");
		return 1;
	}
	int width;
	int height;

	pixel* image = load_ppm(argv[2], &width, &height);
	if(image == NULL) {
		return 1;
	}
	size_t total_pixels = (size_t)width * height;

	pixel* final_image = malloc(total_pixels * sizeof(pixel));
	if(final_image == NULL) {
		free(image);
		return 1;
	}

	switch(identificar(argv[1])) {
		case T:
			black_white(image, total_pixels, final_image);
			break;
		case A:
			invert(image, total_pixels, final_image);
			break;
		case S:
			sepia(image, total_pixels, final_image);
			break;
		case DEFAULT:
			gray(image, total_pixels, final_image);
			break;
	}

	ppm(final_image, width, height, argv[3]);

	free(image);
	free(final_image);

	return 0;
}
