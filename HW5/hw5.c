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

    char input[3] = "0\n";

    while(input[0] != 'q') {
        menu_prompt();
        fgets(input, 3, stdin);

        switch(input[0]) {

        case '1':
        	for (int i = 0; i < num_courses; i++) {
    			printCourse(cLog[i]);
    		}
            break;

        case '2':
        {
            int index = getValidCourseID(cLog, num_courses);

            printCourse(cLog[index]);
        }
        break;

        case '3':
        {
            int index = getValidCourseID(cLog, num_courses);         

            char title[35];
            do {
                new_title_prompt();
                fgets(title, 35, stdin);
                title[34] = '\0';
            }
            while (!validCourseTitle(title));

            sscanf(title, "%[^\n]", title);
            strcpy(cLog[index] -> courseTitle, title);

            course_updated_msg();
        }
        break;

        case '4':
        {
            int index = getValidCourseID(cLog, num_courses);         

            char creditString[10];
            float credits = 0;
            do {
                new_credit_prompt();
                fgets(creditString, 10, stdin);
            }
            while (!validCredits(creditString));

            sscanf(creditString, "%f", &credits);
            cLog[index] -> credits = credits;

            course_updated_msg();          
        }
        break;

        case '5':
        {
            int has = 0;
            int index = 0;
            int year = 0;
            char semester = '\0';
            char letter = '\0';
            char partial = '\0';

            do {
                index = getValidCourseID(cLog, num_courses);
                getValidSemester(&year, &semester);

                getValidGrade(&letter, &partial);

                has = hasNode(tScript, cLog[index], year, semester);

            } while (has);
                
                char grade[3] = "00";
                grade[0] = letter;
                grade[1] = partial;

                addCourse(tScript, cLog[index], grade, year, semester);
                transcript_updated_msg();
        }
        break;

        case '6':
        {

            int taken = 0;
            int index = 0;
            do {
                index = getValidCourseID(cLog, num_courses);
                taken = courseTaken(tScript, cLog[index], 0);
            } while (!taken);

            if (taken == 1) {
                deleteCourse(tScript, cLog[index]);
                transcript_updated_msg();
            } else {
                int year = 0;
                char semester = '\0';

                do {
                    getValidSemester(&year, &semester);
                } while(!semesterTaken(tScript, cLog[index], year, semester));

                deleteCourseInSem(tScript, cLog[index], year, semester);
                transcript_updated_msg();
            }
        }
        break;

        case '7':
        {
            printTranscript(tScript);
        }
        break;

        case '8':
        {
            int taken = 0;
            int index = 0;
            do {
                index = getValidCourseID(cLog, num_courses);
                taken = courseTaken(tScript, cLog[index], 0);
            } while (!taken);
            
            courseTaken(tScript, cLog[index], 1);
        }
        break;

        case '9':
        {
            gpa_msg(calculateGPA(tScript));
        }
        break;

        default:
            break;
        }
    }

    for (int i = 0; i < num_courses; i++) {
        free(cLog[i]);
    }

    free(cLog);

    freeTranscript(tScript);

    return 0;
}
