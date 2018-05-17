#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Hero.h"
#include "Bird.h"
#include "Mob.h"
#include "Cloud.h"
#include "Tree.h"
#include "Round.h"
#include <time.h>
#include <string>
#include <sstream>
#include "Menu.h"
#include "ScoreTable.h"
#include "Screen.h"
#include "Game.h"
using namespace sf;
using namespace std;


int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(screen.GetW(), screen.GetH()), "Runner Bob");
	Round *roun;
	Game game;
	ScoreTable *table;
	Menu menu;

	A:
	menu.menu(window);
	roun = new Round();
	unsigned maxScore = 0;

	Font font;
	font.loadFromFile("a_Alterna.ttf");
	Text textScore("", font, 20);
	game.SetText(textScore, 100, 20);
	Text textMaxScore("", font, 20);
	game.SetText(textMaxScore, 400, 20);

	Text escape("", font, 20);
	game.SetText(escape, 800, 20);
	escape.setString("Press esc for exit");

	Clock clockMove;
	float timer = 0;
	float delay = 0.01;

	Clock clockCloud;
	float timerCloud = 0;
	float delayCloud = 0.02;

	Clock clockStep;
	float timerStep = 0;
	float delayStep = 0.1;
	
	Texture head;	
	head.loadFromFile("images/head.bmp");
	Sprite spriteHead(head);
	spriteHead.setTextureRect(IntRect(0, 0, 35, 35));

	Texture legs;
	legs.loadFromFile("images/legs.bmp");
	Sprite spriteLegs(legs);
	spriteLegs.setTextureRect(IntRect(0, 0, 35, 35));

	while (window.isOpen())
	{
		float time = clockMove.getElapsedTime().asSeconds();
		clockMove.restart();
		timer += time;

		float cloudTime = clockCloud.getElapsedTime().asSeconds();
		clockCloud.restart();
		timerCloud += cloudTime;

		float stepTime = clockStep.getElapsedTime().asSeconds();
		clockStep.restart();
		timerStep += stepTime;

		string str;
		Event event;

		Text ttext("", font, 20);
		game.SetText(ttext, 300, 300);

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) game.key = 1;
		if (Keyboard::isKeyPressed(Keyboard::Escape)) 
		{ 
			table = new ScoreTable;
			table->AddEntry(maxScore, "Sashka");
			delete table;
			delete roun;
			goto A; 
		};

		if (event.key.code == sf::Keyboard::Down)
		{
			if (event.type == sf::Event::KeyPressed) 
			{ 
				game.key = 2;
				spriteHead.setTextureRect(IntRect(35, 0, 35, 35));
			}

			else if (event.type == sf::Event::KeyReleased) 
			{ 
				game.key = 3;
				spriteHead.setTextureRect(IntRect(0, 0, 35, 35));
			}
		}

		if (timer > delay) { timer = 0; game.Tick(roun); }
		if (timerCloud > delayCloud) { timerCloud = 0; game.CloudTick(roun,spriteLegs); }
		if (timerStep > delayStep) { timerStep = 0; game.StepTick(spriteLegs, game.key); }

		if (roun->GetLoose())
		{
			if (roun->GetScore() > maxScore) { maxScore = roun->GetScore(); }
			delete roun;
			Sleep(1000);
			roun = new Round;
		}

		window.clear();
		screen.DrawField(window);
		roun->DrawAll(spriteHead, spriteLegs, window);
		game.PrintScore(textScore, "Current score: ", window, roun->GetScore());
		game.PrintScore(textMaxScore, "Max score: ", window, maxScore);
		window.draw(escape);
		window.display();
	}
}
