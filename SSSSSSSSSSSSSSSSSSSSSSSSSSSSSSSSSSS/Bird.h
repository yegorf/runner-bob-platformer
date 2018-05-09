#pragma once
#include "Barrier.h"

class Bird: public Barrier
{
public:

	Bird()
	{		
		h = 35;
		w = 35;
		Null();
	}

	void Null()
	{
		x = 29 * Scale;
		y = 17 * Scale;
	}

	void Draw(Sprite spriteBird, RenderWindow &window)
	{
		spriteBird.setPosition(x, y);
		window.draw(spriteBird);
	}

	void Move(float temp)
	{
		x -= temp;
	}

	bool Loose(Hero h, int key)
	{
		if (
			x <= h.GetX() + Scale
			&& x + Scale >= h.GetX()
			&& y - Scale <= h.GetLY()
			&& key!=2)
			return true;
		else return false;
	}

};

