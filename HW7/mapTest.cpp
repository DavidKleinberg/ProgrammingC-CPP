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
#include <map>
#include <iterator>
#include <cstdlib>


using std::cout;
using std::endl;
using std::string;
using std::map;

int main(){

    map<string, int> m;

    string s1("a");
    string s2("b");
    string s3("c");
    string s4("d");
    string s5("e");

    m.emplace(s1, 2);
    m.emplace(s3, 3);
    m.emplace(s2, 2);
    
    m.emplace(s4, 4);
    m.emplace(s5, 5);

    std::map<string, int>::iterator it = m.begin();

    while (it != m.end()) {
        cout << it->first << it->second << endl;
        it++;
    }

    std::srand(4747);
    cout << rand()%5 << endl;
    cout << rand()%5 << endl;
    cout << rand()%5 << endl;

 	
    return 0;
}
