/*  File: HW7b.cpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#include <iostream>
#include <string>
#include "TrigramDatabase.hpp"

using std::cout;
using std::endl;
using std::string;


int main(int argc, char* argv[]){

    if (argc != 3) {
        fprintf(stderr, "Usage: inputFile.txt Repetitions\n");
        return 1;  // exit program because no command line argument present
    }

    int numTexts;

    if (sscanf(argv[2], "%d", &numTexts) == 0) {
    	fprintf(stderr, "Requires integer input\n");
        return 1;
    }

    TrigramDatabase database;
    database.openModel(argv[1]);

    std::srand(4747);

    for (int i = 0; i < numTexts; i++) {
    	database.generateText();
    }
    return 0;
}
