#include "GUI.h"
#include "GameMap.h"
#include <map>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

GUI::GUI(GameMap& rGame) : m_rGame(rGame) {}

void GUI::showMenu() const {
	std::cout << "\nBitte geben Sie an was Sie tun moechten: "
		<< "\n (a) Eine Spielwelt laden"
		<< "\n (q) Das Programm beenden";
}

char GUI::getSelection() {
	std::string input = "";
	char mySelection = { 0 }; // get a single char

	std::cout << "\nBitte machen Sie eine Auswahl: ";
	while (true) {
		getline(std::cin, input);
		std::cin.clear();
		if (input.length() == 1) { // checks if input is a single character
			mySelection = input[0];
			if (isdigit(input[0]) == 0) { // checks if char is not an integer
				break;
			}
		}
		std::cout << "Ungueltige Auswahl, bitte waehlen Sie erneut: ";
	}
	return mySelection;
}

void GUI::showFileInfo() const {
	std::cout << "\n- Geben Sie an, aus welcher Datei die Spielwelt geladen werden soll."
		<< "\n- Geben Sie nur den Namen der Datei an (ohne Dateiendung)." 
		<< "\n- Es koennen nur .txt Dateien geladen werden."
		<< "\n- Stellen Sie sicher, dass die Spieldatei im gleichen Ordner wie die Spielanwendung liegt."
		<< "\n- Geben Sie \"quit\" ein, um ins Hauptmenue zurueckzukehren.";
}

std::string GUI::getFileName() {
	std::string fileName = "";
	// get a file name as string
	std::cout << "\nBitte machen Sie eine Eingabe: ";
	getline(std::cin, fileName);
	return fileName;
}

