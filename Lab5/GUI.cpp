#include "GUI.h"
//#include "Chessboard.h"
#include <ctype.h>

//GUI::GUI(Chessboard& rGame) : m_rGame(rGame) {}
GUI::GUI() {}

/*char GUI::getSelection() const { // version 1
	char selection;
	cout << "\nBitte geben Sie an was Sie tun moechten: "
		<< "\n (a) Ein Schachbrett laden"
		<< "\n (b) Den kuerzesten Weg zeigen"
		<< "\n (c) Das geladene Schachbrett anzeigen"
		<< "\n (q) Das Programm beenden"
		<< "\n Ihre Eingabe: ";
	cin >> selection;
	cin.clear();
	return selection;
}*/

void GUI::showMenu() const {
	cout << "\nBitte geben Sie an was Sie tun moechten: "
		<< "\n (a) Ein Schachbrett laden"
		<< "\n (b) Den kuerzesten Weg zeigen"
		<< "\n (c) Das geladene Schachbrett anzeigen"
		<< "\n (q) Das Programm beenden";
}

char GUI::getSelection() { // version 2
	string input = "";
	char mySelection = { 0 }; // get a single char

	cout << "\nBitte machen Sie eine Auswahl: ";
	while (true) {
		getline(cin, input);
		if (input.length() == 1) { // checks if input is a single character
			mySelection = input[0];
			if (isdigit(input[0]) == 0) { // checks if char is not an integer
				break;
			}
		}
		cout << "Die Auswahl ist nicht zulaessig, bitte waehlen Sie es erneut: ";
	}
	return mySelection;
}

void GUI::showBoards() const {
	cout << "\nWelches Schachbrett moechten Sie laden? "
		<< "\n (a) Schachbrett I: 3 Bauern"
		<< "\n (b) Schachbrett II: 2 Bauern"
		<< "\n (c) Schachbrett III: 3 Bauern"
		<< "\n (d) Schachbrett IV: 0 Bauern"
		<< "\n (q) Auswahl beenden"; // nice to have
}

/* redundant? use getSelection() instead
char GUI::getBoard() {
	string input = "";
	char mySelection = { 0 }; // get a single char

	cout << "\n Bitte machen Sie eine Auswahl: ";
	while (true) {
		getline(cin, input);
		if (input.length() == 1) { // checks if input is a single character
			mySelection = input[0];
			break;
		}
		cout << "\n Die Auswahl ist nicht zulaessig, bitte versuchen Sie es erneut." << endl;
	}
	cout << "\n Ihre Eingabe: " << mySelection << endl;
	return mySelection;
} */

char GUI::setBoard(char mySelection) {
	ifstream boardfile;
	std::string output;
	char boardSelection = mySelection;

	while (true) {
		switch (boardSelection) {
		case 'a':
		case 'A':
			boardfile.open("board1.txt");
			if (boardfile.good()) {
				boardfile >> output;
				std::cout << "\nDas Schachbrett mit den Figuren " << output << " wurde geladen.";
				m_rGame.initialize(output);
			}
			else cerr << "\nFehler: Dieses Schachbrett konnte nicht geladen werden." << endl;
			boardfile.close();
			return boardSelection;
		case 'b':
		case 'B':
			boardfile.open("board2.txt");
			if (boardfile.is_open()) {
				boardfile >> output;
				std::cout << "\nDas Schachbrett mit den Figuren " << output << " wurde geladen.";
				m_rGame.initialize(boardfile);
			}
			else cout << "\nFehler: Dieses Schachbrett konnte nicht geladen werden." << endl;
			boardfile.close();
			return boardSelection;
		case 'c':
		case 'C':
			boardfile.open("board3.txt");
			if (boardfile.is_open()) {
				boardfile >> output;
				std::cout << "\nDas Schachbrett mit den Figuren " << output << " wurde geladen.";
				m_rGame.initialize(boardfile);
			}
			else cout << "\nFehler: Dieses Schachrett konnte nicht geladen werden." << endl;
			boardfile.close();
			return boardSelection;
		case 'd':
		case 'D':
			boardfile.open("board4.txt");
			if (boardfile.is_open()) {
				boardfile >> output;
				std::cout << "\nDas Schachbrett mit den Figuren " << output << " wurde geladen.";
				m_rGame.initialize(boardfile);
			}
			else cout << "\nFehler: Dieses Schachbrett konnte nicht geladen werden." << endl;
			boardfile.close();
			return boardSelection;
		case 'q':
		case 'Q':
			cout << "\nVerlasse Schachbrettauswahl.." << endl;
			return 'x';
		default:
			cout << "\nFehler: Dieses Schachbrett existiert nicht." << endl;
			boardSelection = getSelection();
		}
	}
}

void GUI::print(string output) const {
	std::cout << output << endl;
}

void GUI::calculateShortestPath() {
	cout << "\nKuerzester Pfad zum Koenig wird berechnet.." << endl;
	//m_rGame.findKing(kingID);
	//m_rGame.findKnight(knightID);
}

void GUI::showChessboard() const {

}