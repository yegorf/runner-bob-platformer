#pragma once


class Menu
{
public:
	void menu(RenderWindow &window)
	{
		Texture tButton1;
		Texture tButton2;
		Texture tButton3;
		Texture tButton4;

		Texture t;
		t.loadFromFile("images/open.bmp");
		Sprite st(t);
		st.setPosition(400, 50);

		tButton1.loadFromFile("images/button.bmp");
		tButton2.loadFromFile("images/button.bmp");
		tButton3.loadFromFile("images/button.bmp");
		tButton4.loadFromFile("images/button.bmp");

		Sprite sButton1(tButton1);
		Sprite sButton2(tButton2);
		Sprite sButton3(tButton3);
		Sprite sButton4(tButton4);

		sButton1.setTextureRect(IntRect(0, 0, 300, 100));
		sButton2.setTextureRect(IntRect(0, 100, 300, 100));
		sButton3.setTextureRect(IntRect(0, 200, 300, 100));
		sButton4.setTextureRect(IntRect(0, 300, 300, 100));

		sButton1.setPosition(50, 50);
		sButton2.setPosition(50, 150);
		sButton3.setPosition(50, 250);
		sButton4.setPosition(50, 350);

		bool use = true;
		int num = 0;

		while (use)
		{
			num = 0;
			window.clear(Color(10, 250, 100));

			if (IntRect(50, 50, 300, 100).contains(Mouse::getPosition(window))) { sButton1.setTextureRect(IntRect(300, 0, 300, 100)); num = 1; }
			else { sButton1.setTextureRect(IntRect(0, 0, 300, 100)); }
			if (IntRect(50, 150, 300, 100).contains(Mouse::getPosition(window))) { sButton2.setTextureRect(IntRect(300, 100, 300, 100)); num = 2; }
			else sButton2.setTextureRect(IntRect(0, 100, 300, 100));
			if (IntRect(50, 250, 300, 100).contains(Mouse::getPosition(window))) { sButton3.setTextureRect(IntRect(300, 200, 300, 100)); num = 3; }
			else sButton3.setTextureRect(IntRect(0, 200, 300, 100));
			if (IntRect(50, 350, 300, 100).contains(Mouse::getPosition(window))) { sButton4.setTextureRect(IntRect(300, 300, 300, 100)); num = 4; }
			else { sButton4.setTextureRect(IntRect(0, 300, 300, 100)); }

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (num == 1) { use = false; }
				if (num == 2) { Sleep(1000); }
				if (num == 3) { Sleep(1000); }
				if (num == 4) { exit(0); }
			}

			window.draw(sButton1);
			window.draw(sButton2);
			window.draw(sButton3);
			window.draw(sButton4);

			window.draw(st);

			window.display();
		}

	}
};