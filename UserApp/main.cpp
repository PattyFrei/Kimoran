#include <iostream>
#include "GUI.h"
#include <fstream>

using namespace std;

int main()
{
	char mySelection, myBoard;
	//Chessboard game;
	//GUI user(game);
	GUI user;

	user.print("\n_- Springer-Graph-Spiel v0.2 -_");

	while (true) {
		user.showMenu();
		mySelection = user.getSelection();

		switch (mySelection) {
		case 'a':
		case 'A':
			user.showBoards();
			myBoard = user.getSelection();
			user.setBoard(myBoard);
			break;
		case 'b':
		case 'B':
			user.print("calculateShortestPath()"); // placeholder
			user.calculateShortestPath();
			break;
		case 'c':
		case 'C':
			//user.showChessboard();
			user.print("showChessboard()"); // placeholder
			break;
		case 'q':
		case 'Q':
			user.print("Programm wird beendet..");
			system("pause");
			return 0;
		default:
			user.print("Die Funktion konnte nicht gefunden werden.");
			break;
		}
	}

	system("pause");
	return 0;
}

/* Djikstra aufrufen
// Lab 5 Aufgabe 6b:
std::deque<Edge*> path;
g.findShortestPathDijkstra(path, selectedSrcNode, selectedDstNode);

float distance = 0;
// Gibt alle Edges mit Gewichtung aus
for (Edge* pEdge : path) {
	Route* pRoute = dynamic_cast<Route*>(pEdge);
	std::cout << "Die Strecke " << pEdge->toString() << " betraegt " << pEdge->getWeight() << " km." << std::endl;
	distance += pEdge->getWeight();
}
std::cout << "\nDie Gesamtstrecke betraegt " << distance << " km." << std::endl
*/