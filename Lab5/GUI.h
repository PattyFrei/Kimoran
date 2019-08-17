#pragma once
#include <string>
#include <iostream>
#include "GameMap.h"
#include "Player.h"
#include "Island.h"

class GUI
{
public:
	GUI(GameMap& rGame); // init user interface

	void showMenu() const; // shows main menu options
	char getSelection(); // asks for main menu choice
	void showFileInfo() const; // prints information to successfuly read game files 
	std::string getFileName(); // asks for file name
	// checks if game file content is valid, inits all structures
	// play game: includes turns for human and computer player
	int setGameMap(std::string fileName); 
	void showGameMap() const; // prints all Islands and Connections with weights
	Node* getIslandChoice(); // asks for user input for human player
	Node* getIslandRandom(); // randomly gets an Island for computer player
	void print(std::string output) const; // prints something

private:
	GameMap& m_rGame;

};
