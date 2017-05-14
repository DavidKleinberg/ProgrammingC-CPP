/*  File: hw3a.c
    Homework 3, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 3
    02-28-2017
*/

#include <stdio.h>
#include <string.h>

#define LENGTH 16  //LENGTH is now a constant with value 16

/**
 * Encode course listings from input file,
 * minimizing code reusage and space.
 *
 * This program does not handle error, with the exception of
 * returning "-1" for an invalid input (of correct length)
 *
 * @param course (to minimize global variables)
 * @param code equivalent of a switch statement
 * @param index the part of the input to encode
 *
 * return the integer code
 */
int matchCode(char course[], char code[], int index);

/**
 * Print a unsigned int in Binary.
 *
 * @param number the unsigned int to be translated
 *
 */
void integerToBinary(unsigned int number);

/**
 * Encode the course from a string to an unsigned int.
 *
 * @param course the character array (string rep. of the course)
 *
 * return the unsigned integer code
 */
unsigned int courseEncoder(char course[]);

/**
 * Encode course listings from input file.
 * Take input file name at commandline
 *
 * @param argc the number of commandline args accepted
 * @param argv character strings of input
 *
 * return 0 if executed properly, 1 if missing commandline args
 */
int main(int argc, char* argv[]) {

    // Confirm that a command-line argument is present
    if (argc < 3) {
        printf("Usage: inputFile.txt outputFile.txt\n");
        return 1;  // exit program because no command line argument present
    }

    FILE* inputFilePointer = fopen(argv[1], "r");
    FILE* outputFilePointer = fopen(argv[2], "w");

    char input[LENGTH+1];

    if (!inputFilePointer) {
        fprintf(stderr, "invalid input file");
        return 1;
    }

    while(fgets(input, LENGTH+1, inputFilePointer)) {
        //Take out the "\n" from the char array
        input[LENGTH-1] = '\0';
        printf("%s  ", input);
        fprintf(outputFilePointer, "%u\n", courseEncoder(input));
    }

    fclose(inputFilePointer);
    fclose(outputFilePointer);

    return 0;
}

unsigned int courseEncoder(char course[]) {

    unsigned int departmentCode = 0;
    unsigned int courseCode = 0;
    unsigned int multiplier = 100;

    //build the departmentCode and courseCode
    for (int i = 0; i < 3; i++) {
        departmentCode += (unsigned int)(course[i + 3] - '0') * multiplier;
        courseCode += (unsigned int)(course[i + 7] - '0') * multiplier;
        multiplier /= 10;
    }

    //create the bit segments
    departmentCode <<= 19;
    courseCode <<= 9;
    unsigned int division = matchCode(course, "EUDNSHYA", 1);
    division <<= 29;
    unsigned int grade = matchCode(course, "ABCDFISU", 10);
    grade <<= 6;
    unsigned int gradePartTwo = matchCode(course, "+-/", 11);
    gradePartTwo <<= 4;
    unsigned int credits = course[12] - '0';
    credits <<= 1;
    unsigned int compressedCode = matchCode(course, "05", 14);

    //overlap all the bits
    compressedCode |= credits;
    compressedCode |= gradePartTwo;
    compressedCode |= grade;
    compressedCode |= division;
    compressedCode |= courseCode;
    compressedCode |= departmentCode;

    //print standard out
    printf("%u  ", compressedCode);
    integerToBinary(compressedCode);
    printf("\n");

    return compressedCode;
}

int matchCode(char course[], char code[], int index) {
    for (int i = 0; i < (int) strlen(code); i++) {
        if (course[index] == code[i]) {
            return i;
        }
    }
    return -1;
}

void integerToBinary(unsigned int number) {
    unsigned int mask = 1;
    mask <<= 31;
    for (int i = 0; i < 32; i++) {
        if (number & mask) {
            printf("1");
        } else {
            printf("0");
        }
        mask>>=1;
    }
}
