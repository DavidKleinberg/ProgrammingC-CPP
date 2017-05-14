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
#include <assert.h>
#include "prompts.h"
#include "catalog.h"
#include "transcript.h"
#include "functions.h"

void testValidCourseID();
void testHasCourse();
void testValidCourseTitle();
void testValidCredits();
void testValidSemester();
void testValidGrade();
void testHasNode();
void testCourseTaken();
void testSemesterTaken();
void testGradeToGPA();
void testCalculateGPA();

//the following were not tested because they require user input:
//void testGetValidCourseID();
//void testFindCourseID();
//void testGetValidSemester();

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

    int num_courses = numCourses(inputFilePointer);

    fseek(inputFilePointer, 0, SEEK_SET);
    Course* cLog = fillCatalog(inputFilePointer, num_courses);
    fclose(inputFilePointer);

    Node head = create(NULL, "00", 0, '\0');
    Node* tScript = &head;
    char grade[] = "A+";

    addCourse(tScript, cLog[0], grade, 1111, 'F');

	testValidCourseID();
	testHasCourse(cLog, num_courses);
	testValidCourseTitle();
	testValidCredits();
	testValidSemester();
	testValidGrade();
	testHasNode(tScript, cLog[0]);
	testCourseTaken(tScript, cLog[0]);
	testSemesterTaken(tScript, cLog[0]);
	testGradeToGPA();
	testCalculateGPA(tScript);

	printf("all tests passed\n");

	return 0;
}

void testValidCourseID() {

	char invalidCourseID[] = "en.aaa.aaa";
	char validCourse[] = "EN.600.107\n";
	char division[] = "00";
	int department = 0;
	int courseNumber = 0;

	assert(!validCourseID(invalidCourseID, division, &department, &courseNumber));
	assert(validCourseID(validCourse, division, &department, &courseNumber));
}

void testHasCourse(Course* cLog, int numC) {

	char division[] = "en";
	int department = 600;
	int courseNumber = 107;

	assert(hasCourse(cLog, numC, division, department, courseNumber));

	courseNumber = 108;

	assert(hasCourse(cLog, numC, division, department, courseNumber) == -1);

}

void testValidCourseTitle() {
	char title[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	assert(!validCourseTitle(title));
	title[33] = '\0';
	assert(validCourseTitle(title));
}

void testValidCredits() {

	char badCredits[] = "bbb\n";
	assert(!validCredits(badCredits));
	char goodCredits[] = "3.5\n";
	assert(validCredits(goodCredits));
}

void testValidSemester() {

	char goodSemester[] = "1111.F\n";
	assert(validSemester(goodSemester));
	goodSemester[5] = 'S';
	assert(validSemester(goodSemester));
	char badSemester[] = "11111f\n";
	assert(!validSemester(badSemester));
}

void testValidGrade() {
	char goodGrade[] = "A+\n";
	assert(validGrade(goodGrade));
	char badGrade[] = "g+\n";
	assert(!validGrade(badGrade));
}

void testHasNode(Node* tScript, Course c) {

	assert(hasNode(tScript, c, 1111, 'F'));
	assert(!hasNode(tScript, c, 1122, 'F'));
}
void testCourseTaken(Node* tScript, Course c) {

	assert(courseTaken(tScript, c, 0));
}
void testSemesterTaken(Node* tScript, Course c) {
	assert(semesterTaken(tScript, c, 1111, 'F'));
	assert(!semesterTaken(tScript, c, 1122, 'F'));
}
void testGradeToGPA() {

	float aplus = 4.3;
	assert(gradeToGPA('A', '+') == aplus);
}
void testCalculateGPA(Node* tScript) {
	float gpa = 4.3;
	assert(calculateGPA(tScript) == gpa);
}
