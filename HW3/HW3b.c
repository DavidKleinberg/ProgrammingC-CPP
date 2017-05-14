/*  File: hw3b.c
    Homework 3, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 3
    02-28-2017
*/

#include <stdio.h>

/**
 * Print all the menu items.
 */
void printMenu() {
    printf(
        "n - display the total number of courses\n"
        "d - list all courses from a particular department\n"
        "l - list all courses with a particular letter grade\n"
        "c - list all courses with at least a specified number of credits\n"
        "g - compute the GPA of all the courses with letter grades\n"
        "q - quit the program\n"
        "Enter letter choice ->\n");
}

/**
 * Report the total number of courses.
 *
 * @param i the integer number of courses
 */
void promptN(int i) {
    printf("Total number of courses: %d\n", i);
}

/**
 * Prompt the user to enter the department number.
 */
void promptD() {
    printf("Enter the department:\n");
}

/**
 * Prompt the user to enter a letter grade.
 */
void promptL() {
    printf("Enter a letter grade and mark (+,-,/):\n");
}

/**
 * Prompt the user to enter a minimum number of credits.
 */
void promptC() {
    printf("Enter number of credits:\n");
}

/**
 * Report the calculated GPA.
 *
 * @param gpa the float valued calculation
 */
void promptG(float gpa) {
    printf("GPA: %.3f\n", gpa);
}

/**
 * Report that no matches were found.
 */
void noMatches() {
    printf("No matches\n");
}

/**
 * Report the letter grade encoded.
 *
 * @param code the unsigned int code
 *
 * return a character letter grade
 */
char getLetterGrade(unsigned int code) {

    char gradeCodes[] = "ABCDFISU";

    unsigned int grade = 7 << 6;
    grade &= code;
    grade >>= 6;
    return gradeCodes[(int)grade];
}

/**
 * Report the partial letter grade encoded.
 *
 * @param code the unsigned int code
 *
 * return a character partial grade
 */
char getPartialGrade(unsigned int code) {

    char partTwoCodes[] = "+-/";

    unsigned int gradePartTwo = 3 << 4;
    gradePartTwo &= code;
    gradePartTwo >>= 4;
    return partTwoCodes[(int)gradePartTwo];
}

/**
 * Method for calculating 1 single GPA.
 *
 * @param letter grade
 * @param partial grade
 *
 * return a float calculation
 */
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

/**
 * Method for retrieving the credits from the
 * encoded course.
 *
 * @param code the course
 *
 * return a float the number of credits
 */
float getCredits(unsigned int code) {

    unsigned int credits = 7 << 1;
    credits &= code;
    credits >>= 1;

    unsigned int partial = 1;
    partial &= code;

    float credsFull = 0.5 * partial + credits;

    return credsFull;
}

/**
 * Method for retrieving the department and course #.
 *
 * @param code
 * @param bitShift
 *
 * return a three digit unsigned int
 */
unsigned int getThreeDigits(unsigned int code, int bitShift) {

    unsigned int mask10 = 1023;

    unsigned int threeDigits = mask10 << bitShift;
    threeDigits &= code;
    threeDigits >>= bitShift;

    return threeDigits;
}

/**
 * Method for printing the string representation of the course
 *
 * @param code
 */
void courseDecoder(unsigned int code) {

    char *divisionCodes[8] = {"ME","BU","ED","EN","AS","PH","PY","SA"};

    unsigned int division = 7 << 29;
    division &= code;
    division >>= 29;
    printf("%s.", divisionCodes[(int)division]);

    printf("%03u.", getThreeDigits(code, 19));
    printf("%03u.", getThreeDigits(code, 9));

    printf("%c", getLetterGrade(code));
    printf("%c", getPartialGrade(code));
    printf("%.1f\n", getCredits(code));
}

int main(int argc, char* argv[]) {

    // Confirm that a command-line argument is present
    if (argc == 1) {
        printf("Usage: inputFile.txt\n");
        return 1;  // exit program because no command line argument present
    }

    unsigned int codeArray[2500] = {0};
    char stringInput[13];
    int count = 0;

    FILE* inputFilePointer = fopen(argv[1], "r");

    while(fgets(stringInput, 13, inputFilePointer)) {
        sscanf(stringInput, "%u", &codeArray[count]);
        count++;
    }

    fclose(inputFilePointer);

    char input[] = "0\n";
    int matches = 0;

    while(input[0] != 'q') {
        printMenu();
        fgets(input, 4, stdin);

        switch(input[0]) {
        case 'n':
        case 'N':
            promptN(count);
            break;

        case 'd':
        case 'D':
        {
            char departmentString[] = "000\n";
            unsigned int department = 0;
            promptD();

            fgets(departmentString, 6, stdin);
            sscanf(departmentString, "%u", &department);

            for (int i = 0; i < count; i++) {
                if (getThreeDigits(codeArray[i], 19) == department) {
                    courseDecoder(codeArray[i]);
                    matches++;
                }
            }

            if (matches == 0) {
                noMatches();
            }
            matches = 0;
        }
        break;

        case 'l':
        case 'L':
        {
            char letterGradeString[] = "00\n";
            promptL();

            fgets(letterGradeString, 5, stdin);

            for (int i = 0; i < count; i++) {
                if(getLetterGrade(codeArray[i]) == letterGradeString[0] &&
                        getPartialGrade(codeArray[i]) == letterGradeString[1]) {
                    courseDecoder(codeArray[i]);
                    matches++;
                }
            }

            if (matches == 0) {
                noMatches();
            }
            matches = 0;
        }
        break;

        case 'c':
        case 'C':
        {
            char creditString[] = "0.0\n";
            float credits = 0.0;
            promptC();

            fgets(creditString, 6, stdin);
            sscanf(creditString, "%f", &credits);
            for (int i = 0; i < count; i++) {
                if (getCredits(codeArray[i]) >= credits) {
                    courseDecoder(codeArray[i]);
                    matches++;
                }
            }

            if (matches == 0) {
                noMatches();
            }
            matches = 0;
        }
        break;

        case 'g':
        case 'G':
        {
            float sum = 0.0;
            float totalCreds = 0.0;

            for (int i = 0; i < count; i++) {
                sum += getCredits(codeArray[i]) * gradeToGPA(getLetterGrade(codeArray[i]), getPartialGrade(codeArray[i]));
                totalCreds += getCredits(codeArray[i]);
            }
            promptG(sum / totalCreds);
        }
        break;

        default:
            break;
        }
    }
    return 0;
}
