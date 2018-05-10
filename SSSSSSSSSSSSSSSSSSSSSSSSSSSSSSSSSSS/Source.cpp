#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Screen.h"
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
using namespace sf;
using namespace std;

Game *game;
int key=0;
bool loose = false;

int speed = 0;
int tBar = 100;
int barTime = tBar;
int tCloud = 150;
int cloudTimee = tCloud;

void Tick()
{
	loose = game->LooseCheck(key);
	int var = rand()%3;
	int vartime = rand() % 4;

	if(barTime== tBar)
	{
		game->AddBarrier(var);
		barTime = 0;
		switch (vartime)
		{
		case 0:
			tBar = 50-speed;
			break;
		case 1:
			tBar = 75 - speed;
			break;
		case 2:
			tBar = 100 - speed;
			break;
		case 3:
			tBar = 125 - speed;
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
		if(speed<10)
		speed += 1;
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

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(screen.GetW(), screen.GetH()), "Runner Bob");
	Menu menu;

	A:
	menu.menu(window);
	game = new Game();
	unsigned maxScore = 0;

	Font font;
	font.loadFromFile("a_Alterna.ttf");
	Text textScore("", font, 20);
	SetText(textScore, 100, 20);
	Text textMaxScore("", font, 20);
	SetText(textMaxScore, 400, 20);

	Text escape("", font, 20);
	SetText(escape, 800, 20);
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
	
	Texture t1;
	Texture sky;
	t1.loadFromFile("images/weed.bmp");
	sky.loadFromFile("images/sky.bmp");
	Sprite spriteWeed(t1);
	Sprite spriteSky(sky);

	Texture head;	
	head.loadFromFile("images/head.bmp");
	Sprite spriteHead(head);
	spriteHead.setTextureRect(IntRect(0, 0, 35, 35));

	Texture legs;
	legs.loadFromFile("images/legs.bmp");
	Sprite spriteLegs(legs);
	spriteLegs.setTextureRect(IntRect(0, 0, 35, 35));

	Texture tbird;
	tbird.loadFromFile("images/bird.bmp");
	Sprite spriteBird(tbird);

	Texture tmob;
	tmob.loadFromFile("images/mob.bmp");
	Sprite spriteMob(tmob);

	Texture ttree;
	ttree.loadFromFile("images/tree.bmp");
	Sprite spriteTree(ttree);

	Texture tcloud;
	tcloud.loadFromFile("images/cloud.bmp");
	Sprite spriteCloud(tcloud);

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

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Up)) key = 1;

		if (Keyboard::isKeyPressed(Keyboard::Escape)) { delete game; goto A; };

		if (event.key.code == sf::Keyboard::Down)
		{
			if (event.type == sf::Event::KeyPressed) 
			{ 
				key = 2; 	
				spriteHead.setTextureRect(IntRect(35, 0, 35, 35));
			}

			else if (event.type == sf::Event::KeyReleased) 
			{ 
				key = 3;
				spriteHead.setTextureRect(IntRect(0, 0, 35, 35));
			}
		}

		if (timer > delay) { timer = 0; Tick(); }
		if (timerCloud > delayCloud) { timerCloud = 0; CloudTick(spriteLegs); }
		if (timerStep > delayStep) { timerStep = 0; StepTick(spriteLegs, key); }

		if (loose)
		{
			if (game->GetScore() > maxScore) { maxScore = game->GetScore(); }
			delete game;
			Sleep(1000);
			game = new Game;
			speed = 0;
		}

		//DRAW
		window.clear();

		for (int i = 0; i < screen.GetN(); i++)
		{
			spriteWeed.setPosition(i*screen.GetScale(), (screen.GetM()-1)*screen.GetScale());
			window.draw(spriteWeed);
			for (int j = 0; j < screen.GetM()-1; j++)
			{
				spriteSky.setPosition(i*screen.GetScale(), j*screen.GetScale());
				window.draw(spriteSky);
			}
		}

		game->DrawAll(spriteHead, spriteLegs, spriteMob, spriteTree, spriteBird, spriteCloud, window);
		PrintScore(textScore, "Current score: ", window, game->GetScore());
		PrintScore(textMaxScore, "Max score: ", window, maxScore);
		window.draw(escape);

		window.display();
	}
}
