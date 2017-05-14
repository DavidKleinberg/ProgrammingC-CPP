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
#include "prompts.h"
#include "catalog.h"
#include "transcript.h"
#include "functions.h"

int validCourseID(char courseID[], char division[], int *department, int *courseNumber) {

    if ((int)strlen(courseID) != 11) {
        invalid_input_msg();
        return 0;
    }

    if (sscanf(courseID, "%2c %*c %d %*c %d", division, department, courseNumber) != 3) {
        invalid_input_msg();
        return 0;
    }

    division[0] = toupper(division[0]); division[1] = toupper(division[1]);
    return 1;
}

int hasCourse(Course* cLog, int numC, char division[], int department, int courseNumber) {
    for (int i = 0; i < numC; i++) {
        char* div = cLog[i] -> division;
        int dep = cLog[i] -> department;
        int cNum = cLog[i] -> courseNumber;
        
        if (div[0] == division[0] && div[1] == division[1]
            && dep == department && cNum == courseNumber) {
            return i;
        }
    }
    
    return -1;
}

int findCourseID(Course* cLog, int numC) {
    char courseID[15];
    char division[3];
    int department, courseNumber;

    do {
        course_prompt();

        fgets(courseID, 15, stdin);
        courseID[14] = '\0';

    } while (!validCourseID(courseID, division, &department, &courseNumber));

    int index = hasCourse(cLog, numC, division, department, courseNumber);

    return index;
}

int validCourseTitle(char title[]) {
    if (strlen(title) < 34 && strlen(title) > 1) {
        invalid_input_msg();
        return 1;
    } else {
        return 0;
    }
}

int validCredits(char creditString[]) {
    if (strlen(creditString) != 4) {
        invalid_input_msg();
        return 0;
    }

    float credits = 0;

    if (sscanf(creditString, "%f", &credits) != 1) {
        invalid_input_msg();
        return 0;
    }
    return 1;
}

int validSemester(char semesterString[]) {
    int year;
    char semester;
    if (strlen(semesterString) != 7) {
        invalid_input_msg();
        return 0;
    }
    if (sscanf(semesterString, "%d %*c %c", &year, &semester) != 2) {
        invalid_input_msg();
        return 0;
    }

    if ((year/1000) < 1) {
        invalid_input_msg();
        return 0;
    }

    if (semester != 'F' && semester != 'S') {
        invalid_input_msg();
        return 0;
    }
    return 1;
}

int validGrade(char gradeString[]) {
    char letterGrade;
    char partialGrade;
    if (strlen(gradeString) != 3) {
        invalid_input_msg();
        return 0;
    }

    if (sscanf(gradeString, "%c %c", &letterGrade, &partialGrade) != 2) {
        invalid_input_msg();
        return 0;
    }

    int matches = 0;
    char validLetters[] = "ABCDEFSU";
    for (int i = 0; i < (int)strlen(validLetters); i++) {
        if (letterGrade == validLetters[i]) {
            matches++;
        }
    }

    if (!matches) {
        invalid_input_msg();
        return 0;
    }

    matches = 0;
    char validPartials[] = "+-/";
    for (int i = 0; i < (int)strlen(validLetters); i++) {
        if (partialGrade == validPartials[i]) {
            matches++;
        }
    }

    if (!matches) {
        invalid_input_msg();
        return 0;
    }

    return 1;
}

int hasNode(Node* tScript, Course c, int year, char semester) {
    if ((*tScript) -> next == NULL) {
        return 0;
    }

    Node currentNode = (*tScript) -> next;
    
    while(currentNode != NULL) {

        if (equals(currentNode -> c, c) && currentNode -> year == year && currentNode -> semester == semester) {
            duplicate_course_msg();
            return 1;
        }
        
        currentNode = currentNode -> next;
    }
    return 0;
}

int courseTaken(Node* tScript, Course c, int print) {
    int count = 0;

    if ((*tScript) -> next == NULL) {
        course_not_taken_msg();
        return 0;
    }

    Node currentNode = (*tScript) -> next;
    
    while(currentNode != NULL) {

        if (equals(currentNode -> c, c)) {
            count++;
            if (print) {
                printf("%d.%c %s\n", currentNode -> year,
                    currentNode -> semester, currentNode -> grade);
            }
        }
        
        currentNode = currentNode -> next;
    }

    if (count == 0) {
        course_not_taken_msg();
    }
    return count;
}

void getValidGrade(char *letterGrade, char *partialGrade) {
    char gradeString[10];
    
    do {
        grade_prompt();
        fgets(gradeString, 9, stdin);
        gradeString[0] = toupper(gradeString[0]);
        //gradeString[9] = '\0';
    } while (!validGrade(gradeString));
    
    sscanf(gradeString, "%c %c", letterGrade, partialGrade);
}

void getValidSemester(int *year, char *semester) {
    char semesterString[10];
    do {
        semester_prompt();
        fgets(semesterString, 9, stdin);
        semesterString[5] = toupper(semesterString[5]);
        //inputLine[6] = '\0';
    } while (!validSemester(semesterString));

    sscanf(semesterString, "%d %*c %c", year, semester);
}


int getValidCourseID(Course* cLog, int num_courses) {

    int index = findCourseID(cLog, num_courses);

    while (index == -1) {
        course_absent_msg();
        index = findCourseID(cLog, num_courses);
    }
    return index;
}

int semesterTaken(Node* tScript, Course c, int year, char semester) {

    Node currentNode = (*tScript) -> next;
    
    while(currentNode != NULL) {

        if (equals(currentNode -> c, c) && currentNode -> year == year
            && currentNode -> semester == semester) {
            return 1;
        }
        
        currentNode = currentNode -> next;
    }
    return 0;
}

float gradeToGPA(char letterGrade, char partial) {
    char scale[] = "ABCDF";
    float grade = 4.0;

    for (int i = 0; i < 5; i++) {
        if (letterGrade == scale[i]) {
            grade -= i;
        }
    }

    char fractionals[] = "+/-";
    grade += 0.3;

    for (int i = 0; i < 3; i++) {
        if (partial == fractionals[i]) {
            grade -= i*(0.3);
        }
    }
    return grade;
}

float calculateGPA(Node* tScript) {

    double sum = 0.0;
    double totalCreds = 0.0;

    float credits = 0.0;
    char letterGrade = '\0';
    char partialGrade = '\0';

    Node head = *tScript;

    if (head -> next == NULL) {
        return 0;
    } else {

        Node currentNode = head -> next;

        while(currentNode != NULL) {

            credits = currentNode -> c -> credits; //or .credits
            letterGrade = currentNode -> grade[0];
            partialGrade = currentNode -> grade[1];

            sum += credits * gradeToGPA(letterGrade, partialGrade);
            totalCreds += credits;

            currentNode = currentNode -> next;
        }

        return (sum / totalCreds);
    }
}
