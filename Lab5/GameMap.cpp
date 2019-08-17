#include "GameMap.h"

GameMap::GameMap() {
	Node& Kimoran_Berg = addNode(new Node("Kimoran_Berg"));
	Node& Askhora = addNode(new Node("Askhora"));
	Node& Beramorin = addNode(new Node("Beramorin"));
	Node& Ostergaard = addNode(new Node("Ostergaard"));
	Node& Uthenwold = addNode(new Node("Uthenwold"));

	createConnection(Kimoran_Berg, Askhora, "Tunnel");
	createConnection(Beramorin, Ostergaard, "Tunnel");
	createConnection(Kimoran_Berg, Askhora, "Bruecke");
	createConnection(Askhora, Ostergaard, "Bruecke");
	createConnection(Askhora, Uthenwold, "Faehre");
	createConnection(Uthenwold, Kimoran_Berg, "Faehre");
	createConnection(Beramorin, Askhora, "Tunnel");
	createConnection(Ostergaard, Beramorin, "Bruecke");
	createConnection(Beramorin, Kimoran_Berg, "Bruecke");
}

void GameMap::createConnection(Node& rSrc, Node& rDst, std::string type) { // needs edit
	int cost;
	if (type == "Tunnel") {
		cost = 5;
		addEdge(new Connection(rSrc, rDst, cost, type));
	}
	else if (type == "Bruecke") {
		cost = 3;
		addEdge(new Connection(rSrc, rDst, cost, type));
	}
	else if (type == "Faehre") {
		cost = 3;
		addEdge(new Connection(rSrc, rDst, cost, type));
	}
	else
		throw "Der Verbindungstyp: " + type + " wird nicht unterstuetzt!";
}