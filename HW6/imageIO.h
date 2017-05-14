/*  File: imageIO.h
    Homework 6, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 6
    04-09-2017
*/

#ifndef imageIO

#define imageIO

	typedef struct _pixel {
		unsigned char red;
		unsigned char blue;
		unsigned char green;
	} pixel;

	typedef pixel *Pixel;

	typedef struct _image {
		 int columns;
		 int rows;
		 int colors;
		 Pixel data;
	} image;

	typedef image *Image;

	/*
	 * Calculates the area (number of pixels) in the image
	 *
	 * @param i pointer to image struct 
	 *
	 * @return number of pixels
	 */
	int area(Image i);

	/*
	 * Takes data from file and loads into defined structs
	 *
	 * @param filename character array
	 *
	 * @return pointer to an image struct
	 */
	Image readImage(const char *filename);

	/*
	 * Writes the current state of the image to a new file
	 *
	 * @param filename character array
	 *
	 * @param img a pointer to the current state of the image
	 */
	void writeImage(const char *filename, Image img);

	/*
	 * Frees the pixel structs allocated on heap memory
	 */
	void freeData();

#endif
