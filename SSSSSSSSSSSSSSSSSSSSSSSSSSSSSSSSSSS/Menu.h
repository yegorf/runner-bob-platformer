#pragma once


class Menu
{
private:
	Texture t;
	Texture *tbutton;
	Sprite *sbutton;
	int col = 4;

	int h = 100;
	int w = 300;

	bool use;
	int num;

public:

	Menu()
	{
		tbutton = new Texture[col];
		sbutton = new Sprite[col];
		SetTexturesImage();
		SetButtonsSprite();
		SetButtonsPosition();
	}

	void SetTexturesImage()
	{
		for (int i = 0; i < col; i++)
		{
			tbutton[i].loadFromFile("images/button.bmp");
		}
	}

	void SetButtonsSprite()
	{
		for (int i = 0; i < col; i++)
		{
			sbutton[i].setTexture(tbutton[i]);
			sbutton[i].setTextureRect(IntRect(0, h*i, w, h));
		}
	}

	void SetButtonsPosition()
	{
		for (int i = 0; i < col; i++)
		{
			sbutton[i].setPosition(50, 50 + i*h);
		}
	}

	void ButtonClick(RenderWindow &window)
	{
		for (int i = 0; i < col; i++)
		{
			if (IntRect(50, 50 + h * i, w, h).contains(Mouse::getPosition(window))) { sbutton[i].setTextureRect(IntRect(300, i*h, 300, 100)); num = i + 1; }
			else { sbutton[i].setTextureRect(IntRect(0, i*h, 300, 100)); }
		}
	}

	void Result()
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (num == 1) { use = false; }
			if (num == 2) { Sleep(1000); }
			if (num == 3) { Sleep(1000); }
			if (num == 4) { exit(0); }
		}
	}

	void DrawButtons(RenderWindow &window)
	{
		for (int i = 0; i < col; i++)
		{
			window.draw(sbutton[i]);
		}
	}

	void menu(RenderWindow &window)
	{
		t.loadFromFile("images/open.bmp");
		Sprite st(t);
		st.setPosition(400, 50);
		use = true;
		num = 0;

		while (use)
		{
			num = 0;
			window.clear(Color(10, 250, 100));

			ButtonClick(window);
			Result();
			DrawButtons(window);

			window.draw(st);
			window.display();
		}
	}
};