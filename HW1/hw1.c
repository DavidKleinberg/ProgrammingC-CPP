/*  File: hw1.c
    Homework 1, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 1
    02-15-2017
*/

#include <stdio.h>
#include <string.h>

#define LENGTH 16  //LENGTH is now a constant with value 16

/**
 * Encode a course listing from commandline input,
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
int matchCode(char course[], char code[], int index) {
    for (int i = 0; i < (int) strlen(code); i++) {
        if (course[index] == code[i]) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {

    // Confirm that a command-line argument is present
    if (argc == 1) {
        printf("Usage: hw0 XX.###.###Gg#.#\n");
        return 1;  // exit program because no command line argument present
    }

    // Declare a char array to hold the command-line argument string;
    // ensure last char is null character
    char course[LENGTH];
    strncpy(course, argv[1], LENGTH);
    course[LENGTH-1] = '\0';

    // TO DO: eventually remove the line below; it's just for debugging purposes
    // printf("Course string collected: %s\n", course);


    // TO DO: add your code here

    /*
        initialize two arrays of size 4
        to fit the department number (this value doesn't change)
        and the course number (also does not change)
    */
    char departmentCode[] = "000";
    char courseCode[] = "000";

    //build the departmentCode and courseCode strings
    for (int i = 0; i < 3; i++) {
        departmentCode[i] = course[i + 3];
        courseCode[i] = course[i + 7];
    }

    //print the output
    printf("Division: %d\n", matchCode(course, "EUDNSHYA", 1));
    printf("Department: %s\n", departmentCode);
    printf("Course: %s\n", courseCode);
    printf("Grade: %d %d\n", matchCode(course, "ABCDFISU", 10), matchCode(course, "+-/", 11));
    printf("Credits: %c %d\n", course[12], matchCode(course, "05", 14));

    return 0;
}
