#pragma once
//Tyler Shapiro
//IT312
//4/20/2024
//
//fileRead.h
//This file reads in a text file name, opens that file and then displays 
//the content of that file

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class fileRead {
public:

	void readFile(string fileName) {
		string line;
		fstream currFile(fileName);
		if (currFile.is_open()) {
			while (getline(currFile, line)) {
				cout << line << "\n";
			}
		}
		currFile.close();
	}
};