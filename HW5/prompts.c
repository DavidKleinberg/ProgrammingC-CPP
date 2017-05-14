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
#include "prompts.h"

void menu_prompt() {
    printf(
      "Course database\n"
      "---------------\n"
      "1. Display catalog\n"
      "2. Display course info\n"
      "3. Update course title\n"
      "4. Update course credits\n"
      "5. Add course to transcript\n"
      "6. Remove course from student transcript\n"
      "7. Display student transcript\n"
      "8. Display course transcript info\n"
      "9. Compute transcript GPA\n"
      "q. Quit\n"
      "\n"
      "Enter your choice:\n");
}

void course_absent_msg() {
    printf("The course is not available.\n");
}

void course_not_taken_msg() {
    printf("The course has not been taken.\n");
}

void course_updated_msg() {
    printf("The course has been updated.\n");
}

void empty_transcript_msg() {
    printf("The transcript is empty.\n");
}

void invalid_input_msg() {
    printf("Invalid input.\n");
}

void duplicate_course_msg() {
    printf("The course is already present.\n");
}

void transcript_updated_msg() {
    printf("The transcript has been updated.\n");
}

void course_prompt() {
    printf("Enter a course:\n");
}

void semester_prompt() {
    printf("Enter a semester:\n");
}

void grade_prompt() {
    printf("Enter course grade:\n");
}

void new_title_prompt() {
    printf("Enter a new course title:\n");
}

void new_credit_prompt() {
    printf("Enter a new credit assignment:\n");
}

void gpa_msg(double gpa) {
    printf("Student GPA is %.2f\n", gpa);
}
