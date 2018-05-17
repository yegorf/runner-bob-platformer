#pragma once
#include <fstream>
#include "Entry.h"

class ScoreTable
{
private:
	string file = "ScoreTable.txt";
	unsigned col;
	Entry *mas;

public:
	ScoreTable()
	{
		col = FileCol();
		mas = new Entry[col];
	}

	void AddEntry(unsigned _score, string _name)
	{
		ofstream f;
		f.open(file, ios::app);
		f << _score << " " << _name << endl;
		f.close();
	}


	void DrawTable(RenderWindow &window)
	{
		int x = 50;
		int y = 50;

		Font font;
		font.loadFromFile("a_Alterna.ttf");
		Text text("", font, 20);
		text.setColor(Color::Black);

		for (int i = 0; i < col; i++)
		{
			string s = to_string(mas[i].GetScore());
			string str = s + " " + mas[i].GetName();
			text.setString(str);
			text.setPosition(x, y);
			window.draw(text);
			y += 50;
		}

	}

	void ShowTable(RenderWindow &window)
	{
		Texture t;
		t.loadFromFile("images/score.bmp");
		Sprite st(t);
		st.setPosition(0, 0);
		bool use = true;

		while (use)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { use = false; }
			window.draw(st);
			DrawTable(window);
			window.display();
		}
	}

	void About(RenderWindow &window)
	{
		Texture t;
		t.loadFromFile("images/about.bmp");
		Sprite st(t);
		st.setPosition(0, 0);
		bool use = true;

		while (use)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { use = false; }
			window.draw(st);
			window.display();
		}
	}

	void GetFile()
	{
		string st;
		unsigned sc;
		fstream fn(file);

		for (int i = 0; i < col; i++)
		{
			fn >> sc;
			fn >> st;
			mas[i].SetScore(sc);
			mas[i].SetName(st);
		}
		fn.close();
	}

	int FileCol()
	{
		ifstream f(file);
		char *str = new char[1024];
		int j = 0;
		while (!f.eof())
		{
			f.getline(str, 1024, '\n');
			j++;
		}
		f.close();
		delete str;
		return j-1;
	}
};