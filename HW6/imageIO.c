/*  File: imageIO.c
    Homework 6, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 6
    04-09-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "imageIO.h"
#include "imageManip.h"

int area(Image i) {
	return i->columns * i->rows;
}

Image readImage(const char *filename) {
	FILE* inputFilePointer = fopen(filename, "r");

    if (!inputFilePointer) {
        fprintf(stderr, "invalid input file\n");
        return NULL;
    }

    Image newImage = malloc(sizeof(Image));

    char header[200];
    int specs[6];
    int count = 0;

    do {
    	fgets(header, 199, inputFilePointer);
    	
    	if (isdigit(header[0])) {

	    	count += sscanf(header, "%d %d %d", &specs[count], &specs[count+1], &specs[count+2]);
	    }

    } while (count < 3);

    newImage->columns = specs[0];
    newImage->rows = specs[1];
    newImage->colors = specs[2];

    if (newImage->colors > 255) {
    	fprintf(stderr, "invalid input file\n");
        return NULL;
    }

    newImage->data = malloc(sizeof(Pixel) * area(newImage));
    //newImage->data = malloc(sizeof(pixel) * area(newImage));

    unsigned char rgb[] = "RGB";
    for (int i = 0; i < area(newImage); i++) {
    	fread(rgb, 1, 3, inputFilePointer);

    	newImage->data[i].red = rgb[0];
    	newImage->data[i].green = rgb[1];
    	newImage->data[i].blue = rgb[2];
    }

    fclose(inputFilePointer);
    return newImage;
}

void writeImage(const char *filename, Image img) {
	FILE* outputFilePointer = fopen(filename, "w");

	fprintf(outputFilePointer, "P6\n%d %d\n%d\n", img->columns, img->rows, img->colors);

	for (int i = 0; i < area(img); i++) {

    	fwrite(&img->data[i].red, 1, 1, outputFilePointer);
    	fwrite(&img->data[i].green, 1, 1, outputFilePointer);
    	fwrite(&img->data[i].blue, 1, 1, outputFilePointer);
	}

	fclose(outputFilePointer);
	printf("File successfully written\n");
}

void freeData(Image img) {
	
	free(img->data);
}
