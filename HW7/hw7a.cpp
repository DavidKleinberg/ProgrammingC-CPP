/*  File: HW7a.cpp
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
        fprintf(stderr, "Usage: inputFile.txt Order-Symbol\n");
        return 1;  // exit program because no command line argument present
    }
    if (argv[2][0] != 'a' && argv[2][0] != 'r' && argv[2][0] != 'c') {
    	fprintf(stderr, "Invalid Order-Symbol\n");
        return 1;
    }

    TrigramDatabase database;
    database.openFileSet(argv[1]);

    if (argv[2][0] == 'a') {
        database.printAlphabetical();
    } else if (argv[2][0] == 'r') {
        database.printReverseAlphabetical();
    } else {
        database.printCount();
    }

 	
    return 0;
}
