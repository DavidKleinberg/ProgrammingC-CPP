/*  File: dnasearch.c
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

int validTextFile(FILE* inputFile) {
	int numNucleotides = 0;
	char inputCharacter[2];

	while (fgets(inputCharacter, 2, inputFile)) {
		if (hasACGT(inputCharacter[0])) {
			numNucleotides++;
		} else if (!isspace(inputCharacter[0])) {
			return 0;
		}
	}
	return numNucleotides;
}

char* createDynamicArray(FILE* inputFile, int numNucleotides) {
	char* array = malloc(sizeof(char) * numNucleotides + 1);
	//check if allocation succeeded
	if (array == NULL) {
	//output error message
		fprintf(stderr, "space allocation failed");
	}

	char inputCharacter[2];
	array[numNucleotides] = '\0';
	int i = 0;

	while (fgets(inputCharacter, 2, inputFile)) {
		if (hasACGT(inputCharacter[0])) {
			array[i] = inputCharacter[0];
			i++;
		}
	}

	return array;
}

int hasACGT(char nucleotide) {
	nucleotide = toupper(nucleotide);
	if (nucleotide == 'A' || nucleotide == 'C' ||
		nucleotide == 'G' || nucleotide == 'T') {
		return 1;
	} else {
		return 0;
	}
}

int verifyPattern(char* inputPattern, char* genome) {
	char inputCharacter;
	int patternLength = 0;

    for (int i = 0; i < (int)strlen(inputPattern) - 1; i++) {
    	sscanf(&inputPattern[i], "%c", &inputCharacter);
		if (hasACGT(inputCharacter)) {
			inputPattern[i] = toupper(inputPattern[i]);
			patternLength++;
		} else {
			fprintf(stdout, "Invalid pattern\n");
			return 1;
		}
	}

	inputPattern[patternLength] = '\0';

	if (strlen(inputPattern) > strlen(genome)) {
		fprintf(stdout, "Invalid pattern\n");
			return 1;
	}
	if (patternLength > 0) {
		findPattern(genome, inputPattern);
		printf("\n");
	}
	return 0;
}

void findPattern(char* genome, char* pattern) {
	int numMatches = 0;
	printf("%s", pattern);

	for (int i = 0; i <= (int)strlen(genome) - (int)strlen(pattern) + 1; i++) {
		if (patternMatch(genome, pattern, i)) {
			numMatches++;
			printf(" %d", i);
		}
	}
	if (numMatches == 0) {
		printf(" Not found");
	}
}

int patternMatch(char* genome, char* pattern, int startAt) {
	int match = 1;
		for (int j = 0; j < (int)strlen(pattern); j++) {
			if (tolower(pattern[j]) != tolower(genome[startAt + j])) {
				match = 0;
				break;
			}
		}
		if (match) {
			return 1;
		}
	return 0;
}
