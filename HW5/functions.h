/*  File: hw5.c
    Homework 5, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 5
    03-30-2017
*/

#ifndef functions

#define functions

	int validCourseID(char courseID[], char division[], int *department, int *courseNumber);
	int hasCourse(Course* cLog, int numC, char division[], int department, int courseNumber);
	int getValidCourseID(Course* cLog, int num_courses);
	int findCourseID(Course* cLog, int num_courses);
	int validCourseTitle(char title[]);
	int validCredits(char creditString[]);
	void getValidSemester(int *year, char *semester);
	int validSemester(char semesterString[]);
	void getValidGrade(char *letterGrade, char *partialGrade);
	int validGrade(char gradeString[]);
	int hasNode(Node* tScript, Course c, int year, char semester);
	int courseTaken(Node* tScript, Course c, int print);
	int semesterTaken(Node* tScript, Course c, int year, char semester);
	float gradeToGPA(char letterGrade, char partial);
	float calculateGPA(Node* tScript);
	
#endif