int GUI::setGameMap(std::string fileName) {
	std::ifstream gameFile(fileName + ".txt");
	std::string line;
	int failCounter = 0;
	Island setting;
	Player human;
	Player com;

	// setup game section
	if (gameFile.is_open()) {
		std::cout << "\nUeberpruefe Spieldatei..\n";
		// reads file line by line
		while (getline(gameFile, line)) {

			// finds delimiter " " and spilts lines into strings
			auto delimiterPos = line.find(" ");
			std::string object = line.substr(0, delimiterPos);
			std::string objectSetting = line.substr(delimiterPos + 1);

			// processes line based on first string "object"
			if (object == "Insel") { // checks if "Insel" object is available
				Node* compareNode = m_rGame.findNode(objectSetting);
				if (compareNode == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				} else
					std::cout << "Eine " << object << " wurde gefunden.\n";
			}
			else if (object == "Tunnel") { // checks if "Tunnel" object is available
				delimiterPos = objectSetting.find(" ");
				std::string src = objectSetting.substr(0, delimiterPos);
				std::string dst = objectSetting.substr(delimiterPos + 1);
				Node* pSrc = m_rGame.findNode(src);
				Node* pDst = m_rGame.findNode(dst);

				if (pSrc == NULL || pDst == NULL ) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else
					std::cout << "Ein " << object << " wurde gegraben.\n";
			}
			else if (object == "Bruecke") { // checks if "Bruecke" object is available
				delimiterPos = objectSetting.find(" ");
				std::string src = objectSetting.substr(0, delimiterPos);
				std::string dst = objectSetting.substr(delimiterPos + 1);
				Node* pSrc = m_rGame.findNode(src);
				Node* pDst = m_rGame.findNode(dst);

				if (pSrc == NULL || pDst == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else
					std::cout << "Eine " << object << " wurde gebaut.\n";
			}
			else if (object == "Faehre") { // checks if "Faehre" object is available
				delimiterPos = objectSetting.find(" ");
				std::string src = objectSetting.substr(0, delimiterPos);
				std::string dst = objectSetting.substr(delimiterPos + 1);
				Node* pSrc = m_rGame.findNode(src);
				Node* pDst = m_rGame.findNode(dst);

				if (pSrc == NULL || pDst == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else
					std::cout << "Eine " << object << " wurde gesichtet.\n";
			}
			else if (object == "Lager") { // processes "Lager"
				delimiterPos = objectSetting.find(" ");
				std::string camp = objectSetting.substr(0, delimiterPos);
				int coins = std::stoi(objectSetting.substr(delimiterPos + 1));
				
				Node* pCamp = m_rGame.findNode(camp);
				if (pCamp == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else { // creates camps
					//std::cout << "Lager auf " << camp << " mit " << coins << ".\n"; // test point
					if (coins == 3) {
						setting.camp1 = pCamp;
						setting.camp1Coins = coins;
						setting.camp1Looted = false;
					}
					else {
						setting.camp2 = pCamp;
						setting.camp2Coins = coins;
						setting.camp2Looted = false;
					}
					std::cout << "Ein " << object << " wurde aufgestellt.\n";
				}
			}
			else if (object == "Schatz") { // processes "Schatz"
				Node* pTreasure = m_rGame.findNode(objectSetting);
				if (pTreasure == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else { // creates treasure
					setting.treasure = pTreasure;
					//std::cout << "Ein " << object << " wurde auf " << objectSetting << " versteckt.\n"; // test point
					std::cout << "Ein " << object << " wurde versteckt.\n";
				}
			}
			else if (object == "Mensch") { // processes player "Mensch"
				delimiterPos = objectSetting.find(" ");
				std::string startIsland = objectSetting.substr(0, delimiterPos);
				int coins = std::stoi(objectSetting.substr(delimiterPos + 1));

				Node* pCamp = m_rGame.findNode(startIsland);
				if (pCamp == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else { // creates human player
					//std::cout << "Eine Spielfigur fuer " << object << " wurde auf " << startIsland << " mit " << coins << " Taler abgesetzt.\n"; // test point
					human.type = true;
					human.startIsland = pCamp;
					human.currentIsland = pCamp;
					human.startCoins = coins;
					human.currentCoins = coins;
				}
				std::cout << "Ein Spielfigur fuer " << object << " wurde angelegt.\n";
			}
			else if (object == "Computer") {  // processes player "Computer"
				delimiterPos = objectSetting.find(" ");
				std::string startIsland = objectSetting.substr(0, delimiterPos);
				int coins = std::stoi(objectSetting.substr(delimiterPos + 1));

				Node* pCamp = m_rGame.findNode(startIsland);
				if (pCamp == NULL) {
					std::cout << "Ein Objekt fuer " << object << " konnte nicht zugeordnet werden.\n";
					failCounter++;
				}
				else { // creates computer player
					//std::cout << "Eine Spielfigur fuer " << object << " wurde auf " << startIsland << " mit " << coins << " Taler abgesetzt.\n"; // test point
					com.type = false;
					com.startIsland = pCamp;
					com.currentIsland = pCamp;
					com.startCoins = coins;
					com.currentCoins = coins;
				}
				std::cout << "Ein Spielfigur fuer " << object << " wurde angelegt.\n";
			} else 
				failCounter++;
		} 

		std::cout << failCounter << " Spielobjekt/e konnte nicht zugeordnet werden.\n";
		if (failCounter > 2) { // checks if there are to many errors in the file
			std::cout << "Ueberpruefen Sie die Spieldatei erneut, das Spiel wird aus sicherheitsgruenden nicht gestartet.\n";
			return 1;
		}
		else { // play game section
			std::cout << "Die Spieldatei wurde erfolgreich gelesen. Starte Spiel...\n";
			Node* IslandCoice;
			Node* IslandRandom;
			bool treasureFound = false;
			int cost;
			showGameMap();

			do { // play as long as treasure is not found
	
				// human player's turn
				std::cout << " -> Spielers Status ";
				std::cout << "\nSpielers Position: " << human.currentIsland->getID();
				std::cout << "\nSpielers Taler: " << human.currentCoins << " Taler";
				bool playersTurn = true;

				do {
					IslandCoice = getIslandChoice();
					cost = 0;

					std::deque<Edge*> path;
					m_rGame.findShortestPathDijkstra(path, human.currentIsland, IslandCoice);

					for (Edge* pEdge : path) {
						Connection* pRoute = dynamic_cast<Connection*>(pEdge);
						std::cout << "Die Reise '" << pEdge->toString() << "' kostet " << pEdge->getWeight() << " Taler." << std::endl;
						cost += pEdge->getWeight();
					}
					std::cout << "\nDie Gesamtreise kostet " << cost << " Taler.";
					if (cost <= human.currentCoins) {
						human.currentCoins -= cost;
						human.currentIsland = IslandCoice;
						std::cout << "\nDie Reise wurde unternommen und " << cost << " Taler wurden abgezogen." << std::endl;
						playersTurn = false;
						if (human.currentIsland == setting.treasure) {
							std::cout << "\nSie haben den Schatz gefunden!";
							std::cout << "\nHerzlichen Glueckwunsch Sie haben gewonnen!" << std::endl;
							std::cout << "------------------------------------------------------------" << std::endl;
							return 0;
						}
					}
					else {
						std::cout << "\nNicht genugend Taler dabei. Wählen Sie eine andere Insel." << std::endl;
					}
				} while (playersTurn); // player's turn end

				// computer's turn
				std::cout << "------------------------------------------------------------" << std::endl;
				std::cout << " -> Computers Status ";
				std::cout << "\nComputers Position: " << com.currentIsland->getID();
				std::cout << "\nComputers Taler: " << com.currentCoins << " Taler";
				bool compTurn = true;
				
				do {
					IslandRandom = getIslandRandom();
					cost = 0;

					std::deque<Edge*> path;
					m_rGame.findShortestPathDijkstra(path, com.currentIsland, IslandRandom);

					for (Edge* pEdge : path) {
						Connection* pRoute = dynamic_cast<Connection*>(pEdge);
						std::cout << "Die Reise '" << pEdge->toString() << "' kostet " << pEdge->getWeight() << " Taler." << std::endl;
						cost += pEdge->getWeight();
					}
					std::cout << "\nDie Gesamtreise kostet " << cost << " Taler.";

					if (cost <= com.currentCoins) {
						com.currentCoins -= cost;
						com.currentIsland = IslandRandom;
						std::cout << "\nDie Reise wurde unternommen und " << cost << " Taler wurden abgezogen." << std::endl;
						compTurn = false;
						if (com.currentIsland == setting.treasure) {
							std::cout << "\nDer Computer hat den Schatz gefunden!";
							std::cout << "\nSie haben das Spiel leider verloren." << std::endl;
							std::cout << "------------------------------------------------------------" << std::endl;
							return 0;
						}
						std::cout << "------------------------------------------------------------" << std::endl;
					}
					else
						std::cout << "\nNicht genugend Taler dabei. Computer waehlt eine andere Insel." << std::endl;
				} while (compTurn); // computer's turn end

			} while (!treasureFound);
		}
		return 0;
	}
	std::cerr << "Die Datei konnte nicht geoeffnet werden.\n";
	return 1;
}

void GUI::showGameMap() const {
	std::cout << "\n------------------------------------------------------------" << std::endl;
	std::cout << "Die Spielwelt von Kimoran: \n";

	// print all nodes 
	for (std::list<Node*>::const_iterator it = m_rGame.getNodes().begin(); it != m_rGame.getNodes().end(); it++) {
		Node* pCurrentNode = *it;
		std::cout << "\nInsel " << pCurrentNode->getID() << " hat die Verbindungen: \n" ;

		std::string currentNode = pCurrentNode->getID();
		Node* pCamp = m_rGame.findNode(currentNode);
		// print all connections
		std::list<Edge*> listEdges = pCamp->getOutEdges();

		for (std::list<Edge*>::iterator it = listEdges.begin(); it != listEdges.end(); it++) {
			Connection* pConn = dynamic_cast<Connection*> ((*it));
			std::cout << std::setw(14) << std::setfill(' ') << (*it)->getDstNode().getID() << " " << pConn->getName() << " fuer " << pConn->getWeight() << " Taler\n";
		}
	}
	std::cout << "\n------------------------------------------------------------" << std::endl;
}

Node* GUI::getIslandChoice() {
	std::string islandName;
	Node* pIsland = NULL;

	while (true) {
		std::cout << "\nGeben Sie an zu welcher Insel Sie gehen moechten: ";
		getline(std::cin, islandName);
		pIsland = m_rGame.findNode(islandName);
		if (pIsland == NULL) {
			std::cout << "Der Name der Insel '" << islandName << "' ist ungueltig.\n";
		}
		else break;
	}
	return pIsland;
}

Node* GUI::getIslandRandom() {
	Node* pIsland = NULL;
	int num = rand() % 5; // random number from node list size of 5

	// iterator pointing to first element
	std::list<Node*>::const_iterator it = m_rGame.getNodes().begin();
	// advance iterator by "num" positions
	std::advance(it, num);
	pIsland = *it;
	std::cout << "\nDer Computer hat Insel " << pIsland->getID() << " gewaehlt." << std::endl;

	return pIsland;
}

void GUI::print(std::string output) const {
	std::cout << output << std::endl;
}
