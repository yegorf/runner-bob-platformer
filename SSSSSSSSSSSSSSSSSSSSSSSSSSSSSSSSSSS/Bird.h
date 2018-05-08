#pragma once
#include "Barrier.h"

class Bird: public Barrier
{
public:

	Bird()
	{
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
};

