#pragma once

class Entry
{
private:

	unsigned score;
	string name;
public:

	void SetScore(unsigned dop) { score = dop; }
	void SetName(string dop) { name = dop; }
	unsigned GetScore() { return score; }
	string GetName() { return name; }
};

