/*  File: imageManip.h
    Homework 6, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 6
    04-09-2017
*/

#ifndef imageManip

#define imageManip
	
	/*
	 * Crop the current state of the image
	 *
	 * @param img a double pointer to image struct 
	 *
	 * @param corners the x1 y1 x2 y2 pixel coordinates
	 *
	 */
	void cropImage(Image *img, const int *corners);

	/*
	 * Invert colors of the current state of the image
	 *
	 * @param img a double pointer to image struct 
	 *
	 */
	void invertIntensities(Image *img);

	/*
	 * Swap colors in the current state of the image
	 *
	 * @param img a double pointer to image struct 
	 *
	 */
	void swapColorChannels(Image *img);

	/*
	 * Convert the current state of the image to grayscale
	 *
	 * @param img a double pointer to image struct 
	 *
	 */
	void convertToGrayscale(Image *img);

	/*
	 * Change the brightness by a specified factor
	 *
	 * @param img a double pointer to image struct 
	 *
	 * @param factor double
	 *
	 */
	void changeBrightness(Image *img, double factor);

	/*
	 * Calculate the scaling factor with floor and ceiling values
	 *
	 * @param img a double pointer to image struct 
	 *
	 * @param scale double
	 *
	 * @return the new RGB value
	 */
	unsigned char brightnessValue(double scale);

#endif
