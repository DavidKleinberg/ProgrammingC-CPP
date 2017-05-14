/*  File: hw5.c
    Homework 5, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 5
    03-30-2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "catalog.h"

void printCourse(Course c) {

	printf("%s.%d.%d %.1f %s\n", c -> division, c -> department,
   			c -> courseNumber, c -> credits, c -> courseTitle);
}

int numCourses(FILE* inputFile) {
	int numCourses = 0;
	char inputLine[48];

	while (fgets(inputLine, 48, inputFile)) { //this probably will stop at a space
		numCourses++;
	}
	return numCourses;
}

Course* fillCatalog(FILE* inputFile, int numCourses) {
	Course* cLog = malloc(sizeof(Course) * numCourses);

	//check if allocation succeeded
	if (cLog == NULL) {
	//output error message
		fprintf(stderr, "space allocation failed");
	}

	char inputLine[48], division[3], courseTitle[33];
	int department, courseNumber;
	float credits;

	int i = 0;

	while (fgets(inputLine, 48, inputFile)) {

		Course newCourse = malloc(sizeof(course));

		if (newCourse == NULL) {
		//output error message
			fprintf(stderr, "space allocation failed");
		}

   		sscanf(inputLine, "%2c %*c %d %*c %d %f %[^\n]", division, &department,
   			&courseNumber, &credits, courseTitle);

   		division[0] = toupper(division[0]); division[1] = toupper(division[1]);
   		strcpy(newCourse -> division, division);
   		newCourse -> department = department;
   		newCourse -> courseNumber = courseNumber;
   		newCourse -> credits = credits;
   		strcpy(newCourse -> courseTitle, courseTitle);

		cLog[i] = newCourse;
		i++;
	}

	return cLog;
}

int equals(Course c1, Course c2) {

	if (c1 -> division[0] != c2 -> division[0] || c1 -> division[1] != c2 -> division[1]) {
		return 0;
	} else if (c1 -> department != c2 -> department) {
		return 0;
	} else if (c1 -> courseNumber != c2 -> courseNumber) {
		return 0;
	} else {
		return 1;
	}
}
