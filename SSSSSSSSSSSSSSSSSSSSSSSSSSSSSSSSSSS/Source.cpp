#include <SFML\Graphics.hpp>
#include <iostream>
#include "Screen.h"
#include "Cell.h"
#include "Hero.h"
#include "Bird.h"
#include "Mob.h"
#include "Queue.h"
#include "Cloud.h"
#include "Game.h"
#include <time.h>
using namespace sf;

#define scale 35
int key=0;

int tBar = 100;
int barTime = tBar;
int tCloud = 250;
int cloudTime = tCloud;

Game game;

void Tick()
{
	game.LooseCheck(hero, key);
	int var = rand()%2;
	int vartime = rand() % 4;

	if(barTime== tBar)
	{
		game.AddBarrier(var);
		barTime = 0;
		switch (vartime)
		{
		case 0:
			tBar = 125;
			break;
		case 1:
			tBar = 150;
			break;
		case 2:
			tBar = 175;
			break;
		case 3:
			tBar = 200;
			break;
		}
	}
	game.CheckEnd();
	game.HeroJump(key);
	game.MoveAll();
	barTime++;

}

void CloudTick()
{
	
	if (cloudTime == tCloud)
	{
		game.AddBarrier(2);
		cloudTime = 0;
	}
	cloudTime++;
}


int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(screen.GetW(), screen.GetH()), "Runner");

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

		hero.Draw(spriteHead, spriteLegs, window);
		game.DrawAll(spriteMob, spriteBird, spriteCloud, window);

		window.display();
	}

	return 0;
}
