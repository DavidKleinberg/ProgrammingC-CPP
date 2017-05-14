/*  File: TrigramDatabase.cpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#include "TrigramDatabase.hpp"

using std::ifstream;
using std::ofstream;
using std::string;
using std::map;

void TrigramDatabase::addBigram(Bigram* bigram, string unigram) {

	if (this->database.count(bigram) != 0) {
		map<Bigram*, int>::const_iterator iter = this->database.find(bigram);
		iter->first->addUnigram(unigram, 1);
		delete(bigram);
	} else {
		bigram->addUnigram(unigram, 1);
		this->database.emplace(bigram, 1);
	}
	this->count++;
}

void TrigramDatabase::addTrigram(string s1, string s2, string s3, int count) {

	Bigram* bigram = new Bigram(s1, s2);
	if (this->database.count(bigram) != 0) {
		map<Bigram*, int>::const_iterator iter = this->database.find(bigram);
		iter->first->addUnigram(s3, count);
		delete(bigram);
	} else {
		bigram->addUnigram(s3, count);
		this->database.emplace(bigram, count);
	}
	this->count += count;
}

void TrigramDatabase::openFileSet(char* filename) {
	ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open()) { 
		fprintf(stderr, "invalid input file\n");
    	return;
	}
	
	string textFile;
	while (!inputFile.eof()) {
		inputFile >> textFile;
		if (inputFile.eof()) {
			break;
		}
		loadTrigrams(textFile);
	}

	inputFile.close();
}

void TrigramDatabase::openModel(char* filename) {

	ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open()) { 
		fprintf(stderr, "invalid input file\n");
    	return;
	}

	string s1;
	string s2;
	string s3;
	int count;

	while (!inputFile.eof()) {
		inputFile >> s1;
		inputFile >> s2;
		inputFile >> s3;
		inputFile >> count;
		if (inputFile.eof()) {
			break;
		}
		this->addTrigram(s1, s2, s3, count);
	}

	inputFile.close();
}


void TrigramDatabase::loadTrigrams(string filename) {

	ifstream inputFile;
	inputFile.open(filename);

	if (!inputFile.is_open()) { 
		fprintf(stderr, "invalid input file\n");
    	return;
	}

	//Bigram bigram;
	string s1("<START_1>");
	string s2("<START_2>");
	string s3;
	string temp;

	inputFile >> s3;
	this->addBigram(new Bigram(s1, s2), s3);

	while (!inputFile.eof()) {
		temp = s3;
		inputFile >> s3;
		if (inputFile.eof()) {
			break;
		}
		s1 = s2;
		s2 = temp;
		this->addBigram(new Bigram(s1, s2), s3);
	}

	inputFile.close();

	s1 = s2;
	s2 = s3;
	s3 = "<END_1>";
	this->addBigram(new Bigram(s1, s2), s3);

	s1 = s2;
	s2 = s3;
	s3 = "<END_2>";
	this->addBigram(new Bigram(s1, s2), s3);

}

void TrigramDatabase::printAlphabetical() const {

	map<Bigram*, int>::const_iterator iter = this->database.begin();

	while (iter != this->database.end()) {
    	iter->first->printForward();
        iter++;
    }
}

void TrigramDatabase::printReverseAlphabetical() const {

	map<Bigram*, int>::const_iterator iter = this->database.end();

	while (iter != this->database.begin()) {
    	iter--;
    	iter->first->printReverse();
    }
}

void TrigramDatabase::printCount() const {

	//map<Bigram*, int>::const_iterator iter = this->database.begin();
	vector<Bigram*>* bigrams = this->compileBigrams();
	vector<Bigram*>::const_iterator iter = bigrams->begin();

	while (iter != bigrams->end()) {
    	//map<Bigram*, int>::const_iterator iter2 = iter->first->getUnigrams();
		vector<Unigram*>* unigrams = (*iter)->getUnigrams();
		vector<Unigram*>::const_iterator iter2 = unigrams->begin();
		while (iter2 != unigrams->end()){
			(*iter)->print();
			(*iter2)->print();
			iter2++;
		}

        iter++;
    }
}

vector<Bigram*>* TrigramDatabase::compileBigrams() const{

	vector<Bigram*>* grams = new vector<Bigram*>();

	std::map<Bigram*, int>::const_iterator iter = this->database.begin();

	while (iter != this->database.end()) {

		std::vector<Bigram*>::iterator iter2 = grams->begin();

    	while (iter2 != grams->end()) {
    		if (iter->second >= (*iter2)->getCount()) {
    			break;
    		}
    		iter2++;
    	}
    	grams->insert(iter2, iter->first);
        iter++;
    }
    return grams;
}

void TrigramDatabase::generateText() {
	string s1("<START_1>");
	string s2("<START_2>");
	string temp;

	std::cout << s1 << " " << s2 << " ";
	while (this->hasNext(s1, s2)) {
		temp = s2;
		s2 = this->getNext(s1, s2);
		s1 = temp;
		std::cout << s2 << std::endl;
	}
}

bool TrigramDatabase::hasNext(string s1, string s2) {
	Bigram* temp = new Bigram(s1, s2);
	if (this->database.count(temp) != 0) {
		delete(temp);
		return true;
	}
	
	delete(temp);
	return false;
}

string TrigramDatabase::getNext(string s1, string s2) {

	Bigram* temp = new Bigram(s1, s2);
	std::map<Bigram*,int>::iterator iter = this->database.find(temp);
	Bigram* current = iter->first;
	delete(temp);
	return current->getNext();
}
