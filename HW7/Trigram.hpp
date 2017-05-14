/*  File: Trigram.hpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#ifndef Trigram_HPP
#define Trigram_HPP

#include <iostream>
#include <string>

using std::string;

class Trigram {
public:

	Trigram() : s1(), s2(), s3() {};

	Trigram(string one, string two, string three);

	void print();

	void repeated();
	string getS1();
	string getS2();
	string getS3();
	int getCount();

private:

	string s1;
	string s2;
	string s3;
	int count;
};
	
#endif
