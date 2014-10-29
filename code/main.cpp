
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>

#include "mot.h"

using namespace std;

map<size_t, set<word>> words; // Put all the words in here

word currentPattern; // Pattern we play with
set<word> wordsToPlayWith; // Words to play with
set<char> availableLetters;
set<char> usedLetters;

void loadWordsFromFile()
{
	ifstream readFileStream("ODS6.txt"); // Open stream
	if (readFileStream.is_open()) {
		while (!readFileStream.eof()) {
			word word;
			getline(readFileStream, word);
			words[word.length()].insert(word);
		}
	}
	readFileStream.close(); // Close stream
}

void displayGameStatus()
{
	// Display useful informations
	cout << "Lettres disponible : ";
	for_each(availableLetters.begin(), availableLetters.end(), [](char letter){ cout << letter; });
	cout << endl << "Lettres utilitées : ";
	for_each(usedLetters.begin(), usedLetters.end(), [](char letter){cout << letter; });
	cout << endl << "Mot caché : " << currentPattern << endl;
}

void keepPatternThatHaveTheBiggestNumberOfPossibilitiesWithLetter( char& letter)
{
	map< word, set< word>> possibilities;
	for (set< word>::iterator it = wordsToPlayWith.begin(); it != wordsToPlayWith.end(); ++it) {
		word newPattern = currentPattern;
		if (newPattern.update(*it, letter)) {
			possibilities[newPattern].insert(*it);
		}
	}

	// Keep the set of words that have the biggest number of possibilities
	if (possibilities.size() > 0) {
		unsigned int numberOfPossibilities = 0;
		for (map< word, set< word>>::iterator it = possibilities.begin(); it != possibilities.end(); ++it) {
			if (it->second.size() > numberOfPossibilities) {
				numberOfPossibilities = it->second.size();
				currentPattern = it->first;
			}
		}
		wordsToPlayWith = possibilities[currentPattern];
	}
}

void initGame()
{
	availableLetters.clear();
	usedLetters.clear();
	wordsToPlayWith.clear();
	currentPattern.erase();

	// Put available letters into set
	for (unsigned char letter = 65; letter <= 90; ++letter) {
		availableLetters.insert(letter);
	}
}

void play()
{
	initGame();		

	// Ask lenght of the word to play with
	int lenghtOfWord = 0;
	cout << "Veuillez entrer le nombre de lettre du mot à trouver : ";
	cin >> lenghtOfWord;
	if (words.find(lenghtOfWord) == words.end()) {
		cout << endl << "Aucun mot n'existe dans le dictionnaire avec cette longueur. Appuyer sur une touche pour recommencer." << endl;
		system("pause");
		return;
	} else {
		wordsToPlayWith = words[lenghtOfWord];
		currentPattern = word(lenghtOfWord);
	}

	// Start game
	while (cin) {
		system("clear");
		displayGameStatus();
		cout << "Veuillez entrer la lettre à jouer : ";
		char letter;
		cin >> letter;
		if (letter == '#') {
			break;
		} else if (availableLetters.find(letter) != availableLetters.end()) {
			keepPatternThatHaveTheBiggestNumberOfPossibilitiesWithLetter(letter);
			availableLetters.erase(letter);
			usedLetters.insert(letter);
		}
	}
}

int main()
{
	// Load words
	cout << "Chargement des mots..." << endl;
	loadWordsFromFile();

	while (cin) {
		system("clear");
		play();
	}
}