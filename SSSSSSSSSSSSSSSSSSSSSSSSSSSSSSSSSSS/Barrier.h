#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.h"
#include <string>
using namespace sf;
using namespace std;

class Barrier
{
protected:
	Texture texture;
	Sprite sprite;
	float x;
	float y;
	float h;
	float w;
	bool use = false;

public:
	void SetX(float X) { x = X; }
	void SetY(float Y) { y = Y; }
	void SetUse(bool Use) { use = Use; }
	float GetX() { return x; }
	float GetY() { return y; }
	bool GetUse() { return use; }
	float GetH() { return h; }
	float GetW() { return w; }

	void SetTexture(string path)
	{
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}

	virtual void Null() = 0;
	virtual void Draw(RenderWindow&) = 0;
	virtual void Move(float temp) = 0;
};