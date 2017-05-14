/*  File: menuUtil.h
    Homework 6, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 6
    04-09-2017
*/

#ifndef menuUtil

#define menuUtil

	/*
	 * Print the menu options
	 */
	void printMenu();

	/*
	 * Direct user input to imageIO and imageManip functions
	 *
	 * r - frees memory if selected more than once
	 * 		updates the working image to the one specified by user
	 * w - writes to new file
	 * c - creates "new" cropped image
	 *		inclusive to the coordinates specified
	 *		frees memory of larger image
	 * i - inverts intensities
	 * s - swaps color intensities
	 * g - converts image to grayscale
	 * b - changes brightness by specified amount
	 * 		a negative value will floor to 0
	 * q - quits the program
	 *		frees any memory allocated on the heap
	 *		displays goodbye message
	 */
	void directUserInput();

#endif
