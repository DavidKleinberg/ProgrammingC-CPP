/*  File: menuUtil.c
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
#include "menuUtil.h"
#include "imageIO.h"
#include "imageManip.h"

void directUserInput() {

    char input[25] = "0";
    char filename[16];
    int corners[4];
    Image newImage = NULL;
    double factor = 0;

    while(input[0] != 'q') {
        printMenu();
        fgets(input, 24, stdin);

        switch(input[0]) {

        case 'r':
        {
            sscanf(input, "%*c %s", filename);

            printf("Reading from %s...\n", filename);

            if (newImage) {
                freeData(newImage);
                free(newImage);
            }
            newImage = readImage(filename);
        }
        break;

        case 'w':
        {
            sscanf(input, "%*c %s", filename);

            printf("Writing to %s...\n", filename);
            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            writeImage(filename, newImage);
        }
        break;

        case 'c':
        {
            sscanf(input, "%*c %d %d %d %d", &corners[0], &corners[1], &corners[2], &corners[3]);

            printf("Cropping region from (%d, %d) to (%d, %d)...\n", corners[0], corners[1], corners[2], corners[3]);

            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            cropImage(&newImage, corners);
        }
        break;

        case 'i':
        {
            printf("Inverting intensity...\n");
            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            invertIntensities(&newImage);

        }
        break;

        case 's':
        {
            printf("Swapping color channels...\n");
            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            swapColorChannels(&newImage);

        }
        break;

        case 'g':
        {
            printf("Converting to grayscale...\n");

            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            convertToGrayscale(&newImage);

        }
        break;

        case 'b':
        {
            sscanf(input, "%*c %lf", &factor);
            printf("Adjusting brightness by %lf...\n", factor);

            if (!newImage) {
                printf("Error: there is no current image\n");
                break;
            }

            changeBrightness(&newImage, factor);
        }
        break;

        case 'q':
            if (newImage) {
                freeData(newImage);
                free(newImage);
            }
            break;

        default:
            printf("Error: Unknown command\n");
            break;
        }
    }
}

void printMenu() {
    printf(
        "Main menu:\n"
        "\tr <filename> - read image from <filename>\n"
        "\tw <filename> - write image to <filename>\n"
        "\tc <x1> <y1> <x2> <y2> - crop image to the box with the given corners\n"
        "\ti - invert intensities\n"
        "\ts - swap color channels\n"
        "\tg - convert to grayscale\n"
        "\tb <amt> - change brightness (up or down) by the given amount\n"
        "\tq - quit\n"
        "\n"
        "Enter your choice:\n");
}
