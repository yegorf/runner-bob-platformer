#pragma once
#include "Barrier.h"

class Cloud: public Barrier
{
public:

	static bool height;

	Cloud()
	{
		h = 140;
		w = 175;
	}

	void Null()
	{
		x = screen.GetW();
		if (!height)
		{
			y = 175;
			height = true;
		}
		else
		{
			y = 70;
			height = false;
		}
	}

	void Move(float temp)
	{
		x -= temp;
	}

	void Draw(RenderWindow &window)
	{
		sprite.setPosition(x, y);
		window.draw(sprite);
	}

};
bool Cloud::height = false;
