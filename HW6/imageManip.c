/*  File: imageManip.c
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

void cropImage(Image *img, const int *corners) {

    if (corners[2] < corners[0] || corners[3] < corners[1]) {
        printf("Error: cropping failed, image unchanged\n");
        return;
    }

    if ((*img)->columns < corners[2] || (*img)->rows < corners[3]) {
        printf("Error: cropping failed, image unchanged\n");
        return;
    }

    Image newImage = malloc(sizeof(Image));

    newImage->columns = corners[2] - corners[0] + 1;
    newImage->rows = corners[3] - corners[1] + 1;
    newImage->colors = 255;
    newImage->data = malloc(sizeof(pixel) * area(newImage));

    int i = 0;
    int numColumns = (*img)->columns;

    for (int r = corners[1]; r <= corners[3]; r++) {
        for (int c = corners[0]; c <= corners[2]; c++) {
            newImage->data[i] = (*img)->data[c+(numColumns*r)];
            i++;
        }
    }

    Image temp = *img;
    *img = newImage;
    freeData(temp);
    free(temp);
}

void invertIntensities(Image *img) {

    for (int i = 0; i < area(*img); i++) {
        (*img)->data[i].red = 255 - (*img)->data[i].red;
        (*img)->data[i].green = 255 - (*img)->data[i].green;
        (*img)->data[i].blue = 255 - (*img)->data[i].blue;
    }
}

void swapColorChannels(Image *img) {

    for (int i = 0; i < area(*img); i++) {
        unsigned char temp = (*img)->data[i].red;
        (*img)->data[i].red = (*img)->data[i].green;
        (*img)->data[i].green = (*img)->data[i].blue;
        (*img)->data[i].blue = temp;
    }
}

void convertToGrayscale(Image *img) {

    unsigned char intensity = 0;

    for (int i = 0; i < area(*img); i++) {
        intensity += (*img)->data[i].red * 0.3;
        intensity += (*img)->data[i].green * 0.59;
        intensity += (*img)->data[i].blue * 0.11;

        (*img)->data[i].red = intensity;
        (*img)->data[i].green = intensity;
        (*img)->data[i].blue = intensity;

        intensity = 0;
    }
}

void changeBrightness(Image *img, double factor) {
    for (int i = 0; i < area(*img); i++) {
        (*img)->data[i].red = brightnessValue((*img)->data[i].red*factor);
        (*img)->data[i].green = brightnessValue((*img)->data[i].green*factor);
        (*img)->data[i].blue = brightnessValue((*img)->data[i].blue*factor);
    }
}

unsigned char brightnessValue(double scale) {
    if (scale <= 0) {
        return 0;
    }
    if (scale >= 255) {
        return 255;
    }

    return (unsigned char)scale;
}
