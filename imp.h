
#ifndef IMP_H
#define IMP_H

#include <stddef.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
	uint8_t r, g, b;
} pixel;

void ppm(void* data, int width, int height, const char* name);
pixel* load_ppm(const char* filename, int* width, int* height);
void pintar_pixel(pixel* p, uint8_t cor1, uint8_t cor2, uint8_t cor3);
typedef enum {
	T,
	A,
	S,
	DEFAULT
} tipos;
void black_white(pixel* image, size_t total_pixels, pixel* final_image);
void invert(pixel* image, size_t total_pixels, pixel* final_image);
void gray(pixel* image, size_t total_pixels, pixel* final_image);
void sepia(pixel *image, size_t total_pixels, pixel *final_image);
tipos identificar(char* s1);

#endif
