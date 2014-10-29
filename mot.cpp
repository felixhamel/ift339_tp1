#include "mot.h"

word::~word()
{
}

/*
	Will check if both words are not equals but compatibles.
*/
const bool word::compatibleWith(const word& otherWord)
{
	// Compare size
	if (this->size() != otherWord.size()) {
		return false;
	}

	// Compare content
	for (unsigned int i = 0; i < this->size(); ++i) {
		if (this->at(i) != '-' && otherWord[i] != '-') {
			if (this->at(i) != otherWord[i]) {
				return false;
			}
		}
	}
	return true;
}

/*
	Will update pattern with a word and a letter.
	For each occurrence of the letter in the word, we insert it in the current pattern.

	If both words are not compatibles, return false.
	If the letter is not in the given word, return false.
	Otherwise, it should return true.
*/
const bool word::update(const word& word, const char letter)
{
	// Is other word compatible with current pattern ?
	if (!this->compatibleWith(word)) {
		return false;
	}

	// Update pattern
	bool foundLetterInWord = false;
	for (unsigned int i = 0; i < this->size(); ++i) {
		if (word[i] == letter) {
			this->at(i) = letter;
			foundLetterInWord = true;
		}
	}
	return foundLetterInWord;
}