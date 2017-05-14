/*  File: unittest.c
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
#include <assert.h>
#include "dnasearch.h"

void testHasACGT();
void testValidTextFile();
void testCreateDynamicArray();
void testVerifyPattern();
void testFindPattern();
void testPatternMatch();

int main() {

	testHasACGT();
	testValidTextFile();
	testCreateDynamicArray();
	testVerifyPattern();
	testFindPattern();
	testPatternMatch();

	printf("all tests passed\n");

return 0;
}

void testHasACGT() {
	assert(hasACGT('a'));
	assert(hasACGT('c'));
	assert(hasACGT('g'));
	assert(hasACGT('t'));
	assert(hasACGT('A'));
	assert(hasACGT('C'));
	assert(hasACGT('G'));
	assert(hasACGT('T'));
	assert(!hasACGT(' '));
	assert(!hasACGT('\n'));
	assert(!hasACGT('h'));
}

void testValidTextFile() {
	FILE* dna4 = fopen("dna4.txt", "r");
	assert(!validTextFile(dna4));
	FILE* dna7 = fopen("dna7.txt", "r");
	assert(validTextFile(dna7) == 15001);
	FILE* dna1 = fopen("dna1.txt", "r");
	assert(validTextFile(dna1) == 15);
	FILE* dna6 = fopen("dna6.txt", "r");
	assert(validTextFile(dna6) == 7);
}

void testCreateDynamicArray() {
	FILE* dna5 = fopen("dna5.txt", "r");
	char* genome = createDynamicArray(dna5, 19);
	//the size of the array is only as big as the number of nucleotides
	for (int i = 0; i < (int)sizeof(genome); i++) {
		assert(genome[i] == 'A');
	}
}

void testVerifyPattern() {
	char genome[] = "GATTACA";
	
	char patternLong[] = "GATTACAA\n";
	assert(verifyPattern(patternLong, genome));

	char patternInvalid[] = "GAR\n";
	assert(verifyPattern(patternInvalid, genome));

	char emptyPattern[] = "\n";
	assert(!verifyPattern(emptyPattern, genome));

	char validPattern[] = "GA\n";
	assert(!verifyPattern(validPattern, genome));
}

void testFindPattern() {
	char genome[] = "GATTACA";
	char pattern[] = "C\n";

	for (int i = 0; i <= (int)strlen(genome) - (int)strlen(pattern) + 1; i++) {
		if (patternMatch(genome, pattern, i)) {
			assert(i == 5);
		}
	}
}

void testPatternMatch() {
	char genome[] = "GATTACA";
	char pattern[] = "C";

	assert(patternMatch(genome, pattern, 5));
}
