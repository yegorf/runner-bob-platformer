#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "Screen.h"
#include "Cell.h"
#include "Hero.h"
#include "Bird.h"
#include "Mob.h"
#include "Queue.h"
#include "Cloud.h"
#include "Tree.h"
#include "Game.h"
#include <time.h>
#include <string>
#include <sstream>
using namespace sf;
using namespace std;

#define scale 35
int key=0;
bool loose = false;

int speed = 0;
int tBar = 100;
int barTime = tBar;
int tCloud = 150;
int cloudTimee = tCloud;

Game *game;

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


int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(screen.GetW(), screen.GetH()), "Runner Bob");
	game = new Game();
	unsigned maxScore = 0;
	bool step = false;;

	Font font;
	font.loadFromFile("a_Alterna.ttf");
	Text textScore("", font, 20);
	textScore.setColor(Color::Black);
	textScore.setPosition(100, 20);

	Text textMaxScore("", font, 20);
	textMaxScore.setColor(Color::Black);
	textMaxScore.setPosition(400, 20);


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

		if (Keyboard::isKeyPressed(Keyboard::Up)) key = 1;



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
		
		ostringstream score;
		score << game->GetScore();
		textScore.setString("Current score: " + score.str());
		window.draw(textScore);

		ostringstream max_score;
		max_score << maxScore;
		textMaxScore.setString("Max score: " + max_score.str());
		window.draw(textMaxScore);

		window.display();
	}

	return 0;
}
