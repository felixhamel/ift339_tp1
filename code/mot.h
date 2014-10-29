#pragma once

#include <string>

using namespace std;

class word : public string
{
public:
	word(string content) :string(content){};
	word(int i = 0) :string(i, '-'){};
	~word();

	const bool compatibleWith(const word& otherWord);
	const bool update(const word& word, const char letter);
};