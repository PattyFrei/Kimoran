#pragma once

struct Player 
{
	bool type; // false for computer, true for human player
	Node* startIsland;
	Node* currentIsland;
	int startCoins;
	int currentCoins;
};