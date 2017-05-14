/*  File: TrigramDatabase.hpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#ifndef TrigramDatabase_HPP
#define TrigramDatabase_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include "Bigram.hpp"

using std::map;
using std::vector;

class compare {
public:
	bool operator()(const Bigram* lhs, const Bigram* rhs) const {
		return *lhs < *rhs;
	}
};

class TrigramDatabase {
public:

	TrigramDatabase() : count(0) {};

	void addBigram(Bigram* bigram, string unigram);
	void addTrigram(string s1, string s2, string s3, int count);
	void openFileSet(char* filename);
	void openModel(char* filename);
	void loadTrigrams(string filename);
	void generateText();
	bool hasNext(string s1, string s2);
	string getNext(string s1, string s2);

	void printAlphabetical() const;
	void printReverseAlphabetical() const;
	void printCount() const;

	vector<Bigram*>* compileBigrams() const;

private:

	map<Bigram*, int, compare> database;
	int count;

};
	
#endif
