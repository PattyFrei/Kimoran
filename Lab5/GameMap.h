#pragma once
#include "Graph.h"
#include "Connection.h"

class GameMap : public Graph
{
public:
	GameMap(); // init game map
	// creates Connection based on type Tunnel/Fähre/Brücke and applies edge weight and type name
	void createConnection(Node& rSrc, Node& rDst, std::string type); 
};
