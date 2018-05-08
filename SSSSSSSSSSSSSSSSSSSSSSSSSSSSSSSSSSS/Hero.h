#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.h"
#include "Cell.h"
using namespace sf;
int scale = 35;

class Hero
{
private:
	int x;
	int y;
	Cell head;
	Cell legs;


public:

	Hero()
	{
		Null();
	}

	void Null()
	{
		head.SetX(screen.GetScale());
		head.SetY((screen.GetM() - 3)*screen.GetScale());
		legs.SetX(screen.GetScale());
		legs.SetY((screen.GetM() - 2)*screen.GetScale());
	}

	void MoveHero(float temp)
	{
		head.SetY(head.GetY() - temp);
		legs.SetY(legs.GetY() - temp);
	}

	void Draw(Sprite spriteHead, Sprite spriteLegs, RenderWindow &window)
	{
		spriteHead.setPosition(head.GetX(), head.GetY());
		window.draw(spriteHead);
		spriteLegs.setPosition(legs.GetX(), legs.GetY());
		window.draw(spriteLegs);
	}

	float GetX() { return head.GetX(); }
	float GetHeadY() { return head.GetY(); }
	float GetLegsY() { return legs.GetY(); }

}hero;