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
		x = 29 * w;
		y = 17 * w;
	}

	void Draw(RenderWindow &window)
	{
		sprite.setPosition(x, y);
		window.draw(sprite);
	}

	void Move(float temp)
	{
		x -= temp;
	}

	bool Loose(Hero h, int key)
	{
		if (
			x <= h.GetX() + w
			&& x + w >= h.GetX()
			&& y - w <= h.GetLY()
			&& key!=2)
			return true;
		else return false;
	}

	//void SetTexture()
	//{
	//	texture.loadFromFile("images/bird.bmp");
	//	sprite.setTexture(texture);
	//}

};

