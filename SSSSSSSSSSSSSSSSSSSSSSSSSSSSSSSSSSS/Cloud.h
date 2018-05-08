#pragma once
#include "Barrier.h"

bool h = false;
class Cloud: public Barrier
{
public:

	Cloud()
	{
	}

	void Null()
	{
		x = screen.GetW();
		if (!h)
		{
			y = 5 * Scale;
			h = true;
		}
		else
		{
			y = 2 * Scale;
			h = false;
		}
	}

	void Move(float temp)
	{
		x -= temp;
	}

	void Draw(Sprite spriteCloud, RenderWindow &window)
	{
		spriteCloud.setPosition(x, y);
		window.draw(spriteCloud);
	}

};