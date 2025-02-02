#include <iostream>
#include "GameMap.h"
#include "GUI.h"

int main() {
	char mySelection;
	std::string fileName;
	int success;
	GameMap game;
	GUI user(game);

	user.print("\n_- Kimoran Treasure Hunt v1 -_");
	while (true) {
		// main menu
		user.showMenu();
		mySelection = user.getSelection();

		switch (mySelection) {
		case 'a':
		case 'A':
			// setup game section
			while (true) {	
				user.showFileInfo();
				fileName = user.getFileName();
				if (fileName == "quit") break;
				success = user.setGameMap(fileName);
				if (!success) break;
			} 
			if (fileName == "quit") break; // check if needed
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
	return 1;
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