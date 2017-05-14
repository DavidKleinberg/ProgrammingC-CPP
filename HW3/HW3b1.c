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

void promptN(int i) {
    printf("Total number of courses: %d\n", i);
}

void promptD() {
    printf("Enter the department:\n");
}

void promptL() {
    printf("Enter a letter grade and mark (+,-,/):\n");
}

void promptC() {
    printf("Enter number of credits:\n");
}

void promptG(float gpa) {
    printf("GPA: %.3f\n", gpa);
}

void noMatches() {
    printf("No matches\n");
}

char getLetterGrade(unsigned int code) {

    char gradeCodes[] = "ABCDFISU";

    unsigned int grade = 7 << 6;
    grade &= code;
    grade >>= 6;
    return gradeCodes[(int)grade];
}

char getPartialGrade(unsigned int code) {

    char partTwoCodes[] = "+-/";

    unsigned int gradePartTwo = 3 << 4;
    gradePartTwo &= code;
    gradePartTwo >>= 4;
    return partTwoCodes[(int)gradePartTwo];
}

float gradeToGPA(char letterGrade, char partial) {
    char scale[] = "ABCDF";
    float grade = 4.0;

    for (int i = 0; i < 4; i++) {
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

float getCredits(unsigned int code) {

    unsigned int credits = 7 << 1;
    credits &= code;
    credits >>= 1;

    unsigned int partial = 1;
    partial &= code;

    float credsFull = 0.5 * partial + credits;

    return credsFull;
}


void courseDecoder(unsigned int code) {

    char *divisionCodes[8] = {"ME","BU","ED","EN","AS","PH","PY","SA"};
    //char gradeCodes[] = "ABCDFISU";
    //char partTwoCodes[] = "+-/";
    //char partialCredCode[] = "05";

    unsigned int mask10 = 1023;
    unsigned int mask3 = 7;
    unsigned int mask2 = 3;
    unsigned int mask1 = 1;

    unsigned int division = mask3 << 29;
    division &= code;
    division >>= 29;
    printf("%s.", divisionCodes[(int)division]);

    unsigned int department = mask10 << 19;
    department &= code;
    department >>= 19;
    printf("%03u.", department);

    unsigned int courseNumber = mask10 << 9;
    courseNumber &= code;
    courseNumber >>= 9;
    printf("%03u.", courseNumber);

    /*unsigned int grade = mask3 << 6;
    grade &= code;
    grade >>= 6;
    */
    printf("%c", getLetterGrade(code));

    /*unsigned int gradePartTwo = mask2 << 4;
    gradePartTwo &= code;
    gradePartTwo >>= 4;*/
    printf("%c", getPartialGrade(code));

    /*unsigned int credits = mask3 << 1;
    credits &= code;
    credits >>= 1;
    printf("%u.", credits);

    unsigned int fractional = mask1;
    fractional &= code;*/
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

                unsigned int mask = 1023;
                mask <<= 19;
                for (int i = 0; i < count; i++) {
                    unsigned int departmentCheck = codeArray[i];
                    departmentCheck &= mask;
                    departmentCheck >>= 19;
                    if (departmentCheck == department) {
                        courseDecoder(codeArray[i]);
                    }

                }
            }
            break;

            case 'l':
            case 'L':
            {
                char gradeCodes[] = "ABCDFISU";
                char partTwoCodes[] = "+-/";

                char letterGradeString[] = "00\n";
                unsigned int letterGrade = 0;
                unsigned int gradePartTwo = 0;
                promptL();

                fgets(letterGradeString, 5, stdin);
                for (int i = 0; i < 8; i++) {
                    if (letterGradeString[0] == gradeCodes[i]) {
                        letterGrade = i;
                    }
                }
                for (int i = 0; i < 3; i++) {
                    if (letterGradeString[1] == partTwoCodes[i]) {
                        gradePartTwo = i;
                    }
                }

                letterGrade <<= 6;
                gradePartTwo <<= 4;
                letterGrade |= gradePartTwo;
                letterGrade >>= 4;

                unsigned int mask = 31;
                mask <<= 4;
                for (int i = 0; i < count; i++) {
                    unsigned int gradeCheck = codeArray[i];
                    gradeCheck &= mask;
                    gradeCheck >>= 4;
                    if (gradeCheck == letterGrade) {
                        courseDecoder(codeArray[i]);
                    }

                }
            }
            break;

            case 'c':
            case 'C':
            {
                char creditString[] = "0.0\n";
                unsigned int credits = 0;
                unsigned int fractional = 0;
                promptC();

                fgets(creditString, 6, stdin);
                sscanf(&creditString[0], "%u", &credits);
                sscanf(&creditString[2], "%u", &fractional);
                credits <<= 1;
                if (fractional == 5) {
                    fractional = 1;
                } else if (fractional != 0) {
                    fractional = 0;
                }
                credits |= fractional;

                unsigned int mask = 15;
                for (int i = 0; i < count; i++) {
                    unsigned int creditCheck = codeArray[i];
                    creditCheck &= mask;
                    if (creditCheck >= credits) {
                        courseDecoder(codeArray[i]);
                    }

                }
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
