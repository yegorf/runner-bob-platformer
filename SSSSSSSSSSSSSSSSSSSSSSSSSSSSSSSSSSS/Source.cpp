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

int tBar = 100;
int barTime = tBar;
int tCloud = 150;
int cloudTime = tCloud;

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
	game->HeroJump(key);
	game->MoveAll();
	barTime++;
	game->ScoreIteration();

}

void CloudTick()
{
	
	if (cloudTime == tCloud)
	{
		game->AddBarrier(3);
		cloudTime = 0;
		game->Faster();
	}
	cloudTime++;
}


int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(screen.GetW(), screen.GetH()), "Runner");
	game = new Game();
	unsigned maxScore = 0;

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
	

	Texture t1;
	Texture sky;
	t1.loadFromFile("images/weed.bmp");
	sky.loadFromFile("images/sky.bmp");
	Sprite spriteWeed(t1);
	Sprite spriteSky(sky);

	Texture head;
	Texture legs;
	head.loadFromFile("images/head.bmp");
	legs.loadFromFile("images/legs.bmp");
	Sprite spriteHead(head);
	Sprite spriteLegs(legs);

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



		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Up)) key = 1;
		if (Keyboard::isKeyPressed(Keyboard::Down)) key = 2;


		if (timer > delay) { timer = 0; Tick(); }
		if (timerCloud > delayCloud) { timerCloud = 0; CloudTick(); }

		if (loose)
		{
			if (game->GetScore() > maxScore) { maxScore = game->GetScore(); }
			delete game;
			Sleep(1000);
			game = new Game;
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
