/*  File: Trigram.cpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#include "Trigram.hpp"

using std::string;
using std::cout;
using std::endl;

Trigram::Trigram(string one, string two, string three) : s1(one), s2(two), s3(three), count(1) {}

void Trigram::print() {
	cout << s1 << " " << s2 << " " << s3 << " " << count << "\n" << endl;
}

int compareAlphabetical(Trigram trigram) {
	return this->s1.compare(trigram.s1);
}

int compareReverseAlphabetical(Trigram trigram) {
	return (this->s1.compare(trigram.s1) * -1;
}

int compareCount(Trigram trigram) {
	if (this->count > trigram.getCount()) {
		return 1;
	} else if (this->count < trigram.getCount()) {
		return -1;
	} else {
		return this->compareAlphabetical(trigram);
	}
}

string Trigram::getS1() {
	return this-> s1;
}

string Trigram::getS2() {
	return this-> s2;
}

string Trigram::getS3() {
	return this-> s3;
}

int getCount() {
	return this-> count;
}

void Trigram::repeated() {
	this->count += 1;
}
