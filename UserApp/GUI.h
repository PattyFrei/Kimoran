#pragma once
#include <string>
#include <iostream>
//#include "Chessboard.h"

using namespace std;

class GUI
{
public:
	GUI();
	//GUI(Chessboard& rGame);

	void showMenu() const;
	char getSelection();
	void showBoards() const;
	//char getBoard();
	char setBoard(char mySelection);

	void print(string output) const;
	void calculateShortestPath();
	void showChessboard() const;

private:
	//Chessboard& m_rGame;
	// list storage needed?

};
