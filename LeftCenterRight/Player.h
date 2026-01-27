#pragma once

#include <iostream>

using namespace std;

class Player {
public:
	int chips;
	string name;
	Player *playerRight;
	Player *playerLeft;
	
	Player(string name, Player *right, Player *left) {
		this->name = name;
		this->playerRight = right;
		this->playerLeft = left;
		this->chips = 3;
	}

	int getChips() {
		return this->chips;
	}
	void addChip(){
		this->chips++;
	}
	void removeChip() {
		this->chips--;
	}
	string getName() {
		return this->name;
	}
	string setName(string name) {
		this->name = name;
	}

};