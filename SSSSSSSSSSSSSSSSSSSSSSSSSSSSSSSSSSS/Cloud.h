#pragma once
#include "Barrier.h"

class Cloud: public Barrier
{
public:

	static bool H;

	Cloud()
	{
		h = 140;
		w = 175;
	}

	void Null()
	{
		x = screen.GetW();
		if (!H)
		{
			y = 175;
			H = true;
		}
		else
		{
			y = 70;
			H = false;
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
bool Cloud::H = false;
