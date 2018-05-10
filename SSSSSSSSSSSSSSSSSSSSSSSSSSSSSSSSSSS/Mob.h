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
		x = 29 * Scale;
		y = 18 * Scale;
	}

	void Move(float temp)
	{
		x -= temp;
	}

	void Draw(Sprite spriteMob, RenderWindow &window)
	{
		spriteMob.setPosition(x, y);
		window.draw(spriteMob);
	}

	bool Loose(Hero h)
	{
		if (
			x <= h.GetX() + Scale
			&& x + Scale >= h.GetX()
			&& y - Scale <= h.GetLY())
			return true;
		else return false;
	}
};



