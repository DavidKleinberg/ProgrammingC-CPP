/*  File: Bigram.cpp
    Homework 7, 600.120 Spring 2017

    600.120 | dkleinb1
    dkleinb1@jhu.edu
    ~~~~~~~~~~~~~~~~~~
    David A. Kleinberg
    Assignment 7
    04-18-2017
*/

#include "Bigram.hpp"

using std::string;
using std::cout;
using std::endl;

Bigram::Bigram(string one, string two) : s1(one), s2(two), count(0) {}

void Bigram::addUnigram(string unigram, int count) {

	if (this->unigrams.count(unigram) != 0) {
		this->unigrams.at(unigram) += count;
	} else {
		this->unigrams.emplace(unigram, count);
	}
	this->count++;
}

void Bigram::print() {
	cout << s1 << " " << s2 << " ";
}

void Unigram::print() {
	cout << s3 << " " << count << endl;
}

void Bigram::printForward() {

	std::map<string, int>::iterator iter = this->unigrams.begin();

	while (iter != this->unigrams.end()) {
    	cout << s1 << " " << s2 << " " << iter->first << " " << iter->second << endl;
        iter++;
    }
}

void Bigram::printReverse() {

	std::map<string, int>::iterator iter = this->unigrams.end();

	while (iter != this->unigrams.begin()) {
		iter--;
    	cout << s1 << " " << s2 << " " << iter->first << " " << iter->second << endl;
    }
}

void Bigram::printCount() {

	std::map<string, int>::iterator iter = this->unigrams.begin();

	while (iter != this->unigrams.end()) {
    	cout << s1 << " " << s2 << " " << iter->first << " " << iter->second << endl;
        iter++;
    }
}

string Bigram::getS1() const {
	return this->s1;
}

string Bigram::getS2() const {
	return this->s2;
}

int Bigram::getCount() const {
	return this->count;
}

vector<Unigram*>* Bigram::getUnigrams() {

	vector<Unigram*>* grams = new vector<Unigram*>();

	std::map<string, int>::iterator iter = this->unigrams.begin();

	while (iter != this->unigrams.end()) {

		std::vector<Unigram*>::iterator iter2 = grams->begin();

    	while (iter2 != grams->end()) {
    		if (iter->second <= (*iter2)->getCount()) {
    			break;
    		}
    		iter2++;
    	}
    	grams->insert(iter2, new Unigram(iter->first, iter->second));
        iter++;
    }

    return grams;

}

string Bigram::getNext() {

	vector<string> weightedUnigrams;

	std::map<string, int>::iterator iter = this->unigrams.begin();
	while (iter != this->unigrams.end()) {
		for (int i = 0; i < iter->second; i++) {
			weightedUnigrams.push_back(iter->first);
		}
		iter++;
	}
	return weightedUnigrams.at(rand()%this->count);
}

bool Bigram::operator==(Bigram rightHand) const {
	cout << this->getS1() << rightHand.getS1() << endl;

	if (this->getS1().compare(rightHand.getS1()) == 0 && this->getS2().compare(rightHand.getS2()) == 0) {
		return true;
	}
	return false;
}
bool Bigram::operator<(Bigram rightHand) const {
	if (this->getS1().compare(rightHand.getS1()) > 0) {
		return false;
	}
	if (this->getS1().compare(rightHand.getS1()) == 0 && this->getS2().compare(rightHand.getS2()) >= 0) {
		return false;
	}
	return true;
}
