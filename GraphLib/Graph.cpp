#include <iostream>
#include "Graph.h"
#include <list> // sequence container, double linked list, insert/erase operations, iteration in both directions
#include <fstream> // input/ouput stream to operate on files
#include <algorithm> // methods used on ranges of elements, ranges are accessed through iterators and pointers
#include <limits> // to infinity and even further
#include <map>

//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	// - soll einen Node mit der gegebenen id in m_nodes suchen
	// - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
	// - gibt NULL zurück, falls kein Node mit der id gefunden wurde.
	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++) {
		if ((*it)->getID() == id) {
			return *it;
		}
	}
	return NULL;
}

//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	// bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
	//return *new Node("");

	// Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
	// Falls ja:
	//  - Exception werfen
	// Falls nein:
	//  - den neuen Node 'pNewNode' in m_nodes einfügen
	//  - Referenz auf den neuen Node zurück geben
	if (findNode(pNewNode->getID()) == NULL) {
		m_nodes.push_back(pNewNode);
		return *pNewNode;
	}
	else
		throw "Die ID ist schon vorhanden!";
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	// bitte diese Zeile entfernen, wenn Sie die Funktion implementieren:
	//return *new Edge(*new Node(), *new Node());

	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)
	std::list<Node*>::iterator itSrc = std::find(m_nodes.begin(), m_nodes.end(), &pNewEdge->getSrcNode());
	if (itSrc == m_nodes.end()) {
		addNode(&pNewEdge->getSrcNode());
	}

	std::list<Node*>::iterator itDst = std::find(m_nodes.begin(), m_nodes.end(), &pNewEdge->getDstNode());
	if (itDst == m_nodes.end()) {
		addNode(&pNewEdge->getDstNode());
	}

	// - die neue Edge 'pNewEdge' in m_edges einfügen
	// - Referenz auf die neue Edge zurück geben
	m_edges.push_back(pNewEdge);
	return *pNewEdge;
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	// - soll alle Edges im Graph löschen (delete)
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++) {
		delete *it;
	}
	// - soll alle Nodes im Graph löschen (delete)
	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++) {
		delete *it;
	}
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
	// - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end();)
	{ // iterator wird nicht inkrementiert (it++), sonst werden beim löschen elemente übersprungen
		if ((*it)->isConnectedTo(rNode)) {
			delete *it;
			it = m_edges.erase(it); // zeigt auf das nächste element nach dem löschen
		}
		else {
			it++;
		}
	}
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
	// 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
	m_nodes.remove(&rNode);
	// 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!
	delete &rNode;
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
	// - der Pointer auf rEdge muss aus m_edges entfernt werden!
	m_edges.remove(&rEdge);
	// - der Pointer auf rEdge muss mit 'delete' freigegeben werden!
	delete &rEdge;
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
	// - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
	// - füge die Zeiger der Edges in den vector 'ret' ein.
	std::vector<Edge*> ret;
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++) {
		if (&(*it)->getSrcNode() == &rSrc) {
			ret.push_back(*it);
		}
	}
	for (std::list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++) {
		if (&(*it)->getDstNode() == &rDst) {
			ret.push_back(*it);
		}
	}
	return ret;
}

//---------------------------------------------------------------------------------------------------------------------

struct DijkstraEntry {
	double dist;
	Node* prevNode;
	Edge* prevEdge;
};

//void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node* rSrcNode, const Node* rDstNode)
{
	// nodes to search for in the graph:
	Node* pSrc = findNode(rSrcNode->getID());
	Node* pDst = findNode(rDstNode->getID());

	// Test points:
	std::cout << "\nBerechne die kuerzeste Strecke von " << rSrcNode->getID() << " nach " << rDstNode->getID() << ":" << std::endl;
	if (pSrc == NULL || pDst == NULL)
		throw "rSrcNode oder rDstNode war nicht im Graphen vorhanden!";

	// create vertex set Q
	std::list<Node*> Q;
	std::map<Node*, DijkstraEntry> nodeTable;

	// for each vertex v in Graph: -- init
	for (auto pNode : m_nodes) {
		nodeTable[pNode] = {
			std::numeric_limits<double>::max(), NULL, NULL
		};
		// add v to Q -- All nodes initially in Q (unvisited nodes)
		Q.push_back(pNode);
	}

	// dist[source] <- 0 -- Distance from source to source
	nodeTable[pSrc].dist = 0;

	// while Q is not empty
	while (!Q.empty()) {

		// u <- vertex in Q with min dist[u] -- Source node will be selected first
		Node* u = Q.front();
		for (auto pNode : Q) {
			if (nodeTable[pNode].dist < nodeTable[u].dist) {
				u = pNode;
			}
		}
		if (u == pDst)
			break;

		// remove u form Q
		Q.remove(u);

		// for each neighbor v of u: -- where v is still in Q
		for (auto pEdge : u->getOutEdges()) {
			Node* v = &pEdge->getDstNode();
			// alt <- dist[u] + length(u, v)
			double newWeight = nodeTable[u].dist + pEdge->getWeight();
			// if alt < dist[v]: -- A shorter path to v has been found
			if (newWeight < nodeTable[v].dist) {
				// dist[v] <- alt
				// prev[v] <- u
				nodeTable[v].dist = newWeight;
				nodeTable[v].prevNode = u;
				nodeTable[v].prevEdge = pEdge;
			}
		}
	}

	// creates path from table (from dst node to scr node)
	// goes back as long as there's a previous item
	for (Node* currentNode = pDst; nodeTable[currentNode].prevEdge != NULL;
		currentNode = nodeTable[currentNode].prevNode) {
		rPath.push_front(nodeTable[currentNode].prevEdge);
	}

}