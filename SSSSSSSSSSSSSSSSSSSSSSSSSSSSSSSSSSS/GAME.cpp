#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Hero.h"
#include "Bird.h"
#include "Mob.h"
#include "Cloud.h"
#include "Tree.h"
#include "Game.h"
#include <time.h>
#include <string>
#include <sstream>
#include "Menu.h"
#include "ScoreTable.h"
#include "Screen.h"
#include "GAME.h"
using namespace sf;
using namespace std;


class GAME
{
public:
	Game *game;
	ScoreTable *table;
	int key = 0;

	int tBar = 100;
	int barTime = tBar;
	int tCloud = 150;
	int cloudTimee = tCloud;

	void Tick()
	{
		game->LooseCheck(key);

		int var = rand() % 3;
		int vartime = rand() % 4;

		if (barTime == tBar)
		{
			game->AddBarrier(var);
			barTime = 0;
			switch (vartime)
			{
			case 0:
				tBar = 50;
				break;
			case 1:
				tBar = 75;
				break;
			case 2:
				tBar = 100;
				break;
			case 3:
				tBar = 125;
				break;
			}
		}
		game->CheckEnd();
		game->HeroDown(key);
		game->HeroJump(key);
		game->MoveAll();
		barTime++;
		game->ScoreIteration();
	}

	bool step = false;
	void StepTick(Sprite &spriteLegs, int key)
	{
		if (key != 2)
		{
			if (!step)
			{
				spriteLegs.setTextureRect(IntRect(0, 35, 35, 35));
				step = true;
			}
			else
			{
				spriteLegs.setTextureRect(IntRect(0, 70, 35, 35));
				step = false;
			}
		}
		else
		{
			if (!step)
			{
				spriteLegs.setTextureRect(IntRect(35, 35, 35, 35));
				step = true;
			}
			else
			{
				spriteLegs.setTextureRect(IntRect(35, 70, 35, 35));
				step = false;
			}
		}
	}

	void CloudTick(Sprite &spriteLegs)
	{
		if (cloudTimee == tCloud)
		{
			game->AddBarrier(3);
			cloudTimee = 0;
			game->Faster();
		}
		cloudTimee++;
	}

	void SetText(Text &text, int x, int y)
	{
		text.setColor(Color::Black);
		text.setPosition(x, y);
	}

	void PrintScore(Text &text, string word, RenderWindow &window, int Score)
	{
		ostringstream score;
		score << Score;
		text.setString(word + score.str());
		window.draw(text);
	}

};