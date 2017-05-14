/*  File: hw4.c
    Homework 3, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 4
    03-08-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dnasearch.h"

int main(int argc, char* argv[]) {

	// Confirm that ONE command-line argument is present
    if (argc != 2) {
        fprintf(stderr, "Usage: inputFile.txt\n");
        return 1;  // exit program because no command line argument present
    }

    FILE* inputFilePointer = fopen(argv[1], "r");

    if (!inputFilePointer) {
        fprintf(stderr, "invalid input file");
        return 1;
    }

    int numNucleotides  = validTextFile(inputFilePointer);
    fclose(inputFilePointer);

    if (numNucleotides == 0 || numNucleotides > 15000) {
    	fprintf(stdout, "Invalid text file\n");
    	return 1;
    }

    inputFilePointer = fopen(argv[1], "r");
    char* genome = createDynamicArray(inputFilePointer, numNucleotides);
    fclose(inputFilePointer);

    char inputPattern[15002];
    char singleCharacter[2];
    int index = 0;

    while (fgets(singleCharacter, 2, stdin)) {
    	inputPattern[index] = singleCharacter[0];
    	index++;
    	if (singleCharacter[0] == ' ' || singleCharacter[0] == '\n') {
    		inputPattern[index] = '\0';
    		index = 0;
    		if (verifyPattern(inputPattern, genome)) {
    			return 1;
    		}
    	}
	}
    free(genome);

return 0;
}
