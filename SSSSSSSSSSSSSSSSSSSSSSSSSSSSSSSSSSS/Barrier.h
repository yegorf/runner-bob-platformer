#pragma once
#include <SFML\Graphics.hpp>
#include "Screen.h"
#include "Cell.h"
using namespace sf;
int Scale = 35;

class Barrier
{
protected:
	float x;
	float y;
	bool use = false;

public:
	void SetX(float X) { x = X; }
	void SetY(float Y) { y = Y; }
	void SetUse(bool Use) { use = Use; }
	float GetX() { return x; }
	float GetY() { return y; }
	bool GetUse() { return use; }

	virtual void Null() = 0;
	virtual void Draw(Sprite, RenderWindow&) = 0;
	virtual void Move(float temp) = 0;

};