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
		x = 29 * w;
		y = 17 * w;
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
