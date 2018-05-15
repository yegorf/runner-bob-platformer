#pragma once

class Mob: public Barrier
{

public:

	Mob() 
	{
		Null();
		h = 35;
		w = 35;
	}

	void Null()
	{
		x = 29 * w;
		y = 18 * w;
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

	bool Loose(Hero h)
	{
		if (
			x <= h.GetX() + w
			&& x + w >= h.GetX()
			&& y - w <= h.GetLY())
			return true;
		else return false;
	}
};



