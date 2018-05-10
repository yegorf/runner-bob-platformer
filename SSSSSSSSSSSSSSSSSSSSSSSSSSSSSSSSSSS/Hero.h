#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.h"
using namespace sf;
int scale = 35;

class Hero
{
private:
	float hx;
	float hy;
	float lx;
	float ly;
	float h = 35;
	float w = 35;

public:

	Hero()
	{
		Null();
	}

	void Null()
	{
		hx = scale;
		hy = (screen.GetM() - 3)*screen.GetScale();
		lx = screen.GetScale();
		ly = (screen.GetM() - 2)*screen.GetScale();
	}

	void MoveHero(float temp)
	{
		hy -= temp;
		ly -= temp;
	}

	void Draw(Sprite spriteHead, Sprite spriteLegs, RenderWindow &window)
	{
		spriteHead.setPosition(hx, hy);
		window.draw(spriteHead);
		spriteLegs.setPosition(lx, ly);
		window.draw(spriteLegs);
	}

	void Down(int key)
	{ 
		if (key == 2)
		{
			hx = lx - w;
			hy = ly;
		}
		else if(key==3) { Null(); }
	}

	float GetX() { return hx; }
	float GetHY() { return hy; }
	float GetLY() { return ly; }

};