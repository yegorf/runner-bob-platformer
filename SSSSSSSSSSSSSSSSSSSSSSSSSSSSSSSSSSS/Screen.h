#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Screen
{
private:
	int scale = 35;
	int n;
	int m;
	int w;
	int h;

	Texture weed;
	Texture sky;

	Sprite spriteWeed;
	Sprite spriteSky;


public:

	Screen()
	{
		n = 30;
		m = 20;
		w = scale * n;
		h = scale * m;
		SetTextures();
	}

	void SetTextures()
	{
		weed.loadFromFile("images/weed.bmp");
		sky.loadFromFile("images/sky.bmp");
		spriteWeed.setTexture(weed);
		spriteSky.setTexture(sky);
	}

	int GetW() { return w; }
	int GetH() { return h; }
	int GetScale() { return scale; }

	void DrawField(RenderWindow &window)
	{
		for (int i = 0; i < n; i++)
		{
			spriteWeed.setPosition(i*GetScale(), (m - 1)*GetScale());
			window.draw(spriteWeed);
			for (int j = 0; j < m - 1; j++)
			{
				spriteSky.setPosition(i*GetScale(), j*GetScale());
				window.draw(spriteSky);
			}
		}
	}

}screen;