#pragma once

class Tree : public Barrier
{

public:

	Tree()
	{
		Null();
		h = 70;
		w = 35;
	}

	void Null()
	{
		x = 29 * Scale;
		y = 17 * Scale;
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

	bool Loose(Hero hero)
	{
		if (
			x <= hero.GetX() + w
			&& x + w >= hero.GetX()
			&& y - h/2 <= hero.GetLY())
			return true;
		else return false;
	}
};
