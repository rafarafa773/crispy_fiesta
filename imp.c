
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "imp.h"

void ppm(void* data, int width, int height, const char* name) {
	FILE* fp = fopen(name, "wb");
	if(fp == NULL) {
		perror("fopen");
		return;
	}

	fprintf(fp, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(pixel), width * height, fp);

	fclose(fp);
}

pixel* load_ppm(const char* filename, int* width, int* height) {
	FILE* fp = fopen(filename, "rb");
	if(fp == NULL) {
		perror("fopen");
		return NULL;
	}

	char magic[3];
	int maxval;

	if(fscanf(fp, "%2s", magic) != 1) {
		fclose(fp);
		return NULL;
	}

	if(strcmp(magic, "P6") != 0) {
		fclose(fp);
		return NULL;
	}

	fscanf(fp, "%d %d %d", width, height, &maxval);
	fgetc(fp);

	pixel* pixels = malloc((*width) * (*height) * sizeof(pixel));
	if(pixels == NULL) {
		fclose(fp);
		return NULL;
	}

	fread(pixels, sizeof(pixel), (*width) * (*height), fp);

	fclose(fp);
	return pixels;
}

void pintar_pixel(pixel* p, uint8_t cor1, uint8_t cor2, uint8_t cor3) {
	p->r = cor1;
	p->g = cor2;
	p->b = cor3;
}

tipos identificar(char* s1) {
	if(strcmp(s1, "t") == 0) return T;
	if(strcmp(s1, "a") == 0) return A;
	if(strcmp(s1, "s") == 0) return S;
	return DEFAULT;
}
void black_white(pixel* image, size_t total_pixels, pixel* final_image) {
	for (size_t i = 0; i < total_pixels; ++i) {
		if ((image[i].r + image[i].g + image[i].b) > 255)
			pintar_pixel(&final_image[i], 255, 255, 255);
		else
			pintar_pixel(&final_image[i], 0, 0, 0);
		}
}
void invert(pixel* image, size_t total_pixels, pixel* final_image) {
	for (size_t i = 0; i < total_pixels; ++i) {
		pintar_pixel(&final_image[i], 255 - image[i].r, 255 - image[i].g, 255 - image[i].b);
	}
}
void gray(pixel* image, size_t total_pixels, pixel* final_image) {
	for (size_t i = 0; i < total_pixels; ++i) {
		uint8_t gray = (image[i].r + image[i].g + image[i].b) / 3;
		pintar_pixel(&final_image[i], gray, gray, gray);
	}
}

void sepia(pixel *image, size_t total_pixels, pixel *final_image) {
    for (size_t i = 0; i < total_pixels; ++i) {
        int r = image[i].r * 0.393 + image[i].g * 0.769 + image[i].b * 0.189;
        int g = image[i].r * 0.349 + image[i].g * 0.686 + image[i].b * 0.168;
        int b = image[i].r * 0.272 + image[i].g * 0.534 + image[i].b * 0.131;

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

        pintar_pixel(&final_image[i], (uint8_t)r, (uint8_t)g, (uint8_t)b);
    }
}
