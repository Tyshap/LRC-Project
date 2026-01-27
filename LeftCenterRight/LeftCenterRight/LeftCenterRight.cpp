// Tyler Shapiro
// IT312
// 4/20/2024
//
// LeftCenterRight.cpp
// This program is used to run and play the left center right game.

#include <iostream>
#include "fileRead.h"
#include "Player.h"
#include <vector>
#include <cstdlib>
using namespace std;


Player rollDice(Player player);
bool checkWinner(vector<Player> playerList);
vector<Player> fixPlayers(vector<Player> playerList);

int main() {
    srand((unsigned)time(NULL)); //sets seed for rand() function
    fileRead rules;
    rules.readFile("rules.txt"); //Outputs rules to the console
    bool noWinner = true;
    bool lastName = false;
    bool turn = true;
    string choice;
    string name;
    vector<Player> playerList; //Used for storing the players within the game
    do { //Loop gets names from user and then creats a new player object for the player list using that name
        cout << "Please Enter your name(or enter 1 if you are finished): ";
        cin >> name;
        if (name.compare("1") == 0) { //checks if user wants to exit the loop
            if (playerList.size() < 3) {
                cout << "\nYou need at least three players to start the game.\n";
            }
            else {
                lastName = true;
            }
        }
        else {
            playerList.push_back(Player(name, NULL, NULL)); //creates new player to append the list
            cout << "\nPass to the player on the right.\n";
        }
    } while (lastName == false);
    playerList = fixPlayers(playerList); //sets the playerRight and playerLeft once all knon players are available to be called to
    do { //Loop begins and keeps the game going
        for (int i = 0; i < playerList.size(); i++) { //iterates through the list of players
            turn = true;
            do { //loop keeps each turn going until the player rolls the dice
                if (playerList[i].getChips() > 0) { //validating user input
                    cout << playerList[i].getName() << "'s turn. Enter 1 to roll your dice or 2 to check how many chips you have" << endl;
                    cin >> choice;
                    if (choice.compare("1") == 0) {
                        playerList[i] = rollDice(playerList[i]);
                        turn = false;
                    }
                    else if (choice.compare("2") == 0) {
                        cout << "You have " << playerList[i].getChips() << " chips remaining" << endl;
                    }
                    else {
                        cout << "That is not a valid option" << endl;
                    }
                    cout << endl;
                }
                else {
                    cout << playerList[i].getName() << " Has no chips remaining\n" << endl;
                    turn = false;
                }
            } while (turn);
            noWinner = checkWinner(playerList);
            if(!noWinner) {
                break;
            }
        }
   } while (noWinner);
}

Player rollDice(Player player) { //This Funtion takes in a Player and then performs the game action of rolling dice for that player
    int rolls = 2;
    if (player.getChips() == 1) {
        rolls = 1;
    }
    for (int i = 0; i < rolls; i++) {
        int dieOne = (rand() % 6);
        switch (dieOne) {
        case 0:
            cout << player.getName() << " has rolled an L!\n";
            player.playerLeft->addChip();
            player.removeChip();
            cout << player.getChips() << endl;
            cout << player.getName() << " has given a chip to " << player.playerLeft->getName() << ".\n";
            break;
        case 1:
            cout << player.getName() << " has rolled an R!\n";
            player.playerRight->addChip();
            player.removeChip();
            cout << player.getChips() << endl;
            cout << player.getName() << " has given a chip to " << player.playerRight->getName() << ".\n";
            break;
        case 2:
            cout << player.getName() << " has rolled a C!\n";
            player.removeChip();
            cout << player.getChips() << endl;
            cout << player.getName() << " has put a chip in the center.\n";
            break;
        default:
            cout << player.getName() << " rolled a dot!\nNo action is required to be taken\n";
            break;
        }
    }
    return player;

}
bool checkWinner(vector<Player> playerList) { //This function takes in the list of players and determines wether or not there is only 1 player with remaining chips and returns false if there is, but otherwise returns true
    int playersWithChips = 0;
    string winningPlayer;
    for (int i = 0; i < playerList.size(); i++) {
        if (playerList[i].getChips() > 0) {
            playersWithChips++;
            winningPlayer = playerList[i].getName();
        }
    }
    if (playersWithChips == 1) {
        cout << winningPlayer << " is the only player with any chips remaining and has won the game!";
        return false;
    }
    else {
        return true;
    }
}
vector<Player> fixPlayers(vector<Player> playerList) {
    for (int i = 0; i < playerList.size(); i++) {
        if (i == 0) {
            playerList[i].playerRight = &playerList[i + 1];
            playerList[i].playerLeft = &playerList[playerList.size() - 1];
        }
        else if (i == playerList.size() - 1) {
            playerList[i].playerRight = &playerList[0];
            playerList[i].playerLeft = &playerList[i - 1];
        }
        else {
            playerList[i].playerRight = &playerList[i + 1];
            playerList[i].playerLeft = &playerList[i - 1];
        }
    }
    return playerList;
}