#pragma once

struct Island
{
	Node* treasure;
	Node* camp1;
	Node* camp2;
	int camp1Coins;
	int camp2Coins;
	bool camp1Looted;
	bool camp2Looted;
};