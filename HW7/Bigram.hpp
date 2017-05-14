/*  File: Bigram.hpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#ifndef Bigram_HPP
#define Bigram_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Unigram {

public:

	//Constructors:
	Unigram(string three, int i) : s3(three), count(i) {};
	string getString() {
		return s3;
	}
	void print();
	int getCount() {
		return count;
	}


private:
	
	string s3;
	int count;
	//vector<Bigram*> bigrams;
};

class Bigram {

public:

	//Constructors:
	Bigram() : s1(), s2(), count(0) {};
	Bigram(string one, string two);

	//Getters:
	string getS1() const;
	string getS2() const;
	int getCount() const;
	string getNext();
	vector<Unigram*>* getUnigrams();

	//Setters:
	void addUnigram(string unigram, int count);
	
	//Comparators:
	bool operator==(Bigram rightHand) const;
	bool operator<( Bigram rightHand) const;

	//Functions:
	void printForward();
	void printReverse();
	void printCount();
	void print();

private:

	string s1;
	string s2;
	map<string, int> unigrams;
	int count;
};
	
#endif
